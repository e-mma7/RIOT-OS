export APPLICATION = can_trx
include ../Makefile.sys_common

USEMODULE += shell_cmds_default
USEMODULE += ps

USEMODULE += can_trx

TRX_TO_BUILD ?= tja1042

ifneq (,$(filter tja1042,$(TRX_TO_BUILD)))
  USEMODULE += tja1042
	TJA1042_STB_PIN ?= GPIO_PIN\(0,0\)

	CFLAGS += -DTJA1042_STB_PIN=$(TJA1042_STB_PIN)
endif

ifneq (,$(filter ncv7356,$(TRX_TO_BUILD)))
  USEMODULE += ncv7356
	NCV7356_MODE0_PIN ?= GPIO_PIN\(0,0\)
	NCV7356_MODE1_PIN ?= GPIO_PIN\(0,1\)

	CFLAGS += -DNCV7356_MODE0_PIN=$(NCV7356_MODE0_PIN)
	CFLAGS += -DNCV7356_MODE1_PIN=$(NCV7356_MODE1_PIN)
endif

include $(RIOTBASE)/Makefile.include
