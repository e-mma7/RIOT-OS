PKG_NAME    = qcbor
PKG_URL     = https://github.com/laurencelundblade/QCBOR
# v1.2
PKG_VERSION = 92d3f89030baff4af7be8396c563e6c8ef263622
PKG_LICENSE = BSD-3-Clause

include $(RIOTBASE)/pkg/pkg.mk

# some variable seem uninitialized to gcc with -Og but are not
# https://gcc.gnu.org/bugzilla/buglist.cgi?quicksearch=may%20be%20used%20uninitialized
# https://gcc.gnu.org/bugzilla/show_bug.cgi?id=42145
# https://gcc.gnu.org/bugzilla/show_bug.cgi?id=90710#c1
CFLAGS += -Wno-maybe-uninitialized

all:
	$(QQ)"$(MAKE)" -C $(PKG_SOURCE_DIR)/src -f $(RIOTBASE)/Makefile.base MODULE=$(PKG_NAME)
