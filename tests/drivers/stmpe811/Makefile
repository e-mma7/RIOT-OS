BOARD ?= stm32f429i-disc1

include ../Makefile.drivers_common

DRIVER ?= stmpe811_i2c
USEMODULE += $(DRIVER)

STMPE811_POLLING_MODE ?= 0
STMPE811_POLLING_PERIOD ?= 50

CFLAGS += -DSTMPE811_POLLING_MODE=$(STMPE811_POLLING_MODE)
CFLAGS += -DSTMPE811_POLLING_PERIOD=$(STMPE811_POLLING_PERIOD)

ifneq (0,$(STMPE811_POLLING_MODE))
  USEMODULE += ztimer_msec
endif

include $(RIOTBASE)/Makefile.include
