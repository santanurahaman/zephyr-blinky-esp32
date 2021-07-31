# zephyr-blinky-esp32
Zephyr OS LED blinking application for ESP32 using devicetree overlay to define the GPIO port.

## Build & Flash the Example
Run the below command inside the example folder
``` Bash
west build -b esp32 .
west flash --esp-device /dev/ttyUSB0
```

## Update LED Port
The LED IO port can be changed in *boards/esp32.overlay* file - 
<&gpio0 __IO-PORT__ GPIO_ACTIVE_HIGH>; 