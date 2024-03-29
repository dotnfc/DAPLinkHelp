/**
 * @file    DAP_config.c
 * @brief
 *
 * DAPLink Interface Firmware
 * Copyright (c) 2009-2016, ARM Limited, All Rights Reserved
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __DAP_CONFIG_H__
#define __DAP_CONFIG_H__


//**************************************************************************************************
/**
\defgroup DAP_Config_Debug_gr CMSIS-DAP Debug Unit Information
\ingroup DAP_ConfigIO_gr
@{
Provides definitions about:
 - Definition of Cortex-M processor parameters used in CMSIS-DAP Debug Unit.
 - Debug Unit communication packet size.
 - Debug Access Port communication mode (JTAG or SWD).
 - Optional information about a connected Target Device (for Evaluation Boards).
*/

#include "LPC43xx.h"                            // Debug Unit Cortex-M Processor Header File
#include "lpc43xx_scu.h"

typedef unsigned int    BOOL;

#ifndef __TRUE
 #define __TRUE         1
#endif
#ifndef __FALSE
 #define __FALSE        0
#endif

/// Processor Clock of the Cortex-M MCU used in the Debug Unit.
/// This value is used to calculate the SWD/JTAG clock speed.
#define CPU_CLOCK             SystemCoreClock        ///< Specifies the CPU Clock in Hz

/// Number of processor cycles for I/O Port write operations.
/// This value is used to calculate the SWD/JTAG clock speed that is generated with I/O
/// Port write operations in the Debug Unit by a Cortex-M MCU. Most Cortex-M processors
/// requrie 2 processor cycles for a I/O Port Write operation.  If the Debug Unit uses
/// a Cortex-M0+ processor with high-speed peripheral I/O only 1 processor cycle might be
/// required.
#define IO_PORT_WRITE_CYCLES  2               ///< I/O Cycles: 2=default, 1=Cortex-M0+ fast I/0

/// Indicate that Serial Wire Debug (SWD) communication mode is available at the Debug Access Port.
/// This information is returned by the command \ref DAP_Info as part of <b>Capabilities</b>.
#define DAP_SWD               1               ///< SWD Mode:  1 = available, 0 = not available

/// Indicate that JTAG communication mode is available at the Debug Port.
/// This information is returned by the command \ref DAP_Info as part of <b>Capabilities</b>.
#define DAP_JTAG              0               ///< JTAG Mode: 1 = available, 0 = not available.

/// Configure maximum number of JTAG devices on the scan chain connected to the Debug Access Port.
/// This setting impacts the RAM requirements of the Debug Unit. Valid range is 1 .. 255.
#define DAP_JTAG_DEV_CNT      0               ///< Maximum number of JTAG devices on scan chain

/// Default communication mode on the Debug Access Port.
/// Used for the command \ref DAP_Connect when Port Default mode is selected.
#define DAP_DEFAULT_PORT      1               ///< Default JTAG/SWJ Port Mode: 1 = SWD, 2 = JTAG.

/// Default communication speed on the Debug Access Port for SWD and JTAG mode.
/// Used to initialize the default SWD/JTAG clock frequency.
/// The command \ref DAP_SWJ_Clock can be used to overwrite this default setting.
#define DAP_DEFAULT_SWJ_CLOCK 5000000         ///< Default SWD/JTAG clock frequency in Hz.

/// Maximum Package Size for Command and Response data.
/// This configuration settings is used to optimized the communication performance with the
/// debugger and depends on the USB peripheral. Change setting to 1024 for High-Speed USB.
#define DAP_PACKET_SIZE       64              ///< USB: 64 = Full-Speed, 1024 = High-Speed.

/// Maximum Package Buffers for Command and Response data.
/// This configuration settings is used to optimized the communication performance with the
/// debugger and depends on the USB peripheral. For devices with limited RAM or USB buffer the
/// setting can be reduced (valid range is 1 .. 255). Change setting to 4 for High-Speed USB.
#define DAP_PACKET_COUNT      1              ///< Buffers: 64 = Full-Speed, 4 = High-Speed.

