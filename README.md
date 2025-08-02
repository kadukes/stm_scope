
# STM Scope

A tiny oscilloscope written for the STM32F429I board using FreeRTOS. 

## Getting Started

Build and flash the project on your board by

```
source env.sh
mkdir build
cd build
cmake ..
make
make flash
```

## Flashing in WSL

To attach the board to your wsl session, run the following in a Windows terminal with administrator privileges: 

```
usbipd list
usbipd bind --busid <busid>
usbipd attach --wsl --busid <busid>
```
