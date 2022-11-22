cmd_/home/strynzha/unikraft_9p_measure/build/libukdebug/print.o := ""gcc  -nostdlib -U __linux__ -U __FreeBSD__ -U __sun__ -fno-stack-protector -Wall -Wextra -D __Unikraft__ -DUK_CODENAME="Phoebe" -DUK_VERSION=0.10 -DUK_FULLVERSION=0.10.0~43e675b  -fno-tree-sra -fno-split-stack -nostdinc -O2 -fno-omit-frame-pointer -fno-PIC    -I/home/strynzha/unikraft_9p_measure/build/include -I/home/strynzha/.unikraft/unikraft/arch/x86/x86_64/include -I/home/strynzha/.unikraft/unikraft/include  -I/home/strynzha/.unikraft/unikraft/lib/devfs/include -I/home/strynzha/.unikraft/unikraft/lib/posix-process/include -I/home/strynzha/.unikraft/unikraft/lib/posix-process/musl-imported/include -I/home/strynzha/.unikraft/unikraft/lib/posix-process/musl-imported/arch/generic -I/home/strynzha/.unikraft/unikraft/lib/posix-user/musl-imported/include -I/home/strynzha/.unikraft/unikraft/lib/syscall_shim/include -I/home/strynzha/.unikraft/unikraft/lib/ukalloc/include -I/home/strynzha/.unikraft/unikraft/lib/ukallocbbuddy/include -I/home/strynzha/.unikraft/unikraft/lib/ukargparse/include -I/home/strynzha/.unikraft/unikraft/lib/ukboot/include -I/home/strynzha/.unikraft/unikraft/lib/ukbus/include -I/home/strynzha/.unikraft/unikraft/lib/ukdebug/include -I/home/strynzha/.unikraft/unikraft/lib/uklibparam/include -I/home/strynzha/.unikraft/unikraft/lib/uklock/include -I/home/strynzha/.unikraft/unikraft/lib/uksched/include -I/home/strynzha/.unikraft/unikraft/lib/ukschedcoop/include -I/home/strynzha/.unikraft/unikraft/lib/uksglist/include -I/home/strynzha/.unikraft/unikraft/lib/uksignal/include -I/home/strynzha/.unikraft/unikraft/lib/uksp/include -I/home/strynzha/.unikraft/unikraft/lib/ukstore/include -I/home/strynzha/.unikraft/unikraft/lib/ukswrand/include -I/home/strynzha/.unikraft/unikraft/lib/uktime/include -I/home/strynzha/.unikraft/unikraft/lib/uktime/musl-imported/include -I/home/strynzha/.unikraft/unikraft/lib/uktimeconv/include -I/home/strynzha/.unikraft/unikraft/lib/vfscore/include -I/home/strynzha/.unikraft/libs/libnewlib/include -I/home/strynzha/.unikraft/libs/libnewlib/musl-imported/include -I/home/strynzha/.unikraft/libs/libnewlib/musl-imported/arch/generic -I/home/strynzha/.unikraft/libs/libnewlib/musl-imported/arch/x86_64 -I/home/strynzha/unikraft_9p_measure/build/libnewlibc/origin/newlib-2.5.0.20170922/newlib/libc/include      -D__X86_64__ -m64 -mno-red-zone -fno-asynchronous-unwind-tables  -fno-reorder-blocks -mtune=generic  -DCC_VERSION=9.3  -DMISSING_SYSCALL_NAMES -DMALLOC_PROVIDED -D_POSIX_REALTIME_SIGNALS -D_LDBL_EQ_DBL -D_HAVE_LONG_DOUBLE -Wno-char-subscripts -D__DYNAMIC_REENT__ -DCONFIG_UK_NETDEV_SCRATCH_SIZE=0   -D__IN_LIBUKDEBUG__     -g3 -D__LIBNAME__=libukdebug -D__BASENAME__=print.c -c /home/strynzha/.unikraft/unikraft/lib/ukdebug/print.c -o /home/strynzha/unikraft_9p_measure/build/libukdebug/print.o -Wp,-MD,/home/strynzha/unikraft_9p_measure/build/libukdebug/.print.o.d