/// Indicate that UART Serial Wire Output (SWO) trace is available.
/// This information is returned by the command \ref DAP_Info as part of <b>Capabilities</b>.
#define SWO_UART                0               ///< SWO UART:  1 = available, 0 = not available

/// Maximum SWO UART Baudrate
#define SWO_UART_MAX_BAUDRATE   10000000U       ///< SWO UART Maximum Baudrate in Hz

/// Indicate that Manchester Serial Wire Output (SWO) trace is available.
/// This information is returned by the command \ref DAP_Info as part of <b>Capabilities</b>.
#define SWO_MANCHESTER          0               ///< SWO Manchester:  1 = available, 0 = not available

/// SWO Trace Buffer Size.
#define SWO_BUFFER_SIZE         4096U           ///< SWO Trace Buffer Size in bytes (must be 2^n)

/// SWO Streaming Trace.
#define SWO_STREAM              0               ///< SWO Streaming Trace: 1 = available, 0 = not available.

/// Clock frequency of the Test Domain Timer. Timer value is returned with \ref TIMESTAMP_GET.
#define TIMESTAMP_CLOCK         1000000U      ///< Timestamp clock in Hz (0 = timestamps not supported).


/// Debug Unit is connected to fixed Target Device.
/// The Debug Unit may be part of an evaluation board and always connected to a fixed
/// known device.  In this case a Device Vendor and Device Name string is stored which
/// may be used by the debugger or IDE to configure device parameters.
#define TARGET_DEVICE_FIXED   0               ///< Target Device: 1 = known, 0 = unknown;

#if TARGET_DEVICE_FIXED
#define TARGET_DEVICE_VENDOR  ""              ///< String indicating the Silicon Vendor
#define TARGET_DEVICE_NAME    ""              ///< String indicating the Target Device
#endif

///@}


// LPC43xx peripheral register bit masks (used by macros)
#define CCU_CLK_CFG_RUN       (1UL << 0)
#define CCU_CLK_CFG_AUTO      (1UL << 1)
#define CCU_CLK_STAT_RUN      (1UL << 0)

// State of Reset Ouput Enable buffer
extern BOOL gpio_reset_pin_is_input;

// Debug Port I/O Pins

// SWCLK Pin                  P1_3:  GPIO0[10] (0)
#define PORT_SWCLK            0
#define PIN_SWCLK_IN_BIT      10
#define PIN_SWCLK             (1<<PIN_SWCLK_IN_BIT)

// SWCLK Output Enable Pin    P1_13: GPIO1[16] (0)
#define PORT_SWCLK_TXE        1
#define PIN_SWCLK_TXE_IN_BIT  16
#define PIN_SWCLK_TXE         (1<<PIN_SWCLK_TXE_IN_BIT)

// SWDIO Pin                  P1_1:  GPIO0[8]  (0)
#define PORT_SWDIO            0
#define PIN_SWDIO_IN_BIT      8
#define PIN_SWDIO             (1<<PIN_SWDIO_IN_BIT)

// SWDIO Output Enable Pin    P1_17: GPIO0[12] (0)
#define PORT_SWDIO_TXE        0
#define PIN_SWDIO_TXE_IN_BIT  12
#define PIN_SWDIO_TXE         (1<<PIN_SWDIO_TXE_IN_BIT)

// nRESET Pin                 P2_1: GPIO5[1] (4)
#define PORT_nRESET           5
#define PIN_nRESET_IN_BIT     1
#define PIN_nRESET            (1<<PIN_nRESET_IN_BIT)

// nRESET Output Enable Pin   P1_20: GPIO0[15] (0) Not Used
#define PORT_RESET_TXE        0
#define PIN_RESET_TXE_IN_BIT  15
#define PIN_RESET_TXE         (1<<PIN_RESET_TXE_IN_BIT)

// ISP Control Pin          P2_11:  GPIO1[11]
#define ISPCTRL_PORT        1
#define ISPCTRL_BIT         11

