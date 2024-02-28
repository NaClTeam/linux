# SPDX-License-Identifier: GPL-2.0

obj-y = ptrace_user.o setjmp.o os-Linux/

USER_OBJS := ptrace_user.o

$(obj)/user-offsets.s: c_flags = -Wp,-MD,$(depfile) $(USER_CFLAGS) \
	-Iarch/arm64/include/generated
targets += user-offsets.s

include/generated/user_constants.h: $(obj)/user-offsets.s FORCE
	$(call filechk,offsets,__USER_CONSTANT_H__)

include $(srctree)/arch/um/scripts/Makefile.rules
