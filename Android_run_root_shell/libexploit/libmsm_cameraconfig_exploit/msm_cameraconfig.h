#ifndef MSM_CAMERACONFIG_EXPLOIT_H
#define MSM_CAMERACONFIG_EXPLOIT_H

#include <stdbool.h>

void msm_cameraconfig_set_kernel_phys_offset(int offset);
bool msm_cameraconfig_write_value_at_address(unsigned long int address, int value);
bool msm_cameraconfig_run_exploit(bool(*exploit_callback)(void *mmap_base_address,
                            void *user_data), void *user_data);
void *msm_cameraconfig_mmap(int *fd_video, int *fd_config);
int   msm_cameraconfig_munmap(void *address, int fd_video, int fd_config);
void *msm_cameraconfig_convert_to_mmaped_address(void *address, void *mmap_base_address);

#endif /* MSM_CAMERACONFIG_EXPLOIT_H */
/*
vi:ts=2:nowrap:ai:expandtab:sw=2
*/
