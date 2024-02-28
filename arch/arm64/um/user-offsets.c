// SPDX-License-Identifier: GPL-2.0
#include <stdio.h>
#include <stddef.h>
#include <signal.h>
#include <poll.h>
#include <sys/mman.h>
#include <sys/user.h>
#include <linux/ptrace.h>
#include <asm/types.h>
#include <linux/kbuild.h>

#define DEFINE_LONGS(sym, val)	\
	COMMENT(#val " / sizeof(unsigned long)");	\
	DEFINE(sym, val / sizeof(unsigned long))

void foo(void)
{
	DEFINE_LONGS(HOST_FP_SIZE, sizeof(struct user_fpsimd_struct));

	DEFINE_LONGS(HOST_AX, offsetof(struct user_pt_regs, regs[0]));
	DEFINE_LONGS(HOST_X1, offsetof(struct user_pt_regs, regs[1]));
	DEFINE_LONGS(HOST_X2, offsetof(struct user_pt_regs, regs[2]));
	DEFINE_LONGS(HOST_X3, offsetof(struct user_pt_regs, regs[3]));
	DEFINE_LONGS(HOST_X4, offsetof(struct user_pt_regs, regs[4]));
	DEFINE_LONGS(HOST_X5, offsetof(struct user_pt_regs, regs[5]));
	DEFINE_LONGS(HOST_X8, offsetof(struct user_pt_regs, regs[8]));
	DEFINE_LONGS(HOST_BP, offsetof(struct user_pt_regs, regs[29]));
	DEFINE_LONGS(HOST_LR, offsetof(struct user_pt_regs, regs[30]));
	DEFINE_LONGS(HOST_SP, offsetof(struct user_pt_regs, sp));
	DEFINE_LONGS(HOST_IP, offsetof(struct user_pt_regs, pc));

	DEFINE(UM_FRAME_SIZE, sizeof(struct user_regs_struct));

	DEFINE(UM_POLLIN, POLLIN);
	DEFINE(UM_POLLPRI, POLLPRI);
	DEFINE(UM_POLLOUT, POLLOUT);

	DEFINE(UM_PROT_READ, PROT_READ);
	DEFINE(UM_PROT_WRITE, PROT_WRITE);
	DEFINE(UM_PROT_EXEC, PROT_EXEC);
}
