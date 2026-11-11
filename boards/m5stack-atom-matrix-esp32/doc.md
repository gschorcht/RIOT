<!--
SPDX-FileCopyrightText: 2026 Gunar Schorcht
SPDX-License-Identifier: LGPL-2.1-only
-->

@defgroup   boards_m5stack-atom-matrix-esp32 M5Stack Atom Matrix
@ingroup    boards_esp32
@brief      Support for M5Stack Atom Matrix ESP32 Development Kit
@author     Gunar Schorcht <gunar@schorcht.net>

\section m5stack_atom_matrix_esp32 M5Stack Atom Matrix

## Overview

The M5Stack Atom Matrix is a very small ESP32 development kit with a size of
only 24 mm x 24 mm. It is based on the ESP32-PICO-D4 SiP, which integrates
an ESP32 SoC with dual-core Xtensa LX6 CPU, a 40 MHz crystal and 4 MB flash.

The board has the following on-board components:

- 5 x 5 RGB-LED matrix with WS2812C LEDs
- Programmable button underneath the LED matrix
- IR transmitter LED
- MPU6886 6-axis IMU (3-axis gyroscope and 3-axis accelerometer)
- USB Type-C connector with USB-to-UART bridge
- Grove connector (HY2.0-4P)
- 6 GPIOs on the pin header

## Hardware

### MCU

Most features of the board are provided by the ESP32 SoC. For detailed
information about the ESP32, see section \ref esp32_mcu_esp32 "MCU ESP32".

### Board Configuration {#m5stack_atom_matrix_esp32_board_configuration}

The following table shows the default board configuration, which is sorted
according to the defined functionality of GPIOs. This configuration can be
overridden by an \ref esp32_application_specific_configurations
"application-specific configuration".

<center>
Pin    | Default Configuration* | Optional Modules | Remarks / Prerequisites | Configuration
:------|:-----------------------|:-----------------|:------------------------|:-------------
GPIO39 | BTN0                   | | Button underneath the LED matrix, input only, low active | |
GPIO27 | RGB-LED matrix         | | 5 x 5 WS2812C LEDs, supported by driver module `ws281x` | |
GPIO12 | PWM_DEV(0):0           | | IR transmitter LED | \ref esp32_pwm_channels "PWM Channels"
GPIO21 | I2C_DEV(0):SCL         | | MPU6886 IMU, also on header | \ref esp32_i2c_interfaces "I2C Interfaces"
GPIO25 | I2C_DEV(0):SDA         | | MPU6886 IMU, also on header | \ref esp32_i2c_interfaces "I2C Interfaces"
GPIO32 | I2C_DEV(1):SCL         | | Grove connector | \ref esp32_i2c_interfaces "I2C Interfaces"
GPIO26 | I2C_DEV(1):SDA         | | Grove connector | \ref esp32_i2c_interfaces "I2C Interfaces"
GPIO23 | SPI_DEV(0):SCK         | | header | \ref esp32_spi_interfaces "SPI Interfaces"
GPIO33 | SPI_DEV(0):MISO        | | header | \ref esp32_spi_interfaces "SPI Interfaces"
GPIO19 | SPI_DEV(0):MOSI        | | header | \ref esp32_spi_interfaces "SPI Interfaces"
GPIO22 | SPI_DEV(0):CS0         | | header | \ref esp32_spi_interfaces "SPI Interfaces"
GPIO1  | UART_DEV(0):TxD        | | Console (configuration is fixed) | \ref esp32_uart_interfaces "UART interfaces"
GPIO3  | UART_DEV(0):RxD        | | Console (configuration is fixed) | \ref esp32_uart_interfaces "UART interfaces"
GPIO32 | ADC_LINE(0)            | | Grove connector | \ref esp32_adc_channels "ADC Channels"
GPIO33 | ADC_LINE(1)            | | header | \ref esp32_adc_channels "ADC Channels"
GPIO26 | DAC_LINE(0)            | | Grove connector | \ref esp32_dac_channels "DAC Channels"
</center>

\b * Default configuration cannot be used or is not available at all when
optional hardware is used.

@note
- Some GPIOs are used in several default configurations. The purpose for
  which a GPIO is used depends on which module or function is used first.
  For example, if the module `periph_i2c` is not used, GPIO26 and GPIO32 at
  the Grove connector can be used as ADC or DAC channels.
- GPIO16 and GPIO17 are used by the ESP32-PICO-D4 for the embedded flash
  and are not available.
- Due to a hardware bug of the ESP32 (see errata section 3.11 in the
  [ESP32 Series SoC Errata](https://www.espressif.com/sites/default/files/documentation/esp32_errata_en.pdf)),
  GPIO39 may generate spurious interrupts when the ADC or WiFi is used.
- The MPU6886 IMU is connected to I2C_DEV(0) with address 0x68. However,
  there is no driver for the MPU6886 in RIOT yet.

For detailed information about the configuration of ESP32 boards, see
section \ref esp32_peripherals "Common Peripherals".

### RGB-LED Matrix

The 25 WS2812C LEDs of the 5 x 5 matrix are connected in a chain to GPIO27
and can be controlled using the driver module \ref drivers_ws281x "ws281x".
The LEDs are chained row by row starting with the top left LED, i.e. the
LED in row `r` and column `c` has the index `r * 5 + c`.

@warning M5Stack recommends not to use more than 20 of 255 for the
         brightness of the LEDs to avoid damaging the LEDs and the
         acrylic plate due to heat.

### Board Pinout {#m5stack_atom_matrix_esp32_pinout}

The following picture shows the pinout of the M5Stack Atom Matrix (back
view) as defined by the default board configuration. The GPIOs GPIO19,
GPIO21, GPIO22, GPIO23, GPIO25 and GPIO33 are broken out on the pin header,
GPIO26 and GPIO32 on the Grove connector. Some GPIOs are used in several
default configurations, see section
\ref m5stack_atom_matrix_esp32_board_configuration for more information.

<img src="https://gitlab.com/gschorcht/RIOT.wiki-Images/-/raw/116d4fc78044cea086b3441edf2c0670f7a06d3a/esp32/M5Stack_Atom_Matrix-ESP32.png" alt="M5Stack Atom Matrix ESP32 pinout" />

The board schematic and further information can be found on the
[M5Stack Atom Matrix documentation page](https://docs.m5stack.com/en/core/ATOM%20Matrix).

## Flashing the Device

Flashing RIOT is quite easy. The board has a USB Type-C connector with a
USB-to-UART bridge and a reset/boot/flash logic. Just connect the board to
your host computer and type:

```shell
BOARD=m5stack-atom-matrix-esp32 make flash ...
```

@note The USB-to-UART bridge of the board does not work reliably at higher
      baudrates when flashing. Therefore, the board definition sets the
      baudrate used for flashing to 115200 baud by default. It can be
      overridden with the `PROGRAMMER_SPEED` variable if necessary.

For detailed information about ESP32 as well as configuring and compiling
RIOT for ESP32 boards, see \ref esp32_riot.
