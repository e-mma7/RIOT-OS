# the driver to test
USEMODULE = atwinc15x0

# msp430-gcc doesn't support -Wno-discarded-qualifiers
FEATURES_BLACKLIST += arch_msp430 cpu_core_atxmega

include ../Makefile.drivers_common
include ../../net/netdev_common/Makefile.netdev.mk
