INCLUDES += -I$(APPDIR)

include ../Makefile.drivers_common

ifeq (,$(filter pcf857%,$(USEMODULE)))
    # default expander module
    USEMODULE += pcf8575
endif

USEMODULE += shell
USEMODULE += benchmark

include $(RIOTBASE)/Makefile.include
