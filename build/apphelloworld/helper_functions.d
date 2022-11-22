cmd_/home/strynzha/unikraft_9p_measure/build/apphelloworld/helper_functions.o := ""gcc  -nostdlib -U __linux__ -U __FreeBSD__ -U __sun__ -fno-stack-protector -Wall -Wextra -D __Unikraft__ -DUK_CODENAME="Phoebe" -DUK_VERSION=0.10 -DUK_FULLVERSION=0.10.0~43e675b  -fno-tree-sra -fno-split-stack -nostdinc -O2 -fno-omit-frame-pointer -fno-PIC    -I/home/strynzha/unikraft_9p_measure/build/include -I/home/strynzha/.unikraft/unikraft/arch/x86/x86_64/include -I/home/strynzha/.unikraft/unikraft/include  -I/home/strynzha/.unikraft/unikraft/lib/devfs/include -I/home/strynzha/.unikraft/unikraft/lib/posix-process/include -I/home/strynzha/.unikraft/unikraft/lib/posix-process/musl-imported/include -I/home/strynzha/.unikraft/unikraft/lib/posix-process/musl-imported/arch/generic -I/home/strynzha/.unikraft/unikraft/lib/posix-user/musl-imported/include -I/home/strynzha/.unikraft/unikraft/lib/syscall_shim/include -I/home/strynzha/.unikraft/unikraft/lib/ukalloc/include -I/home/strynzha/.unikraft/unikraft/lib/ukallocbbuddy/include -I/home/strynzha/.unikraft/unikraft/lib/ukargparse/include -I/home/strynzha/.unikraft/unikraft/lib/ukboot/include -I/home/strynzha/.unikraft/unikraft/lib/ukbus/include -I/home/strynzha/.unikraft/unikraft/lib/ukdebug/include -I/home/strynzha/.unikraft/unikraft/lib/uklibparam/include -I/home/strynzha/.unikraft/unikraft/lib/uklock/include -I/home/strynzha/.unikraft/unikraft/lib/uksched/include -I/home/strynzha/.unikraft/unikraft/lib/ukschedcoop/include -I/home/strynzha/.unikraft/unikraft/lib/uksglist/include -I/home/strynzha/.unikraft/unikraft/lib/uksignal/include -I/home/strynzha/.unikraft/unikraft/lib/uksp/include -I/home/strynzha/.unikraft/unikraft/lib/ukstore/include -I/home/strynzha/.unikraft/unikraft/lib/ukswrand/include -I/home/strynzha/.unikraft/unikraft/lib/uktime/include -I/home/strynzha/.unikraft/unikraft/lib/uktime/musl-imported/include -I/home/strynzha/.unikraft/unikraft/lib/uktimeconv/include -I/home/strynzha/.unikraft/unikraft/lib/vfscore/include -I/home/strynzha/.unikraft/libs/libnewlib/include -I/home/strynzha/.unikraft/libs/libnewlib/musl-imported/include -I/home/strynzha/.unikraft/libs/libnewlib/musl-imported/arch/generic -I/home/strynzha/.unikraft/libs/libnewlib/musl-imported/arch/x86_64 -I/home/strynzha/unikraft_9p_measure/build/libnewlibc/origin/newlib-2.5.0.20170922/newlib/libc/include      -D__X86_64__ -m64 -mno-red-zone -fno-asynchronous-unwind-tables  -fno-reorder-blocks -mtune=generic  -DCC_VERSION=9.3  -DMISSING_SYSCALL_NAMES -DMALLOC_PROVIDED -D_POSIX_REALTIME_SIGNALS -D_LDBL_EQ_DBL -D_HAVE_LONG_DOUBLE -Wno-char-subscripts -D__DYNAMIC_REENT__ -DCONFIG_UK_NETDEV_SCRATCH_SIZE=0        -g3 -D__LIBNAME__=apphelloworld -D__BASENAME__=helper_functions.c -c /home/strynzha/unikraft_9p_measure/src/helper_functions.c -o /home/strynzha/unikraft_9p_measure/build/apphelloworld/helper_functions.o -Wp,-MD,/home/strynzha/unikraft_9p_measure/build/apphelloworld/.helper_functions.o.d