// LED0 Green: Target & USB Running      P2_3: GPIO5[3] (4)
#define PORT_LED_RUN          5
#define PORT_LED_RUN_BIT      3
#define PIN_LED_RUN           (1<<PORT_LED_RUN_BIT)

// LED1 Blue: Target Connected     P2_4: GPIO5[4] (4)
#define PORT_LED_CNTD         5
#define PIN_LED_CNTD_BIT      4
#define PIN_LED_CNTD          (1<<PIN_LED_CNTD_BIT)

#define X_SET(str)     LPC_GPIO_PORT->SET[PORT_##str] = PIN_##str
#define X_CLR(str)     LPC_GPIO_PORT->CLR[PORT_##str] = PIN_##str
#define X_DIR_OUT(str) LPC_GPIO_PORT->DIR[PORT_##str] |= (PIN_##str)
#define X_DIR_IN(str)  LPC_GPIO_PORT->DIR[PORT_##str] &= ~(PIN_##str)
#define X_BYTE(str)    LPC_GPIO_PORT->B[(PORT_##str << 5) + PIN_##str##_IN_BIT]


//**************************************************************************************************
/**
\defgroup DAP_Config_PortIO_gr CMSIS-DAP Hardware I/O Pin Access
\ingroup DAP_ConfigIO_gr
@{

Standard I/O Pins of the CMSIS-DAP Hardware Debug Port support standard JTAG mode
and Serial Wire Debug (SWD) mode. In SWD mode only 2 pins are required to implement the debug
interface of a device. The following I/O Pins are provided:

JTAG I/O Pin                 | SWD I/O Pin          | CMSIS-DAP Hardware pin mode
---------------------------- | -------------------- | ---------------------------------------------
TCK: Test Clock              | SWCLK: Clock         | Output Push/Pull
TMS: Test Mode Select        | SWDIO: Data I/O      | Output Push/Pull; Input (for receiving data)
TDI: Test Data Input         |                      | Output Push/Pull
TDO: Test Data Output        |                      | Input
nTRST: Test Reset (optional) |                      | Output Open Drain with pull-up resistor
nRESET: Device Reset         | nRESET: Device Reset | Output Open Drain with pull-up resistor


DAP Hardware I/O Pin Access Functions
-------------------------------------
The various I/O Pins are accessed by functions that implement the Read, Write, Set, or Clear to
these I/O Pins.

For the SWDIO I/O Pin there are additional functions that are called in SWD I/O mode only.
This functions are provided to achieve faster I/O that is possible with some advanced GPIO
peripherals that can independently write/read a single I/O pin without affecting any other pins
of the same I/O port. The following SWDIO I/O Pin functions are provided:
 - \ref PIN_SWDIO_OUT_ENABLE to enable the output mode from the DAP hardware.
 - \ref PIN_SWDIO_OUT_DISABLE to enable the input mode to the DAP hardware.
 - \ref PIN_SWDIO_IN to read from the SWDIO I/O pin with utmost possible speed.
 - \ref PIN_SWDIO_OUT to write to the SWDIO I/O pin with utmost possible speed.
*/


// Configure DAP I/O pins ------------------------------

/** Setup JTAG I/O pins: TCK, TMS, TDI, TDO, nTRST, and nRESET.
Configures the DAP Hardware I/O pins for JTAG mode:
 - TCK, TMS, TDI, nTRST, nRESET to output mode and set to high level.
 - TDO to input mode.
*/
__STATIC_INLINE void PORT_JTAG_SETUP(void) {}

/** Setup SWD I/O pins: SWCLK, SWDIO, and nRESET.
Configures the DAP Hardware I/O pins for Serial Wire Debug (SWD) mode:
 - SWCLK, SWDIO, nRESET to output mode and set to default high level.
 - TDI, TMS, nTRST to HighZ mode (pins are unused in SWD mode).
*/
__STATIC_INLINE void PORT_SWD_SETUP(void)
{
    X_SET(SWCLK);
    X_SET(SWDIO);
    X_DIR_OUT(SWCLK);
    X_DIR_OUT(SWDIO);
    
    X_SET(SWCLK_TXE);
    X_DIR_OUT(SWCLK_TXE);
    X_SET(SWDIO_TXE);
    X_DIR_OUT(SWDIO_TXE);
}


