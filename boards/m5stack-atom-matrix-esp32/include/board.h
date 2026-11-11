/*
 * SPDX-FileCopyrightText: 2026 Gunar Schorcht
 * SPDX-License-Identifier: LGPL-2.1-only
 */

#pragma once

/**
 * @ingroup     boards_m5stack-atom-matrix-esp32
 * @brief       Board specific definitions for M5Stack Atom Matrix
 * @{
 *
 * The M5Stack Atom Matrix is a very small ESP32 development kit
 * (24 mm x 24 mm) based on the ESP32-PICO-D4 SiP with 4 MB embedded flash.
 * It has a 5 x 5 matrix of WS2812C RGB-LEDs, a programmable button
 * underneath the LED matrix, an IR transmitter LED and a MPU6886 6-axis IMU
 * on board.
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

/**
 * @name    Button pin definitions
 * @{
 */

/**
 * @brief   Default button GPIO pin definition
 *
 * The programmable button underneath the LED matrix is connected to GPIO39.
 * Since GPIO39 is pulled up by an external resistor, the button signal is
 * inverted, i.e., pressing the button will give a low signal.
 */
#define BTN0_PIN        GPIO39

/**
 * @brief   Default button GPIO mode definition
 *
 * GPIO39 is an input-only pin without internal pull-up/pull-down resistors.
 * Since it is pulled up with an external resistor, the mode for the GPIO pin
 * has to be GPIO_IN.
 */
#define BTN0_MODE       GPIO_IN

/**
 * @brief   Default interrupt flank definition for the button GPIO
 */
#ifndef BTN0_INT_FLANK
#define BTN0_INT_FLANK  GPIO_FALLING
#endif

/**
 * @brief   Definition for compatibility with previous versions
 */
#define BUTTON0_PIN     BTN0_PIN

/** @} */

/**
 * @name    LED (on-board) configuration
 *
 * The M5Stack Atom Matrix has no simple on-board LED, but a 5 x 5 matrix
 * of WS2812C RGB-LEDs connected in a chain to GPIO27. The WS281x driver
 * module `ws281x` can be used to control it.
 *
 * @warning M5Stack recommends not to use more than 20 of 255 for the
 *          brightness of the LEDs to avoid damaging the LEDs and the
 *          acrylic plate due to heat.
 * @{
 */
#ifndef WS281X_PARAM_PIN
#  define WS281X_PARAM_PIN      (GPIO27)  /**< GPIO pin connected to the data pin */
#endif
#ifndef WS281X_PARAM_NUMOF
#  define WS281X_PARAM_NUMOF    (25U)     /**< Number of LEDs chained */
#endif
/** @} */

/**
 * @name    IR transmitter configuration
 *
 * The IR transmitter LED is connected to GPIO12. It is configured as
 * PWM channel PWM_DEV(0):0 so that it can be used to generate the IR
 * carrier frequency.
 * @{
 */
#define IR_TX_PIN       GPIO12          /**< GPIO used for the IR transmitter LED */
/** @} */

/**
 * @name    MPU6886 IMU configuration
 *
 * The MPU6886 6-axis IMU is connected to I2C_DEV(0) using address 0x68.
 * There is no driver for the MPU6886 in RIOT yet.
 * @{
 */
#define MPU6886_I2C_DEV     I2C_DEV(0)  /**< I2C device used for the MPU6886 */
#define MPU6886_I2C_ADDR    (0x68)      /**< I2C address of the MPU6886 */
/** @} */

/* include common board definitions as last step */
#include "board_common.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
} /* end extern "C" */
#endif

/** @} */
