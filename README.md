# Control Hampton Bay/Harbor Breeze fans with a ESP8266

First of all, I am not a programmer use at your own risk.

If you need the codes for different dip switch settings let me know and when I have time I will upload them. Also if see ways to improve the code let me know.

As of now i have added the following dip switch settings.
0000, 0001, 0010, 0011, 0100, 1011, 1100, 1110, 1111.

This provides a way to control your Hampton Bay/ Harbour Breeze fans with Hubitat as of right now it only works with RF fan controls that this remote FCC ID: CHQ8BT7096T  my remotes did not have the forward/reverse button so I did not record those commands. If your controller has this chip https://www.radiolocman.com/datasheet/data.html?di=71835&/HT48R31-28SDIP-B-0 this setup may work for you.

Parts that you are going to need are.
1. ESP8266
2. Soldering Iron
3. Wire small gauge
4. One circuit board https://www.ebay.com/itm/315-433-868Mhz-DC-3-12V-1-3-9V-ASK-Wireless-Transmitter-f-Arduino-ARM-AVR-Alarm/172856439299?ssPageName=STRK%3AMEBIDX%3AIT&var=471637974549&_trksid=p2057872.m2749.l2649
5. SAW Resonator 303.875Mhz https://www.ebay.com/itm/10PCS-303-875M-303-875MHz-R303A-SAW-Resonator-Crystals-TO-39/361312062608?ssPageName=STRK%3AMEBIDX%3AIT&_trksid=p2057872.m2749.l2649

You will have to unsolder the 315Mhz SAW that comes with the circuit board and solder on the 303.875Mhz SAW.

Wire IAW drawing below, if you want you cut a piece of wire approximately 9.25 inches for an antenna
https://github.com/Quiqui64/HubitatFanRemote/blob/master/Fan_bb.jpg


Software.

1. Arduino IDE https://www.arduino.cc/en/main/software
2. ESP8266 Library https://randomnerdtutorials.com/how-to-install-esp8266-board-arduino-ide/
3. IRremoteESP8266 https://github.com/crankyoldgit/IRremoteESP8266
4. Download the fan.ino file, open it with the Ardunio IDE.
5. Add you ssid and password to sketch.
6. Upload the sketch to the ESP8266 and note the IP address in the serial monitor.
7. Add these two drivers to Hubitat and creat a virtual fan and light                        https://github.com/Quiqui64/HubitatFanRemote/blob/master/VirtualHamptonBayLight.groovy
 https://github.com/Quiqui64/HubitatFanRemote/blob/master/VirtualHamptonBayFan.groovy
 Here are instructions how to add a custom driver to Hubitat https://docs.hubitat.com/index.php?title=How_to_Install_Custom_Drivers
8. Then on your devices under Preferences add your IP address and dip switch settings. i.e. http://192.168.1.4/1010 the last for digits are your dip switch settings i.e. Up,Down,Up,Down = 1010.


Website to look up FCC ID https://www.fcc.gov/oet/ea/fccid

Website for IRscrutinizer http://www.harctoolbox.org/

Where to down load IRscrutinizer https://github.com/bengtmartensson/harctoolboxbundle/releases/tag/Version-2.1.0
