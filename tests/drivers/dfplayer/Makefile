include ../Makefile.drivers_common

USEMODULE += dfplayer
USEMODULE += event_thread
USEMODULE += shell_cmds_default

include $(RIOTBASE)/Makefile.include

ifneq (,$(BUSY_PIN))
  CFLAGS += '-DDFPLAYER_PARAM_BUSY_PIN=$(BUSY_PIN)'
endif