/** Disable JTAG/SWD I/O Pins.
Disables the DAP Hardware I/O pins which configures:
 - TCK/SWCLK, TMS/SWDIO, TDI, TDO, nTRST, nRESET to High-Z mode.
*/
__STATIC_INLINE void PORT_OFF(void)
{
    X_CLR(SWCLK);
    X_CLR(SWDIO);
    X_DIR_OUT(SWCLK);
    X_DIR_OUT(SWDIO);
    
    X_SET(SWCLK_TXE);
    X_DIR_OUT(SWCLK_TXE);
    X_SET(SWDIO_TXE);
    X_DIR_OUT(SWDIO_TXE);
}


// SWCLK/TCK I/O pin -------------------------------------

/** SWCLK/TCK I/O pin: Get Input.
\return Current status of the SWCLK/TCK DAP hardware I/O pin.
*/
__STATIC_FORCEINLINE uint32_t PIN_SWCLK_TCK_IN(void)
{
    return (0);   // Not available
}

/** SWCLK/TCK I/O pin: Set Output to High.
Set the SWCLK/TCK DAP hardware I/O pin to high level.
*/
__STATIC_FORCEINLINE void     PIN_SWCLK_TCK_SET(void)
{
    X_SET(SWCLK);
}

/** SWCLK/TCK I/O pin: Set Output to Low.
Set the SWCLK/TCK DAP hardware I/O pin to low level.
*/
__STATIC_FORCEINLINE void     PIN_SWCLK_TCK_CLR(void)
{
    X_CLR(SWCLK);
}


// SWDIO/TMS Pin I/O --------------------------------------

/** SWDIO/TMS I/O pin: Get Input.
\return Current status of the SWDIO/TMS DAP hardware I/O pin.
*/
__STATIC_FORCEINLINE uint32_t PIN_SWDIO_TMS_IN(void)
{
    return X_BYTE(SWDIO) & 0x1;
}

/** SWDIO/TMS I/O pin: Set Output to High.
Set the SWDIO/TMS DAP hardware I/O pin to high level.
*/
__STATIC_FORCEINLINE void     PIN_SWDIO_TMS_SET(void)
{
    X_SET(SWDIO);
}

/** SWDIO/TMS I/O pin: Set Output to Low.
Set the SWDIO/TMS DAP hardware I/O pin to low level.
*/
__STATIC_FORCEINLINE void     PIN_SWDIO_TMS_CLR(void)
{
    X_CLR(SWDIO);
}

/** SWDIO I/O pin: Get Input (used in SWD mode only).
\return Current status of the SWDIO DAP hardware I/O pin.
*/
__STATIC_FORCEINLINE uint32_t PIN_SWDIO_IN(void)
{
    return X_BYTE(SWDIO) & 0x1;
}

/** SWDIO I/O pin: Set Output (used in SWD mode only).
\param bit Output value for the SWDIO DAP hardware I/O pin.
*/
__STATIC_FORCEINLINE void     PIN_SWDIO_OUT(uint32_t bit)
{
    if (bit & 0x1) {
        X_SET(SWDIO);
    } else {
        X_CLR(SWDIO);
    }
}

/** SWDIO I/O pin: Switch to Output mode (used in SWD mode only).
Configure the SWDIO DAP hardware I/O pin to output mode. This function is
called prior \ref PIN_SWDIO_OUT function calls.
*/
__STATIC_FORCEINLINE void     PIN_SWDIO_OUT_ENABLE(void)
{
    X_SET(SWDIO_TXE);
    X_DIR_OUT(SWDIO);
}

/** SWDIO I/O pin: Switch to Input mode (used in SWD mode only).
Configure the SWDIO DAP hardware I/O pin to input mode. This function is
called prior \ref PIN_SWDIO_IN function calls.
*/
__STATIC_FORCEINLINE void     PIN_SWDIO_OUT_DISABLE(void)
{
    X_DIR_IN(SWDIO);
    X_CLR(SWDIO_TXE);
}


