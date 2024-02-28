/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __SYSDEP_AARCH64_PTRACE_H
#define __SYSDEP_AARCH64_PTRACE_H

#include <generated/user_constants.h>

#define MAX_REG_OFFSET (UM_FRAME_SIZE)
#define MAX_REG_NR ((MAX_REG_OFFSET) / sizeof(unsigned long))

#define REGS_IP(r) ((r)[HOST_IP])
#define REGS_SP(r) ((r)[HOST_SP])
#define REGS_AX(r) ((r)[HOST_AX])
#define REGS_BP(r) ((r)[HOST_BP])

#define UPT_IP(r) REGS_IP((r)->gp)
#define UPT_SP(r) REGS_SP((r)->gp)
#define UPT_AX(r) REGS_AX((r)->gp)
#define UPT_BP(r) REGS_BP((r)->gp)

#define MAX_FP_NR HOST_FP_SIZE

#define REGS_X1(r) ((r)[HOST_X1])
#define REGS_X2(r) ((r)[HOST_X2])
#define REGS_X3(r) ((r)[HOST_X3])
#define REGS_X4(r) ((r)[HOST_X4])
#define REGS_X5(r) ((r)[HOST_X5])
#define REGS_X8(r) ((r)[HOST_X8])

#define UPT_X1(r) REGS_X8((r)->gp)
#define UPT_X2(r) REGS_X8((r)->gp)
#define UPT_X3(r) REGS_X8((r)->gp)
#define UPT_X4(r) REGS_X8((r)->gp)
#define UPT_X5(r) REGS_X8((r)->gp)
#define UPT_X8(r) REGS_X8((r)->gp)

#define UPT_SYSCALL_ARG1(r) UPT_AX(r)
#define UPT_SYSCALL_ARG2(r) UPT_X1(r)
#define UPT_SYSCALL_ARG3(r) UPT_X2(r)
#define UPT_SYSCALL_ARG4(r) UPT_X3(r)
#define UPT_SYSCALL_ARG5(r) UPT_X4(r)
#define UPT_SYSCALL_ARG6(r) UPT_X5(r)

extern void arch_init_registers(int pid);

struct syscall_args {
	unsigned long args[6];
};

#define SYSCALL_ARGS(r) ((struct syscall_args) \
			 { .args = { UPT_SYSCALL_ARG1(r),	 \
				     UPT_SYSCALL_ARG2(r),	 \
				     UPT_SYSCALL_ARG3(r),	 \
				     UPT_SYSCALL_ARG4(r),	 \
				     UPT_SYSCALL_ARG5(r),	 \
				     UPT_SYSCALL_ARG6(r) } } )

struct uml_pt_regs {
	unsigned long gp[MAX_REG_NR];
	unsigned long fp[MAX_FP_NR];
	long syscall;
	int is_user;
};

#define EMPTY_UML_PT_REGS { }

#define UPT_SYSCALL_NR(r) ((r)->syscall)
#define UPT_IS_USER(r) ((r)->is_user)

extern int user_context(unsigned long sp);

#endif /* __SYSDEP_AARCH64_PTRACE_H */
