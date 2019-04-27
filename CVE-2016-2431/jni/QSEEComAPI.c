#include "QSEEComAPI.h"
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
	
struct qcom_wv_handle* initialize_wv_handle() {

	//Initializing the handle
    struct qcom_wv_handle* handle = malloc(sizeof(struct qcom_wv_handle));
    memset(handle, 0, sizeof(struct qcom_wv_handle));

	//Getting the QSEECom library
    handle->libhandle = dlopen("libQSEEComAPI.so", RTLD_NOW);
    if (!handle->libhandle) {
        perror("[-] Failed to load QSEEComAPI");
        return NULL;
    }

	//Loading the symbols from QSEEComAPI
    *(void **)(&handle->QSEECom_start_app) = dlsym(handle->libhandle,"QSEECom_start_app");
    if (handle->QSEECom_start_app == NULL) {
        perror("[-] dlsym: Error Loading QSEECom_start_app");
        dlclose(handle->libhandle);
        handle->libhandle = NULL;
        return NULL;
    }
    *(void **)(&handle->QSEECom_shutdown_app) = dlsym(handle->libhandle,"QSEECom_shutdown_app");
    if (handle->QSEECom_shutdown_app == NULL) {
        perror("[-] dlsym: Error Loading QSEECom_shutdown_app");
        dlclose(handle->libhandle);
        handle->libhandle = NULL;
        return NULL;
    }
    *(void **)(&handle->QSEECom_send_cmd) = dlsym(handle->libhandle,"QSEECom_send_cmd");
    if (handle->QSEECom_send_cmd == NULL) {
        perror("[-] dlsym: Error Loading QSEECom_send_cmd");
        dlclose(handle->libhandle);
        handle->libhandle = NULL;
        return NULL;
    }
    *(void **)(&handle->QSEECom_send_modified_cmd) = dlsym(handle->libhandle,"QSEECom_send_modified_cmd");
    if (handle->QSEECom_send_modified_cmd == NULL) {
        perror("[-] dlsym: Error Loading QSEECom_send_modified_cmd");
        dlclose(handle->libhandle);
        handle->libhandle = NULL;
        return NULL;
    }
    *(void **)(&handle->QSEECom_set_bandwidth) = dlsym(handle->libhandle,"QSEECom_set_bandwidth");
    if (handle->QSEECom_set_bandwidth == NULL) {
        perror("[-] dlsym: Error Loading QSEECom_set_bandwidth");
        dlclose(handle->libhandle);
        handle->libhandle = NULL;
        return NULL;
    }

	return handle;
}