// TDI Pin I/O ---------------------------------------------

/** TDI I/O pin: Get Input.
\return Current status of the TDI DAP hardware I/O pin.
*/
__STATIC_FORCEINLINE uint32_t PIN_TDI_IN(void)
{
    return (0);   // Not available
}

/** TDI I/O pin: Set Output.
\param bit Output value for the TDI DAP hardware I/O pin.
*/
__STATIC_FORCEINLINE void     PIN_TDI_OUT(uint32_t bit)
{
    ;             // Not available
}


// TDO Pin I/O ---------------------------------------------

/** TDO I/O pin: Get Input.
\return Current status of the TDO DAP hardware I/O pin.
*/
__STATIC_FORCEINLINE uint32_t PIN_TDO_IN(void)
{
    return (0);   // Not available
}


// nTRST Pin I/O -------------------------------------------

/** nTRST I/O pin: Get Input.
\return Current status of the nTRST DAP hardware I/O pin.
*/
__STATIC_FORCEINLINE uint32_t PIN_nTRST_IN(void)
{
    return (0);   // Not available
}

/** nTRST I/O pin: Set Output.
\param bit JTAG TRST Test Reset pin status:
           - 0: issue a JTAG TRST Test Reset.
           - 1: release JTAG TRST Test Reset.
*/
__STATIC_FORCEINLINE void     PIN_nTRST_OUT(uint32_t bit)
{
    ;             // Not available
}

// nRESET Pin I/O------------------------------------------

/** nRESET I/O pin: Get Input.
\return Current status of the nRESET DAP hardware I/O pin.
*/
__STATIC_FORCEINLINE uint32_t PIN_nRESET_IN(void)
{
    if (gpio_reset_pin_is_input) {
        return X_BYTE(nRESET) & 0x1;
    } else {
        return 0; // Always LOW when output
    }
}

/** nRESET I/O pin: Set Output.
\param bit target device hardware reset pin status:
           - 0: issue a device hardware reset.
           - 1: release device hardware reset.
*/
__STATIC_FORCEINLINE void     PIN_nRESET_OUT(uint32_t bit)
{
    if (bit) {
        // release device hardware reset. (reset INPUT, reset oe LOW=INPUT)
        X_DIR_IN(nRESET);
        X_CLR(RESET_TXE);
        gpio_reset_pin_is_input = __TRUE;
        LPC_GPIO_PIN_INT->IST = 0x01;    // ACK any pending edge interrupt
        LPC_GPIO_PIN_INT->SIENF |= 0x1;  // Enable falling edge interrupt
    } else {
        // issue a device hardware reset. (reset OUTPUT+LOW, reset oe HIGH=OUTPUT)
        gpio_reset_pin_is_input = __FALSE;
        LPC_GPIO_PIN_INT->CIENF |= 0x1;  // Disable falling edge interrupt
        LPC_GPIO_PIN_INT->IST = 0x01;    // ACK any pending edge interrupt
        X_SET(RESET_TXE);
        X_CLR(nRESET);
        X_DIR_OUT(nRESET);
    }
}

///@}


//**************************************************************************************************
/**
\defgroup DAP_Config_LEDs_gr CMSIS-DAP Hardware Status LEDs
\ingroup DAP_ConfigIO_gr
@{

CMSIS-DAP Hardware may provide LEDs that indicate the status of the CMSIS-DAP Debug Unit.

It is recommended to provide the following LEDs for status indication:
 - Connect LED: is active when the DAP hardware is connected to a debugger.
 - Running LED: is active when the debugger has put the target device into running state.
*/

/** Debug Unit: Set status of Connected LED.
\param bit status of the Connect LED.
           - 1: Connect LED ON: debugger is connected to CMSIS-DAP Debug Unit.
           - 0: Connect LED OFF: debugger is not connected to CMSIS-DAP Debug Unit.
*/
__STATIC_INLINE void LED_CONNECTED_OUT(uint32_t bit)
{
    if (bit & 0x1) {
        X_CLR(LED_CNTD);
    } else {
        X_SET(LED_CNTD);
    }
}

