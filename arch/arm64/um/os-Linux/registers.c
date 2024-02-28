// SPDX-License-Identifier: GPL-2.0

#include <errno.h>
#include <stdlib.h>
#include <sys/ptrace.h>
#include <longjmp.h>
#include <sysdep/ptrace_user.h>
#include <sys/uio.h>
#include <asm/sigcontext.h>
#include <linux/elf.h>
#include <registers.h>

int have_fpsimd_support;

int save_i387_registers(int pid, unsigned long *fp_regs)
{
	struct iovec iov;

	if (!have_fpsimd_support)
		return 0;

	iov.iov_base = fp_regs;
	iov.iov_len = HOST_FP_SIZE;
	if (ptrace(PTRACE_GETREGSET, pid, NT_PRFPREG, &iov) < 0)
		return -errno;
	return 0;
}

int save_fp_registers(int pid, unsigned long *fp_regs)
{
	return save_i387_registers(pid, fp_regs);
}

int restore_i387_registers(int pid, unsigned long *fp_regs)
{
	struct iovec iov;

	if (!have_fpsimd_support)
		return 0;

	iov.iov_base = fp_regs;
	iov.iov_len = HOST_FP_SIZE;
	if (ptrace(PTRACE_SETREGSET, pid, NT_PRFPREG, &iov) < 0)
		return -errno;
	return 0;
}

int restore_fp_registers(int pid, unsigned long *fp_regs)
{
	return restore_i387_registers(pid, fp_regs);
}

int get_fp_registers(int pid, unsigned long *regs)
{
	return save_fp_registers(pid, regs);
}

int put_fp_registers(int pid, unsigned long *regs)
{
	return restore_fp_registers(pid, regs);
}

void arch_init_registers(int pid)
{
	void * fp_regs;
	struct iovec iov;

	fp_regs = malloc(FP_SIZE * sizeof(unsigned long));
	if(fp_regs == NULL)
		return;

	iov.iov_base = fp_regs;
	iov.iov_len = FP_SIZE * sizeof(unsigned long);
	if (ptrace(PTRACE_GETREGSET, pid, NT_PRFPREG, &iov) == 0)
		have_fpsimd_support = 1;

	free(fp_regs);
}

unsigned long get_thread_reg(int reg, jmp_buf *buf)
{
	switch (reg) {
	case HOST_BP:
		return buf[0]->__x29;
	case HOST_LR:
		return buf[0]->__x30;
	case HOST_SP:
		return buf[0]->__sp;
	default:
		printk(UM_KERN_ERR "get_thread_regs - unknown register %d\n",
		       reg);
		return 0;
	}
}

int get_syscall_nr(int pid, unsigned long *syscallno)
{
	struct iovec iov;

	iov.iov_base = syscallno;
	iov.iov_len = sizeof(unsigned long);
	if (ptrace(PTRACE_GETREGSET, NT_ARM_SYSTEM_CALL, &iov) < 0)
		return -errno;
	return 0;
}

int put_syscall_nr(int pid, unsigned long syscallno)
{
	struct iovec iov;

	iov.iov_base = &syscallno;
	iov.iov_len = sizeof(unsigned long);
	if (ptrace(PTRACE_SETREGSET, NT_ARM_SYSTEM_CALL, &iov) < 0)
		return -errno;
	return 0;
}
