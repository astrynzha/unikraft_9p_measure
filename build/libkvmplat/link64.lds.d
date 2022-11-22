cmd_/home/strynzha/unikraft_9p_measure/build/libkvmplat/link64.lds := ""gcc -E -P -x assembler-with-cpp  -nostdlib -U __linux__ -U __FreeBSD__ -U __sun__ -fno-stack-protector -Wall -Wextra -D __Unikraft__ -DUK_CODENAME="Phoebe" -DUK_VERSION=0.10 -DUK_FULLVERSION=0.10.0~43e675b  -fno-tree-sra -fno-split-stack -nostdinc -O2 -fno-omit-frame-pointer -fno-PIC  -I/home/strynzha/unikraft_9p_measure/build/include -I/home/strynzha/.unikraft/unikraft/arch/x86/x86_64/include -I/home/strynzha/.unikraft/unikraft/include  -I/home/strynzha/.unikraft/unikraft/lib/uklibparam/include  -I/home/strynzha/.unikraft/unikraft/plat/kvm/include -I/home/strynzha/.unikraft/unikraft/plat/common/include    -D__X86_64__ -m64 -mno-red-zone -fno-asynchronous-unwind-tables  -fno-reorder-blocks -mtune=generic  -DCC_VERSION=9.3 -D__ASSEMBLY__   -DKVMPLAT    /home/strynzha/.unikraft/unikraft/plat/kvm/x86/link64.lds.S -o /home/strynzha/unikraft_9p_measure/build/libkvmplat/link64.lds -Wp,-MD,/home/strynzha/unikraft_9p_measure/build/libkvmplat/.link64.lds.d

source_/home/strynzha/unikraft_9p_measure/build/libkvmplat/link64.lds := /home/strynzha/.unikraft/unikraft/plat/kvm/x86/link64.lds.S

deps_/home/strynzha/unikraft_9p_measure/build/libkvmplat/link64.lds := \
  /home/strynzha/.unikraft/unikraft/include/uk/arch/limits.h \
  /home/strynzha/.unikraft/unikraft/include/uk/config.h \
  /home/strynzha/.unikraft/unikraft/arch/x86/x86_64/include/uk/asm/limits.h \
    $(wildcard include/config/stack/size/page/order.h) \
  /home/strynzha/.unikraft/unikraft/plat/common/include/uk/plat/common/common.lds.h \

/home/strynzha/unikraft_9p_measure/build/libkvmplat/link64.lds: $(deps_/home/strynzha/unikraft_9p_measure/build/libkvmplat/link64.lds)

$(deps_/home/strynzha/unikraft_9p_measure/build/libkvmplat/link64.lds):