/** Debug Unit: Set status Target Running LED.
\param bit status of the Target Running LED.
           - 1: Target Running LED ON: program execution in target started.
           - 0: Target Running LED OFF: program execution in target stopped.
*/
__STATIC_INLINE void LED_RUNNING_OUT(uint32_t bit)
{
    if (bit & 0x1) {
        X_CLR(LED_RUN);
    } else {
        X_SET(LED_RUN);
    }
}

///@}


//**************************************************************************************************
/**
\defgroup DAP_Config_Timestamp_gr CMSIS-DAP Timestamp
\ingroup DAP_ConfigIO_gr
@{
Access function for Test Domain Timer.

The value of the Test Domain Timer in the Debug Unit is returned by the function \ref TIMESTAMP_GET. By
default, the DWT timer is used.  The frequency of this timer is configured with \ref TIMESTAMP_CLOCK.

*/

/** Get timestamp of Test Domain Timer.
\return Current timestamp value.
*/
__STATIC_INLINE uint32_t TIMESTAMP_GET (void) {
  return (DWT->CYCCNT) / (CPU_CLOCK / TIMESTAMP_CLOCK);
}

///@}


//**************************************************************************************************
/**
\defgroup DAP_Config_Initialization_gr CMSIS-DAP Initialization
\ingroup DAP_ConfigIO_gr
@{

CMSIS-DAP Hardware I/O and LED Pins are initialized with the function \ref DAP_SETUP.
*/

/** Setup of the Debug Unit I/O pins and LEDs (called when Debug Unit is initialized).
This function performs the initialization of the CMSIS-DAP Hardware I/O Pins and the
Status LEDs. In detail the operation of Hardware I/O and LED pins are enabled and set:
 - I/O clock system enabled.
 - all I/O pins: input buffer enabled, output pins are set to HighZ mode.
 - for nTRST, nRESET a weak pull-up (if available) is enabled.
 - LED output pins are enabled and LEDs are turned off.
*/
__STATIC_INLINE void DAP_SETUP(void)
{
    /* Enable clock and init GPIO outputs */
    LPC_CCU1->CLK_M4_GPIO_CFG = CCU_CLK_CFG_AUTO | CCU_CLK_CFG_RUN;

    while (!(LPC_CCU1->CLK_M4_GPIO_STAT & CCU_CLK_STAT_RUN));

    /* Configure I/O pins: function number, input buffer enabled,    */
    /*                     no pull-up/down                           */
    scu_pinmux(1,  3, GPIO_NOPULL, FUNC0);   /* SWCLK/TCK: GPIO0[10] */
    scu_pinmux(1, 13, GPIO_NOPULL, FUNC0);   /* SWCLK_OE:  GPIO1[16]  */
    scu_pinmux(1,  1, GPIO_NOPULL, FUNC0);   /* SWDIO/TMS: GPIO0[8]  */
    scu_pinmux(1, 17, GPIO_NOPULL, FUNC0);   /* SWDIO_OE:  GPIO1[8]  */
    
    /* LED */
    scu_pinmux(2,  3, GPIO_NOPULL, FUNC4);   /* LED-Green  */
    scu_pinmux(2,  4, GPIO_NOPULL, FUNC4);   /* LED-Blue   */
    
    /* swd clock output enable default */
    X_SET(SWCLK_TXE);
}

/** Reset Target Device with custom specific I/O pin or command sequence.
This function allows the optional implementation of a device specific reset sequence.
It is called when the command \ref DAP_ResetTarget and is for example required
when a device needs a time-critical unlock sequence that enables the debug port.
\return 0 = no device specific reset sequence is implemented.\n
        1 = a device specific reset sequence is implemented.
*/
__STATIC_INLINE uint32_t RESET_TARGET(void)
{
    return (0);              // change to '1' when a device reset sequence is implemented
}

///@}


#endif /* __DAP_CONFIG_H__ */
