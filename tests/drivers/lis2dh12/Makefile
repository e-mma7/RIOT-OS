include ../Makefile.drivers_common

# use lis2dh12_spi for SPI-Mode and lis2dh12_i2c for I2C-Mode
DRIVER ?= lis2dh12_spi

USEMODULE += fmt
USEMODULE += ztimer
USEMODULE += ztimer_msec
USEMODULE += shell_cmds_default
USEMODULE += $(DRIVER)

# for using lis2dh12 with interrupt function
USEMODULE += lis2dh12_int

include $(RIOTBASE)/Makefile.include