source_/home/strynzha/unikraft_9p_measure/build/libukdebug/print.o := /home/strynzha/.unikraft/unikraft/lib/ukdebug/print.c

deps_/home/strynzha/unikraft_9p_measure/build/libukdebug/print.o := \
    $(wildcard include/config/libukdebug/ansi/color.h) \
    $(wildcard include/config/libukdebug/redir/printd.h) \
    $(wildcard include/config/libukdebug/printk.h) \
    $(wildcard include/config/libukdebug/print/time.h) \
    $(wildcard include/config/libukdebug/print/caller.h) \
    $(wildcard include/config/libukdebug/print/srcname.h) \
    $(wildcard include/config/libukdebug/redir/printk.h) \
    $(wildcard include/config/libukdebug/printd.h) \
  /home/strynzha/.unikraft/unikraft/lib/ukdebug/snprintf.h \
    $(wildcard include/config/libnolibc.h) \
  /home/strynzha/.unikraft/unikraft/include/uk/config.h \
  /home/strynzha/.unikraft/libs/libnewlib/include/stddef.h \
  /home/strynzha/.unikraft/libs/libnewlib/include/__stddef_max_align_t.h \
  /home/strynzha/.unikraft/libs/libnewlib/include/stdarg.h \
  /home/strynzha/.unikraft/unikraft/include/uk/essentials.h \
    $(wildcard include/config/libnewlibc.h) \
    $(wildcard include/config/have/sched.h) \
  /home/strynzha/unikraft_9p_measure/build/libnewlibc/origin/newlib-2.5.0.20170922/newlib/libc/include/sys/cdefs.h \
  /home/strynzha/unikraft_9p_measure/build/libnewlibc/origin/newlib-2.5.0.20170922/newlib/libc/include/machine/_default_types.h \
  /home/strynzha/unikraft_9p_measure/build/libnewlibc/origin/newlib-2.5.0.20170922/newlib/libc/include/sys/features.h \
  /home/strynzha/unikraft_9p_measure/build/libnewlibc/origin/newlib-2.5.0.20170922/newlib/libc/include/_newlib_version.h \
  /home/strynzha/.unikraft/libs/libnewlib/include/sys/param.h \
  /home/strynzha/unikraft_9p_measure/build/libnewlibc/origin/newlib-2.5.0.20170922/newlib/libc/include/sys/param.h \
  /home/strynzha/unikraft_9p_measure/build/libnewlibc/origin/newlib-2.5.0.20170922/newlib/libc/include/sys/config.h \
  /home/strynzha/unikraft_9p_measure/build/libnewlibc/origin/newlib-2.5.0.20170922/newlib/libc/include/machine/ieeefp.h \
  /home/strynzha/unikraft_9p_measure/build/libnewlibc/origin/newlib-2.5.0.20170922/newlib/libc/include/sys/syslimits.h \
  /home/strynzha/unikraft_9p_measure/build/libnewlibc/origin/newlib-2.5.0.20170922/newlib/libc/include/machine/endian.h \
  /home/strynzha/.unikraft/libs/libnewlib/include/sys/_types.h \
  /home/strynzha/.unikraft/libs/libnewlib/include/uk/_types.h \
  /home/strynzha/.unikraft/unikraft/lib/uktime/include/uk/time_types.h \
  /home/strynzha/unikraft_9p_measure/build/libnewlibc/origin/newlib-2.5.0.20170922/newlib/libc/include/stdint.h \
  /home/strynzha/unikraft_9p_measure/build/libnewlibc/origin/newlib-2.5.0.20170922/newlib/libc/include/sys/_intsup.h \
  /home/strynzha/unikraft_9p_measure/build/libnewlibc/origin/newlib-2.5.0.20170922/newlib/libc/include/sys/_stdint.h \
  /home/strynzha/unikraft_9p_measure/build/libnewlibc/origin/newlib-2.5.0.20170922/newlib/libc/include/sys/_types.h \
  /home/strynzha/unikraft_9p_measure/build/libnewlibc/origin/newlib-2.5.0.20170922/newlib/libc/include/newlib.h \
  /home/strynzha/unikraft_9p_measure/build/libnewlibc/origin/newlib-2.5.0.20170922/newlib/libc/include/machine/_types.h \
  /home/strynzha/unikraft_9p_measure/build/libnewlibc/origin/newlib-2.5.0.20170922/newlib/libc/include/sys/lock.h \
  /home/strynzha/unikraft_9p_measure/build/libnewlibc/origin/newlib-2.5.0.20170922/newlib/libc/include/_ansi.h \
  /home/strynzha/unikraft_9p_measure/build/libnewlibc/origin/newlib-2.5.0.20170922/newlib/libc/include/machine/_endian.h \
  /home/strynzha/unikraft_9p_measure/build/libnewlibc/origin/newlib-2.5.0.20170922/newlib/libc/include/machine/param.h \
  /home/strynzha/unikraft_9p_measure/build/libnewlibc/origin/newlib-2.5.0.20170922/newlib/libc/include/inttypes.h \
  /home/strynzha/unikraft_9p_measure/build/libnewlibc/origin/newlib-2.5.0.20170922/newlib/libc/include/_ansi.h \
  /home/strynzha/unikraft_9p_measure/build/libnewlibc/origin/newlib-2.5.0.20170922/newlib/libc/include/xlocale.h \
  /home/strynzha/.unikraft/unikraft/arch/x86/x86_64/include/uk/asm/compiler.h \
  /home/strynzha/.unikraft/unikraft/include/uk/arch/types.h \
  /home/strynzha/.unikraft/unikraft/arch/x86/x86_64/include/uk/asm/intsizes.h \
  /home/strynzha/.unikraft/unikraft/arch/x86/x86_64/include/uk/asm/types.h \
  /home/strynzha/.unikraft/libs/libnewlib/include/limits.h \
  /home/strynzha/.unikraft/unikraft/include/uk/arch/limits.h \
  /home/strynzha/.unikraft/unikraft/arch/x86/x86_64/include/uk/asm/limits.h \
    $(wildcard include/config/stack/size/page/order.h) \
  /home/strynzha/unikraft_9p_measure/build/libnewlibc/origin/newlib-2.5.0.20170922/newlib/libc/include/string.h \
  /home/strynzha/unikraft_9p_measure/build/libnewlibc/origin/newlib-2.5.0.20170922/newlib/libc/include/sys/reent.h \
  /home/strynzha/unikraft_9p_measure/build/libnewlibc/origin/newlib-2.5.0.20170922/newlib/libc/include/strings.h \
  /home/strynzha/unikraft_9p_measure/build/libnewlibc/origin/newlib-2.5.0.20170922/newlib/libc/include/sys/string.h \
  /home/strynzha/.unikraft/unikraft/include/uk/plat/console.h \
  /home/strynzha/.unikraft/unikraft/include/uk/plat/time.h \
    $(wildcard include/config/hz.h) \
  /home/strynzha/.unikraft/unikraft/include/uk/arch/time.h \
  /home/strynzha/.unikraft/unikraft/lib/ukdebug/include/uk/print.h \
    $(wildcard include/config/libukdebug/printk/crit.h) \
    $(wildcard include/config/libukdebug/printk/err.h) \
    $(wildcard include/config/libukdebug/printk/warn.h) \
    $(wildcard include/config/libukdebug/printk/info.h) \
  /home/strynzha/.unikraft/unikraft/include/uk/arch/lcpu.h \
  /home/strynzha/.unikraft/unikraft/arch/x86/x86_64/include/uk/asm/lcpu.h \
  /home/strynzha/.unikraft/unikraft/include/uk/errptr.h \

/home/strynzha/unikraft_9p_measure/build/libukdebug/print.o: $(deps_/home/strynzha/unikraft_9p_measure/build/libukdebug/print.o)

$(deps_/home/strynzha/unikraft_9p_measure/build/libukdebug/print.o):
