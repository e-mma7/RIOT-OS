MODULE = nrf5x_common_periph

# Select the specific implementation for `periph_i2c`
ifneq (,$(filter periph_i2c,$(USEMODULE)))
  ifneq (,$(filter $(CPU_FAM),nrf52 nrf53 nrf9160))
    SRC += i2c_nrf52_nrf9160.c
  endif
endif

# Select the specific implementation for `periph_pwm`
# nRF51 has its own PWM driver variant in its periph driver folder
ifneq (,$(filter periph_pwm,$(USEMODULE)))
  ifneq (,$(filter $(CPU_FAM),nrf52 nrf53 nrf9160))
    SRC += pwm_nrfxx.c
  endif
endif

# Select the specific implementation for `periph_spi`
ifneq (,$(filter periph_spi,$(USEMODULE)))
  ifneq (,$(filter $(CPU_FAM),nrf52 nrf53 nrf9160))
    SRC += spi_nrf52_nrf9160.c
  endif
endif

include $(RIOTMAKE)/periph.mk
