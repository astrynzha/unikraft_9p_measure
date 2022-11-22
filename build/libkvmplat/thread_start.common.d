cmd_/home/strynzha/unikraft_9p_measure/build/libkvmplat/thread_start.common.o := ""gcc  -nostdlib -U __linux__ -U __FreeBSD__ -U __sun__ -fno-stack-protector -Wall -Wextra -D __Unikraft__ -DUK_CODENAME="Phoebe" -DUK_VERSION=0.10 -DUK_FULLVERSION=0.10.0~43e675b  -fno-tree-sra -fno-split-stack -nostdinc -O2 -fno-omit-frame-pointer -fno-PIC    -I/home/strynzha/unikraft_9p_measure/build/include -I/home/strynzha/.unikraft/unikraft/arch/x86/x86_64/include -I/home/strynzha/.unikraft/unikraft/include  -I/home/strynzha/.unikraft/unikraft/lib/uklibparam/include  -I/home/strynzha/.unikraft/unikraft/plat/kvm/include -I/home/strynzha/.unikraft/unikraft/plat/common/include    -D__X86_64__ -m64 -mno-red-zone -fno-asynchronous-unwind-tables  -fno-reorder-blocks -mtune=generic  -DCC_VERSION=9.3 -D__ASSEMBLY__   -DKVMPLAT      -g3 -D__LIBNAME__=libkvmplat -D__BASENAME__=thread_start.S -D__VARIANT__=common -c /home/strynzha/.unikraft/unikraft/plat/common/x86/thread_start.S -o /home/strynzha/unikraft_9p_measure/build/libkvmplat/thread_start.common.o -Wp,-MD,/home/strynzha/unikraft_9p_measure/build/libkvmplat/.thread_start.common.o.d

source_/home/strynzha/unikraft_9p_measure/build/libkvmplat/thread_start.common.o := /home/strynzha/.unikraft/unikraft/plat/common/x86/thread_start.S

deps_/home/strynzha/unikraft_9p_measure/build/libkvmplat/thread_start.common.o := \
    $(wildcard include/config/libuksignal.h) \
  /home/strynzha/.unikraft/unikraft/include/uk/config.h \
  /home/strynzha/.unikraft/unikraft/plat/common/include/uk/plat/common/sw_ctx.h \

/home/strynzha/unikraft_9p_measure/build/libkvmplat/thread_start.common.o: $(deps_/home/strynzha/unikraft_9p_measure/build/libkvmplat/thread_start.common.o)

$(deps_/home/strynzha/unikraft_9p_measure/build/libkvmplat/thread_start.common.o):
