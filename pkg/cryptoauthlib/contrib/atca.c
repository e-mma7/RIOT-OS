/*
 * Copyright (C) 2019 HAW Hamburg
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     pkg_cryptoauthlib
 * @{
 *
 * @file
 * @brief       HAL implementation for the library Microchip CryptoAuth devices
 *
 * @author      Lena Boeckmann <lena.boeckmann@haw-hamburg.de>
 *
 * @}
 */
#include <stdio.h>
#include <stdint.h>
#include "timex.h"
#include "ztimer.h"
#include "periph/i2c.h"
#include "periph/gpio.h"

#include "atca.h"
#include "atca_params.h"

/* Timer functions */
void atca_delay_us(uint32_t delay)
{
    ztimer_sleep(ZTIMER_USEC, delay);
}

void atca_delay_10us(uint32_t delay)
{
    ztimer_sleep(ZTIMER_USEC, delay * 10);
}

void atca_delay_ms(uint32_t delay)
{
    ztimer_sleep(ZTIMER_USEC, delay * US_PER_MS);
}

/* Hal I2C implementation */
ATCA_STATUS hal_i2c_init(ATCAIface iface, ATCAIfaceCfg *cfg)
{
    (void)iface;
    if (cfg->iface_type != ATCA_I2C_IFACE) {
        return ATCA_BAD_PARAM;
    }

    atcab_wakeup();

    return ATCA_SUCCESS;
}

ATCA_STATUS hal_i2c_post_init(ATCAIface iface)
{
    (void)iface;
    return ATCA_SUCCESS;
}

ATCA_STATUS hal_i2c_send(ATCAIface iface, uint8_t word_address, uint8_t *txdata, int txlength)
{
    (void)word_address;
    ATCAIfaceCfg *cfg = atgetifacecfg(iface);
    int ret;

    i2c_acquire(cfg->atcai2c.bus);
    ret = i2c_write_bytes(cfg->atcai2c.bus, (cfg->atcai2c.address >> 1),
                          txdata, txlength, 0);
    i2c_release(cfg->atcai2c.bus);

    if (ret != 0) {
        return ATCA_TX_FAIL;
    }

    return ATCA_SUCCESS;
}

ATCA_STATUS hal_i2c_receive(ATCAIface iface, uint8_t word_address, uint8_t *rxdata,
                            uint16_t *rxlength)
{
    (void)word_address;
    ATCAIfaceCfg *cfg = atgetifacecfg(iface);
    uint8_t retries = cfg->rx_retries;
    int ret = -1;

    /* read rest of output and insert into rxdata array after first byte */
    i2c_acquire(cfg->atcai2c.bus);
    while (retries-- > 0 && ret != 0) {
        ret = i2c_read_bytes(cfg->atcai2c.bus,
                             (cfg->atcai2c.address >> 1), (rxdata),
                             *rxlength, 0);
    }
    i2c_release(cfg->atcai2c.bus);

    if (ret != 0) {
        return ATCA_RX_TIMEOUT;
    }

    return ATCA_SUCCESS;
}

ATCA_STATUS hal_i2c_wake(ATCAIface iface)
{
    ATCAIfaceCfg *cfg = atgetifacecfg(iface);
    uint8_t data[4] = { 0 };

#if IS_USED(MODULE_PERIPH_I2C_RECONFIGURE)
    /* switch I2C peripheral to GPIO function */
    i2c_deinit_pins(cfg->atcai2c.bus);
    gpio_init(i2c_pin_sda(cfg->atcai2c.bus), GPIO_OUT);

    /* send wake pulse of 100us (t_WOL) */
    gpio_clear(i2c_pin_sda(cfg->atcai2c.bus));
    atca_delay_us(100);

    /* reinit I2C peripheral */
    i2c_init_pins(cfg->atcai2c.bus);
#else
    /* send wake pulse by sending byte 0x00 */
    /* this requires the I2C clock to be 100kHz at a max */
    i2c_acquire(cfg->atcai2c.bus);
    i2c_write_byte(cfg->atcai2c.bus, ATCA_WAKE_ADDR, data[0], 0);
    i2c_release(cfg->atcai2c.bus);
#endif

    atca_delay_us(cfg->wake_delay);

    uint8_t retries = cfg->rx_retries;
    int status = -1;

    i2c_acquire(cfg->atcai2c.bus);
    while (retries-- > 0 && status != 0) {
        status = i2c_read_bytes(cfg->atcai2c.bus,
                                (cfg->atcai2c.address >> 1),
                                &data[0], 4, 0);
    }
    i2c_release(cfg->atcai2c.bus);

    if (status != ATCA_SUCCESS) {
        return ATCA_COMM_FAIL;
    }
    return hal_check_wake(data, 4);
}

ATCA_STATUS hal_i2c_idle(ATCAIface iface)
{
    ATCAIfaceCfg *cfg = atgetifacecfg(iface);

    i2c_acquire(cfg->atcai2c.bus);
    i2c_write_byte(cfg->atcai2c.bus, (cfg->atcai2c.address >> 1),
                   ATCA_IDLE_ADDR, 0);
    i2c_release(cfg->atcai2c.bus);
    return ATCA_SUCCESS;
}

ATCA_STATUS hal_i2c_sleep(ATCAIface iface)
{
    ATCAIfaceCfg *cfg = atgetifacecfg(iface);

    i2c_acquire(cfg->atcai2c.bus);
    i2c_write_byte(cfg->atcai2c.bus, (cfg->atcai2c.address >> 1),
                   ATCA_SLEEP_ADDR, 0);
    i2c_release(cfg->atcai2c.bus);
    return ATCA_SUCCESS;
}

ATCA_STATUS hal_i2c_control(ATCAIface iface, uint8_t option, void *param, size_t paramlen)
{
    (void)param;
    (void)paramlen;
    switch (option) {
    case ATCA_HAL_CONTROL_WAKE:
        return hal_i2c_wake(iface);
    case ATCA_HAL_CONTROL_IDLE:
        return hal_i2c_idle(iface);
    case ATCA_HAL_CONTROL_SLEEP:
        return hal_i2c_sleep(iface);
    case ATCA_HAL_CHANGE_BAUD:
        return ATCA_UNIMPLEMENTED;
    case ATCA_HAL_CONTROL_SELECT:
    case ATCA_HAL_CONTROL_DESELECT:
        return ATCA_SUCCESS;
    default:
        return ATCA_BAD_PARAM;
    }
    return ATCA_UNIMPLEMENTED;
}

ATCA_STATUS hal_i2c_release(void *hal_data)
{
    (void)hal_data;
    /* This function is unimplemented, because currently the bus gets acquired
       and released before and after each read or write operation. It returns
       a success code, in case it gets called somewhere in the library. */
    return ATCA_SUCCESS;
}

ATCA_STATUS hal_i2c_discover_buses(int i2c_buses[], int max_buses)
{
    (void)i2c_buses;
    (void)max_buses;
    return ATCA_UNIMPLEMENTED;
}

ATCA_STATUS hal_i2c_discover_devices(int bus_num, ATCAIfaceCfg *cfg, int *found)
{
    (void)bus_num;
    (void)cfg;
    (void)found;
    return ATCA_UNIMPLEMENTED;
}
