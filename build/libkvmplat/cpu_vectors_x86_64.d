cmd_/home/strynzha/unikraft_9p_measure/build/libkvmplat/cpu_vectors_x86_64.o := ""gcc  -nostdlib -U __linux__ -U __FreeBSD__ -U __sun__ -fno-stack-protector -Wall -Wextra -D __Unikraft__ -DUK_CODENAME="Phoebe" -DUK_VERSION=0.10 -DUK_FULLVERSION=0.10.0~43e675b  -fno-tree-sra -fno-split-stack -nostdinc -O2 -fno-omit-frame-pointer -fno-PIC    -I/home/strynzha/unikraft_9p_measure/build/include -I/home/strynzha/.unikraft/unikraft/arch/x86/x86_64/include -I/home/strynzha/.unikraft/unikraft/include  -I/home/strynzha/.unikraft/unikraft/lib/uklibparam/include  -I/home/strynzha/.unikraft/unikraft/plat/kvm/include -I/home/strynzha/.unikraft/unikraft/plat/common/include    -D__X86_64__ -m64 -mno-red-zone -fno-asynchronous-unwind-tables  -fno-reorder-blocks -mtune=generic  -DCC_VERSION=9.3 -D__ASSEMBLY__   -DKVMPLAT      -g3 -D__LIBNAME__=libkvmplat -D__BASENAME__=cpu_vectors_x86_64.S -c /home/strynzha/.unikraft/unikraft/plat/kvm/x86/cpu_vectors_x86_64.S -o /home/strynzha/unikraft_9p_measure/build/libkvmplat/cpu_vectors_x86_64.o -Wp,-MD,/home/strynzha/unikraft_9p_measure/build/libkvmplat/.cpu_vectors_x86_64.o.d

source_/home/strynzha/unikraft_9p_measure/build/libkvmplat/cpu_vectors_x86_64.o := /home/strynzha/.unikraft/unikraft/plat/kvm/x86/cpu_vectors_x86_64.S

deps_/home/strynzha/unikraft_9p_measure/build/libkvmplat/cpu_vectors_x86_64.o := \
  /home/strynzha/.unikraft/unikraft/plat/common/include/x86/traps.h \
  /home/strynzha/.unikraft/unikraft/include/uk/arch/lcpu.h \
  /home/strynzha/.unikraft/unikraft/arch/x86/x86_64/include/uk/asm/lcpu.h \
  /home/strynzha/.unikraft/unikraft/include/uk/arch/traps.h \
  /home/strynzha/.unikraft/unikraft/arch/x86/x86_64/include/uk/asm/traps.h \
  /home/strynzha/.unikraft/unikraft/plat/common/include/uk/plat/common/lcpu.h \
    $(wildcard include/config/have/smp.h) \
  /home/strynzha/.unikraft/unikraft/include/uk/config.h \
  /home/strynzha/.unikraft/unikraft/plat/common/include/x86/lcpu_defs.h \

/home/strynzha/unikraft_9p_measure/build/libkvmplat/cpu_vectors_x86_64.o: $(deps_/home/strynzha/unikraft_9p_measure/build/libkvmplat/cpu_vectors_x86_64.o)

$(deps_/home/strynzha/unikraft_9p_measure/build/libkvmplat/cpu_vectors_x86_64.o):
