BOARD ?= nrf52dk
include ../Makefile.pkg_common

# include shell support
USEMODULE += shell
USEMODULE += shell_cmds_default
USEMODULE += ps

# Include GNRC and RPL
USEMODULE += auto_init_gnrc_netif
USEMODULE += gnrc_ipv6_router_default
USEMODULE += gnrc_icmpv6_echo
USEMODULE += auto_init_gnrc_rpl
USEMODULE += gnrc_rpl

# Setup Nimble
USEMODULE += nimble_autoconn_ipsp
USEMODULE += nimble_autoconn_ext
FEATURES_OPTIONAL += ble_phy_2mbit
FEATURES_OPTIONAL += ble_phy_coded

TEST_ON_CI_WHITELIST += nrf52dk nrf52840dk

include $(RIOTBASE)/Makefile.include
