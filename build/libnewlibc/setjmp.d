cmd_/home/strynzha/unikraft_9p_measure/build/libnewlibc/setjmp.o := ""gcc  -nostdlib -U __linux__ -U __FreeBSD__ -U __sun__ -fno-stack-protector -Wall -Wextra -D __Unikraft__ -DUK_CODENAME="Phoebe" -DUK_VERSION=0.10 -DUK_FULLVERSION=0.10.0~43e675b  -fno-tree-sra -fno-split-stack -nostdinc -O2 -fno-omit-frame-pointer -fno-PIC    -I/home/strynzha/unikraft_9p_measure/build/include -I/home/strynzha/.unikraft/unikraft/arch/x86/x86_64/include -I/home/strynzha/.unikraft/unikraft/include  -I/home/strynzha/.unikraft/unikraft/lib/uklibparam/include      -D__X86_64__ -m64 -mno-red-zone -fno-asynchronous-unwind-tables  -fno-reorder-blocks -mtune=generic  -DCC_VERSION=9.3 -D__ASSEMBLY__         -g3 -D__LIBNAME__=libnewlibc -D__BASENAME__=setjmp.S -c /home/strynzha/unikraft_9p_measure/build/libnewlibc/origin/newlib-2.5.0.20170922/newlib/libc/machine/x86_64/setjmp.S -o /home/strynzha/unikraft_9p_measure/build/libnewlibc/setjmp.o -Wp,-MD,/home/strynzha/unikraft_9p_measure/build/libnewlibc/.setjmp.o.d

source_/home/strynzha/unikraft_9p_measure/build/libnewlibc/setjmp.o := /home/strynzha/unikraft_9p_measure/build/libnewlibc/origin/newlib-2.5.0.20170922/newlib/libc/machine/x86_64/setjmp.S

deps_/home/strynzha/unikraft_9p_measure/build/libnewlibc/setjmp.o := \
  /home/strynzha/unikraft_9p_measure/build/libnewlibc/origin/newlib-2.5.0.20170922/newlib/libc/machine/x86_64/x86_64mach.h \

/home/strynzha/unikraft_9p_measure/build/libnewlibc/setjmp.o: $(deps_/home/strynzha/unikraft_9p_measure/build/libnewlibc/setjmp.o)

$(deps_/home/strynzha/unikraft_9p_measure/build/libnewlibc/setjmp.o):