source_/home/strynzha/unikraft_9p_measure/build/apphelloworld/helper_functions.o := /home/strynzha/unikraft_9p_measure/src/helper_functions.c

deps_/home/strynzha/unikraft_9p_measure/build/apphelloworld/helper_functions.o := \
  /home/strynzha/unikraft_9p_measure/src/helper_functions.h \
  /home/strynzha/.unikraft/libs/libnewlib/include/stdio.h \
  /home/strynzha/unikraft_9p_measure/build/libnewlibc/origin/newlib-2.5.0.20170922/newlib/libc/include/stdio.h \
  /home/strynzha/unikraft_9p_measure/build/libnewlibc/origin/newlib-2.5.0.20170922/newlib/libc/include/_ansi.h \
  /home/strynzha/unikraft_9p_measure/build/libnewlibc/origin/newlib-2.5.0.20170922/newlib/libc/include/newlib.h \
  /home/strynzha/unikraft_9p_measure/build/libnewlibc/origin/newlib-2.5.0.20170922/newlib/libc/include/sys/config.h \
  /home/strynzha/unikraft_9p_measure/build/libnewlibc/origin/newlib-2.5.0.20170922/newlib/libc/include/machine/ieeefp.h \
  /home/strynzha/unikraft_9p_measure/build/libnewlibc/origin/newlib-2.5.0.20170922/newlib/libc/include/sys/features.h \
  /home/strynzha/unikraft_9p_measure/build/libnewlibc/origin/newlib-2.5.0.20170922/newlib/libc/include/_newlib_version.h \
  /home/strynzha/unikraft_9p_measure/build/libnewlibc/origin/newlib-2.5.0.20170922/newlib/libc/include/sys/cdefs.h \
  /home/strynzha/unikraft_9p_measure/build/libnewlibc/origin/newlib-2.5.0.20170922/newlib/libc/include/machine/_default_types.h \
  /home/strynzha/.unikraft/libs/libnewlib/include/stddef.h \
  /home/strynzha/.unikraft/libs/libnewlib/include/__stddef_max_align_t.h \
  /home/strynzha/.unikraft/libs/libnewlib/include/stdarg.h \
  /home/strynzha/unikraft_9p_measure/build/libnewlibc/origin/newlib-2.5.0.20170922/newlib/libc/include/sys/reent.h \
  /home/strynzha/unikraft_9p_measure/build/libnewlibc/origin/newlib-2.5.0.20170922/newlib/libc/include/_ansi.h \
  /home/strynzha/.unikraft/libs/libnewlib/include/sys/_types.h \
  /home/strynzha/.unikraft/libs/libnewlib/include/uk/_types.h \
  /home/strynzha/.unikraft/unikraft/lib/uktime/include/uk/time_types.h \
  /home/strynzha/unikraft_9p_measure/build/libnewlibc/origin/newlib-2.5.0.20170922/newlib/libc/include/stdint.h \
  /home/strynzha/unikraft_9p_measure/build/libnewlibc/origin/newlib-2.5.0.20170922/newlib/libc/include/sys/_intsup.h \
  /home/strynzha/unikraft_9p_measure/build/libnewlibc/origin/newlib-2.5.0.20170922/newlib/libc/include/sys/_stdint.h \
  /home/strynzha/unikraft_9p_measure/build/libnewlibc/origin/newlib-2.5.0.20170922/newlib/libc/include/sys/_types.h \
  /home/strynzha/unikraft_9p_measure/build/libnewlibc/origin/newlib-2.5.0.20170922/newlib/libc/include/machine/_types.h \
  /home/strynzha/unikraft_9p_measure/build/libnewlibc/origin/newlib-2.5.0.20170922/newlib/libc/include/sys/lock.h \
  /home/strynzha/unikraft_9p_measure/build/libnewlibc/origin/newlib-2.5.0.20170922/newlib/libc/include/sys/types.h \
  /home/strynzha/unikraft_9p_measure/build/libnewlibc/origin/newlib-2.5.0.20170922/newlib/libc/include/machine/endian.h \
  /home/strynzha/unikraft_9p_measure/build/libnewlibc/origin/newlib-2.5.0.20170922/newlib/libc/include/machine/_endian.h \
  /home/strynzha/unikraft_9p_measure/build/libnewlibc/origin/newlib-2.5.0.20170922/newlib/libc/include/sys/select.h \
  /home/strynzha/unikraft_9p_measure/build/libnewlibc/origin/newlib-2.5.0.20170922/newlib/libc/include/sys/_sigset.h \
  /home/strynzha/unikraft_9p_measure/build/libnewlibc/origin/newlib-2.5.0.20170922/newlib/libc/include/sys/_timeval.h \
  /home/strynzha/.unikraft/libs/libnewlib/include/sys/timespec.h \
  /home/strynzha/.unikraft/libs/libnewlib/include/uk/_timespec.h \
  /home/strynzha/unikraft_9p_measure/build/libnewlibc/origin/newlib-2.5.0.20170922/newlib/libc/include/sys/_pthreadtypes.h \
  /home/strynzha/unikraft_9p_measure/build/libnewlibc/origin/newlib-2.5.0.20170922/newlib/libc/include/sys/sched.h \
  /home/strynzha/.unikraft/libs/libnewlib/include/sys/_timespec.h \
  /home/strynzha/unikraft_9p_measure/build/libnewlibc/origin/newlib-2.5.0.20170922/newlib/libc/include/machine/types.h \
  /home/strynzha/unikraft_9p_measure/build/libnewlibc/origin/newlib-2.5.0.20170922/newlib/libc/include/sys/stdio.h \
  /home/strynzha/unikraft_9p_measure/build/libnewlibc/origin/newlib-2.5.0.20170922/newlib/libc/include/math.h \
  /home/strynzha/unikraft_9p_measure/build/libnewlibc/origin/newlib-2.5.0.20170922/newlib/libc/include/assert.h \
  /home/strynzha/.unikraft/unikraft/lib/ukswrand/include/sys/random.h \
  /home/strynzha/.unikraft/libs/libnewlib/include/stdlib.h \
  /home/strynzha/unikraft_9p_measure/build/libnewlibc/origin/newlib-2.5.0.20170922/newlib/libc/include/stdlib.h \
    $(wildcard include/config/libukalloc/ifstats/perlib.h) \
  /home/strynzha/unikraft_9p_measure/build/libnewlibc/origin/newlib-2.5.0.20170922/newlib/libc/include/machine/stdlib.h \
  /home/strynzha/unikraft_9p_measure/build/libnewlibc/origin/newlib-2.5.0.20170922/newlib/libc/include/alloca.h \
  /home/strynzha/.unikraft/unikraft/include/uk/config.h \
  /home/strynzha/unikraft_9p_measure/build/libnewlibc/origin/newlib-2.5.0.20170922/newlib/libc/include/string.h \
  /home/strynzha/unikraft_9p_measure/build/libnewlibc/origin/newlib-2.5.0.20170922/newlib/libc/include/xlocale.h \
  /home/strynzha/unikraft_9p_measure/build/libnewlibc/origin/newlib-2.5.0.20170922/newlib/libc/include/strings.h \
  /home/strynzha/unikraft_9p_measure/build/libnewlibc/origin/newlib-2.5.0.20170922/newlib/libc/include/sys/string.h \
  /home/strynzha/unikraft_9p_measure/build/libnewlibc/origin/newlib-2.5.0.20170922/newlib/libc/include/unistd.h \
  /home/strynzha/.unikraft/libs/libnewlib/include/sys/unistd.h \
  /home/strynzha/unikraft_9p_measure/build/libnewlibc/origin/newlib-2.5.0.20170922/newlib/libc/include/sys/unistd.h \

/home/strynzha/unikraft_9p_measure/build/apphelloworld/helper_functions.o: $(deps_/home/strynzha/unikraft_9p_measure/build/apphelloworld/helper_functions.o)

$(deps_/home/strynzha/unikraft_9p_measure/build/apphelloworld/helper_functions.o):
