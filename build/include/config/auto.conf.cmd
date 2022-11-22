deps_config := \
	/home/strynzha/.unikraft/libs/libnewlib/Config.uk \
	/home/strynzha/.unikraft/unikraft/lib/Config.uk \
	/home/strynzha/.unikraft/unikraft/lib//vfscore/Config.uk \
	/home/strynzha/.unikraft/unikraft/lib//uktimeconv/Config.uk \
	/home/strynzha/.unikraft/unikraft/lib//uktime/Config.uk \
	/home/strynzha/.unikraft/unikraft/lib//uktest/Config.uk \
	/home/strynzha/.unikraft/unikraft/lib//ukswrand/Config.uk \
	/home/strynzha/.unikraft/unikraft/lib//ukstore/Config.uk \
	/home/strynzha/.unikraft/unikraft/lib//uksp/Config.uk \
	/home/strynzha/.unikraft/unikraft/lib//uksignal/Config.uk \
	/home/strynzha/.unikraft/unikraft/lib//uksglist/Config.uk \
	/home/strynzha/.unikraft/unikraft/lib//ukschedcoop/Config.uk \
	/home/strynzha/.unikraft/unikraft/lib//uksched/Config.uk \
	/home/strynzha/.unikraft/unikraft/lib//ukrust/Config.uk \
	/home/strynzha/.unikraft/unikraft/lib//ukring/Config.uk \
	/home/strynzha/.unikraft/unikraft/lib//uknetdev/Config.uk \
	/home/strynzha/.unikraft/unikraft/lib//ukmpi/Config.uk \
	/home/strynzha/.unikraft/unikraft/lib//ukmmap/Config.uk \
	/home/strynzha/.unikraft/unikraft/lib//uklock/Config.uk \
	/home/strynzha/.unikraft/unikraft/lib//uklibparam/Config.uk \
	/home/strynzha/.unikraft/unikraft/lib//ukfallocbuddy/Config.uk \
	/home/strynzha/.unikraft/unikraft/lib//ukfalloc/Config.uk \
	/home/strynzha/.unikraft/unikraft/lib//ukdebug/Config.uk \
	/home/strynzha/.unikraft/unikraft/lib//ukcpio/Config.uk \
	/home/strynzha/.unikraft/unikraft/lib//ukbus/Config.uk \
	/home/strynzha/.unikraft/unikraft/lib//ukboot/Config.uk \
	/home/strynzha/.unikraft/unikraft/lib//ukblkdev/Config.uk \
	/home/strynzha/.unikraft/unikraft/lib//ukargparse/Config.uk \
	/home/strynzha/.unikraft/unikraft/lib//ukallocregion/Config.uk \
	/home/strynzha/.unikraft/unikraft/lib//ukallocpool/Config.uk \
	/home/strynzha/.unikraft/unikraft/lib//ukallocbbuddy/Config.uk \
	/home/strynzha/.unikraft/unikraft/lib//ukalloc/Config.uk \
	/home/strynzha/.unikraft/unikraft/lib//uk9p/Config.uk \
	/home/strynzha/.unikraft/unikraft/lib//ubsan/Config.uk \
	/home/strynzha/.unikraft/unikraft/lib//syscall_shim/Config.uk \
	/home/strynzha/.unikraft/unikraft/lib//ramfs/Config.uk \
	/home/strynzha/.unikraft/unikraft/lib//posix-user/Config.uk \
	/home/strynzha/.unikraft/unikraft/lib//posix-sysinfo/Config.uk \
	/home/strynzha/.unikraft/unikraft/lib//posix-socket/Config.uk \
	/home/strynzha/.unikraft/unikraft/lib//posix-process/Config.uk \
	/home/strynzha/.unikraft/unikraft/lib//posix-libdl/Config.uk \
	/home/strynzha/.unikraft/unikraft/lib//posix-futex/Config.uk \
	/home/strynzha/.unikraft/unikraft/lib//posix-event/Config.uk \
	/home/strynzha/.unikraft/unikraft/lib//nolibc/Config.uk \
	/home/strynzha/.unikraft/unikraft/lib//isrlib/Config.uk \
	/home/strynzha/.unikraft/unikraft/lib//fdt/Config.uk \
	/home/strynzha/.unikraft/unikraft/lib//devfs/Config.uk \
	/home/strynzha/.unikraft/unikraft/lib//9pfs/Config.uk \
	/home/strynzha/unikraft_9p_measure/build/kconfig/libs.uk \
	/home/strynzha/.unikraft/unikraft/plat/Config.uk \
	/home/strynzha/.unikraft/unikraft/plat//xen/Config.uk \
	/home/strynzha/.unikraft/unikraft/plat//linuxu/Config.uk \
	/home/strynzha/.unikraft/unikraft/plat//kvm/Config.uk \
	/home/strynzha/unikraft_9p_measure/build/kconfig/plat.uk \
	/home/strynzha/.unikraft/unikraft/arch/arm/arm64/Config.uk \
	/home/strynzha/.unikraft/unikraft/arch/arm/arm/Config.uk \
	/home/strynzha/.unikraft/unikraft/arch/x86/x86_64/Config.uk \
	/home/strynzha/.unikraft/unikraft/arch/Config.uk \
	/home/strynzha/.unikraft/unikraft/Config.uk

/home/strynzha/unikraft_9p_measure/build/kconfig/auto.conf: \
	$(deps_config)

