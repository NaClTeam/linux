/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __ASM_HWCAP_H
#define __ASM_HWCAP_H

extern long elf_aux_hwcap;
#define ELF_HWCAP (elf_aux_hwcap)

#endif
