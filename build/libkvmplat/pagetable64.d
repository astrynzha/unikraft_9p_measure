cmd_/home/strynzha/unikraft_9p_measure/build/libkvmplat/pagetable64.o := ""gcc  -nostdlib -U __linux__ -U __FreeBSD__ -U __sun__ -fno-stack-protector -Wall -Wextra -D __Unikraft__ -DUK_CODENAME="Phoebe" -DUK_VERSION=0.10 -DUK_FULLVERSION=0.10.0~43e675b  -fno-tree-sra -fno-split-stack -nostdinc -O2 -fno-omit-frame-pointer -fno-PIC    -I/home/strynzha/unikraft_9p_measure/build/include -I/home/strynzha/.unikraft/unikraft/arch/x86/x86_64/include -I/home/strynzha/.unikraft/unikraft/include  -I/home/strynzha/.unikraft/unikraft/lib/uklibparam/include  -I/home/strynzha/.unikraft/unikraft/plat/kvm/include -I/home/strynzha/.unikraft/unikraft/plat/common/include    -D__X86_64__ -m64 -mno-red-zone -fno-asynchronous-unwind-tables  -fno-reorder-blocks -mtune=generic  -DCC_VERSION=9.3 -D__ASSEMBLY__   -DKVMPLAT      -g3 -D__LIBNAME__=libkvmplat -D__BASENAME__=pagetable64.S -c /home/strynzha/.unikraft/unikraft/plat/kvm/x86/pagetable64.S -o /home/strynzha/unikraft_9p_measure/build/libkvmplat/pagetable64.o -Wp,-MD,/home/strynzha/unikraft_9p_measure/build/libkvmplat/.pagetable64.o.d

source_/home/strynzha/unikraft_9p_measure/build/libkvmplat/pagetable64.o := /home/strynzha/.unikraft/unikraft/plat/kvm/x86/pagetable64.S

deps_/home/strynzha/unikraft_9p_measure/build/libkvmplat/pagetable64.o := \
    $(wildcard include/config/paging.h) \
  /home/strynzha/.unikraft/unikraft/include/uk/config.h \
  /home/strynzha/.unikraft/unikraft/include/uk/arch/paging.h \
  /home/strynzha/.unikraft/unikraft/include/uk/arch/types.h \
  /home/strynzha/.unikraft/unikraft/arch/x86/x86_64/include/uk/asm/intsizes.h \
  /home/strynzha/.unikraft/unikraft/arch/x86/x86_64/include/uk/asm/types.h \
  /home/strynzha/.unikraft/unikraft/arch/x86/x86_64/include/uk/asm/paging.h \
    $(wildcard include/config/libukdebug.h) \
    $(wildcard include/config/paging/5level.h) \
    $(wildcard include/config/paravirt.h) \

/home/strynzha/unikraft_9p_measure/build/libkvmplat/pagetable64.o: $(deps_/home/strynzha/unikraft_9p_measure/build/libkvmplat/pagetable64.o)

$(deps_/home/strynzha/unikraft_9p_measure/build/libkvmplat/pagetable64.o):
