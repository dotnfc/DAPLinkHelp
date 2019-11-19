# STM32F072 HIC for DAPLink Build Guide

## 1. GPIOs used by this hic
### 1.1 LED
HID/CDC/MSC => PA0
### 1.2 SWD
```bash
SWD_DAT => PA4
SWD_CLK => PA2
SWD_NRST=> PA1
SWD_SWO => PA3  (RFU, not implemented yet)
BTN     => PB6  (to config hic in vmsd mode)
```
### 1.3 USART
```bash
RTS     => PA6  (RFU, not implemented yet)
CTS     => PA7  (RFU, not implemented yet)
DTR     => PA8  (RFU, not implemented yet)
TX      => PA9
RX      => PA10

**see IO_Config.h for detail**
```
## 2. How to test

### 2.1 Make sure the following lines within your projects.yaml
```xml
module:
    hic_stm32f072cb: &module_hic_stm32f072cb
        - records/rtos/rtos-cm0.yaml
        - records/hic_hal/stm32f072cb.yaml
```
### 2.2 Add  your target in projects.yaml like:
```xml
projects:
    stm32f072cb_stm32f103rb_if:
        - *module_if
        - *module_hic_stm32f072cb
        - records/board/stm32f103rb.yaml
```
### 2.3 Generate Keil MDK project file
Follow the 'DAPLink Developers Guide' to generate mdk project or makefile,
see 'docs/DEVELOPERS-GUIDE.md'
```bash
# for keil mdk project
progen generate -f projects.yaml -p stm32f072cb_stm32f103rb_if -t uvision

# for armcc makefile
progen generate -f projects.yaml -p stm32f072cb_stm32f103rb_if -t make_armcc
```
### 2.4 build from keil mdk
launch stm32f072cb_stm32f103rb_if.uvprojx 

### 2.5 build from makefile
for make.exe, size.exe
> * install mingw binutils from https://osdn.net/projects/mingw/releases/
> * or get them from devc++ package. 
> * set your mdk armcc bin path, and mingw bin path
> * make and go.

### 2.6 Note for DFU upgrade of STM32F072
> * you can use F072 IAP (USB DFU) to download the daplink firmware to HIC, see
 https://github.com/dotnfc/DFUCmd.
> * or try stm32cube programmer to load daplink fw (recommended):
 https://blog.st.com/stlink-v3set-in-circuit-debugger-programmer/.

<br />
---
by dotnfc@163.com, 2018/09/01£¬ 2019/11/17

