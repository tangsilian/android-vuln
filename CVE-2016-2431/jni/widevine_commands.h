#ifndef __WIDEVINE_COMMANDS_H__
#define __WIDEVINE_COMMANDS_H__

#include "QSEEComAPI.h"

/**
 * Command codes for the widevine commands
 */
enum widevine_command_code {

	//2x Commands
	OEMCrypto_EncryptAndStore = 0x20002,
	OEMCrypto_GetKeyboxData,
	OEMCrypto_IdentifyDevice,
	OEMCrypto_GetRandom,
	unused,
	OEMCrypto_InstallKeybox,
	OEMCrypto_IsKeyBoxValid,
	OEMCrypto_Initialize,
	OEMCrypto_Terminate,
	OEMCrypto_GetKeyData,
	OEMCrypto_GetDeviceID,
	OEMCrypto_SetEntitlementKey,
	OEMCrypto_DeriveControlWord,
	OEMCrypto_DecryptVideo,
	OEMCrypto_DecryptAudio,
	unused2,
	QC_OEMCrypto_Delete_Keybox,

	//5x Commands
	drm_save_keys = 0x50001,
	drm_verify_keys,
	PRDiagMaintenanceHandler,
	PRDiagProvisionDataHandler,
	drm_prov_finalize,
	drm_app_save_qsee_ipc_wrapped_keys,
	drm_app_encapsulate_save_keys,
	drm_save_wrapped_keys,

	//6x Commands
	wv_dash_core_initialize = 0x61001,
	OEMCrypto_Dash_Terminate,
  	OEMCrypto_OpenSession,
 	OEMCrypto_CloseSession,
  	OEMCrypto_GenerateDerivedKeys,
  	OEMCrypto_GenerateNonce,
  	OEMCrypto_GenerateSignature,
  	wv_dash_core_load_keys_v8,
  	wv_dash_core_refresh_keys,
  	OEMCrypto_SelectKey,
  	OEMCrypto_DecryptCTR,
  	OEMCrypto_WrapKeybox,
  	OEMCrypto_Dash_InstallKeybox,
  	OEMCrypto_Dash_IsKeyboxValid,
  	OEMCrypto_Dash_GetDeviceID,
  	OEMCrypto_Dash_GetKeyData,
  	OEMCrypto_Dash_GetRandom,
  	wrapper_wv_dash_core_rewrap_device_rsakey,
  	OEMCrypto_LoadDeviceRSAKey,
  	OEMCrypto_GenerateRSASignature_V8,
  	OEMCrypto_DeriveKeysFromSessionKey,
  	OEMCrypto_ApiVersion,
  	OEMCrypto_Generic_Encrypt,
  	OEMCrypto_Generic_Decrypt,
  	OEMCrypto_Generic_Sign,
  	OEMCrypto_Generic_Verify,
  	OEMCrypto_Dash_InstallEncapKeybox,
  	OEMCrypto_Dash_InstallOEMWrappedKeybox,
  	QC_OEMCrypto_Dash_Delete_Keybox,
  	wrapper_get_hdcp_capability,
  	unknown,
  	OEMCrypto_UpdateUsageTable,
  	OEMCrypto_DeactivateUsageEntry,
  	OEMCrypto_ReportUsage,
  	OEMCrypto_DeleteUsageEntry,
  	OEMCrypto_DeleteUsageTable,
  	wv_dash_core_load_keys,
  	OEMCrypto_GenerateRSASignature,

};

int close_session(struct qcom_wv_handle* handle, int ctx_id);

int derive_keys_from_session_key(struct qcom_wv_handle* handle,
								 int ctx_id,
								 uint32_t enc_session_key_length,
								 uint32_t mac_key_context_length,
								 uint32_t enc_key_context_length);

int send_cmd_1026(struct qcom_wv_handle* handle);

int generate_nonce(struct qcom_wv_handle* handle, int ctx_id, uint32_t* nonce);

int exec_func(struct qcom_wv_handle* handle, void* app, uint32_t function_address, uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4);

#endif
