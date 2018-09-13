# ClockClock
---
## Features
* Daylight alarm via led strip will start to brighten 15 minutes before scheduled alarm time
* Bed Shaker will start 1 minute before scheduled alarm time
* Buzzer will start at scheduled alarm time
* Alarm finishes one minute after scheduled alarm time
* WiFi setup/config is provided by the amazing WiFi Config lib at [https://github.com/tzapu/WiFiManager](https://github.com/tzapu/WiFiManager)
## Hardware
Currently this is being developed on a wemos D1 and a 128x64 OLED display
![PCB](/meta/pcb.jpg)
![3dtop](/meta/3d_top.jpg)
![32angle](/meta/3d_angle.jpg)
### More Info
Time is kept in sync via NTP lib at [https://github.com/PaulStoffregen/Time](https://github.com/PaulStoffregen/Time)
Timezone/Daylight savings time are handled via TimeZone lib at [https://github.com/JChristensen/Timezone](https://github.com/JChristensen/Timezone)