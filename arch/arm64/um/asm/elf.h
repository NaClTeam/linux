/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (C) 2012 ARM Ltd.
 */
#ifndef __UM_ELF_AARCH64_H
#define __UM_ELF_AARCH64_H

#include <asm/hwcap.h>

#include <asm/user.h>
#include <uapi/asm/ptrace.h>
#include <skas.h>

/*
 * This is used to ensure we don't load something for the wrong architecture.
 */
#define elf_check_arch(x) \
	((x)->e_machine == EM_AARCH64)

#define ELF_CLASS	ELFCLASS64
#define ELF_DATA        ELFDATA2LSB
#define ELF_ARCH        EM_AARCH64

/*
 * When the program starts, a1 contains a pointer to a function to be
 * registered with atexit, as per the SVR4 ABI.  A value of 0 means we have no
 * such handler.
 */
#define ELF_PLAT_INIT(regs, load_addr)    do { \
	PT_REGS_AX(regs) = 0; \
} while (0)

#define ELF_CORE_COPY_REGS(pr_reg, _regs)		\
	(pr_reg) = (_regs)->regs.gp;

#define ELF_PLATFORM "aarch64"

typedef unsigned long elf_greg_t;

#define ELF_NGREG (sizeof(struct user_pt_regs) / sizeof(elf_greg_t))
typedef elf_greg_t elf_gregset_t[ELF_NGREG];

typedef struct user_fpsimd_state elf_fpregset_t;

struct task_struct;

#define ELF_EXEC_PAGESIZE 4096

#define ELF_ET_DYN_BASE (TASK_SIZE / 3 * 2)

#define SET_PERSONALITY(ex) do {} while(0)

#endif