ifneq "$(UK_FULLVERSION)" "0.10.0~43e675b"
/home/strynzha/unikraft_9p_measure/build/kconfig/auto.conf: FORCE
endif
ifneq "$(UK_CODENAME)" "Phoebe"
/home/strynzha/unikraft_9p_measure/build/kconfig/auto.conf: FORCE
endif
ifneq "$(UK_ARCH)" "x86_64"
/home/strynzha/unikraft_9p_measure/build/kconfig/auto.conf: FORCE
endif
ifneq "$(UK_BASE)" "/home/strynzha/.unikraft/unikraft"
/home/strynzha/unikraft_9p_measure/build/kconfig/auto.conf: FORCE
endif
ifneq "$(UK_APP)" "/home/strynzha/unikraft_9p_measure"
/home/strynzha/unikraft_9p_measure/build/kconfig/auto.conf: FORCE
endif
ifneq "$(UK_NAME)" "unikraft_9p_measure"
/home/strynzha/unikraft_9p_measure/build/kconfig/auto.conf: FORCE
endif
ifneq "$(CC)" "gcc"
/home/strynzha/unikraft_9p_measure/build/kconfig/auto.conf: FORCE
endif
ifneq "$(KCONFIG_PLAT_DIR)" "/home/strynzha/.unikraft/unikraft/plat//kvm /home/strynzha/.unikraft/unikraft/plat//linuxu /home/strynzha/.unikraft/unikraft/plat//xen  /home/strynzha/.unikraft/unikraft/plat/"
/home/strynzha/unikraft_9p_measure/build/kconfig/auto.conf: FORCE
endif
ifneq "$(KCONFIG_PLAT_IN)" "/home/strynzha/unikraft_9p_measure/build/kconfig/plat.uk"
/home/strynzha/unikraft_9p_measure/build/kconfig/auto.conf: FORCE
endif
ifneq "$(KCONFIG_LIB_DIR)" "/home/strynzha/.unikraft/unikraft/lib//9pfs /home/strynzha/.unikraft/unikraft/lib//devfs /home/strynzha/.unikraft/unikraft/lib//fdt /home/strynzha/.unikraft/unikraft/lib//isrlib /home/strynzha/.unikraft/unikraft/lib//nolibc /home/strynzha/.unikraft/unikraft/lib//posix-event /home/strynzha/.unikraft/unikraft/lib//posix-futex /home/strynzha/.unikraft/unikraft/lib//posix-libdl /home/strynzha/.unikraft/unikraft/lib//posix-process /home/strynzha/.unikraft/unikraft/lib//posix-socket /home/strynzha/.unikraft/unikraft/lib//posix-sysinfo /home/strynzha/.unikraft/unikraft/lib//posix-user /home/strynzha/.unikraft/unikraft/lib//ramfs /home/strynzha/.unikraft/unikraft/lib//syscall_shim /home/strynzha/.unikraft/unikraft/lib//ubsan /home/strynzha/.unikraft/unikraft/lib//uk9p /home/strynzha/.unikraft/unikraft/lib//ukalloc /home/strynzha/.unikraft/unikraft/lib//ukallocbbuddy /home/strynzha/.unikraft/unikraft/lib//ukallocpool /home/strynzha/.unikraft/unikraft/lib//ukallocregion /home/strynzha/.unikraft/unikraft/lib//ukargparse /home/strynzha/.unikraft/unikraft/lib//ukblkdev /home/strynzha/.unikraft/unikraft/lib//ukboot /home/strynzha/.unikraft/unikraft/lib//ukbus /home/strynzha/.unikraft/unikraft/lib//ukcpio /home/strynzha/.unikraft/unikraft/lib//ukdebug /home/strynzha/.unikraft/unikraft/lib//ukfalloc /home/strynzha/.unikraft/unikraft/lib//ukfallocbuddy /home/strynzha/.unikraft/unikraft/lib//uklibparam /home/strynzha/.unikraft/unikraft/lib//uklock /home/strynzha/.unikraft/unikraft/lib//ukmmap /home/strynzha/.unikraft/unikraft/lib//ukmpi /home/strynzha/.unikraft/unikraft/lib//uknetdev /home/strynzha/.unikraft/unikraft/lib//ukring /home/strynzha/.unikraft/unikraft/lib//ukrust /home/strynzha/.unikraft/unikraft/lib//uksched /home/strynzha/.unikraft/unikraft/lib//ukschedcoop /home/strynzha/.unikraft/unikraft/lib//uksglist /home/strynzha/.unikraft/unikraft/lib//uksignal /home/strynzha/.unikraft/unikraft/lib//uksp /home/strynzha/.unikraft/unikraft/lib//ukstore /home/strynzha/.unikraft/unikraft/lib//ukswrand /home/strynzha/.unikraft/unikraft/lib//uktest /home/strynzha/.unikraft/unikraft/lib//uktime /home/strynzha/.unikraft/unikraft/lib//uktimeconv /home/strynzha/.unikraft/unikraft/lib//vfscore /home/strynzha/.unikraft/unikraft/lib /home/strynzha/.unikraft/libs/libnewlib"
/home/strynzha/unikraft_9p_measure/build/kconfig/auto.conf: FORCE
endif
ifneq "$(KCONFIG_LIB_IN)" "/home/strynzha/unikraft_9p_measure/build/kconfig/libs.uk"
/home/strynzha/unikraft_9p_measure/build/kconfig/auto.conf: FORCE
endif
ifneq "$(KCONFIG_APP_DIR)" "/home/strynzha/unikraft_9p_measure"
/home/strynzha/unikraft_9p_measure/build/kconfig/auto.conf: FORCE
endif

$(deps_config): ;
