PKG_NAME=flashdb
PKG_URL=https://github.com/armink/FlashDB.git
# 2.0.0
PKG_VERSION=fab8a161809d72878d1ad5bdd6ddd54301dfcb81
PKG_LICENSE=Apache-2.0

include $(RIOTBASE)/pkg/pkg.mk

CFLAGS += -Wno-pedantic
CFLAGS += -Wno-cast-align
CFLAGS += -Wno-unused
CFLAGS += -Wno-unused-parameter
CFLAGS += -Wno-format

.PHONY: flashdb_fal

all: $(filter flashdb_fal, $(USEMODULE))
	$(QQ)"$(MAKE)" -C $(PKG_SOURCE_DIR)/src -f $(CURDIR)/Makefile.flashdb

flashdb_fal:
	$(QQ)"$(MAKE)" -C $(PKG_SOURCE_DIR)/port/fal/src -f $(CURDIR)/Makefile.fal
