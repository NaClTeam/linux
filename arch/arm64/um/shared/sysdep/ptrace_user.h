/* SPDX-License-Identifier: GPL-2.0 */
#include <generated/user_constants.h>

#define PT_OFFSET(r) ((r) * sizeof(long))

#define PT_SYSCALL_RET_OFFSET PT_OFFSET(HOST_AX)

#define REGS_IP_INDEX HOST_IP
#define REGS_SP_INDEX HOST_SP

#define FP_SIZE HOST_FP_SIZE

