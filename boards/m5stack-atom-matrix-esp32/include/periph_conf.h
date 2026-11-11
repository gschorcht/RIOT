/*
 * SPDX-FileCopyrightText: 2026 Gunar Schorcht
 * SPDX-License-Identifier: LGPL-2.1-only
 */

#pragma once

/**
 * @ingroup     boards_m5stack-atom-matrix-esp32
 * @brief       Peripheral MCU configuration for M5Stack Atom Matrix
 * @{
 *
 * The M5Stack Atom Matrix is a very small ESP32 development kit based on the
 * ESP32-PICO-D4 SiP with 4 MB embedded flash. Only GPIO19, GPIO21, GPIO22,
 * GPIO23, GPIO25 and GPIO33 are broken out on the header and GPIO26 and
 * GPIO32 on the Grove connector. GPIO21 and GPIO25 are shared with the
 * on-board MPU6886 IMU.
 *
 * For detailed information about the configuration of ESP32 boards, see
 * section \ref esp32_peripherals "Common Peripherals".
 *
 * @note
 * Most definitions can be overridden by an \ref esp32_application_specific_configurations
 * "application-specific board configuration".
 *
 * @file
 * @author      Gunar Schorcht <gunar@schorcht.net>
 */

#include <stdint.h>

#ifdef __cplusplus
 extern "C" {
#endif

/**
 * @name    ADC and DAC channel configuration
 * @{
 */

/**
 * @brief   Declaration of GPIOs that can be used as ADC channels
 *
 * Only GPIO32 and GPIO33 are ADC1 channels that are broken out. They can be
 * used together with WiFi.
 *
 * @note As long as the GPIOs listed in ADC_GPIOS are not initialized as ADC
 * channels with the \ref adc_init function, they can be used for other
 * purposes.
 */
#ifndef ADC_GPIOS
#define ADC_GPIOS   { GPIO32, GPIO33 }
#endif

/**
 * @brief   Declaration of GPIOs that can be used as DAC channels
 *
 * GPIO25 is used as I2C SDA signal of the on-board IMU. Therefore, only
 * GPIO26 at the Grove connector is used as DAC channel.
 *
 * @note As long as the GPIOs listed in DAC_GPIOS are not initialized as DAC
 * channels with the \ref dac_init function, they can be used for other
 * purposes.
 */
#ifndef DAC_GPIOS
#define DAC_GPIOS   { GPIO26 }
#endif
/** @} */

/**
 * @name   I2C configuration
 *
 * I2C_DEV(0) is connected to the on-board MPU6886 IMU and is also broken
 * out on the header. I2C_DEV(1) is available at the Grove connector.
 *
 * @note The GPIOs listed in the configuration are only initialized as I2C
 * signals when module `periph_i2c` is used. Otherwise they are not
 * allocated and can be used for other purposes.
 *
 * @{
 */
#ifndef I2C0_SPEED
#define I2C0_SPEED  I2C_SPEED_FAST  /**< I2C bus speed of I2C_DEV(0) */
#endif
#ifndef I2C0_SCL
#define I2C0_SCL    GPIO21          /**< SCL signal of I2C_DEV(0) (IMU) */
#endif
#ifndef I2C0_SDA
#define I2C0_SDA    GPIO25          /**< SDA signal of I2C_DEV(0) (IMU) */
#endif

#ifndef I2C1_SPEED
#define I2C1_SPEED  I2C_SPEED_FAST  /**< I2C bus speed of I2C_DEV(1) */
#endif
#ifndef I2C1_SCL
#define I2C1_SCL    GPIO32          /**< SCL signal of I2C_DEV(1) (Grove) */
#endif
#ifndef I2C1_SDA
#define I2C1_SDA    GPIO26          /**< SDA signal of I2C_DEV(1) (Grove) */
#endif
/** @} */

/**
 * @name   PWM channel configuration
 *
 * PWM_DEV(0):0 is connected to the IR transmitter LED.
 *
 * @note As long as the according PWM device is not initialized with
 * the `pwm_init`, the GPIOs declared for this device can be used
 * for other purposes.
 *
 * @{
 */
/** PWM channels for device PWM_DEV(0) */
#ifndef PWM0_GPIOS
#define PWM0_GPIOS  { GPIO12 }
#endif
/** @} */

/**
 * @name    SPI configuration
 *
 * @note The GPIOs listed in the configuration are first initialized as SPI
 * signals when the corresponding SPI interface is used for the first time
 * by either calling the `spi_init_cs` function or the `spi_acquire`
 * function. That is, they are not allocated as SPI signals before and can
 * be used for other purposes as long as the SPI interface is not used.
 *
 * @{
 */
#ifndef SPI0_CTRL
#define SPI0_CTRL   VSPI    /**< VSPI is used as SPI_DEV(0) */
#endif
#ifndef SPI0_SCK
#define SPI0_SCK    GPIO23  /**< VSPI SCK */
#endif
#ifndef SPI0_MISO
#define SPI0_MISO   GPIO33  /**< VSPI MISO */
#endif
#ifndef SPI0_MOSI
#define SPI0_MOSI   GPIO19  /**< VSPI MOSI */
#endif
#ifndef SPI0_CS0
#define SPI0_CS0    GPIO22  /**< VSPI CS0 */
#endif
/** @} */

/**
 * @name   UART configuration
 *
 * ESP32 provides 3 UART interfaces at maximum:
 *
 * UART_DEV(0) uses fixed standard configuration.<br>
 * UART_DEV(1) is not used by default.<br>
 * UART_DEV(2) is not used.<br>
 *
 * @{
 */
#define UART0_TXD   GPIO1  /**< direct I/O pin for UART_DEV(0) TxD, can't be changed */
#define UART0_RXD   GPIO3  /**< direct I/O pin for UART_DEV(0) RxD, can't be changed */
/** @} */

#ifdef __cplusplus
} /* end extern "C" */
#endif

/* include common board definitions as last step */
#include "periph_conf_common.h"

/** @} */
