/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __UM_AARCH64_PTRACE_H
#define __UM_AARCH64_PTRACE_H

#include <linux/compiler.h>
#include <asm/ptrace-generic.h>

#define user_mode(r) UPT_IS_USER(&(r)->regs)

#define PT_REGS_AX(r) UPT_AX(&(r)->regs)

#define PT_REGS_BP(r) UPT_BP(&(r)->regs)

#define PT_REGS_ORIG_SYSCALL(r) PT_REGS_X8(r)
#define PT_REGS_SYSCALL_RET(r) PT_REGS_AX(r)

#define PT_FIX_EXEC_STACK(sp) do ; while(0)

#define profile_pc(regs) PT_REGS_IP(regs)

#define UPT_RESTART_SYSCALL(r) (UPT_IP(r) -= 4)
#define PT_REGS_SET_SYSCALL_RETURN(r, res) (PT_REGS_AX(r) = (res))

static inline long regs_return_value(struct pt_regs *regs)
{
	return PT_REGS_AX(regs);
}

#define PT_REGS_X1(r) UPT_X1(&(r)->regs)
#define PT_REGS_X2(r) UPT_X2(&(r)->regs)
#define PT_REGS_X3(r) UPT_X3(&(r)->regs)
#define PT_REGS_X4(r) UPT_X4(&(r)->regs)
#define PT_REGS_X5(r) UPT_X5(&(r)->regs)
#define PT_REGS_X8(r) UPT_X8(&(r)->regs)

extern long arch_prctl(struct task_struct *task, int option,
		       unsigned long __user *addr);

#define user_stack_pointer(regs) PT_REGS_SP(regs)
#endif /* __UM_AARCH64_PTRACE_H */
