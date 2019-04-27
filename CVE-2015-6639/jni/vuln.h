#ifndef __VULN_H__
#define __VULN_H__

/**
 * Overwrites data in the global buffer in the Widevine application using the given data.
 * @param handle The handle used to communicate with QSEECom
 * @param session_id The session ID whose context pointer should be overwritten
 * @param target_ptr The target address written as the context pointer
 * @return 0 if successful, a negative linux error code otherwise. 
 */
int overwrite_session_pointer(struct qcom_wv_handle* handle, uint32_t session_id, uint32_t target_ptr);

#endif
