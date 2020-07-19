/**
 *  Hampton Bay Fan
 * 
 *  Copyright 2019 Jason Brown
 *  This made to me used with IRremoteESP8266 Version 2.7.0
 *  
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except
 *  in compliance with the License. You may obtain a copy of the License at:
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software distributed under the License is distributed
 *  on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License
 *  for the specific language governing permissions and limitations under the License.
 *
 */
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Arduino.h> // For RF Tansmitter
#include <IRremoteESP8266.h> // For RF Tansmitter
#include <IRsend.h> // For RF Tansmitter
#include <EEPROM.h>

ESP8266WebServer server;
const char* ssid = ""; // your router login mame
const char* password = ""; // your router password
const uint16_t kIrLed = 12;  // ESP8266 GPIO pin 12 (D6) output.
IRsend irsend(kIrLed);  // Set the GPIO to be used to sending the message.
const int IRrepeat = 30; // Number times to transmit signal

void setup()
{
  Serial.begin(115200);
  EEPROM.begin(512);
  setupEEPROM(); // Checks to see if any values are saved to EEPROM
  irsend.begin();// For the RF transmiter
  WiFi.begin(ssid,password);
  while(WiFi.status()!=WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  server.on("/0000",set0000);
  server.on("/0001",set0001);
  server.on("/0010",set0010);
  server.on("/0011",set0011);
  server.on("/0100",set0100);
  server.on("/0101",set0101);
  server.on("/0110",set0110);
  server.on("/0111",set0111);
  server.on("/1000",set1000);
  server.on("/1001",set1001);
  server.on("/1010",set1010);
  server.on("/1011",set1011);
  server.on("/1100",set1100);
  server.on("/1110",set1110);
  server.on("/1111",set1111);
  server.begin();
}

void loop()
{
  server.handleClient();
}

// If this is the first time the program has been run it saves all the fan and light variables in the EEPROM to off.
void setupEEPROM(){
  if(EEPROM.read(0) == 255){
    writeString(0, "off");
    writeString(5, "off");
    writeString(10, "off");
    writeString(15, "off");
    writeString(20, "off");
    writeString(25, "off");
    writeString(30, "off");
    writeString(35, "off");
    writeString(40, "off");
    writeString(45, "off");
    writeString(50, "off");
    writeString(55, "off");
    writeString(60, "off");
    writeString(65, "off");
    writeString(70, "off");
    writeString(75, "off");
    writeString(80, "off");
    writeString(85, "off");
    writeString(90, "off");
    writeString(95, "off");
    writeString(100, "off");
    writeString(105, "off");
    writeString(110, "off");
    writeString(115, "off");
    writeString(120, "off");
    writeString(125, "off");
    writeString(130, "off");
    writeString(135, "off");
    writeString(140, "off");
    writeString(145, "off");
    writeString(150, "off");
    writeString(155, "off");
  }
}

void writeString(char add,String data)
{
  int _size = data.length();
  int i;
  for(i=0;i<_size;i++)
  {
    EEPROM.write(add+i,data[i]);
  }
  EEPROM.write(add+_size,'\0');   //Add termination null character for String Data
  EEPROM.commit();
}
 
 
String read_String(char add)
{
  int i;
  char data[100]; //Max 100 Bytes
  int len=0;
  unsigned char k;
  k=EEPROM.read(add);
  while(k != '\0' && len<500)   //Read until null character
  {    
    k=EEPROM.read(add+len);
    data[len]=k;
    len++;
  }
  data[len]='\0';
  return String(data);
}

void sendRAW_Flash(const unsigned int * signalArray, unsigned int signalLength, unsigned char carrierFreq) {
  irsend.enableIROut(carrierFreq); //initialise the carrier frequency for each signal to be sent 
  for (unsigned int i=0;i<signalLength;i++){
    //tmp=pgm_read_word_near(&signalArray[i]);
   // tmp=cleanPanasonic(tmp); //not needed
    if (i & 1) irsend.space(pgm_read_word_near(&signalArray[i]));
    else irsend.mark(pgm_read_word_near(&signalArray[i]));
  }
  irsend.space(1);//make sure IR is turned off at end of signal
}

void set0000()
{  
//FAN CHQ8BT7096T DIP SWITCHES DN,DN,DN,DN OR 0000
static const unsigned int lightOffFanOff[] PROGMEM = {330,330,662,330,662,330,662,662,330,662,330,662,330,662,330,330,662,330,662,330,662,330,662,330,662,330,662,330,662,330,662,330,662,330,662,662,330,662,330,662,330,662,330,10028};
static const unsigned int lightOffFanLow[] PROGMEM = {330,330,663,330,663,330,663,663,330,663,330,663,330,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,663,330,330,663,10020};
static const unsigned int lightOffFanMed[] PROGMEM = {330,330,663,330,663,330,663,663,330,663,330,663,330,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,663,330,10043};
static const unsigned int lightOffFanHigh[] PROGMEM = {330,330,663,330,663,330,663,663,330,663,330,663,330,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,10046};
static const unsigned int light20FanOff[] PROGMEM = {331,331,662,331,662,331,662,662,331,662,331,662,331,662,331,331,662,662,331,331,662,662,331,331,662,331,662,662,331,331,662,331,662,331,662,662,331,662,331,331,662,662,331,10047};
static const unsigned int light20FanLow[] PROGMEM = {330,330,662,330,662,330,662,662,330,662,330,662,330,662,330,330,662,662,330,330,662,662,330,330,662,330,662,662,330,662,330,662,330,330,662,330,662,330,662,330,662,330,662,10032};
static const unsigned int light20FanMed[] PROGMEM = {331,331,662,331,662,331,662,662,331,662,331,662,331,662,331,331,662,662,331,331,662,662,331,331,662,331,662,662,331,662,331,331,662,331,662,662,331,662,331,662,331,662,331,10047};
static const unsigned int light20FanHigh[] PROGMEM = {331,331,662,331,662,331,662,662,331,662,331,662,331,662,331,331,662,662,331,331,662,662,331,331,662,331,662,662,331,331,662,662,331,331,662,662,331,662,331,662,331,331,662,10047};
static const unsigned int light30FanOff[] PROGMEM = {330,330,663,330,663,330,663,663,330,663,330,663,330,663,330,330,663,663,330,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,10034};
static const unsigned int light30FanLow[] PROGMEM = {331,331,662,331,662,331,662,662,331,662,331,662,331,662,331,331,662,662,331,331,662,331,662,662,331,331,662,331,662,662,331,662,331,331,662,662,331,331,662,662,331,662,331,10049};
static const unsigned int light30FanMed[] PROGMEM = {330,330,662,330,662,330,662,662,330,662,330,662,330,662,330,330,662,662,330,330,662,330,662,662,330,330,662,330,662,662,330,330,662,330,662,662,330,330,662,662,330,330,662,10045};
static const unsigned int light30FanHigh[] PROGMEM = {330,330,662,330,662,330,662,662,330,662,330,662,330,662,330,330,662,662,330,330,662,330,662,662,330,330,662,330,662,330,662,662,330,330,662,662,330,330,662,330,662,662,330,10030};
static const unsigned int light40FanOff[] PROGMEM = {331,331,662,331,662,331,662,662,331,662,331,662,331,662,331,331,662,331,662,662,331,662,331,662,331,662,331,662,331,331,662,331,662,331,662,331,662,331,662,662,331,331,662,10041};
static const unsigned int light40FanLow[] PROGMEM = {331,331,661,331,661,331,661,661,331,661,331,661,331,661,331,331,661,331,661,661,331,661,331,661,331,661,331,661,331,661,331,661,331,331,661,331,661,661,331,331,661,661,331,10052};
static const unsigned int light40FanMed[] PROGMEM = {331,331,662,331,662,331,662,662,331,662,331,662,331,662,331,331,662,331,662,662,331,662,331,662,331,662,331,662,331,662,331,331,662,331,662,331,662,662,331,331,662,331,662,10047};
static const unsigned int light40FanHigh[] PROGMEM = {331,331,662,331,662,331,662,662,331,662,331,662,331,662,331,331,662,331,662,662,331,662,331,662,331,662,331,662,331,331,662,662,331,331,662,331,662,331,662,662,331,662,331,10053};
static const unsigned int light50FanOff[] PROGMEM = {331,331,662,331,662,331,662,662,331,662,331,662,331,662,331,331,662,331,662,662,331,662,331,331,662,662,331,331,662,331,662,331,662,331,662,662,331,662,331,331,662,662,331,10043};
static const unsigned int light50FanLow[] PROGMEM = {330,330,662,330,662,330,662,662,330,662,330,662,330,662,330,330,662,330,662,662,330,662,330,330,662,662,330,330,662,662,330,662,330,330,662,330,662,330,662,330,662,330,662,10036};
static const unsigned int light50FanMed[] PROGMEM = {331,331,662,331,662,331,662,662,331,662,331,662,331,662,331,331,662,331,662,662,331,662,331,331,662,662,331,331,662,662,331,331,662,331,662,662,331,662,331,662,331,662,331,10055};
static const unsigned int light50FanHigh[] PROGMEM = {331,331,662,331,662,331,662,662,331,662,331,662,331,662,331,331,662,331,662,662,331,662,331,331,662,662,331,331,662,331,662,662,331,331,662,662,331,662,331,662,331,331,662,10052};
static const unsigned int light60FanOff[] PROGMEM = {330,330,662,330,662,330,662,662,330,662,330,662,330,662,330,330,662,330,662,662,330,330,662,662,330,330,662,662,330,330,662,330,662,330,662,662,330,330,662,330,662,330,662,10043};
static const unsigned int light60FanLow[] PROGMEM = {331,331,662,331,662,331,662,662,331,662,331,662,331,662,331,331,662,331,662,662,331,331,662,662,331,331,662,662,331,662,331,662,331,331,662,662,331,331,662,662,331,662,331,10034};
static const unsigned int light60FanMed[] PROGMEM = {331,331,662,331,662,331,662,662,331,662,331,662,331,662,331,331,662,331,662,662,331,331,662,662,331,331,662,662,331,662,331,331,662,331,662,662,331,331,662,662,331,331,662,10047};
static const unsigned int light60FanHigh[] PROGMEM = {331,331,662,331,662,331,662,662,331,662,331,662,331,662,331,331,662,331,662,662,331,331,662,662,331,331,662,662,331,331,662,662,331,331,662,662,331,331,662,331,662,662,331,10039};
static const unsigned int light70FanOff[] PROGMEM = {330,330,663,330,663,330,663,663,330,663,330,663,330,663,330,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,10036};
static const unsigned int light70FanLow[] PROGMEM = {330,330,662,330,662,330,662,662,330,662,330,662,330,662,330,330,662,330,662,662,330,330,662,330,662,330,662,330,662,662,330,662,330,330,662,330,662,662,330,662,330,330,662,10047};
static const unsigned int light70FanMed[] PROGMEM = {330,330,662,330,662,330,662,662,330,662,330,662,330,662,330,330,662,330,662,662,330,330,662,330,662,330,662,330,662,662,330,330,662,330,662,330,662,662,330,330,662,662,330,10028};
static const unsigned int light70FanHigh[] PROGMEM = {330,330,663,330,663,330,663,663,330,663,330,663,330,663,330,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,663,330,330,663,330,663,10036};
static const unsigned int light80FanOff[] PROGMEM = {331,331,662,331,662,331,662,662,331,662,331,662,331,662,331,331,662,331,662,331,662,662,331,331,662,662,331,662,331,331,662,331,662,331,662,662,331,662,331,331,662,662,331,10032};
static const unsigned int light80FanLow[] PROGMEM = {330,330,662,330,662,330,662,662,330,662,330,662,330,662,330,330,662,330,662,330,662,662,330,330,662,662,330,662,330,662,330,662,330,330,662,330,662,330,662,330,662,330,662,10029};
static const unsigned int light80FanMed[] PROGMEM = {331,331,662,331,662,331,662,662,331,662,331,662,331,662,331,331,662,331,662,331,662,662,331,331,662,662,331,662,331,662,331,331,662,331,662,662,331,662,331,662,331,662,331,10038};
static const unsigned int light80FanHigh[] PROGMEM = {331,331,662,331,662,331,662,662,331,662,331,662,331,662,331,331,662,331,662,331,662,662,331,331,662,662,331,662,331,331,662,662,331,331,662,662,331,662,331,662,331,331,662,10054};
static const unsigned int light90FanOff[] PROGMEM = {330,330,663,330,663,330,663,663,330,663,330,663,330,663,330,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,10042};
static const unsigned int light90FanLow[] PROGMEM = {331,331,662,331,662,331,662,662,331,662,331,662,331,662,331,331,662,331,662,331,662,331,662,662,331,662,331,331,662,662,331,662,331,331,662,662,331,331,662,662,331,662,331,10058};
static const unsigned int light90FanMed[] PROGMEM = {330,330,662,330,662,330,662,662,330,662,330,662,330,662,330,330,662,330,662,330,662,330,662,662,330,662,330,330,662,662,330,330,662,330,662,662,330,330,662,662,330,330,662,10047};
static const unsigned int light90FanHigh[] PROGMEM = {330,330,662,330,662,330,662,662,330,662,330,662,330,662,330,330,662,330,662,330,662,330,662,662,330,662,330,330,662,330,662,662,330,330,662,662,330,330,662,330,662,662,330,10030};
static const unsigned int light100FanOff[] PROGMEM = {330,330,663,330,663,330,663,663,330,663,330,663,330,663,330,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,663,330,663,330,10036};
static const unsigned int light100FanLow[] PROGMEM = {330,330,662,330,662,330,662,662,330,662,330,662,330,662,330,330,662,330,662,330,662,330,662,330,662,330,662,662,330,662,330,662,330,330,662,330,662,662,330,662,330,330,662,10038};
static const unsigned int light100FanMed[] PROGMEM = {330,330,662,330,662,330,662,662,330,662,330,662,330,662,330,330,662,330,662,330,662,330,662,330,662,330,662,662,330,662,330,330,662,330,662,330,662,662,330,330,662,662,330,10051};
static const unsigned int light100FanHigh[] PROGMEM = {330,330,663,330,663,330,663,663,330,663,330,663,330,663,330,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,330,663,663,330,330,663,330,663,10030};

  server.send(204,"");
  String lastFanSpeed = read_String(0);
  String lastLightState = read_String(5);  
  String fanSpeed = server.arg("fanSpeed");
  String lightState = server.arg("lightState");
  
  if(fanSpeed == "same"){
    fanSpeed = lastFanSpeed;
  }
  else{
    lastFanSpeed = fanSpeed;
    writeString(0, fanSpeed);
  }
  
  if(lightState == "same"){
    lightState = lastLightState;
  }
  else{
    lastLightState = lightState;
    writeString(5, lightState);
  } 
  
  for (int i = 0; i <= IRrepeat; i++) {
     yield(); 
    if (lightState == "off") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(lightOffFanOff, 44,38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(lightOffFanLow, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(lightOffFanMed, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(lightOffFanHigh, 44, 38); // Send a raw data capture at 38kHz
        }
      }    
  else if (lightState == "20") {
        if(fanSpeed == "off"){
            sendRAW_Flash(light20FanOff, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light20FanLow, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light20FanMed, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light20FanHigh, 44, 38); // Send a raw data capture at 38kHz
        }   
  }
  else if (lightState == "30") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light30FanOff, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light20FanLow, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light30FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light30FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "40") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light40FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light40FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light40FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light40FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "50") {
        if(fanSpeed == "off"){
            sendRAW_Flash(light50FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light50FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light50FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light50FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "60") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light60FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light60FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light60FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light60FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "70") {
        yield();
        if(fanSpeed == "off"){
            sendRAW_Flash(light70FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light70FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light70FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light70FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "80") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light80FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light80FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light80FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light80FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }
    
  }
  else if (lightState == "90") {
        if(fanSpeed == "off"){
            sendRAW_Flash(light90FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light90FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light90FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light90FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "100") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light100FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light100FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light100FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light100FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }
      }    
  }
}

void set0001()
{  
//FAN CHQ8BT7096T DIP SWITCHES DN,DN,DN,UP OR 0001

static const unsigned int lightOffFanOff[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,663,330,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,663,330,330,663,10035};
static const unsigned int lightOffFanLow[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,663,330,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,330,663,663,330,10039};
static const unsigned int lightOffFanMed[] PROGMEM = {329,329,663,329,663,329,663,329,663,663,329,663,329,663,329,329,663,329,663,329,663,329,663,329,663,329,663,329,663,663,329,329,663,329,663,329,663,329,663,329,663,329,663,10042};
static const unsigned int lightOffFanHigh[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,663,330,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,663,330,663,330,663,330,10040};
static const unsigned int light20FanOff[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,663,330,663,330,330,663,663,330,330,663,663,330,330,663,330,663,663,330,330,663,330,663,330,663,663,330,663,330,330,663,330,663,10044};
static const unsigned int light20FanLow[] PROGMEM = {331,331,662,331,662,331,662,331,662,662,331,662,331,662,331,331,662,662,331,331,662,662,331,331,662,331,662,662,331,662,331,662,331,331,662,662,331,662,331,662,331,662,331,10043};
static const unsigned int light20FanMed[] PROGMEM = {331,331,662,331,662,331,662,331,662,662,331,662,331,662,331,331,662,662,331,331,662,662,331,331,662,331,662,662,331,662,331,331,662,331,662,662,331,662,331,662,331,331,662,10048};
static const unsigned int light20FanHigh[] PROGMEM = {331,331,662,331,662,331,662,331,662,662,331,662,331,662,331,331,662,662,331,331,662,662,331,331,662,331,662,662,331,331,662,662,331,331,662,662,331,662,331,331,662,662,331,10042};
static const unsigned int light30FanOff[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,663,330,663,330,330,663,663,330,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,663,330,10041};
static const unsigned int light30FanLow[] PROGMEM = {331,331,662,331,662,331,662,331,662,662,331,662,331,662,331,331,662,662,331,331,662,331,662,662,331,331,662,331,662,662,331,662,331,331,662,662,331,331,662,662,331,331,662,10052};
static const unsigned int light30FanMed[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,663,330,663,330,330,663,663,330,330,663,330,663,663,330,330,663,330,663,663,330,330,663,330,663,663,330,330,663,330,663,663,330,10048};
static const unsigned int light30FanHigh[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,663,330,663,330,330,663,663,330,330,663,330,663,663,330,330,663,330,663,330,663,663,330,330,663,663,330,330,663,330,663,330,663,10050};
static const unsigned int light40FanOff[] PROGMEM = {330,330,662,330,662,330,662,330,662,662,330,662,330,662,330,330,662,330,662,662,330,662,330,662,330,662,330,662,330,330,662,330,662,330,662,330,662,330,662,330,662,662,330,10041};
static const unsigned int light40FanLow[] PROGMEM = {331,331,662,331,662,331,662,331,662,662,331,662,331,662,331,331,662,331,662,662,331,662,331,662,331,662,331,662,331,662,331,662,331,331,662,331,662,662,331,331,662,331,662,10041};
static const unsigned int light40FanMed[] PROGMEM = {331,331,662,331,662,331,662,331,662,662,331,662,331,662,331,331,662,331,662,662,331,662,331,662,331,662,331,662,331,662,331,331,662,331,662,331,662,331,662,662,331,662,331,10043};
static const unsigned int light40FanHigh[] PROGMEM = {331,331,662,331,662,331,662,331,662,662,331,662,331,662,331,331,662,331,662,662,331,662,331,662,331,662,331,662,331,331,662,662,331,331,662,331,662,331,662,662,331,331,662,10046};
static const unsigned int light50FanOff[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,663,330,663,330,330,663,330,663,663,330,663,330,330,663,663,330,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,10039};
static const unsigned int light50FanLow[] PROGMEM = {331,331,662,331,662,331,662,331,662,662,331,662,331,662,331,331,662,331,662,662,331,662,331,331,662,662,331,331,662,662,331,662,331,331,662,662,331,662,331,662,331,662,331,10041};
static const unsigned int light50FanMed[] PROGMEM = {331,331,662,331,662,331,662,331,662,662,331,662,331,662,331,331,662,331,662,662,331,662,331,331,662,662,331,331,662,662,331,331,662,331,662,662,331,662,331,662,331,331,662,10048};
static const unsigned int light50FanHigh[] PROGMEM = {331,331,662,331,662,331,662,331,662,662,331,662,331,662,331,331,662,331,662,662,331,662,331,331,662,662,331,331,662,331,662,662,331,331,662,662,331,662,331,331,662,662,331,10050};
static const unsigned int light60FanOff[] PROGMEM = {331,331,662,331,662,331,662,331,662,662,331,662,331,662,331,331,662,331,662,662,331,331,662,662,331,331,662,662,331,331,662,331,662,331,662,331,662,662,331,662,331,662,331,10046};
static const unsigned int light60FanLow[] PROGMEM = {331,331,662,331,662,331,662,331,662,662,331,662,331,662,331,331,662,331,662,662,331,331,662,662,331,331,662,662,331,662,331,662,331,331,662,662,331,331,662,662,331,331,662,10048};
static const unsigned int light60FanMed[] PROGMEM = {331,331,662,331,662,331,662,331,662,662,331,662,331,662,331,331,662,331,662,662,331,331,662,662,331,331,662,662,331,662,331,331,662,331,662,662,331,331,662,331,662,662,331,10054};
static const unsigned int light60FanHigh[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,663,330,663,330,330,663,330,663,663,330,330,663,663,330,330,663,663,330,330,663,663,330,330,663,663,330,330,663,330,663,330,663,10040};
static const unsigned int light70FanOff[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,663,330,663,330,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,10054};
static const unsigned int light70FanLow[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,663,330,663,330,330,663,330,663,663,330,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,663,330,330,663,663,330,10041};
static const unsigned int light70FanMed[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,663,330,663,330,330,663,330,663,663,330,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,663,330,330,663,330,663,10044};
static const unsigned int light70FanHigh[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,663,330,663,330,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,663,330,663,330,10052};
static const unsigned int light80FanOff[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,663,330,663,330,330,663,330,663,330,663,663,330,330,663,663,330,663,330,330,663,330,663,330,663,663,330,663,330,330,663,330,663,10048};
static const unsigned int light80FanLow[] PROGMEM = {331,331,662,331,662,331,662,331,662,662,331,662,331,662,331,331,662,331,662,331,662,662,331,331,662,662,331,662,331,662,331,662,331,331,662,662,331,662,331,662,331,662,331,10046};
static const unsigned int light80FanMed[] PROGMEM = {331,331,662,331,662,331,662,331,662,662,331,662,331,662,331,331,662,331,662,331,662,662,331,331,662,662,331,662,331,662,331,331,662,331,662,662,331,662,331,662,331,331,662,10041};
static const unsigned int light80FanHigh[] PROGMEM = {331,331,662,331,662,331,662,331,662,662,331,662,331,662,331,331,662,331,662,331,662,662,331,331,662,662,331,662,331,331,662,662,331,331,662,662,331,662,331,331,662,662,331,10043};
static const unsigned int light90FanOff[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,663,330,663,330,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,330,663,330,663,663,330,663,330,663,330,10030};
static const unsigned int light90FanLow[] PROGMEM = {331,331,662,331,662,331,662,331,662,662,331,662,331,662,331,331,662,331,662,331,662,331,662,662,331,662,331,331,662,662,331,662,331,331,662,662,331,331,662,662,331,331,662,10045};
static const unsigned int light90FanMed[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,663,330,663,330,330,663,330,663,330,663,330,663,663,330,663,330,330,663,663,330,330,663,330,663,663,330,330,663,330,663,663,330,10041};
static const unsigned int light90FanHigh[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,663,330,663,330,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,663,330,330,663,663,330,330,663,330,663,330,663,10039};
static const unsigned int light100FanOff[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,663,330,663,330,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,663,330,330,663,10035};
static const unsigned int light100FanLow[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,663,330,663,330,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,663,330,330,663,330,663,663,330,330,663,663,330,10035};
static const unsigned int light100FanMed[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,663,330,663,330,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,663,330,330,663,330,663,10033};
static const unsigned int light100FanHigh[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,663,330,663,330,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,330,663,330,663,663,330,663,330,10035};

    server.send(204,"");
  String lastFanSpeed = read_String(10);
  String lastLightState = read_String(15);  
  String fanSpeed = server.arg("fanSpeed");
  String lightState = server.arg("lightState");
  
  if(fanSpeed == "same"){
    fanSpeed = lastFanSpeed;
  }
  else{
    lastFanSpeed = fanSpeed;
    writeString(10, fanSpeed);
  }
  
  if(lightState == "same"){
    lightState = lastLightState;
  }
  else{
    lastLightState = lightState;
    writeString(15, lightState);
  }  
  
  for (int i = 0; i <= IRrepeat; i++) {
     yield(); 
    if (lightState == "off") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(lightOffFanOff, 44,38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(lightOffFanLow, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(lightOffFanMed, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(lightOffFanHigh, 44, 38); // Send a raw data capture at 38kHz
        }
      }    
  else if (lightState == "20") {
        if(fanSpeed == "off"){
            sendRAW_Flash(light20FanOff, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light20FanLow, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light20FanMed, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light20FanHigh, 44, 38); // Send a raw data capture at 38kHz
        }   
  }
  else if (lightState == "30") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light30FanOff, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light20FanLow, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light30FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light30FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "40") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light40FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light40FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light40FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light40FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "50") {
        if(fanSpeed == "off"){
            sendRAW_Flash(light50FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light50FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light50FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light50FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "60") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light60FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light60FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light60FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light60FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "70") {
        yield();
        if(fanSpeed == "off"){
            sendRAW_Flash(light70FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light70FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light70FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light70FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "80") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light80FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light80FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light80FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light80FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }
    
  }
  else if (lightState == "90") {
        if(fanSpeed == "off"){
            sendRAW_Flash(light90FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light90FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light90FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light90FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "100") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light100FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light100FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light100FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light100FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }
      }    
  }
}

void set0010()
{  
//FAN CHQ8BT7096T DIP SWITCHES DN,DN,UP,DN OR 0010
static const unsigned int lightOffFanOff[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,663,330,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,663,330,10044};
static const unsigned int lightOffFanLow[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,663,330,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,663,330,330,663,663,330,330,663,10040};
static const unsigned int lightOffFanMed[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,663,330,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,663,330,330,663,330,663,663,330,10031};
static const unsigned int lightOffFanHigh[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,663,330,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,330,663,330,663,10051};
static const unsigned int light20FanOff[] PROGMEM = {330,330,662,330,662,330,662,662,330,330,662,662,330,662,330,330,662,662,330,330,662,662,330,330,662,330,662,662,330,330,662,330,662,330,662,330,662,662,330,330,662,662,330,10036};
static const unsigned int light20FanLow[] PROGMEM = {330,330,662,330,662,330,662,662,330,330,662,662,330,662,330,330,662,662,330,330,662,662,330,330,662,330,662,662,330,662,330,662,330,330,662,662,330,330,662,330,662,330,662,10042};
static const unsigned int light20FanMed[] PROGMEM = {331,331,662,331,662,331,662,662,331,331,662,662,331,662,331,331,662,662,331,331,662,662,331,331,662,331,662,662,331,662,331,331,662,331,662,331,662,662,331,662,331,662,331,10038};
static const unsigned int light20FanHigh[] PROGMEM = {330,330,662,330,662,330,662,662,330,330,662,662,330,662,330,330,662,662,330,330,662,662,330,330,662,330,662,662,330,330,662,662,330,330,662,330,662,662,330,662,330,330,662,10029};
static const unsigned int light30FanOff[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,663,330,663,330,330,663,663,330,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,10053};
static const unsigned int light30FanLow[] PROGMEM = {330,330,662,330,662,330,662,662,330,330,662,662,330,662,330,330,662,662,330,330,662,330,662,662,330,330,662,330,662,662,330,662,330,330,662,330,662,330,662,662,330,662,330,10036};
static const unsigned int light30FanMed[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,663,330,663,330,330,663,663,330,330,663,330,663,663,330,330,663,330,663,663,330,330,663,330,663,330,663,330,663,663,330,330,663,10036};
static const unsigned int light30FanHigh[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,663,330,663,330,330,663,663,330,330,663,330,663,663,330,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,663,330,10034};
static const unsigned int light40FanOff[] PROGMEM = {331,331,662,331,662,331,662,662,331,331,662,662,331,662,331,331,662,331,662,662,331,662,331,662,331,662,331,662,331,331,662,331,662,331,662,662,331,331,662,662,331,331,662,10038};
static const unsigned int light40FanLow[] PROGMEM = {331,331,661,331,661,331,661,661,331,331,661,661,331,661,331,331,661,331,661,661,331,661,331,661,331,661,331,661,331,661,331,661,331,331,661,661,331,661,331,331,661,661,331,10062};
static const unsigned int light40FanMed[] PROGMEM = {331,331,662,331,662,331,662,662,331,331,662,662,331,662,331,331,662,331,662,662,331,662,331,662,331,662,331,662,331,662,331,331,662,331,662,662,331,662,331,331,662,331,662,10044};
static const unsigned int light40FanHigh[] PROGMEM = {331,331,662,331,662,331,662,662,331,331,662,662,331,662,331,331,662,331,662,662,331,662,331,662,331,662,331,662,331,331,662,662,331,331,662,662,331,331,662,662,331,662,331,10038};
static const unsigned int light50FanOff[] PROGMEM = {330,330,662,330,662,330,662,662,330,330,662,662,330,662,330,330,662,330,662,662,330,662,330,330,662,662,330,330,662,330,662,330,662,330,662,330,662,662,330,330,662,662,330,10040};
static const unsigned int light50FanLow[] PROGMEM = {330,330,662,330,662,330,662,662,330,330,662,662,330,662,330,330,662,330,662,662,330,662,330,330,662,662,330,330,662,662,330,662,330,330,662,662,330,330,662,330,662,330,662,10034};
static const unsigned int light50FanMed[] PROGMEM = {331,331,662,331,662,331,662,662,331,331,662,662,331,662,331,331,662,331,662,662,331,662,331,331,662,662,331,331,662,662,331,331,662,331,662,331,662,662,331,662,331,662,331,10034};
static const unsigned int light50FanHigh[] PROGMEM = {330,330,662,330,662,330,662,662,330,330,662,662,330,662,330,330,662,330,662,662,330,662,330,330,662,662,330,330,662,330,662,662,330,330,662,330,662,662,330,662,330,330,662,10034};
static const unsigned int light60FanOff[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,663,330,663,330,330,663,330,663,663,330,330,663,663,330,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,10038};
static const unsigned int light60FanLow[] PROGMEM = {331,331,662,331,662,331,662,662,331,331,662,662,331,662,331,331,662,331,662,662,331,331,662,662,331,331,662,662,331,662,331,662,331,331,662,331,662,331,662,662,331,662,331,10036};
static const unsigned int light60FanMed[] PROGMEM = {330,330,662,330,662,330,662,662,330,330,662,662,330,662,330,330,662,330,662,662,330,330,662,662,330,330,662,662,330,662,330,330,662,330,662,330,662,330,662,662,330,330,662,10045};
static const unsigned int light60FanHigh[] PROGMEM = {330,330,662,330,662,330,662,662,330,330,662,662,330,662,330,330,662,330,662,662,330,330,662,662,330,330,662,662,330,330,662,662,330,330,662,330,662,330,662,330,662,662,330,10041};
static const unsigned int light70FanOff[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,663,330,663,330,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,663,330,10036};
static const unsigned int light70FanLow[] PROGMEM = {330,330,662,330,662,330,662,662,330,330,662,662,330,662,330,330,662,330,662,662,330,330,662,330,662,330,662,330,662,662,330,662,330,330,662,662,330,662,330,662,330,330,662,10031};
static const unsigned int light70FanMed[] PROGMEM = {330,330,662,330,662,330,662,662,330,330,662,662,330,662,330,330,662,330,662,662,330,330,662,330,662,330,662,330,662,662,330,330,662,330,662,662,330,662,330,330,662,662,330,10045};
static const unsigned int light70FanHigh[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,663,330,663,330,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,663,330,330,663,330,663,10034};
static const unsigned int light80FanOff[] PROGMEM = {330,330,662,330,662,330,662,662,330,330,662,662,330,662,330,330,662,330,662,330,662,662,330,330,662,662,330,662,330,330,662,330,662,330,662,330,662,662,330,330,662,662,330,10049};
static const unsigned int light80FanLow[] PROGMEM = {330,330,662,330,662,330,662,662,330,330,662,662,330,662,330,330,662,330,662,330,662,662,330,330,662,662,330,662,330,662,330,662,330,330,662,662,330,330,662,330,662,330,662,10045};
static const unsigned int light80FanMed[] PROGMEM = {331,331,662,331,662,331,662,662,331,331,662,662,331,662,331,331,662,331,662,331,662,662,331,331,662,662,331,662,331,662,331,331,662,331,662,331,662,662,331,662,331,662,331,10040};
static const unsigned int light80FanHigh[] PROGMEM = {330,330,662,330,662,330,662,662,330,330,662,662,330,662,330,330,662,330,662,330,662,662,330,330,662,662,330,662,330,330,662,662,330,330,662,330,662,662,330,662,330,330,662,10034};
static const unsigned int light90FanOff[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,663,330,663,330,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,10038};
static const unsigned int light90FanLow[] PROGMEM = {330,330,662,330,662,330,662,662,330,330,662,662,330,662,330,330,662,330,662,330,662,330,662,662,330,662,330,330,662,662,330,662,330,330,662,330,662,330,662,662,330,662,330,10038};
static const unsigned int light90FanMed[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,663,330,663,330,330,663,330,663,330,663,330,663,663,330,663,330,330,663,663,330,330,663,330,663,330,663,330,663,663,330,330,663,10034};
static const unsigned int light90FanHigh[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,663,330,663,330,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,663,330,330,663,330,663,330,663,330,663,663,330,10032};
static const unsigned int light100FanOff[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,663,330,663,330,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,663,330,330,663,663,330,663,330,10034};
static const unsigned int light100FanLow[] PROGMEM = {330,330,662,330,662,330,662,662,330,330,662,662,330,662,330,330,662,330,662,330,662,330,662,330,662,330,662,662,330,662,330,662,330,330,662,662,330,662,330,662,330,330,662,10043};
static const unsigned int light100FanMed[] PROGMEM = {330,330,662,330,662,330,662,662,330,330,662,662,330,662,330,330,662,330,662,330,662,330,662,330,662,330,662,662,330,662,330,330,662,330,662,662,330,662,330,330,662,662,330,10030};
static const unsigned int light100FanHigh[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,663,330,663,330,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,663,330,663,330,330,663,330,663,10043};

  server.send(204,"");
  String lastFanSpeed = read_String(20);
  String lastLightState = read_String(25);  
  String fanSpeed = server.arg("fanSpeed");
  String lightState = server.arg("lightState");
  
  if(fanSpeed == "same"){
    fanSpeed = lastFanSpeed;
  }
  else{
    lastFanSpeed = fanSpeed;
    writeString(20, fanSpeed);
  }
  
  if(lightState == "same"){
    lightState = lastLightState;
  }
  else{
    lastLightState = lightState;
    writeString(25, lightState);
  }  
  
  for (int i = 0; i <= IRrepeat; i++) {
     yield(); 
    if (lightState == "off") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(lightOffFanOff, 44,38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(lightOffFanLow, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(lightOffFanMed, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(lightOffFanHigh, 44, 38); // Send a raw data capture at 38kHz
        }
      }    
  else if (lightState == "20") {
        if(fanSpeed == "off"){
            sendRAW_Flash(light20FanOff, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light20FanLow, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light20FanMed, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light20FanHigh, 44, 38); // Send a raw data capture at 38kHz
        }   
  }
  else if (lightState == "30") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light30FanOff, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light20FanLow, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light30FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light30FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "40") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light40FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light40FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light40FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light40FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "50") {
        if(fanSpeed == "off"){
            sendRAW_Flash(light50FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light50FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light50FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light50FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "60") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light60FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light60FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light60FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light60FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "70") {
        yield();
        if(fanSpeed == "off"){
            sendRAW_Flash(light70FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light70FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light70FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light70FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "80") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light80FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light80FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light80FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light80FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }
    
  }
  else if (lightState == "90") {
        if(fanSpeed == "off"){
            sendRAW_Flash(light90FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light90FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light90FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light90FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "100") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light100FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light100FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light100FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light100FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }
      }    
  }
}

void set0011()
{  
//FAN CHQ8BT7096T DIP SWITCHES DN,DN,UP,UP OR 0011
static const unsigned int lightOffFanOff[] PROGMEM = {329,329,663,329,663,329,663,329,663,329,663,663,329,663,329,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,663,329,663,329,329,663,10044};
static const unsigned int lightOffFanLow[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,663,330,330,663,330,663,663,330,10033};
static const unsigned int lightOffFanMed[] PROGMEM = {329,329,663,329,663,329,663,329,663,329,663,663,329,663,329,329,663,329,663,329,663,329,663,329,663,329,663,329,663,663,329,329,663,329,663,663,329,329,663,329,663,329,663,10031};
static const unsigned int lightOffFanHigh[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,663,330,663,330,663,330,10038};
static const unsigned int light20FanOff[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,663,330,330,663,663,330,330,663,330,663,663,330,330,663,330,663,330,663,330,663,663,330,330,663,330,663,10025};
static const unsigned int light20FanLow[] PROGMEM = {331,331,662,331,662,331,662,331,662,331,662,662,331,662,331,331,662,662,331,331,662,662,331,331,662,331,662,662,331,662,331,662,331,331,662,331,662,662,331,662,331,662,331,10038};
static const unsigned int light20FanMed[] PROGMEM = {330,330,662,330,662,330,662,330,662,330,662,662,330,662,330,330,662,662,330,330,662,662,330,330,662,330,662,662,330,662,330,330,662,330,662,330,662,662,330,662,330,330,662,10031};
static const unsigned int light20FanHigh[] PROGMEM = {330,330,662,330,662,330,662,330,662,330,662,662,330,662,330,330,662,662,330,330,662,662,330,330,662,330,662,662,330,330,662,662,330,330,662,330,662,662,330,330,662,662,330,10031};
static const unsigned int light30FanOff[] PROGMEM = {330,330,662,330,662,330,662,330,662,330,662,662,330,662,330,330,662,662,330,330,662,330,662,662,330,330,662,330,662,330,662,330,662,330,662,662,330,662,330,662,330,662,330,10051};
static const unsigned int light30FanLow[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,663,330,330,663,330,663,663,330,330,663,330,663,663,330,663,330,330,663,330,663,330,663,663,330,330,663,10037};
static const unsigned int light30FanMed[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,663,330,330,663,330,663,663,330,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,663,330,10035};
static const unsigned int light30FanHigh[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,663,330,330,663,330,663,663,330,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,10053};
static const unsigned int light40FanOff[] PROGMEM = {330,330,662,330,662,330,662,330,662,330,662,662,330,662,330,330,662,330,662,662,330,662,330,662,330,662,330,662,330,330,662,330,662,330,662,662,330,330,662,330,662,662,330,10036};
static const unsigned int light40FanLow[] PROGMEM = {331,331,662,331,662,331,662,331,662,331,662,662,331,662,331,331,662,331,662,662,331,662,331,662,331,662,331,662,331,662,331,662,331,331,662,662,331,662,331,331,662,331,662,10051};
static const unsigned int light40FanMed[] PROGMEM = {331,331,662,331,662,331,662,331,662,331,662,662,331,662,331,331,662,331,662,662,331,662,331,662,331,662,331,662,331,662,331,331,662,331,662,662,331,331,662,662,331,662,331,10042};
static const unsigned int light40FanHigh[] PROGMEM = {331,331,662,331,662,331,662,331,662,331,662,662,331,662,331,331,662,331,662,662,331,662,331,662,331,662,331,662,331,331,662,662,331,331,662,662,331,331,662,662,331,331,662,10042};
static const unsigned int light50FanOff[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,663,330,663,330,330,663,663,330,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,10040};
static const unsigned int light50FanLow[] PROGMEM = {331,331,662,331,662,331,662,331,662,331,662,662,331,662,331,331,662,331,662,662,331,662,331,331,662,662,331,331,662,662,331,662,331,331,662,331,662,662,331,662,331,662,331,10046};
static const unsigned int light50FanMed[] PROGMEM = {330,330,662,330,662,330,662,330,662,330,662,662,330,662,330,330,662,330,662,662,330,662,330,330,662,662,330,330,662,662,330,330,662,330,662,330,662,662,330,662,330,330,662,10042};
static const unsigned int light50FanHigh[] PROGMEM = {330,330,662,330,662,330,662,330,662,330,662,662,330,662,330,330,662,330,662,662,330,662,330,330,662,662,330,330,662,330,662,662,330,330,662,330,662,662,330,330,662,662,330,10044};
static const unsigned int light60FanOff[] PROGMEM = {330,330,662,330,662,330,662,330,662,330,662,662,330,662,330,330,662,330,662,662,330,330,662,662,330,330,662,662,330,330,662,330,662,330,662,662,330,662,330,662,330,662,330,10031};
static const unsigned int light60FanLow[] PROGMEM = {330,330,662,330,662,330,662,330,662,330,662,662,330,662,330,330,662,330,662,662,330,330,662,662,330,330,662,662,330,662,330,662,330,330,662,330,662,330,662,662,330,330,662,10036};
static const unsigned int light60FanMed[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,663,330,330,663,663,330,330,663,663,330,663,330,330,663,330,663,330,663,330,663,330,663,663,330,10033};
static const unsigned int light60FanHigh[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,663,330,330,663,663,330,330,663,663,330,330,663,663,330,330,663,330,663,330,663,330,663,330,663,10036};
static const unsigned int light70FanOff[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,10037};
static const unsigned int light70FanLow[] PROGMEM = {330,330,662,330,662,330,662,330,662,330,662,662,330,662,330,330,662,330,662,662,330,330,662,330,662,330,662,330,662,662,330,662,330,330,662,662,330,662,330,330,662,662,330,10038};
static const unsigned int light70FanMed[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,663,330,330,663,330,663,330,663,330,663,663,330,330,663,330,663,663,330,663,330,330,663,330,663,10044};
static const unsigned int light70FanHigh[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,663,330,663,330,10036};
static const unsigned int light80FanOff[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,663,330,330,663,663,330,663,330,330,663,330,663,330,663,330,663,663,330,330,663,330,663,10035};
static const unsigned int light80FanLow[] PROGMEM = {331,331,662,331,662,331,662,331,662,331,662,662,331,662,331,331,662,331,662,331,662,662,331,331,662,662,331,662,331,662,331,662,331,331,662,331,662,662,331,662,331,662,331,10038};
static const unsigned int light80FanMed[] PROGMEM = {330,330,662,330,662,330,662,330,662,330,662,662,330,662,330,330,662,330,662,330,662,662,330,330,662,662,330,662,330,662,330,330,662,330,662,330,662,662,330,662,330,330,662,10038};
static const unsigned int light80FanHigh[] PROGMEM = {330,330,662,330,662,330,662,330,662,330,662,662,330,662,330,330,662,330,662,330,662,662,330,330,662,662,330,662,330,330,662,662,330,330,662,330,662,662,330,330,662,662,330,10042};
static const unsigned int light90FanOff[] PROGMEM = {330,330,662,330,662,330,662,330,662,330,662,662,330,662,330,330,662,330,662,330,662,330,662,662,330,662,330,330,662,330,662,330,662,330,662,662,330,662,330,662,330,662,330,10038};
static const unsigned int light90FanLow[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,330,663,663,330,663,330,330,663,663,330,663,330,330,663,330,663,330,663,663,330,330,663,10051};
static const unsigned int light90FanMed[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,330,663,663,330,663,330,330,663,663,330,330,663,330,663,330,663,330,663,330,663,663,330,10044};
static const unsigned int light90FanHigh[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,10050};
static const unsigned int light100FanOff[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,663,330,330,663,663,330,330,663,10036};
static const unsigned int light100FanLow[] PROGMEM = {330,330,662,330,662,330,662,330,662,330,662,662,330,662,330,330,662,330,662,330,662,330,662,330,662,330,662,662,330,662,330,662,330,330,662,662,330,662,330,330,662,662,330,10034};
static const unsigned int light100FanMed[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,663,330,663,330,330,663,330,663,10044};
static const unsigned int light100FanHigh[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,663,330,330,663,663,330,663,330,10027};

  server.send(204,"");
  String lastFanSpeed = read_String(30);
  String lastLightState = read_String(35);  
  String fanSpeed = server.arg("fanSpeed");
  String lightState = server.arg("lightState");
  
  if(fanSpeed == "same"){
    fanSpeed = lastFanSpeed;
  }
  else{
    lastFanSpeed = fanSpeed;
    writeString(30, fanSpeed);
  }
  
  if(lightState == "same"){
    lightState = lastLightState;
  }
  else{
    lastLightState = lightState;
    writeString(35, lightState);
  }  
  
  for (int i = 0; i <= IRrepeat; i++) {
     yield(); 
    if (lightState == "off") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(lightOffFanOff, 44,38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(lightOffFanLow, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(lightOffFanMed, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(lightOffFanHigh, 44, 38); // Send a raw data capture at 38kHz
        }
      }    
  else if (lightState == "20") {
        if(fanSpeed == "off"){
            sendRAW_Flash(light20FanOff, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light20FanLow, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light20FanMed, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light20FanHigh, 44, 38); // Send a raw data capture at 38kHz
        }   
  }
  else if (lightState == "30") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light30FanOff, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light20FanLow, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light30FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light30FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "40") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light40FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light40FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light40FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light40FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "50") {
        if(fanSpeed == "off"){
            sendRAW_Flash(light50FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light50FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light50FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light50FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "60") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light60FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light60FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light60FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light60FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "70") {
        yield();
        if(fanSpeed == "off"){
            sendRAW_Flash(light70FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light70FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light70FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light70FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "80") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light80FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light80FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light80FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light80FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }
    
  }
  else if (lightState == "90") {
        if(fanSpeed == "off"){
            sendRAW_Flash(light90FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light90FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light90FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light90FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "100") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light100FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light100FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light100FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light100FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }
      }    
  }
}

void set0100()
{  
//FAN CHQ8BT7096T DIP SWITCHES DN,UP,DN,DN OR 0100
static const unsigned int lightOffFanOff[] PROGMEM = {330,330,663,330,663,330,663,663,330,663,330,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,663,330,10051};
static const unsigned int lightOffFanLow[] PROGMEM = {330,330,662,330,662,330,662,662,330,662,330,330,662,662,330,330,662,330,662,330,662,330,662,330,662,330,662,330,662,662,330,662,330,330,662,662,330,662,330,662,330,330,662,10038};
static const unsigned int lightOffFanMed[] PROGMEM = {330,330,663,330,663,330,663,663,330,663,330,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,663,330,663,330,330,663,663,330,10057};
static const unsigned int lightOffFanHigh[] PROGMEM = {330,330,663,330,663,330,663,663,330,663,330,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,663,330,330,663,330,663,10047};
static const unsigned int light20FanOff[] PROGMEM = {330,330,662,330,662,330,662,662,330,662,330,330,662,662,330,330,662,662,330,330,662,662,330,330,662,330,662,662,330,330,662,330,662,330,662,662,330,330,662,330,662,662,330,10038};
static const unsigned int light20FanLow[] PROGMEM = {331,331,662,331,662,331,662,662,331,662,331,331,662,662,331,331,662,662,331,331,662,662,331,331,662,331,662,662,331,662,331,662,331,331,662,662,331,662,331,331,662,331,662,10040};
static const unsigned int light20FanMed[] PROGMEM = {331,331,662,331,662,331,662,662,331,662,331,331,662,662,331,331,662,662,331,331,662,662,331,331,662,331,662,662,331,662,331,331,662,331,662,662,331,331,662,662,331,662,331,10036};
static const unsigned int light20FanHigh[] PROGMEM = {330,330,662,330,662,330,662,662,330,662,330,330,662,662,330,330,662,662,330,330,662,662,330,330,662,330,662,662,330,330,662,662,330,330,662,662,330,330,662,662,330,330,662,10041};
static const unsigned int light30FanOff[] PROGMEM = {330,330,663,330,663,330,663,663,330,663,330,330,663,663,330,330,663,663,330,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,10036};
static const unsigned int light30FanLow[] PROGMEM = {331,331,662,331,662,331,662,662,331,662,331,331,662,662,331,331,662,662,331,331,662,331,662,662,331,331,662,331,662,662,331,662,331,331,662,331,662,662,331,662,331,662,331,10038};
static const unsigned int light30FanMed[] PROGMEM = {330,330,662,330,662,330,662,662,330,662,330,330,662,662,330,330,662,662,330,330,662,330,662,662,330,330,662,330,662,662,330,330,662,330,662,330,662,662,330,662,330,330,662,10032};
static const unsigned int light30FanHigh[] PROGMEM = {330,330,662,330,662,330,662,662,330,662,330,330,662,662,330,330,662,662,330,330,662,330,662,662,330,330,662,330,662,330,662,662,330,330,662,330,662,662,330,330,662,662,330,10032};
static const unsigned int light40FanOff[] PROGMEM = {331,331,662,331,662,331,662,662,331,662,331,331,662,662,331,331,662,331,662,662,331,662,331,662,331,662,331,662,331,331,662,331,662,331,662,662,331,662,331,662,331,331,662,10045};
static const unsigned int light40FanLow[] PROGMEM = {331,331,662,331,662,331,662,662,331,662,331,331,662,662,331,331,662,331,662,662,331,662,331,662,331,662,331,662,331,662,331,662,331,331,662,331,662,331,662,331,662,662,331,10047};
static const unsigned int light40FanMed[] PROGMEM = {330,330,662,330,662,330,662,662,330,662,330,330,662,662,330,330,662,330,662,662,330,662,330,662,330,662,330,662,330,662,330,330,662,330,662,330,662,330,662,330,662,330,662,10032};
static const unsigned int light40FanHigh[] PROGMEM = {331,331,661,331,661,331,661,661,331,661,331,331,661,661,331,331,661,331,661,661,331,661,331,661,331,661,331,661,331,331,661,661,331,331,661,661,331,661,331,661,331,661,331,10094};
static const unsigned int light50FanOff[] PROGMEM = {330,330,662,330,662,330,662,662,330,662,330,330,662,662,330,330,662,330,662,662,330,662,330,330,662,662,330,330,662,330,662,330,662,330,662,662,330,330,662,330,662,662,330,10045};
static const unsigned int light50FanLow[] PROGMEM = {331,331,662,331,662,331,662,662,331,662,331,331,662,662,331,331,662,331,662,662,331,662,331,331,662,662,331,331,662,662,331,662,331,331,662,662,331,662,331,331,662,331,662,10038};
static const unsigned int light50FanMed[] PROGMEM = {331,331,662,331,662,331,662,662,331,662,331,331,662,662,331,331,662,331,662,662,331,662,331,331,662,662,331,331,662,662,331,331,662,331,662,662,331,331,662,662,331,662,331,10038};
static const unsigned int light50FanHigh[] PROGMEM = {330,330,662,330,662,330,662,662,330,662,330,330,662,662,330,330,662,330,662,662,330,662,330,330,662,662,330,330,662,330,662,662,330,330,662,662,330,330,662,662,330,330,662,10036};
static const unsigned int light60FanOff[] PROGMEM = {330,330,663,330,663,330,663,663,330,663,330,330,663,663,330,330,663,330,663,663,330,330,663,663,330,330,663,663,330,330,663,330,663,330,663,330,663,663,330,330,663,330,663,10041};
static const unsigned int light60FanLow[] PROGMEM = {331,331,662,331,662,331,662,662,331,662,331,331,662,662,331,331,662,331,662,662,331,331,662,662,331,331,662,662,331,662,331,662,331,331,662,331,662,662,331,662,331,662,331,10047};
static const unsigned int light60FanMed[] PROGMEM = {330,330,662,330,662,330,662,662,330,662,330,330,662,662,330,330,662,330,662,662,330,330,662,662,330,330,662,662,330,662,330,330,662,330,662,330,662,662,330,662,330,330,662,10032};
static const unsigned int light60FanHigh[] PROGMEM = {330,330,662,330,662,330,662,662,330,662,330,330,662,662,330,330,662,330,662,662,330,330,662,662,330,330,662,662,330,330,662,662,330,330,662,330,662,662,330,330,662,662,330,10038};
static const unsigned int light70FanOff[] PROGMEM = {330,330,662,330,662,330,662,662,330,662,330,330,662,662,330,330,662,330,662,662,330,330,662,330,662,330,662,330,662,330,662,330,662,330,662,662,330,662,330,662,330,662,330,10038};
static const unsigned int light70FanLow[] PROGMEM = {330,330,663,330,663,330,663,663,330,663,330,330,663,663,330,330,663,330,663,663,330,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,663,330,330,663,10042};
static const unsigned int light70FanMed[] PROGMEM = {330,330,663,330,663,330,663,663,330,663,330,330,663,663,330,330,663,330,663,663,330,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,663,330,10034};
static const unsigned int light70FanHigh[] PROGMEM = {330,330,663,330,663,330,663,663,330,663,330,330,663,663,330,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,10042};
static const unsigned int light80FanOff[] PROGMEM = {330,330,662,330,662,330,662,662,330,662,330,330,662,662,330,330,662,330,662,330,662,662,330,330,662,662,330,662,330,330,662,330,662,330,662,662,330,330,662,330,662,662,330,10038};
static const unsigned int light80FanLow[] PROGMEM = {331,331,662,331,662,331,662,662,331,662,331,331,662,662,331,331,662,331,662,331,662,662,331,331,662,662,331,662,331,662,331,662,331,331,662,662,331,662,331,331,662,331,662,10051};
static const unsigned int light80FanMed[] PROGMEM = {331,331,662,331,662,331,662,662,331,662,331,331,662,662,331,331,662,331,662,331,662,662,331,331,662,662,331,662,331,662,331,331,662,331,662,662,331,331,662,662,331,662,331,10044};
static const unsigned int light80FanHigh[] PROGMEM = {330,330,662,330,662,330,662,662,330,662,330,330,662,662,330,330,662,330,662,330,662,662,330,330,662,662,330,662,330,330,662,662,330,330,662,662,330,330,662,662,330,330,662,10034};
static const unsigned int light90FanOff[] PROGMEM = {330,330,663,330,663,330,663,663,330,663,330,330,663,663,330,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,10030};
static const unsigned int light90FanLow[] PROGMEM = {331,331,662,331,662,331,662,662,331,662,331,331,662,662,331,331,662,331,662,331,662,331,662,662,331,662,331,331,662,662,331,662,331,331,662,331,662,662,331,662,331,662,331,10033};
static const unsigned int light90FanMed[] PROGMEM = {330,330,662,330,662,330,662,662,330,662,330,330,662,662,330,330,662,330,662,330,662,330,662,662,330,662,330,330,662,662,330,330,662,330,662,330,662,662,330,662,330,330,662,10044};
static const unsigned int light90FanHigh[] PROGMEM = {330,330,662,330,662,330,662,662,330,662,330,330,662,662,330,330,662,330,662,330,662,330,662,662,330,662,330,330,662,330,662,662,330,330,662,330,662,662,330,330,662,662,330,10042};
static const unsigned int light100FanOff[] PROGMEM = {330,330,662,330,662,330,662,662,330,662,330,330,662,662,330,330,662,330,662,330,662,330,662,330,662,330,662,662,330,330,662,330,662,330,662,662,330,662,330,662,330,662,330,10044};
static const unsigned int light100FanLow[] PROGMEM = {330,330,663,330,663,330,663,663,330,663,330,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,663,330,330,663,330,663,330,663,663,330,330,663,10049};
static const unsigned int light100FanMed[] PROGMEM = {330,330,663,330,663,330,663,663,330,663,330,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,330,663,330,663,663,330,10042};
static const unsigned int light100FanHigh[] PROGMEM = {330,330,663,330,663,330,663,663,330,663,330,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,330,663,330,663,330,663,330,663,10046};

  server.send(204,"");
  String lastFanSpeed = read_String(40);
  String lastLightState = read_String(45);  
  String fanSpeed = server.arg("fanSpeed");
  String lightState = server.arg("lightState");
  
  if(fanSpeed == "same"){
    fanSpeed = lastFanSpeed;
  }
  else{
    lastFanSpeed = fanSpeed;
    writeString(40, fanSpeed);
  }
  
  if(lightState == "same"){
    lightState = lastLightState;
  }
  else{
    lastLightState = lightState;
    writeString(45, lightState);
  }  
  
  for (int i = 0; i <= IRrepeat; i++) {
     yield(); 
    if (lightState == "off") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(lightOffFanOff, 44,38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(lightOffFanLow, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(lightOffFanMed, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(lightOffFanHigh, 44, 38); // Send a raw data capture at 38kHz
        }
      }    
  else if (lightState == "20") {
        if(fanSpeed == "off"){
            sendRAW_Flash(light20FanOff, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light20FanLow, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light20FanMed, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light20FanHigh, 44, 38); // Send a raw data capture at 38kHz
        }   
  }
  else if (lightState == "30") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light30FanOff, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light20FanLow, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light30FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light30FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "40") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light40FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light40FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light40FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light40FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "50") {
        if(fanSpeed == "off"){
            sendRAW_Flash(light50FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light50FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light50FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light50FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "60") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light60FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light60FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light60FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light60FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "70") {
        yield();
        if(fanSpeed == "off"){
            sendRAW_Flash(light70FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light70FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light70FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light70FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "80") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light80FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light80FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light80FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light80FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }
    
  }
  else if (lightState == "90") {
        if(fanSpeed == "off"){
            sendRAW_Flash(light90FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light90FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light90FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light90FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "100") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light100FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light100FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light100FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light100FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }
      }    
  }
}

void set0101()
{  
//FAN CHQ8BT7096T DIP SWITCHES DN,UP,DN,UP OR 0101
static const unsigned int lightOffFanOff[] PROGMEM = {329,329,663,329,663,329,663,329,663,663,329,329,663,663,329,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,663,329,329,663,663,329,329,663,10035};
static const unsigned int lightOffFanLow[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,663,330,663,330,330,663,663,330,10034};
static const unsigned int lightOffFanMed[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,663,330,663,330,330,663,330,663,10036};
static const unsigned int lightOffFanHigh[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,663,330,663,330,10036};
static const unsigned int light20FanOff[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,663,330,330,663,663,330,330,663,330,663,663,330,330,663,330,663,330,663,663,330,330,663,330,663,330,663,10055};
static const unsigned int light20FanLow[] PROGMEM = {331,331,662,331,662,331,662,331,662,662,331,331,662,662,331,331,662,662,331,331,662,662,331,331,662,331,662,662,331,662,331,662,331,331,662,662,331,331,662,662,331,662,331,10040};
static const unsigned int light20FanMed[] PROGMEM = {330,330,662,330,662,330,662,330,662,662,330,330,662,662,330,330,662,662,330,330,662,662,330,330,662,330,662,662,330,662,330,330,662,330,662,662,330,330,662,662,330,330,662,10040};
static const unsigned int light20FanHigh[] PROGMEM = {330,330,662,330,662,330,662,330,662,662,330,330,662,662,330,330,662,662,330,330,662,662,330,330,662,330,662,662,330,330,662,662,330,330,662,662,330,330,662,330,662,662,330,10038};
static const unsigned int light30FanOff[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,663,330,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,10051};
static const unsigned int light30FanLow[] PROGMEM = {330,330,662,330,662,330,662,330,662,662,330,330,662,662,330,330,662,662,330,330,662,330,662,662,330,330,662,330,662,662,330,662,330,330,662,330,662,662,330,662,330,330,662,10040};
static const unsigned int light30FanMed[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,663,330,330,663,330,663,663,330,330,663,330,663,663,330,330,663,330,663,330,663,663,330,330,663,663,330,10046};
static const unsigned int light30FanHigh[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,663,330,330,663,330,663,663,330,330,663,330,663,330,663,663,330,330,663,330,663,663,330,330,663,330,663,10042};
static const unsigned int light40FanOff[] PROGMEM = {331,331,662,331,662,331,662,331,662,662,331,331,662,662,331,331,662,331,662,662,331,662,331,662,331,662,331,662,331,331,662,331,662,331,662,662,331,662,331,331,662,662,331,10051};
static const unsigned int light40FanLow[] PROGMEM = {330,330,662,330,662,330,662,330,662,662,330,330,662,662,330,330,662,330,662,662,330,662,330,662,330,662,330,662,330,662,330,662,330,330,662,330,662,330,662,330,662,330,662,10046};
static const unsigned int light40FanMed[] PROGMEM = {331,331,662,331,662,331,662,331,662,662,331,331,662,662,331,331,662,331,662,662,331,662,331,662,331,662,331,662,331,662,331,331,662,331,662,662,331,662,331,662,331,662,331,10034};
static const unsigned int light40FanHigh[] PROGMEM = {331,331,662,331,662,331,662,331,662,662,331,331,662,662,331,331,662,331,662,662,331,662,331,662,331,662,331,662,331,331,662,662,331,331,662,662,331,662,331,662,331,331,662,10053};
static const unsigned int light50FanOff[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,330,663,663,330,663,330,330,663,663,330,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,10034};
static const unsigned int light50FanLow[] PROGMEM = {331,331,662,331,662,331,662,331,662,662,331,331,662,662,331,331,662,331,662,662,331,662,331,331,662,662,331,331,662,662,331,662,331,331,662,662,331,331,662,662,331,662,331,10035};
static const unsigned int light50FanMed[] PROGMEM = {330,330,662,330,662,330,662,330,662,662,330,330,662,662,330,330,662,330,662,662,330,662,330,330,662,662,330,330,662,662,330,330,662,330,662,662,330,330,662,662,330,330,662,10048};
static const unsigned int light50FanHigh[] PROGMEM = {330,330,662,330,662,330,662,330,662,662,330,330,662,662,330,330,662,330,662,662,330,662,330,330,662,662,330,330,662,330,662,662,330,330,662,662,330,330,662,330,662,662,330,10036};
static const unsigned int light60FanOff[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,330,663,663,330,330,663,663,330,330,663,663,330,330,663,330,663,330,663,330,663,330,663,663,330,663,330,10036};
static const unsigned int light60FanLow[] PROGMEM = {330,330,662,330,662,330,662,330,662,662,330,330,662,662,330,330,662,330,662,662,330,330,662,662,330,330,662,662,330,662,330,662,330,330,662,330,662,662,330,662,330,330,662,10035};
static const unsigned int light60FanMed[] PROGMEM = {330,330,662,330,662,330,662,330,662,662,330,330,662,662,330,330,662,330,662,662,330,330,662,662,330,330,662,662,330,662,330,330,662,330,662,330,662,662,330,330,662,662,330,10046};
static const unsigned int light60FanHigh[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,330,663,663,330,330,663,663,330,330,663,663,330,330,663,663,330,330,663,330,663,663,330,330,663,330,663,10036};
static const unsigned int light70FanOff[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,663,330,330,663,10040};
static const unsigned int light70FanLow[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,330,663,663,330,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,330,663,663,330,10031};
static const unsigned int light70FanMed[] PROGMEM = {329,329,663,329,663,329,663,329,663,663,329,329,663,663,329,329,663,329,663,663,329,329,663,329,663,329,663,329,663,663,329,329,663,329,663,329,663,329,663,329,663,329,663,10046};
static const unsigned int light70FanHigh[] PROGMEM = {330,330,662,330,662,330,662,330,662,662,330,330,662,662,330,330,662,330,662,662,330,330,662,330,662,330,662,330,662,330,662,662,330,330,662,662,330,662,330,662,330,662,330,10040};
static const unsigned int light80FanOff[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,330,663,330,663,663,330,330,663,663,330,663,330,330,663,330,663,330,663,663,330,330,663,330,663,330,663,10037};
static const unsigned int light80FanLow[] PROGMEM = {331,331,662,331,662,331,662,331,662,662,331,331,662,662,331,331,662,331,662,331,662,662,331,331,662,662,331,662,331,662,331,662,331,331,662,662,331,331,662,662,331,662,331,10036};
static const unsigned int light80FanMed[] PROGMEM = {330,330,662,330,662,330,662,330,662,662,330,330,662,662,330,330,662,330,662,330,662,662,330,330,662,662,330,662,330,662,330,330,662,330,662,662,330,330,662,662,330,330,662,10046};
static const unsigned int light80FanHigh[] PROGMEM = {330,330,662,330,662,330,662,330,662,662,330,330,662,662,330,330,662,330,662,330,662,662,330,330,662,662,330,662,330,330,662,662,330,330,662,662,330,330,662,330,662,662,330,10046};
static const unsigned int light90FanOff[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,10027};
static const unsigned int light90FanLow[] PROGMEM = {330,330,662,330,662,330,662,330,662,662,330,330,662,662,330,330,662,330,662,330,662,330,662,662,330,662,330,330,662,662,330,662,330,330,662,330,662,662,330,662,330,330,662,10044};
static const unsigned int light90FanMed[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,330,663,330,663,330,663,663,330,663,330,330,663,663,330,330,663,330,663,330,663,663,330,330,663,663,330,10044};
static const unsigned int light90FanHigh[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,663,330,330,663,330,663,663,330,330,663,330,663,10040};
static const unsigned int light100FanOff[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,663,330,663,330,663,330,330,663,10051};
static const unsigned int light100FanLow[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,663,330,330,663,330,663,330,663,330,663,663,330,10048};
static const unsigned int light100FanMed[] PROGMEM = {329,329,663,329,663,329,663,329,663,663,329,329,663,663,329,329,663,329,663,329,663,329,663,329,663,329,663,663,329,663,329,329,663,329,663,329,663,329,663,329,663,329,663,10031};
static const unsigned int light100FanHigh[] PROGMEM = {330,330,662,330,662,330,662,330,662,662,330,330,662,662,330,330,662,330,662,330,662,330,662,330,662,330,662,662,330,330,662,662,330,330,662,662,330,662,330,662,330,662,330,10042};

  server.send(204,"");
  String lastFanSpeed = read_String(50);
  String lastLightState = read_String(55);  
  String fanSpeed = server.arg("fanSpeed");
  String lightState = server.arg("lightState");
  
  if(fanSpeed == "same"){
    fanSpeed = lastFanSpeed;
  }
  else{
    lastFanSpeed = fanSpeed;
    writeString(50, fanSpeed);
  }
  
  if(lightState == "same"){
    lightState = lastLightState;
  }
  else{
    lastLightState = lightState;
    writeString(55, lightState);
  } 
  
  for (int i = 0; i <= IRrepeat; i++) {
     yield(); 
    if (lightState == "off") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(lightOffFanOff, 44,38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(lightOffFanLow, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(lightOffFanMed, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(lightOffFanHigh, 44, 38); // Send a raw data capture at 38kHz
        }
      }    
  else if (lightState == "20") {
        if(fanSpeed == "off"){
            sendRAW_Flash(light20FanOff, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light20FanLow, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light20FanMed, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light20FanHigh, 44, 38); // Send a raw data capture at 38kHz
        }   
  }
  else if (lightState == "30") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light30FanOff, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light20FanLow, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light30FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light30FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "40") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light40FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light40FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light40FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light40FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "50") {
        if(fanSpeed == "off"){
            sendRAW_Flash(light50FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light50FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light50FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light50FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "60") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light60FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light60FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light60FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light60FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "70") {
        yield();
        if(fanSpeed == "off"){
            sendRAW_Flash(light70FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light70FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light70FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light70FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "80") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light80FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light80FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light80FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light80FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }
    
  }
  else if (lightState == "90") {
        if(fanSpeed == "off"){
            sendRAW_Flash(light90FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light90FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light90FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light90FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "100") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light100FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light100FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light100FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light100FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }
      }    
  }
}

void set0110()
{  
//FAN CHQ8BT7096T DIP SWITCHES DN,UP,UP,DN OR 0110
static const unsigned int lightOffFanOff[] PROGMEM = {329,329,663,329,663,329,663,663,329,329,663,329,663,663,329,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,663,329,663,329,10036};
static const unsigned int lightOffFanLow[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,663,330,663,330,330,663,10046};
static const unsigned int lightOffFanMed[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,663,330,330,663,663,330,10051};
static const unsigned int lightOffFanHigh[] PROGMEM = {329,329,663,329,663,329,663,663,329,329,663,329,663,663,329,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,663,329,329,663,329,663,663,329,329,663,329,663,10044};
static const unsigned int light20FanOff[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,330,663,663,330,330,663,663,330,330,663,663,330,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,663,330,10038};
static const unsigned int light20FanLow[] PROGMEM = {330,330,662,330,662,330,662,662,330,330,662,330,662,662,330,330,662,662,330,330,662,662,330,330,662,330,662,662,330,662,330,662,330,330,662,330,662,662,330,330,662,330,662,10025};
static const unsigned int light20FanMed[] PROGMEM = {330,330,662,330,662,330,662,662,330,330,662,330,662,662,330,330,662,662,330,330,662,662,330,330,662,330,662,662,330,662,330,330,662,330,662,330,662,330,662,662,330,662,330,10042};
static const unsigned int light20FanHigh[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,330,663,663,330,330,663,663,330,330,663,663,330,330,663,330,663,663,330,330,663,663,330,330,663,330,663,330,663,663,330,330,663,10032};
static const unsigned int light30FanOff[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,330,663,663,330,330,663,663,330,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,10032};
static const unsigned int light30FanLow[] PROGMEM = {331,331,662,331,662,331,662,662,331,331,662,331,662,662,331,331,662,662,331,331,662,331,662,662,331,331,662,331,662,662,331,662,331,331,662,662,331,662,331,662,331,662,331,10042};
static const unsigned int light30FanMed[] PROGMEM = {330,330,662,330,662,330,662,662,330,330,662,330,662,662,330,330,662,662,330,330,662,330,662,662,330,330,662,330,662,662,330,330,662,330,662,662,330,662,330,662,330,330,662,10049};
static const unsigned int light30FanHigh[] PROGMEM = {330,330,662,330,662,330,662,662,330,330,662,330,662,662,330,330,662,662,330,330,662,330,662,662,330,330,662,330,662,330,662,662,330,330,662,662,330,662,330,330,662,662,330,10051};
static const unsigned int light40FanOff[] PROGMEM = {330,330,662,330,662,330,662,662,330,330,662,330,662,662,330,330,662,330,662,662,330,662,330,662,330,662,330,662,330,330,662,330,662,330,662,330,662,662,330,662,330,330,662,10038};
static const unsigned int light40FanLow[] PROGMEM = {331,331,662,331,662,331,662,662,331,331,662,331,662,662,331,331,662,331,662,662,331,662,331,662,331,662,331,662,331,662,331,662,331,331,662,662,331,331,662,331,662,662,331,10044};
static const unsigned int light40FanMed[] PROGMEM = {330,330,662,330,662,330,662,662,330,330,662,330,662,662,330,330,662,330,662,662,330,662,330,662,330,662,330,662,330,662,330,330,662,330,662,662,330,330,662,330,662,330,662,10032};
static const unsigned int light40FanHigh[] PROGMEM = {331,331,662,331,662,331,662,662,331,331,662,331,662,662,331,331,662,331,662,662,331,662,331,662,331,662,331,662,331,331,662,662,331,331,662,331,662,662,331,662,331,662,331,10040};
static const unsigned int light50FanOff[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,330,663,663,330,330,663,330,663,663,330,663,330,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,10036};
static const unsigned int light50FanLow[] PROGMEM = {330,330,662,330,662,330,662,662,330,330,662,330,662,662,330,330,662,330,662,662,330,662,330,330,662,662,330,330,662,662,330,662,330,330,662,330,662,662,330,330,662,330,662,10034};
static const unsigned int light50FanMed[] PROGMEM = {330,330,662,330,662,330,662,662,330,330,662,330,662,662,330,330,662,330,662,662,330,662,330,330,662,662,330,330,662,662,330,330,662,330,662,330,662,330,662,662,330,662,330,10044};
static const unsigned int light50FanHigh[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,330,663,663,330,330,663,330,663,663,330,663,330,330,663,663,330,330,663,330,663,663,330,330,663,330,663,330,663,663,330,330,663,10040};
static const unsigned int light60FanOff[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,330,663,663,330,330,663,330,663,663,330,330,663,663,330,330,663,663,330,330,663,330,663,330,663,663,330,663,330,330,663,330,663,10049};
static const unsigned int light60FanLow[] PROGMEM = {331,331,662,331,662,331,662,662,331,331,662,331,662,662,331,331,662,331,662,662,331,331,662,662,331,331,662,662,331,662,331,662,331,331,662,662,331,662,331,662,331,662,331,10051};
static const unsigned int light60FanMed[] PROGMEM = {330,330,662,330,662,330,662,662,330,330,662,330,662,662,330,330,662,330,662,662,330,330,662,662,330,330,662,662,330,662,330,330,662,330,662,662,330,662,330,662,330,330,662,10047};
static const unsigned int light60FanHigh[] PROGMEM = {330,330,662,330,662,330,662,662,330,330,662,330,662,662,330,330,662,330,662,662,330,330,662,662,330,330,662,662,330,330,662,662,330,330,662,662,330,662,330,330,662,662,330,10036};
static const unsigned int light70FanOff[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,330,663,663,330,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,663,330,10040};
static const unsigned int light70FanLow[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,330,663,663,330,330,663,330,663,663,330,330,663,330,663,330,663,330,663,663,330,663,330,330,663,663,330,330,663,663,330,330,663,10036};
static const unsigned int light70FanMed[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,330,663,663,330,330,663,330,663,663,330,330,663,330,663,330,663,330,663,663,330,330,663,330,663,663,330,330,663,330,663,663,330,10044};
static const unsigned int light70FanHigh[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,330,663,663,330,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,330,663,330,663,10047};
static const unsigned int light80FanOff[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,330,663,663,330,330,663,330,663,330,663,663,330,330,663,663,330,663,330,330,663,330,663,330,663,330,663,330,663,330,663,663,330,10036};
static const unsigned int light80FanLow[] PROGMEM = {330,330,662,330,662,330,662,662,330,330,662,330,662,662,330,330,662,330,662,330,662,662,330,330,662,662,330,662,330,662,330,662,330,330,662,330,662,662,330,330,662,330,662,10040};
static const unsigned int light80FanMed[] PROGMEM = {330,330,662,330,662,330,662,662,330,330,662,330,662,662,330,330,662,330,662,330,662,662,330,330,662,662,330,662,330,662,330,330,662,330,662,330,662,330,662,662,330,662,330,10029};
static const unsigned int light80FanHigh[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,330,663,663,330,330,663,330,663,330,663,663,330,330,663,663,330,663,330,330,663,663,330,330,663,330,663,330,663,663,330,330,663,10042};
static const unsigned int light90FanOff[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,330,663,663,330,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,10036};
static const unsigned int light90FanLow[] PROGMEM = {331,331,662,331,662,331,662,662,331,331,662,331,662,662,331,331,662,331,662,331,662,331,662,662,331,662,331,331,662,662,331,662,331,331,662,662,331,662,331,662,331,662,331,10053};
static const unsigned int light90FanMed[] PROGMEM = {330,330,662,330,662,330,662,662,330,330,662,330,662,662,330,330,662,330,662,330,662,330,662,662,330,662,330,330,662,662,330,330,662,330,662,662,330,662,330,662,330,330,662,10042};
static const unsigned int light90FanHigh[] PROGMEM = {330,330,662,330,662,330,662,662,330,330,662,330,662,662,330,330,662,330,662,330,662,330,662,662,330,662,330,330,662,330,662,662,330,330,662,662,330,662,330,330,662,662,330,10044};
static const unsigned int light100FanOff[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,663,330,663,330,663,330,10042};
static const unsigned int light100FanLow[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,663,330,330,663,663,330,330,663,663,330,330,663,10040};
static const unsigned int light100FanMed[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,663,330,330,663,330,663,663,330,10046};
static const unsigned int light100FanHigh[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,663,330,330,663,330,663,330,663,10055};

  server.send(204,"");
  String lastFanSpeed = read_String(60);
  String lastLightState = read_String(65);  
  String fanSpeed = server.arg("fanSpeed");
  String lightState = server.arg("lightState");
  
  if(fanSpeed == "same"){
    fanSpeed = lastFanSpeed;
  }
  else{
    lastFanSpeed = fanSpeed;
    writeString(60, fanSpeed);
  }
  
  if(lightState == "same"){
    lightState = lastLightState;
  }
  else{
    lastLightState = lightState;
    writeString(65, lightState);
  }
  
  for (int i = 0; i <= IRrepeat; i++) {
     yield(); 
    if (lightState == "off") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(lightOffFanOff, 44,38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(lightOffFanLow, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(lightOffFanMed, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(lightOffFanHigh, 44, 38); // Send a raw data capture at 38kHz
        }
      }    
  else if (lightState == "20") {
        if(fanSpeed == "off"){
            sendRAW_Flash(light20FanOff, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light20FanLow, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light20FanMed, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light20FanHigh, 44, 38); // Send a raw data capture at 38kHz
        }   
  }
  else if (lightState == "30") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light30FanOff, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light20FanLow, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light30FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light30FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "40") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light40FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light40FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light40FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light40FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "50") {
        if(fanSpeed == "off"){
            sendRAW_Flash(light50FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light50FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light50FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light50FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "60") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light60FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light60FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light60FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light60FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "70") {
        yield();
        if(fanSpeed == "off"){
            sendRAW_Flash(light70FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light70FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light70FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light70FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "80") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light80FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light80FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light80FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light80FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }
    
  }
  else if (lightState == "90") {
        if(fanSpeed == "off"){
            sendRAW_Flash(light90FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light90FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light90FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light90FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "100") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light100FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light100FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light100FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light100FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }
      }    
  }
}

void set0111()
{  
//FAN CHQ8BT7096T DIP SWITCHES DN,UP,UP,UP OR 0111
static const unsigned int lightOffFanOff[] PROGMEM = {329,329,664,329,664,329,664,329,664,329,664,329,664,664,329,329,664,329,664,329,664,329,664,329,664,329,664,329,664,329,664,329,664,329,664,329,664,329,664,664,329,329,664,10033};
static const unsigned int lightOffFanLow[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,663,330,330,663,663,330,10038};
static const unsigned int lightOffFanMed[] PROGMEM = {329,329,663,329,663,329,663,329,663,329,663,329,663,663,329,329,663,329,663,329,663,329,663,329,663,329,663,329,663,663,329,329,663,329,663,329,663,663,329,329,663,329,663,10036};
static const unsigned int lightOffFanHigh[] PROGMEM = {329,329,663,329,663,329,663,329,663,329,663,329,663,663,329,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,663,329,329,663,329,663,329,663,663,329,663,329,10046};
static const unsigned int light20FanOff[] PROGMEM = {329,329,663,329,663,329,663,329,663,329,663,329,663,663,329,329,663,663,329,329,663,663,329,329,663,329,663,663,329,329,663,329,663,329,663,329,663,329,663,329,663,329,663,10044};
static const unsigned int light20FanLow[] PROGMEM = {330,330,662,330,662,330,662,330,662,330,662,330,662,662,330,330,662,662,330,330,662,662,330,330,662,330,662,662,330,662,330,662,330,330,662,330,662,330,662,662,330,662,330,10035};
static const unsigned int light20FanMed[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,663,330,330,663,330,663,663,330,663,330,330,663,330,663,330,663,330,663,663,330,330,663,10036};
static const unsigned int light20FanHigh[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,663,330,330,663,330,663,663,330,330,663,663,330,330,663,330,663,330,663,330,663,663,330,10046};
static const unsigned int light30FanOff[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,663,330,10044};
static const unsigned int light30FanLow[] PROGMEM = {330,330,662,330,662,330,662,330,662,330,662,330,662,662,330,330,662,662,330,330,662,330,662,662,330,330,662,330,662,662,330,662,330,330,662,662,330,662,330,662,330,330,662,10038};
static const unsigned int light30FanMed[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,330,663,663,330,330,663,330,663,663,330,330,663,330,663,663,330,663,330,330,663,663,330,10046};
static const unsigned int light30FanHigh[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,330,663,663,330,330,663,330,663,330,663,663,330,330,663,663,330,663,330,330,663,330,663,10034};
static const unsigned int light40FanOff[] PROGMEM = {330,330,662,330,662,330,662,330,662,330,662,330,662,662,330,330,662,330,662,662,330,662,330,662,330,662,330,662,330,330,662,330,662,330,662,330,662,662,330,330,662,662,330,10029};
static const unsigned int light40FanLow[] PROGMEM = {330,330,662,330,662,330,662,330,662,330,662,330,662,662,330,330,662,330,662,662,330,662,330,662,330,662,330,662,330,662,330,662,330,330,662,662,330,330,662,330,662,330,662,10036};
static const unsigned int light40FanMed[] PROGMEM = {331,331,662,331,662,331,662,331,662,331,662,331,662,662,331,331,662,331,662,662,331,662,331,662,331,662,331,662,331,662,331,331,662,331,662,331,662,662,331,662,331,662,331,10040};
static const unsigned int light40FanHigh[] PROGMEM = {330,330,662,330,662,330,662,330,662,330,662,330,662,662,330,330,662,330,662,662,330,662,330,662,330,662,330,662,330,330,662,662,330,330,662,330,662,662,330,662,330,330,662,10034};
static const unsigned int light50FanOff[] PROGMEM = {329,329,663,329,663,329,663,329,663,329,663,329,663,663,329,329,663,329,663,663,329,663,329,329,663,663,329,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,10033};
static const unsigned int light50FanLow[] PROGMEM = {330,330,662,330,662,330,662,330,662,330,662,330,662,662,330,330,662,330,662,662,330,662,330,330,662,662,330,330,662,662,330,662,330,330,662,330,662,330,662,662,330,662,330,10036};
static const unsigned int light50FanMed[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,663,330,663,330,330,663,663,330,330,663,663,330,330,663,330,663,330,663,330,663,663,330,330,663,10040};
static const unsigned int light50FanHigh[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,663,330,663,330,330,663,663,330,330,663,330,663,663,330,330,663,330,663,330,663,330,663,663,330,10027};
static const unsigned int light60FanOff[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,663,330,330,663,663,330,330,663,663,330,330,663,330,663,330,663,663,330,330,663,663,330,663,330,10040};
static const unsigned int light60FanLow[] PROGMEM = {330,330,662,330,662,330,662,330,662,330,662,330,662,662,330,330,662,330,662,662,330,330,662,662,330,330,662,662,330,662,330,662,330,330,662,662,330,662,330,662,330,330,662,10042};
static const unsigned int light60FanMed[] PROGMEM = {330,330,662,330,662,330,662,330,662,330,662,330,662,662,330,330,662,330,662,662,330,330,662,662,330,330,662,662,330,662,330,330,662,330,662,662,330,662,330,330,662,662,330,10038};
static const unsigned int light60FanHigh[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,663,330,330,663,663,330,330,663,663,330,330,663,663,330,330,663,663,330,663,330,330,663,330,663,10038};
static const unsigned int light70FanOff[] PROGMEM = {329,329,663,329,663,329,663,329,663,329,663,329,663,663,329,329,663,329,663,663,329,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,663,329,663,329,329,663,10038};
static const unsigned int light70FanLow[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,663,330,330,663,330,663,330,663,330,663,663,330,663,330,330,663,663,330,330,663,330,663,663,330,10034};
static const unsigned int light70FanMed[] PROGMEM = {329,329,663,329,663,329,663,329,663,329,663,329,663,663,329,329,663,329,663,663,329,329,663,329,663,329,663,329,663,663,329,329,663,329,663,663,329,329,663,329,663,329,663,10027};
static const unsigned int light70FanHigh[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,663,330,663,330,663,330,10051};
static const unsigned int light80FanOff[] PROGMEM = {329,329,663,329,663,329,663,329,663,329,663,329,663,663,329,329,663,329,663,329,663,663,329,329,663,663,329,663,329,329,663,329,663,329,663,329,663,329,663,329,663,329,663,10038};
static const unsigned int light80FanLow[] PROGMEM = {330,330,662,330,662,330,662,330,662,330,662,330,662,662,330,330,662,330,662,330,662,662,330,330,662,662,330,662,330,662,330,662,330,330,662,330,662,330,662,662,330,662,330,10040};
static const unsigned int light80FanMed[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,663,330,330,663,663,330,663,330,663,330,330,663,330,663,330,663,330,663,663,330,330,663,10029};
static const unsigned int light80FanHigh[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,663,330,330,663,663,330,663,330,330,663,663,330,330,663,330,663,330,663,330,663,663,330,10042};
static const unsigned int light90FanOff[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,330,663,663,330,330,663,663,330,663,330,10047};
static const unsigned int light90FanLow[] PROGMEM = {330,330,662,330,662,330,662,330,662,330,662,330,662,662,330,330,662,330,662,330,662,330,662,662,330,662,330,330,662,662,330,662,330,330,662,662,330,662,330,662,330,330,662,10044};
static const unsigned int light90FanMed[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,663,330,663,330,330,663,663,330,330,663,330,663,663,330,663,330,330,663,663,330,10038};
static const unsigned int light90FanHigh[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,663,330,330,663,663,330,663,330,330,663,330,663,10044};
static const unsigned int light100FanOff[] PROGMEM = {329,329,663,329,663,329,663,329,663,329,663,329,663,663,329,329,663,329,663,329,663,329,663,329,663,329,663,663,329,329,663,329,663,329,663,329,663,663,329,663,329,329,663,10042};
static const unsigned int light100FanLow[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,663,330,330,663,663,330,330,663,330,663,663,330,10043};
static const unsigned int light100FanMed[] PROGMEM = {329,329,663,329,663,329,663,329,663,329,663,329,663,663,329,329,663,329,663,329,663,329,663,329,663,329,663,663,329,663,329,329,663,329,663,663,329,329,663,329,663,329,663,10036};
static const unsigned int light100FanHigh[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,330,663,663,330,663,330,663,330,10047};

  server.send(204,"");
  String lastFanSpeed = read_String(70);
  String lastLightState = read_String(75);  
  String fanSpeed = server.arg("fanSpeed");
  String lightState = server.arg("lightState");
  
  if(fanSpeed == "same"){
    fanSpeed = lastFanSpeed;
  }
  else{
    lastFanSpeed = fanSpeed;
    writeString(70, fanSpeed);
  }
  
  if(lightState == "same"){
    lightState = lastLightState;
  }
  else{
    lastLightState = lightState;
    writeString(75, lightState);
  }
  
  for (int i = 0; i <= IRrepeat; i++) {
     yield(); 
    if (lightState == "off") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(lightOffFanOff, 44,38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(lightOffFanLow, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(lightOffFanMed, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(lightOffFanHigh, 44, 38); // Send a raw data capture at 38kHz
        }
      }    
  else if (lightState == "20") {
        if(fanSpeed == "off"){
            sendRAW_Flash(light20FanOff, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light20FanLow, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light20FanMed, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light20FanHigh, 44, 38); // Send a raw data capture at 38kHz
        }   
  }
  else if (lightState == "30") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light30FanOff, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light20FanLow, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light30FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light30FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "40") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light40FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light40FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light40FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light40FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "50") {
        if(fanSpeed == "off"){
            sendRAW_Flash(light50FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light50FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light50FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light50FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "60") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light60FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light60FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light60FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light60FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "70") {
        yield();
        if(fanSpeed == "off"){
            sendRAW_Flash(light70FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light70FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light70FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light70FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "80") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light80FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light80FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light80FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light80FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }
    
  }
  else if (lightState == "90") {
        if(fanSpeed == "off"){
            sendRAW_Flash(light90FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light90FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light90FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light90FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "100") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light100FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light100FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light100FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light100FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }
      }    
  }
}

void set1000()
{  
//FAN CHQ8BT7096T DIP SWITCHES UP,DN,DN,DN OR 1000
static const unsigned int lightOffFanOff[] PROGMEM = {330,330,663,330,663,330,663,663,330,663,330,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,663,330,10028};
static const unsigned int lightOffFanLow[] PROGMEM = {330,330,663,330,663,330,663,663,330,663,330,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,330,663,330,663,10044};
static const unsigned int lightOffFanMed[] PROGMEM = {330,330,662,330,662,330,662,662,330,662,330,662,330,330,662,330,662,330,662,330,662,330,662,330,662,330,662,330,662,662,330,330,662,330,662,662,330,662,330,662,330,662,330,10045};
static const unsigned int lightOffFanHigh[] PROGMEM = {330,330,663,330,663,330,663,663,330,663,330,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,663,330,663,330,330,663,10041};
static const unsigned int light20FanOff[] PROGMEM = {330,330,662,330,662,330,662,662,330,662,330,662,330,330,662,330,662,662,330,330,662,662,330,330,662,330,662,662,330,330,662,330,662,330,662,662,330,330,662,662,330,662,330,10042};
static const unsigned int light20FanLow[] PROGMEM = {331,331,662,331,662,331,662,662,331,662,331,662,331,331,662,331,662,662,331,331,662,662,331,331,662,331,662,662,331,662,331,662,331,331,662,662,331,662,331,662,331,331,662,10036};
static const unsigned int light20FanMed[] PROGMEM = {331,331,662,331,662,331,662,662,331,662,331,662,331,331,662,331,662,662,331,331,662,662,331,331,662,331,662,662,331,662,331,331,662,331,662,662,331,662,331,331,662,662,331,10029};
static const unsigned int light20FanHigh[] PROGMEM = {330,330,662,330,662,330,662,662,330,662,330,662,330,330,662,330,662,662,330,330,662,662,330,330,662,330,662,662,330,330,662,662,330,330,662,662,330,662,330,330,662,330,662,10032};
static const unsigned int light30FanOff[] PROGMEM = {330,330,663,330,663,330,663,663,330,663,330,663,330,330,663,330,663,663,330,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,10039};
static const unsigned int light30FanLow[] PROGMEM = {330,330,662,330,662,330,662,662,330,662,330,662,330,330,662,330,662,662,330,330,662,330,662,662,330,330,662,330,662,662,330,662,330,330,662,662,330,330,662,330,662,662,330,10040};
static const unsigned int light30FanMed[] PROGMEM = {330,330,663,330,663,330,663,663,330,663,330,663,330,330,663,330,663,663,330,330,663,330,663,663,330,330,663,330,663,663,330,330,663,330,663,663,330,330,663,330,663,330,663,10046};
static const unsigned int light30FanHigh[] PROGMEM = {330,330,662,330,662,330,662,662,330,662,330,662,330,330,662,330,662,662,330,330,662,330,662,662,330,330,662,330,662,330,662,662,330,330,662,330,662,662,330,662,330,662,330,10040};
static const unsigned int light40FanOff[] PROGMEM = {330,330,662,330,662,330,662,662,330,662,330,662,330,330,662,330,662,330,662,662,330,662,330,662,330,662,330,662,330,330,662,330,662,330,662,330,662,330,662,330,662,330,662,10045};
static const unsigned int light40FanLow[] PROGMEM = {331,331,662,331,662,331,662,662,331,662,331,662,331,331,662,331,662,331,662,662,331,662,331,662,331,662,331,662,331,662,331,662,331,331,662,331,662,331,662,662,331,662,331,10051};
static const unsigned int light40FanMed[] PROGMEM = {331,331,662,331,662,331,662,662,331,662,331,662,331,331,662,331,662,331,662,662,331,662,331,662,331,662,331,662,331,662,331,331,662,331,662,331,662,331,662,662,331,331,662,10028};
static const unsigned int light40FanHigh[] PROGMEM = {331,331,662,331,662,331,662,662,331,662,331,662,331,331,662,331,662,331,662,662,331,662,331,662,331,662,331,662,331,331,662,662,331,331,662,331,662,331,662,331,662,662,331,10042};
static const unsigned int light50FanOff[] PROGMEM = {330,330,662,330,662,330,662,662,330,662,330,662,330,330,662,330,662,330,662,662,330,662,330,330,662,662,330,330,662,330,662,330,662,330,662,662,330,330,662,662,330,662,330,10036};
static const unsigned int light50FanLow[] PROGMEM = {331,331,662,331,662,331,662,662,331,662,331,662,331,331,662,331,662,331,662,662,331,662,331,331,662,662,331,331,662,662,331,662,331,331,662,662,331,662,331,662,331,331,662,10061};
static const unsigned int light50FanMed[] PROGMEM = {331,331,662,331,662,331,662,662,331,662,331,662,331,331,662,331,662,331,662,662,331,662,331,331,662,662,331,331,662,662,331,331,662,331,662,662,331,662,331,331,662,662,331,10040};
static const unsigned int light50FanHigh[] PROGMEM = {330,330,662,330,662,330,662,662,330,662,330,662,330,330,662,330,662,330,662,662,330,662,330,330,662,662,330,330,662,330,662,662,330,330,662,662,330,662,330,330,662,330,662,10043};
static const unsigned int light60FanOff[] PROGMEM = {330,330,662,330,662,330,662,662,330,662,330,662,330,330,662,330,662,330,662,662,330,330,662,662,330,330,662,662,330,330,662,330,662,330,662,330,662,662,330,662,330,330,662,10036};
static const unsigned int light60FanLow[] PROGMEM = {331,331,662,331,662,331,662,662,331,662,331,662,331,331,662,331,662,331,662,662,331,331,662,662,331,331,662,662,331,662,331,662,331,331,662,662,331,331,662,331,662,662,331,10030};
static const unsigned int light60FanMed[] PROGMEM = {330,330,662,330,662,330,662,662,330,662,330,662,330,330,662,330,662,330,662,662,330,330,662,662,330,330,662,662,330,662,330,330,662,330,662,662,330,330,662,330,662,330,662,10034};
static const unsigned int light60FanHigh[] PROGMEM = {331,331,662,331,662,331,662,662,331,662,331,662,331,331,662,331,662,331,662,662,331,331,662,662,331,331,662,662,331,331,662,662,331,331,662,331,662,662,331,662,331,662,331,10036};
static const unsigned int light70FanOff[] PROGMEM = {330,330,663,330,663,330,663,663,330,663,330,663,330,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,10051};
static const unsigned int light70FanLow[] PROGMEM = {330,330,663,330,663,330,663,663,330,663,330,663,330,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,663,330,330,663,330,663,10044};
static const unsigned int light70FanMed[] PROGMEM = {330,330,663,330,663,330,663,663,330,663,330,663,330,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,663,330,663,330,10034};
static const unsigned int light70FanHigh[] PROGMEM = {330,330,663,330,663,330,663,663,330,663,330,663,330,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,663,330,330,663,10030};
static const unsigned int light80FanOff[] PROGMEM = {330,330,662,330,662,330,662,662,330,662,330,662,330,330,662,330,662,330,662,330,662,662,330,330,662,662,330,662,330,330,662,330,662,330,662,662,330,330,662,662,330,662,330,10045};
static const unsigned int light80FanLow[] PROGMEM = {331,331,662,331,662,331,662,662,331,662,331,662,331,331,662,331,662,331,662,331,662,662,331,331,662,662,331,662,331,662,331,662,331,331,662,662,331,662,331,662,331,331,662,10049};
static const unsigned int light80FanMed[] PROGMEM = {331,331,662,331,662,331,662,662,331,662,331,662,331,331,662,331,662,331,662,331,662,662,331,331,662,662,331,662,331,662,331,331,662,331,662,662,331,662,331,331,662,662,331,10051};
static const unsigned int light80FanHigh[] PROGMEM = {330,330,662,330,662,330,662,662,330,662,330,662,330,330,662,330,662,330,662,330,662,662,330,330,662,662,330,662,330,330,662,662,330,330,662,662,330,662,330,330,662,330,662,10034};
static const unsigned int light90FanOff[] PROGMEM = {330,330,663,330,663,330,663,663,330,663,330,663,330,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,10040};
static const unsigned int light90FanLow[] PROGMEM = {330,330,662,330,662,330,662,662,330,662,330,662,330,330,662,330,662,330,662,330,662,330,662,662,330,662,330,330,662,662,330,662,330,330,662,662,330,330,662,330,662,662,330,10038};
static const unsigned int light90FanMed[] PROGMEM = {330,330,663,330,663,330,663,663,330,663,330,663,330,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,663,330,330,663,330,663,663,330,330,663,330,663,330,663,10040};
static const unsigned int light90FanHigh[] PROGMEM = {330,330,662,330,662,330,662,662,330,662,330,662,330,330,662,330,662,330,662,330,662,330,662,662,330,662,330,330,662,330,662,662,330,330,662,330,662,662,330,662,330,662,330,10034};
static const unsigned int light100FanOff[] PROGMEM = {330,330,663,330,663,330,663,663,330,663,330,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,663,330,10047};
static const unsigned int light100FanLow[] PROGMEM = {330,330,663,330,663,330,663,663,330,663,330,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,663,330,330,663,330,663,663,330,330,663,330,663,10043};
static const unsigned int light100FanMed[] PROGMEM = {330,330,663,330,663,330,663,663,330,663,330,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,330,663,663,330,663,330,10049};
static const unsigned int light100FanHigh[] PROGMEM = {330,330,663,330,663,330,663,663,330,663,330,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,330,663,330,663,663,330,330,663,10045};

  server.send(204,"");
  String lastFanSpeed = read_String(80);
  String lastLightState = read_String(85);  
  String fanSpeed = server.arg("fanSpeed");
  String lightState = server.arg("lightState");
  
  if(fanSpeed == "same"){
    fanSpeed = lastFanSpeed;
  }
  else{
    lastFanSpeed = fanSpeed;
    writeString(80, fanSpeed);
  }
  
  if(lightState == "same"){
    lightState = lastLightState;
  }
  else{
    lastLightState = lightState;
    writeString(85, lightState);
  }
  
  for (int i = 0; i <= IRrepeat; i++) {
     yield(); 
    if (lightState == "off") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(lightOffFanOff, 44,38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(lightOffFanLow, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(lightOffFanMed, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(lightOffFanHigh, 44, 38); // Send a raw data capture at 38kHz
        }
      }    
  else if (lightState == "20") {
        if(fanSpeed == "off"){
            sendRAW_Flash(light20FanOff, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light20FanLow, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light20FanMed, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light20FanHigh, 44, 38); // Send a raw data capture at 38kHz
        }   
  }
  else if (lightState == "30") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light30FanOff, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light20FanLow, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light30FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light30FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "40") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light40FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light40FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light40FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light40FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "50") {
        if(fanSpeed == "off"){
            sendRAW_Flash(light50FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light50FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light50FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light50FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "60") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light60FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light60FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light60FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light60FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "70") {
        yield();
        if(fanSpeed == "off"){
            sendRAW_Flash(light70FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light70FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light70FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light70FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "80") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light80FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light80FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light80FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light80FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }
    
  }
  else if (lightState == "90") {
        if(fanSpeed == "off"){
            sendRAW_Flash(light90FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light90FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light90FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light90FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "100") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light100FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light100FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light100FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light100FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }
      }    
  }
}

void set1001()
{  
//FAN CHQ8BT7096T DIP SWITCHES UP,DN,DN,UP OR 1001
static const unsigned int lightOffFanOff[] PROGMEM = {329,329,663,329,663,329,663,329,663,663,329,663,329,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,663,329,663,329,329,663,329,663,10040};
static const unsigned int lightOffFanLow[] PROGMEM = {330,330,662,330,662,330,662,330,662,662,330,662,330,330,662,330,662,330,662,330,662,330,662,330,662,330,662,330,662,662,330,662,330,330,662,662,330,662,330,662,330,662,330,10044};
static const unsigned int lightOffFanMed[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,663,330,663,330,663,330,330,663,10040};
static const unsigned int lightOffFanHigh[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,663,330,330,663,663,330,10042};
static const unsigned int light20FanOff[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,663,330,330,663,663,330,330,663,330,663,663,330,330,663,330,663,330,663,663,330,330,663,663,330,330,663,10044};
static const unsigned int light20FanLow[] PROGMEM = {331,331,662,331,662,331,662,331,662,662,331,662,331,331,662,331,662,662,331,331,662,662,331,331,662,331,662,662,331,662,331,662,331,331,662,662,331,662,331,331,662,662,331,10033};
static const unsigned int light20FanMed[] PROGMEM = {330,330,662,330,662,330,662,330,662,662,330,662,330,330,662,330,662,662,330,330,662,662,330,330,662,330,662,662,330,662,330,330,662,330,662,662,330,662,330,330,662,330,662,10034};
static const unsigned int light20FanHigh[] PROGMEM = {330,330,662,330,662,330,662,330,662,662,330,662,330,330,662,330,662,662,330,330,662,662,330,330,662,330,662,662,330,330,662,662,330,330,662,662,330,330,662,662,330,662,330,10042};
static const unsigned int light30FanOff[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,663,330,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,10038};
static const unsigned int light30FanLow[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,663,330,330,663,330,663,663,330,330,663,330,663,663,330,663,330,330,663,663,330,330,663,330,663,330,663,10042};
static const unsigned int light30FanMed[] PROGMEM = {330,330,662,330,662,330,662,330,662,662,330,662,330,330,662,330,662,662,330,330,662,330,662,662,330,330,662,330,662,662,330,330,662,330,662,330,662,662,330,662,330,662,330,10044};
static const unsigned int light30FanHigh[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,663,330,330,663,330,663,663,330,330,663,330,663,330,663,663,330,330,663,330,663,663,330,663,330,330,663,10034};
static const unsigned int light40FanOff[] PROGMEM = {331,331,662,331,662,331,662,331,662,662,331,662,331,331,662,331,662,331,662,662,331,662,331,662,331,662,331,662,331,331,662,331,662,331,662,662,331,662,331,662,331,662,331,10045};
static const unsigned int light40FanLow[] PROGMEM = {331,331,662,331,662,331,662,331,662,662,331,662,331,331,662,331,662,331,662,662,331,662,331,662,331,662,331,662,331,662,331,662,331,331,662,331,662,331,662,662,331,331,662,10040};
static const unsigned int light40FanMed[] PROGMEM = {330,330,662,330,662,330,662,330,662,662,330,662,330,330,662,330,662,330,662,662,330,662,330,662,330,662,330,662,330,662,330,330,662,330,662,330,662,330,662,330,662,662,330,10038};
static const unsigned int light40FanHigh[] PROGMEM = {330,330,662,330,662,330,662,330,662,662,330,662,330,330,662,330,662,330,662,662,330,662,330,662,330,662,330,662,330,330,662,662,330,330,662,330,662,330,662,330,662,330,662,10040};
static const unsigned int light50FanOff[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,663,330,663,330,330,663,663,330,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,10040};
static const unsigned int light50FanLow[] PROGMEM = {331,331,662,331,662,331,662,331,662,662,331,662,331,331,662,331,662,331,662,662,331,662,331,331,662,662,331,331,662,662,331,662,331,331,662,662,331,662,331,331,662,662,331,10040};
static const unsigned int light50FanMed[] PROGMEM = {330,330,662,330,662,330,662,330,662,662,330,662,330,330,662,330,662,330,662,662,330,662,330,330,662,662,330,330,662,662,330,330,662,330,662,662,330,662,330,330,662,330,662,10034};
static const unsigned int light50FanHigh[] PROGMEM = {330,330,662,330,662,330,662,330,662,662,330,662,330,330,662,330,662,330,662,662,330,662,330,330,662,662,330,330,662,330,662,662,330,330,662,662,330,330,662,662,330,662,330,10036};
static const unsigned int light60FanOff[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,663,330,330,663,663,330,330,663,663,330,330,663,330,663,330,663,330,663,663,330,330,663,663,330,10038};
static const unsigned int light60FanLow[] PROGMEM = {330,330,662,330,662,330,662,330,662,662,330,662,330,330,662,330,662,330,662,662,330,330,662,662,330,330,662,662,330,662,330,662,330,330,662,662,330,330,662,330,662,330,662,10040};
static const unsigned int light60FanMed[] PROGMEM = {330,330,662,330,662,330,662,330,662,662,330,662,330,330,662,330,662,330,662,662,330,330,662,662,330,330,662,662,330,662,330,330,662,330,662,330,662,662,330,662,330,662,330,10042};
static const unsigned int light60FanHigh[] PROGMEM = {330,330,662,330,662,330,662,330,662,662,330,662,330,330,662,330,662,330,662,662,330,330,662,662,330,330,662,662,330,330,662,662,330,330,662,330,662,662,330,662,330,330,662,10028};
static const unsigned int light70FanOff[] PROGMEM = {329,329,663,329,663,329,663,329,663,663,329,663,329,329,663,329,663,329,663,663,329,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,10034};
static const unsigned int light70FanLow[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,663,330,663,330,10038};
static const unsigned int light70FanMed[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,663,330,330,663,10049};
static const unsigned int light70FanHigh[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,663,330,10045};
static const unsigned int light80FanOff[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,330,663,663,330,330,663,663,330,663,330,330,663,330,663,330,663,663,330,330,663,663,330,330,663,10036};
static const unsigned int light80FanLow[] PROGMEM = {331,331,662,331,662,331,662,331,662,662,331,662,331,331,662,331,662,331,662,331,662,662,331,331,662,662,331,662,331,662,331,662,331,331,662,662,331,662,331,331,662,662,331,10042};
static const unsigned int light80FanMed[] PROGMEM = {330,330,662,330,662,330,662,330,662,662,330,662,330,330,662,330,662,330,662,330,662,662,330,330,662,662,330,662,330,662,330,330,662,330,662,662,330,662,330,330,662,330,662,10028};
static const unsigned int light80FanHigh[] PROGMEM = {330,330,662,330,662,330,662,330,662,662,330,662,330,330,662,330,662,330,662,330,662,662,330,330,662,662,330,662,330,330,662,662,330,330,662,662,330,330,662,662,330,662,330,10036};
static const unsigned int light90FanOff[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,10045};
static const unsigned int light90FanLow[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,663,330,663,330,330,663,663,330,330,663,330,663,330,663,10038};
static const unsigned int light90FanMed[] PROGMEM = {330,330,662,330,662,330,662,330,662,662,330,662,330,330,662,330,662,330,662,330,662,330,662,662,330,662,330,330,662,662,330,330,662,330,662,330,662,662,330,662,330,662,330,10042};
static const unsigned int light90FanHigh[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,663,330,330,663,330,663,663,330,663,330,330,663,10034};
static const unsigned int light100FanOff[] PROGMEM = {329,329,663,329,663,329,663,329,663,663,329,663,329,329,663,329,663,329,663,329,663,329,663,329,663,329,663,663,329,329,663,329,663,329,663,329,663,329,663,329,663,329,663,10044};
static const unsigned int light100FanLow[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,663,330,330,663,330,663,330,663,663,330,663,330,10045};
static const unsigned int light100FanMed[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,330,663,663,330,330,663,10038};
static const unsigned int light100FanHigh[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,330,663,330,663,330,663,663,330,10040};

  server.send(204,"");
  String lastFanSpeed = read_String(90);
  String lastLightState = read_String(95);  
  String fanSpeed = server.arg("fanSpeed");
  String lightState = server.arg("lightState");
  
  if(fanSpeed == "same"){
    fanSpeed = lastFanSpeed;
  }
  else{
    lastFanSpeed = fanSpeed;
    writeString(90, fanSpeed);
  }
  
  if(lightState == "same"){
    lightState = lastLightState;
  }
  else{
    lastLightState = lightState;
    writeString(95, lightState);
  }
  
  for (int i = 0; i <= IRrepeat; i++) {
     yield(); 
    if (lightState == "off") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(lightOffFanOff, 44,38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(lightOffFanLow, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(lightOffFanMed, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(lightOffFanHigh, 44, 38); // Send a raw data capture at 38kHz
        }
      }    
  else if (lightState == "20") {
        if(fanSpeed == "off"){
            sendRAW_Flash(light20FanOff, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light20FanLow, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light20FanMed, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light20FanHigh, 44, 38); // Send a raw data capture at 38kHz
        }   
  }
  else if (lightState == "30") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light30FanOff, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light20FanLow, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light30FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light30FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "40") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light40FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light40FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light40FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light40FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "50") {
        if(fanSpeed == "off"){
            sendRAW_Flash(light50FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light50FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light50FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light50FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "60") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light60FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light60FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light60FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light60FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "70") {
        yield();
        if(fanSpeed == "off"){
            sendRAW_Flash(light70FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light70FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light70FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light70FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "80") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light80FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light80FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light80FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light80FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }
    
  }
  else if (lightState == "90") {
        if(fanSpeed == "off"){
            sendRAW_Flash(light90FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light90FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light90FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light90FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "100") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light100FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light100FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light100FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light100FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }
      }    
  }
}

void set1010()
{  
//FAN CHQ8BT7096T DIP SWITCHES UP,DN,UP,DN OR 1010
static const unsigned int lightOffFanOff[] PROGMEM = {329,329,663,329,663,329,663,663,329,329,663,663,329,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,663,329,329,663,663,329,10034};
static const unsigned int lightOffFanLow[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,663,330,330,663,330,663,330,663,10042};
static const unsigned int lightOffFanMed[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,663,330,663,330,663,330,10049};
static const unsigned int lightOffFanHigh[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,663,330,663,330,330,663,10042};
static const unsigned int light20FanOff[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,663,330,330,663,330,663,663,330,330,663,663,330,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,663,330,663,330,10042};
static const unsigned int light20FanLow[] PROGMEM = {330,330,662,330,662,330,662,662,330,330,662,662,330,330,662,330,662,662,330,330,662,662,330,330,662,330,662,662,330,662,330,662,330,330,662,330,662,662,330,662,330,330,662,10033};
static const unsigned int light20FanMed[] PROGMEM = {330,330,662,330,662,330,662,662,330,330,662,662,330,330,662,330,662,662,330,330,662,662,330,330,662,330,662,662,330,662,330,330,662,330,662,330,662,662,330,330,662,662,330,10060};
static const unsigned int light20FanHigh[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,663,330,330,663,330,663,663,330,330,663,663,330,330,663,330,663,663,330,330,663,663,330,330,663,330,663,663,330,330,663,330,663,10038};
static const unsigned int light30FanOff[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,663,330,330,663,330,663,663,330,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,663,330,663,330,663,330,330,663,10044};
static const unsigned int light30FanLow[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,663,330,330,663,330,663,663,330,330,663,330,663,663,330,330,663,330,663,663,330,663,330,330,663,330,663,330,663,330,663,663,330,10040};
static const unsigned int light30FanMed[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,663,330,330,663,330,663,663,330,330,663,330,663,663,330,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,10034};
static const unsigned int light30FanHigh[] PROGMEM = {330,330,662,330,662,330,662,662,330,330,662,662,330,330,662,330,662,662,330,330,662,330,662,662,330,330,662,330,662,330,662,662,330,330,662,662,330,662,330,662,330,662,330,10031};
static const unsigned int light40FanOff[] PROGMEM = {330,330,662,330,662,330,662,662,330,330,662,662,330,330,662,330,662,330,662,662,330,662,330,662,330,662,330,662,330,330,662,330,662,330,662,662,330,330,662,330,662,330,662,10047};
static const unsigned int light40FanLow[] PROGMEM = {331,331,662,331,662,331,662,662,331,331,662,662,331,331,662,331,662,331,662,662,331,662,331,662,331,662,331,662,331,662,331,662,331,331,662,662,331,331,662,662,331,662,331,10042};
static const unsigned int light40FanMed[] PROGMEM = {331,331,662,331,662,331,662,662,331,331,662,662,331,331,662,331,662,331,662,662,331,662,331,662,331,662,331,662,331,662,331,331,662,331,662,662,331,331,662,662,331,331,662,10044};
static const unsigned int light40FanHigh[] PROGMEM = {331,331,662,331,662,331,662,662,331,331,662,662,331,331,662,331,662,331,662,662,331,662,331,662,331,662,331,662,331,331,662,662,331,331,662,662,331,331,662,331,662,662,331,10031};
static const unsigned int light50FanOff[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,663,330,330,663,330,663,330,663,663,330,663,330,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,10046};
static const unsigned int light50FanLow[] PROGMEM = {330,330,662,330,662,330,662,662,330,330,662,662,330,330,662,330,662,330,662,662,330,662,330,330,662,662,330,330,662,662,330,662,330,330,662,330,662,662,330,662,330,330,662,10038};
static const unsigned int light50FanMed[] PROGMEM = {330,330,662,330,662,330,662,662,330,330,662,662,330,330,662,330,662,330,662,662,330,662,330,330,662,662,330,330,662,662,330,330,662,330,662,330,662,662,330,330,662,662,330,10027};
static const unsigned int light50FanHigh[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,663,330,330,663,330,663,330,663,663,330,663,330,330,663,663,330,330,663,330,663,663,330,330,663,330,663,663,330,330,663,330,663,10023};
static const unsigned int light60FanOff[] PROGMEM = {330,330,662,330,662,330,662,662,330,330,662,662,330,330,662,330,662,330,662,662,330,330,662,662,330,330,662,662,330,330,662,330,662,330,662,662,330,662,330,662,330,330,662,10049};
static const unsigned int light60FanLow[] PROGMEM = {330,330,662,330,662,330,662,662,330,330,662,662,330,330,662,330,662,330,662,662,330,330,662,662,330,330,662,662,330,662,330,662,330,330,662,330,662,330,662,330,662,662,330,10038};
static const unsigned int light60FanMed[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,663,330,330,663,330,663,330,663,663,330,330,663,663,330,330,663,663,330,663,330,330,663,330,663,330,663,330,663,330,663,330,663,10049};
static const unsigned int light60FanHigh[] PROGMEM = {331,331,662,331,662,331,662,662,331,331,662,662,331,331,662,331,662,331,662,662,331,331,662,662,331,331,662,662,331,331,662,662,331,331,662,662,331,662,331,662,331,662,331,10042};
static const unsigned int light70FanOff[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,663,330,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,663,330,10040};
static const unsigned int light70FanLow[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,663,330,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,663,330,663,330,330,663,663,330,663,330,330,663,330,663,10047};
static const unsigned int light70FanMed[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,663,330,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,663,330,330,663,330,663,663,330,330,663,663,330,663,330,10032};
static const unsigned int light70FanHigh[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,663,330,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,663,330,330,663,10040};
static const unsigned int light80FanOff[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,663,330,330,663,330,663,330,663,330,663,663,330,330,663,663,330,663,330,330,663,330,663,330,663,330,663,330,663,663,330,663,330,10036};
static const unsigned int light80FanLow[] PROGMEM = {330,330,662,330,662,330,662,662,330,330,662,662,330,330,662,330,662,330,662,330,662,662,330,330,662,662,330,662,330,662,330,662,330,330,662,330,662,662,330,662,330,330,662,10034};
static const unsigned int light80FanMed[] PROGMEM = {330,330,662,330,662,330,662,662,330,330,662,662,330,330,662,330,662,330,662,330,662,662,330,330,662,662,330,662,330,662,330,330,662,330,662,330,662,662,330,330,662,662,330,10047};
static const unsigned int light80FanHigh[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,663,330,330,663,330,663,330,663,330,663,663,330,330,663,663,330,663,330,330,663,663,330,330,663,330,663,663,330,330,663,330,663,10034};
static const unsigned int light90FanOff[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,663,330,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,330,663,663,330,663,330,663,330,330,663,10038};
static const unsigned int light90FanLow[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,663,330,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,663,330,663,330,330,663,330,663,330,663,330,663,663,330,10036};
static const unsigned int light90FanMed[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,663,330,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,10048};
static const unsigned int light90FanHigh[] PROGMEM = {330,330,662,330,662,330,662,662,330,330,662,662,330,330,662,330,662,330,662,330,662,330,662,662,330,662,330,330,662,330,662,662,330,330,662,662,330,662,330,662,330,662,330,10042};
static const unsigned int light100FanOff[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,663,330,330,663,330,663,663,330,10042};
static const unsigned int light100FanLow[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,663,330,330,663,663,330,663,330,330,663,330,663,10033};
static const unsigned int light100FanMed[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,663,330,330,663,663,330,663,330,10038};
static const unsigned int light100FanHigh[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,663,330,330,663,663,330,330,663,10042};

  server.send(204,"");
  String lastFanSpeed = read_String(100);
  String lastLightState = read_String(105);  
  String fanSpeed = server.arg("fanSpeed");
  String lightState = server.arg("lightState");
  
  if(fanSpeed == "same"){
    fanSpeed = lastFanSpeed;
  }
  else{
    lastFanSpeed = fanSpeed;
    writeString(100, fanSpeed);
  }
  
  if(lightState == "same"){
    lightState = lastLightState;
  }
  else{
    lastLightState = lightState;
    writeString(105, lightState);
  }  
  
  for (int i = 0; i <= IRrepeat; i++) {
     yield(); 
    if (lightState == "off") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(lightOffFanOff, 44,38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(lightOffFanLow, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(lightOffFanMed, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(lightOffFanHigh, 44, 38); // Send a raw data capture at 38kHz
        }
      }    
  else if (lightState == "20") {
        if(fanSpeed == "off"){
            sendRAW_Flash(light20FanOff, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light20FanLow, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light20FanMed, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light20FanHigh, 44, 38); // Send a raw data capture at 38kHz
        }   
  }
  else if (lightState == "30") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light30FanOff, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light20FanLow, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light30FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light30FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "40") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light40FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light40FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light40FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light40FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "50") {
        if(fanSpeed == "off"){
            sendRAW_Flash(light50FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light50FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light50FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light50FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "60") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light60FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light60FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light60FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light60FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "70") {
        yield();
        if(fanSpeed == "off"){
            sendRAW_Flash(light70FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light70FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light70FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light70FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "80") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light80FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light80FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light80FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light80FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }
    
  }
  else if (lightState == "90") {
        if(fanSpeed == "off"){
            sendRAW_Flash(light90FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light90FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light90FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light90FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "100") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light100FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light100FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light100FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light100FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }
      }    
  }
}

void set1011()
{  
//Remote CHQ8BT7096T DIP SWITCHES UP,DN,UP,UP OR 1011

static const unsigned int lightOffFanOff[] PROGMEM = {329,329,664,329,664,329,664,329,664,329,664,664,329,329,664,329,664,329,664,329,664,329,664,329,664,329,664,329,664,329,664,329,664,329,664,329,664,664,329,329,664,329,664,10044};
static const unsigned int lightOffFanLow[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,663,330,663,330,663,330,10028};
static const unsigned int lightOffFanMed[] PROGMEM = {329,329,663,329,663,329,663,329,663,329,663,663,329,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,663,329,329,663,329,663,329,663,663,329,663,329,329,663,10028};
static const unsigned int lightOffFanHigh[] PROGMEM = {329,329,663,329,663,329,663,329,663,329,663,663,329,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,663,329,329,663,329,663,663,329,329,663,663,329,10026};
static const unsigned int light20FanOff[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,663,330,330,663,663,330,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,663,330,330,663,10051};
static const unsigned int light20FanLow[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,663,330,330,663,663,330,330,663,330,663,663,330,663,330,663,330,330,663,330,663,663,330,330,663,663,330,10045};
static const unsigned int light20FanMed[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,663,330,330,663,663,330,330,663,330,663,663,330,663,330,330,663,330,663,330,663,663,330,330,663,330,663,10041};
static const unsigned int light20FanHigh[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,663,330,330,663,663,330,330,663,330,663,663,330,330,663,663,330,330,663,330,663,330,663,663,330,663,330,10041};
static const unsigned int light30FanOff[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,663,330,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,663,330,10041};
static const unsigned int light30FanLow[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,663,330,330,663,330,663,663,330,330,663,330,663,663,330,663,330,330,663,330,663,330,663,330,663,330,663,10053};
static const unsigned int light30FanMed[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,663,330,330,663,330,663,663,330,330,663,330,663,663,330,330,663,330,663,663,330,663,330,663,330,663,330,10041};
static const unsigned int light30FanHigh[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,663,330,330,663,330,663,663,330,330,663,330,663,330,663,663,330,330,663,663,330,663,330,663,330,330,663,10034};
static const unsigned int light40FanOff[] PROGMEM = {331,331,662,331,662,331,662,331,662,331,662,662,331,331,662,331,662,331,662,662,331,662,331,662,331,662,331,662,331,331,662,331,662,331,662,331,662,662,331,662,331,662,331,10036};
static const unsigned int light40FanLow[] PROGMEM = {331,331,662,331,662,331,662,331,662,331,662,662,331,331,662,331,662,331,662,662,331,662,331,662,331,662,331,662,331,662,331,662,331,331,662,662,331,331,662,662,331,331,662,10041};
static const unsigned int light40FanMed[] PROGMEM = {331,331,662,331,662,331,662,331,662,331,662,662,331,331,662,331,662,331,662,662,331,662,331,662,331,662,331,662,331,662,331,331,662,331,662,662,331,331,662,331,662,662,331,10041};
static const unsigned int light40FanHigh[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,663,330,663,330,663,330,663,330,663,330,330,663,663,330,330,663,663,330,330,663,330,663,330,663,10053};
static const unsigned int light50FanOff[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,663,330,663,330,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,10041};
static const unsigned int light50FanLow[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,663,330,663,330,330,663,663,330,330,663,663,330,663,330,330,663,330,663,663,330,330,663,663,330,10041};
static const unsigned int light50FanMed[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,663,330,663,330,330,663,663,330,330,663,663,330,330,663,330,663,330,663,663,330,330,663,330,663,10048};
static const unsigned int light50FanHigh[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,663,330,663,330,330,663,663,330,330,663,330,663,663,330,330,663,330,663,330,663,663,330,663,330,10052};
static const unsigned int light60FanOff[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,663,330,330,663,663,330,330,663,663,330,330,663,330,663,330,663,663,330,663,330,330,663,663,330,10039};
static const unsigned int light60FanLow[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,663,330,330,663,663,330,330,663,663,330,663,330,663,330,330,663,330,663,330,663,330,663,330,663,10034};
static const unsigned int light60FanMed[] PROGMEM = {331,331,662,331,662,331,662,331,662,331,662,662,331,331,662,331,662,331,662,662,331,331,662,662,331,331,662,662,331,662,331,331,662,331,662,662,331,662,331,662,331,662,331,10039};
static const unsigned int light60FanHigh[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,663,330,330,663,663,330,330,663,663,330,330,663,663,330,330,663,663,330,663,330,663,330,330,663,10056};
static const unsigned int light70FanOff[] PROGMEM = {329,329,664,329,664,329,664,329,664,329,664,664,329,329,664,329,664,329,664,664,329,329,664,329,664,329,664,329,664,329,664,329,664,329,664,664,329,329,664,329,664,329,664,10039};
static const unsigned int light70FanLow[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,663,330,663,330,330,663,663,330,330,663,663,330,663,330,10039};
static const unsigned int light70FanMed[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,663,330,330,663,330,663,663,330,330,663,663,330,330,663,10049};
static const unsigned int light70FanHigh[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,330,663,663,330,10049};
static const unsigned int light80FanOff[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,663,330,330,663,663,330,663,330,330,663,330,663,330,663,330,663,330,663,663,330,330,663,10047};
static const unsigned int light80FanLow[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,663,330,330,663,663,330,663,330,663,330,663,330,330,663,330,663,663,330,330,663,663,330,10049};
static const unsigned int light80FanMed[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,663,330,330,663,663,330,663,330,663,330,330,663,330,663,330,663,663,330,330,663,330,663,10047};
static const unsigned int light80FanHigh[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,663,330,330,663,663,330,663,330,330,663,663,330,330,663,330,663,330,663,663,330,663,330,10045};
static const unsigned int light90FanOff[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,330,663,663,330,663,330,330,663,663,330,10054};
static const unsigned int light90FanLow[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,663,330,663,330,330,663,330,663,330,663,330,663,330,663,10034};
static const unsigned int light90FanMed[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,663,330,330,663,330,663,663,330,663,330,663,330,663,330,10037};
static const unsigned int light90FanHigh[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,663,330,330,663,663,330,663,330,663,330,330,663,10043};
static const unsigned int light100FanOff[] PROGMEM = {329,329,664,329,664,329,664,329,664,329,664,664,329,329,664,329,664,329,664,329,664,329,664,329,664,329,664,664,329,329,664,329,664,329,664,664,329,329,664,329,664,329,664,10041};
static const unsigned int light100FanLow[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,663,330,330,663,663,330,330,663,663,330,663,330,10045};
static const unsigned int light100FanMed[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,663,330,330,663,663,330,330,663,10043};
static const unsigned int light100FanHigh[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,663,330,330,663,330,663,663,330,10045};
 
  server.send(204,"");
  String lastFanSpeed = read_String(110);
  String lastLightState = read_String(115);  
  String fanSpeed = server.arg("fanSpeed");
  String lightState = server.arg("lightState");
  
  if(fanSpeed == "same"){
    fanSpeed = lastFanSpeed;
  }
  else{
    lastFanSpeed = fanSpeed;
    writeString(110, fanSpeed);
  }
  
  if(lightState == "same"){
    lightState = lastLightState;
  }
  else{
    lastLightState = lightState;
    writeString(115, lightState);
  }
  
  for (int i = 0; i <= IRrepeat; i++) {
     yield(); 
    if (lightState == "off") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(lightOffFanOff, 44,38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(lightOffFanLow, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(lightOffFanMed, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(lightOffFanHigh, 44, 38); // Send a raw data capture at 38kHz
        }
      }    
  else if (lightState == "20") {
        if(fanSpeed == "off"){
            sendRAW_Flash(light20FanOff, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light20FanLow, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light20FanMed, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light20FanHigh, 44, 38); // Send a raw data capture at 38kHz
        }   
  }
  else if (lightState == "30") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light30FanOff, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light20FanLow, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light30FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light30FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "40") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light40FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light40FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light40FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light40FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "50") {
        if(fanSpeed == "off"){
            sendRAW_Flash(light50FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light50FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light50FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light50FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "60") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light60FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light60FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light60FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light60FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "70") {
        yield();
        if(fanSpeed == "off"){
            sendRAW_Flash(light70FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light70FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light70FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light70FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "80") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light80FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light80FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light80FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light80FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }
    
  }
  else if (lightState == "90") {
        if(fanSpeed == "off"){
            sendRAW_Flash(light90FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light90FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light90FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light90FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "100") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light100FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light100FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light100FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light100FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }
      }    
  }
}

void set1100()
{  
//FAN CHQ8BT7096T DIP SWITCHES UP,UP,DN,DN OR 1100

static const unsigned int lightOffFanOff[] PROGMEM = {330,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,663,330,10043};
static const unsigned int lightOffFanLow[] PROGMEM = {330,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,663,330,663,330,330,663,330,663,10048};
static const unsigned int lightOffFanMed[] PROGMEM = {330,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,663,330,330,663,663,330,663,330,10045};
static const unsigned int lightOffFanHigh[] PROGMEM = {330,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,663,330,330,663,10035};
static const unsigned int light20FanOff[] PROGMEM = {330,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,663,330,330,663,663,330,330,663,330,663,663,330,330,663,330,663,330,663,330,663,663,330,663,330,663,330,10032};
static const unsigned int light20FanLow[] PROGMEM = {331,331,662,331,662,331,662,662,331,662,331,331,662,331,662,331,662,662,331,331,662,662,331,331,662,331,662,662,331,662,331,662,331,331,662,662,331,331,662,662,331,331,662,10039};
static const unsigned int light20FanMed[] PROGMEM = {330,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,663,330,330,663,663,330,330,663,330,663,663,330,663,330,330,663,330,663,663,330,330,663,330,663,663,330,10049};
static const unsigned int light20FanHigh[] PROGMEM = {330,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,663,330,330,663,663,330,330,663,330,663,663,330,330,663,663,330,330,663,663,330,330,663,330,663,330,663,10045};
static const unsigned int light30FanOff[] PROGMEM = {330,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,663,330,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,10041};
static const unsigned int light30FanLow[] PROGMEM = {330,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,663,330,330,663,330,663,663,330,330,663,330,663,663,330,663,330,330,663,330,663,663,330,330,663,663,330,10050};
static const unsigned int light30FanMed[] PROGMEM = {330,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,663,330,330,663,330,663,663,330,330,663,330,663,663,330,330,663,330,663,330,663,663,330,330,663,330,663,10043};
static const unsigned int light30FanHigh[] PROGMEM = {330,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,663,330,330,663,330,663,663,330,330,663,330,663,330,663,663,330,330,663,330,663,330,663,663,330,663,330,10045};
static const unsigned int light40FanOff[] PROGMEM = {331,331,662,331,662,331,662,662,331,662,331,331,662,331,662,331,662,331,662,662,331,662,331,662,331,662,331,662,331,331,662,331,662,331,662,662,331,662,331,331,662,331,662,10045};
static const unsigned int light40FanLow[] PROGMEM = {331,331,662,331,662,331,662,662,331,662,331,331,662,331,662,331,662,331,662,662,331,662,331,662,331,662,331,662,331,662,331,662,331,331,662,662,331,662,331,662,331,662,331,10080};
static const unsigned int light40FanMed[] PROGMEM = {331,331,662,331,662,331,662,662,331,662,331,331,662,331,662,331,662,331,662,662,331,662,331,662,331,662,331,662,331,662,331,331,662,331,662,662,331,662,331,662,331,331,662,10058};
static const unsigned int light40FanHigh[] PROGMEM = {331,331,662,331,662,331,662,662,331,662,331,331,662,331,662,331,662,331,662,662,331,662,331,662,331,662,331,662,331,331,662,662,331,331,662,662,331,662,331,331,662,662,331,10052};
static const unsigned int light50FanOff[] PROGMEM = {330,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,330,663,663,330,663,330,330,663,663,330,330,663,330,663,330,663,330,663,330,663,663,330,663,330,663,330,10029};
static const unsigned int light50FanLow[] PROGMEM = {331,331,662,331,662,331,662,662,331,662,331,331,662,331,662,331,662,331,662,662,331,662,331,331,662,662,331,331,662,662,331,662,331,331,662,662,331,331,662,662,331,331,662,10041};
static const unsigned int light50FanMed[] PROGMEM = {330,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,330,663,663,330,663,330,330,663,663,330,330,663,663,330,330,663,330,663,663,330,330,663,330,663,663,330,10031};
static const unsigned int light50FanHigh[] PROGMEM = {330,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,330,663,663,330,663,330,330,663,663,330,330,663,330,663,663,330,330,663,663,330,330,663,330,663,330,663,10050};
static const unsigned int light60FanOff[] PROGMEM = {330,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,663,330,330,663,330,663,330,663,330,663,330,663,663,330,330,663,10044};
static const unsigned int light60FanLow[] PROGMEM = {331,331,662,331,662,331,662,662,331,662,331,331,662,331,662,331,662,331,662,662,331,331,662,662,331,331,662,662,331,662,331,662,331,331,662,331,662,662,331,331,662,662,331,10033};
static const unsigned int light60FanMed[] PROGMEM = {330,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,663,330,663,330,330,663,330,663,330,663,663,330,330,663,330,663,10043};
static const unsigned int light60FanHigh[] PROGMEM = {330,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,663,330,330,663,663,330,330,663,330,663,330,663,663,330,663,330,10048};
static const unsigned int light70FanOff[] PROGMEM = {330,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,663,330,10043};
static const unsigned int light70FanLow[] PROGMEM = {330,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,330,663,330,663,10043};
static const unsigned int light70FanMed[] PROGMEM = {330,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,663,330,330,663,330,663,663,330,663,330,663,330,663,330,10037};
static const unsigned int light70FanHigh[] PROGMEM = {330,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,663,330,663,330,330,663,10041};
static const unsigned int light80FanOff[] PROGMEM = {330,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,663,330,330,663,330,663,330,663,330,663,663,330,663,330,663,330,10049};
static const unsigned int light80FanLow[] PROGMEM = {331,331,662,331,662,331,662,662,331,662,331,331,662,331,662,331,662,331,662,331,662,662,331,331,662,662,331,662,331,662,331,662,331,331,662,662,331,331,662,662,331,331,662,10041};
static const unsigned int light80FanMed[] PROGMEM = {330,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,663,330,663,330,330,663,330,663,663,330,330,663,330,663,663,330,10052};
static const unsigned int light80FanHigh[] PROGMEM = {330,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,663,330,330,663,663,330,330,663,663,330,330,663,330,663,330,663,10039};
static const unsigned int light90FanOff[] PROGMEM = {330,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,10052};
static const unsigned int light90FanLow[] PROGMEM = {330,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,663,330,663,330,330,663,330,663,663,330,330,663,663,330,10037};
static const unsigned int light90FanMed[] PROGMEM = {330,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,663,330,330,663,330,663,330,663,663,330,330,663,330,663,10033};
static const unsigned int light90FanHigh[] PROGMEM = {330,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,663,330,330,663,330,663,330,663,663,330,663,330,10041};
static const unsigned int light100FanOff[] PROGMEM = {330,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,663,330,663,330,330,663,663,330,10043};
static const unsigned int light100FanLow[] PROGMEM = {330,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,663,330,330,663,330,663,330,663,330,663,330,663,10052};
static const unsigned int light100FanMed[] PROGMEM = {330,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,663,330,663,330,663,330,663,330,10030};
static const unsigned int light100FanHigh[] PROGMEM = {330,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,663,330,663,330,663,330,330,663,10033};

  server.send(204,"");
  String lastFanSpeed = read_String(120);
  String lastLightState = read_String(125);  
  String fanSpeed = server.arg("fanSpeed");
  String lightState = server.arg("lightState");
  
  if(fanSpeed == "same"){
    fanSpeed = lastFanSpeed;
  }
  else{
    lastFanSpeed = fanSpeed;
    writeString(120, fanSpeed);
  }
  
  if(lightState == "same"){
    lightState = lastLightState;
  }
  else{
    lastLightState = lightState;
    writeString(125, lightState);
  }
  
  for (int i = 0; i <= IRrepeat; i++) {
     yield(); 
    if (lightState == "off") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(lightOffFanOff, 44,38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(lightOffFanLow, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(lightOffFanMed, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(lightOffFanHigh, 44, 38); // Send a raw data capture at 38kHz
        }
      }    
  else if (lightState == "20") {
        if(fanSpeed == "off"){
            sendRAW_Flash(light20FanOff, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light20FanLow, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light20FanMed, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light20FanHigh, 44, 38); // Send a raw data capture at 38kHz
        }   
  }
  else if (lightState == "30") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light30FanOff, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light20FanLow, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light30FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light30FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "40") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light40FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light40FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light40FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light40FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "50") {
        if(fanSpeed == "off"){
            sendRAW_Flash(light50FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light50FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light50FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light50FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "60") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light60FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light60FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light60FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light60FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "70") {
        yield();
        if(fanSpeed == "off"){
            sendRAW_Flash(light70FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light70FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light70FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light70FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "80") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light80FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light80FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light80FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light80FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }
    
  }
  else if (lightState == "90") {
        if(fanSpeed == "off"){
            sendRAW_Flash(light90FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light90FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light90FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light90FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "100") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light100FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light100FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light100FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light100FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }
      }    
  }
}


void set1101()
{
  Serial.println("At 1101");  
//FAN CHQ8BT7096T DIP SWITCHES UP,UP,DN,UP OR 1101
static const unsigned int lightOffFanOff[] PROGMEM = {329,329,664,329,664,329,664,329,664,664,329,329,664,329,664,329,664,329,664,329,664,329,664,329,664,329,664,329,664,329,664,329,664,329,664,664,329,329,664,329,664,329,664,10054};
static const unsigned int lightOffFanLow[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,663,330,330,663,663,330,663,330,10050};
static const unsigned int lightOffFanMed[] PROGMEM = {329,329,663,329,663,329,663,329,663,663,329,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,663,329,329,663,329,663,663,329,329,663,663,329,329,663,10037};
static const unsigned int lightOffFanHigh[] PROGMEM = {329,329,663,329,663,329,663,329,663,663,329,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,663,329,329,663,663,329,329,663,329,663,663,329,10042};
static const unsigned int light20FanOff[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,663,330,330,663,663,330,330,663,330,663,663,330,330,663,330,663,330,663,330,663,663,330,663,330,330,663,10045};
static const unsigned int light20FanLow[] PROGMEM = {330,330,662,330,662,330,662,330,662,662,330,330,662,330,662,330,662,662,330,330,662,662,330,330,662,330,662,662,330,662,330,662,330,330,662,662,330,330,662,330,662,662,330,10040};
static const unsigned int light20FanMed[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,663,330,330,663,663,330,330,663,330,663,663,330,663,330,330,663,330,663,663,330,330,663,330,663,330,663,10036};
static const unsigned int light20FanHigh[] PROGMEM = {330,330,662,330,662,330,662,330,662,662,330,330,662,330,662,330,662,662,330,330,662,662,330,330,662,330,662,662,330,330,662,662,330,330,662,330,662,662,330,662,330,662,330,10044};
static const unsigned int light30FanOff[] PROGMEM = {329,329,663,329,663,329,663,329,663,663,329,329,663,329,663,329,663,663,329,329,663,329,663,663,329,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,663,329,10035};
static const unsigned int light30FanLow[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,663,330,330,663,330,663,663,330,330,663,330,663,663,330,663,330,330,663,330,663,663,330,330,663,330,663,10026};
static const unsigned int light30FanMed[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,663,330,330,663,330,663,663,330,330,663,330,663,663,330,330,663,330,663,330,663,330,663,663,330,663,330,10047};
static const unsigned int light30FanHigh[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,663,330,330,663,330,663,663,330,330,663,330,663,330,663,663,330,330,663,330,663,330,663,663,330,330,663,10049};
static const unsigned int light40FanOff[] PROGMEM = {330,330,662,330,662,330,662,330,662,662,330,330,662,330,662,330,662,330,662,662,330,662,330,662,330,662,330,662,330,330,662,330,662,330,662,662,330,330,662,662,330,662,330,10028};
static const unsigned int light40FanLow[] PROGMEM = {331,331,662,331,662,331,662,331,662,662,331,331,662,331,662,331,662,331,662,662,331,662,331,662,331,662,331,662,331,662,331,662,331,331,662,662,331,662,331,662,331,331,662,10030};
static const unsigned int light40FanMed[] PROGMEM = {331,331,662,331,662,331,662,331,662,662,331,331,662,331,662,331,662,331,662,662,331,662,331,662,331,662,331,662,331,662,331,331,662,331,662,662,331,662,331,331,662,662,331,10050};
static const unsigned int light40FanHigh[] PROGMEM = {330,330,662,330,662,330,662,330,662,662,330,330,662,330,662,330,662,330,662,662,330,662,330,662,330,662,330,662,330,330,662,662,330,330,662,662,330,662,330,330,662,330,662,10037};
static const unsigned int light50FanOff[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,663,330,663,330,330,663,663,330,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,10037};
static const unsigned int light50FanLow[] PROGMEM = {330,330,662,330,662,330,662,330,662,662,330,330,662,330,662,330,662,330,662,662,330,662,330,330,662,662,330,330,662,662,330,662,330,330,662,662,330,330,662,330,662,662,330,10052};
static const unsigned int light50FanMed[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,663,330,663,330,330,663,663,330,330,663,663,330,330,663,330,663,663,330,330,663,330,663,330,663,10033};
static const unsigned int light50FanHigh[] PROGMEM = {330,330,662,330,662,330,662,330,662,662,330,330,662,330,662,330,662,330,662,662,330,662,330,330,662,662,330,330,662,330,662,662,330,330,662,330,662,662,330,662,330,662,330,10037};
static const unsigned int light60FanOff[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,663,330,10027};
static const unsigned int light60FanLow[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,663,330,663,330,663,330,330,663,330,663,663,330,330,663,330,663,10036};
static const unsigned int light60FanMed[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,663,330,663,330,330,663,330,663,330,663,330,663,663,330,663,330,10038};
static const unsigned int light60FanHigh[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,663,330,330,663,663,330,330,663,330,663,330,663,663,330,330,663,10044};
static const unsigned int light70FanOff[] PROGMEM = {329,329,663,329,663,329,663,329,663,663,329,329,663,329,663,329,663,329,663,663,329,329,663,329,663,329,663,329,663,329,663,329,663,329,663,663,329,663,329,329,663,329,663,10038};
static const unsigned int light70FanLow[] PROGMEM = {330,330,662,330,662,330,662,330,662,662,330,330,662,330,662,330,662,330,662,662,330,330,662,330,662,330,662,330,662,662,330,662,330,330,662,662,330,662,330,662,330,662,330,10035};
static const unsigned int light70FanMed[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,663,330,330,663,330,663,663,330,663,330,663,330,330,663,10037};
static const unsigned int light70FanHigh[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,663,330,330,663,663,330,10038};
static const unsigned int light80FanOff[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,663,330,330,663,330,663,330,663,330,663,663,330,663,330,330,663,10036};
static const unsigned int light80FanLow[] PROGMEM = {330,330,662,330,662,330,662,330,662,662,330,330,662,330,662,330,662,330,662,330,662,662,330,330,662,662,330,662,330,662,330,662,330,330,662,662,330,330,662,330,662,662,330,10042};
static const unsigned int light80FanMed[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,663,330,663,330,330,663,330,663,663,330,330,663,330,663,330,663,10035};
static const unsigned int light80FanHigh[] PROGMEM = {330,330,662,330,662,330,662,330,662,662,330,330,662,330,662,330,662,330,662,330,662,662,330,330,662,662,330,662,330,330,662,662,330,330,662,330,662,662,330,662,330,662,330,10044};
static const unsigned int light90FanOff[] PROGMEM = {329,329,663,329,663,329,663,329,663,663,329,329,663,329,663,329,663,329,663,329,663,329,663,663,329,663,329,329,663,329,663,329,663,329,663,329,663,329,663,329,663,663,329,10032};
static const unsigned int light90FanLow[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,663,330,663,330,330,663,330,663,663,330,330,663,330,663,10036};
static const unsigned int light90FanMed[] PROGMEM = {[330,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,663,330,330,663,330,663,330,663,330,663,663,330,663,330,10042};
static const unsigned int light90FanHigh[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,663,330,330,663,330,663,330,663,663,330,330,663,10038};
static const unsigned int light100FanOff[] PROGMEM = {329,329,663,329,663,329,663,329,663,663,329,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,663,329,329,663,329,663,329,663,663,329,663,329,329,663,329,663,10034};
static const unsigned int light100FanLow[] PROGMEM = {330,330,662,330,662,330,662,330,662,662,330,330,662,330,662,330,662,330,662,330,662,330,662,330,662,330,662,662,330,662,330,662,330,330,662,662,330,662,330,662,330,662,330,10042};
static const unsigned int light100FanMed[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,663,330,663,330,663,330,330,663,10044};
static const unsigned int light100FanHigh[] PROGMEM = {330,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,663,330,663,330,330,663,663,330,10042};

  server.send(204,"");
  String lastFanSpeed = read_String(50);
  String lastLightState = read_String(55);  
  String fanSpeed = server.arg("fanSpeed");
  String lightState = server.arg("lightState");
  
  if(fanSpeed == "same"){
    fanSpeed = lastFanSpeed;
  }
  else{
    lastFanSpeed = fanSpeed;
    writeString(50, fanSpeed);
  }
  
  if(lightState == "same"){
    lightState = lastLightState;
  }
  else{
    lastLightState = lightState;
    writeString(55, lightState);
  }
  
  for (int i = 0; i <= IRrepeat; i++) {
     yield(); 
    if (lightState == "off") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(lightOffFanOff, 44,38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(lightOffFanLow, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(lightOffFanMed, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(lightOffFanHigh, 44, 38); // Send a raw data capture at 38kHz
        }
      }    
  else if (lightState == "20") {
        if(fanSpeed == "off"){
            sendRAW_Flash(light20FanOff, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light20FanLow, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light20FanMed, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light20FanHigh, 44, 38); // Send a raw data capture at 38kHz
        }   
  }
  else if (lightState == "30") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light30FanOff, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light20FanLow, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light30FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light30FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "40") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light40FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light40FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light40FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light40FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "50") {
        if(fanSpeed == "off"){
            sendRAW_Flash(light50FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light50FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light50FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light50FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "60") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light60FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light60FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light60FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light60FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "70") {
        yield();
        if(fanSpeed == "off"){
            sendRAW_Flash(light70FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light70FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light70FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light70FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "80") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light80FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light80FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light80FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light80FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }
    
  }
  else if (lightState == "90") {
        if(fanSpeed == "off"){
            sendRAW_Flash(light90FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light90FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light90FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light90FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "100") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light100FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light100FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light100FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light100FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }
      }    
  }
}

void set1110()
{  
//Remote CHQ8BT7096T DIP SWITCHES UP,UP,UP,DN OR 1110

static const unsigned int lightOffFanOff[] PROGMEM = {329,329,664,329,664,329,664,664,329,329,664,329,664,329,664,329,664,329,664,329,664,329,664,329,664,329,664,329,664,329,664,329,664,329,664,329,664,329,664,329,664,664,329,10026};
static const unsigned int lightOffFanLow[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,663,330,330,663,330,663,10045};
static const unsigned int lightOffFanMed[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,663,330,663,330,10039};
static const unsigned int lightOffFanHigh[] PROGMEM = {329,329,664,329,664,329,664,664,329,329,664,329,664,329,664,329,664,329,664,329,664,329,664,329,664,329,664,329,664,329,664,664,329,329,664,329,664,329,664,664,329,329,664,10039};
static const unsigned int light20FanOff[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,330,663,663,330,330,663,330,663,330,663,663,330,663,330,663,330,663,330,10045};
static const unsigned int light20FanLow[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,330,663,663,330,663,330,663,330,330,663,330,663,330,663,663,330,330,663,10037};
static const unsigned int light20FanMed[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,330,663,663,330,663,330,330,663,330,663,330,663,330,663,330,663,663,330,10041};
static const unsigned int light20FanHigh[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,330,663,663,330,330,663,663,330,330,663,330,663,330,663,330,663,330,663,10048};
static const unsigned int light30FanOff[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,663,330,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,10033};
static const unsigned int light30FanLow[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,663,330,330,663,330,663,663,330,330,663,330,663,663,330,663,330,330,663,663,330,663,330,330,663,663,330,10031};
static const unsigned int light30FanMed[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,663,330,330,663,330,663,663,330,330,663,330,663,663,330,330,663,330,663,663,330,663,330,330,663,330,663,10048};
static const unsigned int light30FanHigh[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,663,330,330,663,330,663,663,330,330,663,330,663,330,663,663,330,330,663,663,330,330,663,663,330,663,330,10041};
static const unsigned int light40FanOff[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,663,330,663,330,663,330,663,330,663,330,330,663,330,663,330,663,330,663,663,330,330,663,330,663,10037};
static const unsigned int light40FanLow[] PROGMEM = {331,331,662,331,662,331,662,662,331,331,662,331,662,331,662,331,662,331,662,662,331,662,331,662,331,662,331,662,331,662,331,662,331,331,662,331,662,662,331,662,331,662,331,10047};
static const unsigned int light40FanMed[] PROGMEM = {331,331,662,331,662,331,662,662,331,331,662,331,662,331,662,331,662,331,662,662,331,662,331,662,331,662,331,662,331,662,331,331,662,331,662,331,662,662,331,662,331,331,662,10044};
static const unsigned int light40FanHigh[] PROGMEM = {331,331,662,331,662,331,662,662,331,331,662,331,662,331,662,331,662,331,662,662,331,662,331,662,331,662,331,662,331,331,662,662,331,331,662,331,662,662,331,331,662,662,331,10041};
static const unsigned int light50FanOff[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,663,330,330,663,330,663,330,663,330,663,663,330,663,330,663,330,663,330,10052};
static const unsigned int light50FanLow[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,663,330,330,663,663,330,663,330,330,663,330,663,330,663,663,330,330,663,10039};
static const unsigned int light50FanMed[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,663,330,330,663,663,330,330,663,330,663,330,663,330,663,330,663,663,330,10035};
static const unsigned int light50FanHigh[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,663,330,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,10033};
static const unsigned int light60FanOff[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,663,330,330,663,330,663,330,663,663,330,330,663,663,330,330,663,10049};
static const unsigned int light60FanLow[] PROGMEM = {331,331,662,331,662,331,662,662,331,331,662,331,662,331,662,331,662,331,662,662,331,331,662,662,331,331,662,662,331,662,331,662,331,331,662,662,331,662,331,331,662,662,331,10051};
static const unsigned int light60FanMed[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,663,330,663,330,330,663,330,663,663,330,663,330,330,663,330,663,10052};
static const unsigned int light60FanHigh[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,663,330,330,663,663,330,330,663,663,330,330,663,663,330,663,330,10039};
static const unsigned int light70FanOff[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,10048};
static const unsigned int light70FanLow[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,663,330,663,330,330,663,663,330,330,663,330,663,330,663,10060};
static const unsigned int light70FanMed[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,663,330,663,330,663,330,10034};
static const unsigned int light70FanHigh[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,663,330,663,330,330,663,10035};
static const unsigned int light80FanOff[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,663,330,330,663,330,663,330,663,663,330,663,330,663,330,663,330,10028};
static const unsigned int light80FanLow[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,663,330,663,330,663,330,330,663,330,663,330,663,663,330,330,663,10043};
static const unsigned int light80FanMed[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,663,330,663,330,330,663,330,663,330,663,330,663,330,663,663,330,10039};
static const unsigned int light80FanHigh[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,663,330,330,663,663,330,330,663,330,663,330,663,330,663,330,663,10045};
static const unsigned int light90FanOff[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,10045};
static const unsigned int light90FanLow[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,663,330,663,330,330,663,663,330,663,330,330,663,663,330,10049};
static const unsigned int light90FanMed[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,663,330,330,663,330,663,663,330,663,330,330,663,330,663,10041};
static const unsigned int light90FanHigh[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,663,330,330,663,663,330,330,663,663,330,663,330,10037};
static const unsigned int light100FanOff[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,663,330,330,663,663,330,10033};
static const unsigned int light100FanLow[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,663,330,330,663,663,330,330,663,330,663,330,663,10039};
static const unsigned int light100FanMed[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,663,330,663,330,663,330,10041};
static const unsigned int light100FanHigh[] PROGMEM = {330,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,330,663,663,330,663,330,330,663,10050};

  server.send(204,"");
  String lastFanSpeed = read_String(140);
  String lastLightState = read_String(145);  
  String fanSpeed = server.arg("fanSpeed");
  String lightState = server.arg("lightState");
  
  if(fanSpeed == "same"){
    fanSpeed = lastFanSpeed;
  }
  else{
    lastFanSpeed = fanSpeed;
    writeString(140, fanSpeed);
  }
  
  if(lightState == "same"){
    lightState = lastLightState;
  }
  else{
    lastLightState = lightState;
    writeString(145, lightState);
  }
  
  for (int i = 0; i <= IRrepeat; i++) {
     yield(); 
    if (lightState == "off") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(lightOffFanOff, 44,38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(lightOffFanLow, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(lightOffFanMed, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(lightOffFanHigh, 44, 38); // Send a raw data capture at 38kHz
        }
      }    
  else if (lightState == "20") {
        if(fanSpeed == "off"){
            sendRAW_Flash(light20FanOff, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light20FanLow, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light20FanMed, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light20FanHigh, 44, 38); // Send a raw data capture at 38kHz
        }   
  }
  else if (lightState == "30") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light30FanOff, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light20FanLow, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light30FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light30FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "40") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light40FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light40FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light40FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light40FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "50") {
        if(fanSpeed == "off"){
            sendRAW_Flash(light50FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light50FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light50FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light50FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "60") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light60FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light60FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light60FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light60FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "70") {
        yield();
        if(fanSpeed == "off"){
            sendRAW_Flash(light70FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light70FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light70FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light70FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "80") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light80FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light80FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light80FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light80FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }
    
  }
  else if (lightState == "90") {
        if(fanSpeed == "off"){
            sendRAW_Flash(light90FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light90FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light90FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light90FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "100") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light100FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light100FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light100FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light100FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }
      }    
  }
}

void set1111()
{  
//Remote CHQ8BT7096T DIP SWITCHES ALL UP OR 1111
static const unsigned int lightOffFanOff[] PROGMEM = {327,327,666,327,666,327,666,327,666,327,666,327,666,327,666,327,666,327,666,327,666,327,666,327,666,327,666,327,666,327,666,327,666,327,666,327,666,327,666,327,666,327,666,10031};
static const unsigned int lightOffFanLow[] PROGMEM = {329,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,663,329,663,329,329,663,329,663,329,663,663,329,663,329,10076};
static const unsigned int lightOffFanMed[] PROGMEM = {329,329,664,329,664,329,664,329,664,329,664,329,664,329,664,329,664,329,664,329,664,329,664,329,664,329,664,329,664,664,329,329,664,329,664,329,664,329,664,664,329,329,664,10038};
static const unsigned int lightOffFanHigh[] PROGMEM = {329,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,663,329,329,663,329,663,329,663,329,663,663,329,10048};
static const unsigned int light20FanOff[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,330,663,663,330,330,663,330,663,330,663,663,330,663,330,663,330,330,663,10042};
static const unsigned int light20FanLow[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,330,663,663,330,663,330,663,330,330,663,330,663,330,663,330,663,663,330,10042};
static const unsigned int light20FanMed[] PROGMEM = {330,330,664,330,664,330,664,330,664,330,664,330,664,330,664,330,664,664,330,330,664,664,330,330,664,330,664,664,330,664,330,330,664,330,664,330,664,330,664,330,664,330,664,10037};
static const unsigned int light20FanHigh[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,330,663,663,330,330,663,663,330,330,663,663,330,663,330,663,330,663,330,10043};
static const unsigned int light30FanOff[] PROGMEM = {330,330,664,330,664,330,664,330,664,330,664,330,664,330,664,330,664,664,330,330,664,330,664,664,330,330,664,330,664,330,664,330,664,330,664,664,330,330,664,330,664,664,330,10038};
static const unsigned int light30FanLow[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,663,330,330,663,330,663,663,330,663,330,330,663,663,330,663,330,330,663,330,663,10050};
static const unsigned int light30FanMed[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,663,330,330,663,330,663,663,330,330,663,330,663,663,330,330,663,663,330,663,330,10042};
static const unsigned int light30FanHigh[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,663,330,330,663,330,663,330,663,663,330,330,663,663,330,330,663,663,330,330,663,10044};
static const unsigned int light40FanOff[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,663,330,663,330,663,330,330,663,330,663,330,663,330,663,330,663,663,330,663,330,10057};
static const unsigned int light40FanLow[] PROGMEM = {331,331,663,331,663,331,663,331,663,331,663,331,663,331,663,331,663,331,663,663,331,663,331,663,331,663,331,663,331,663,331,663,331,331,663,331,663,663,331,663,331,331,663,10050};
static const unsigned int light40FanMed[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,663,330,663,330,663,330,663,330,330,663,330,663,330,663,663,330,330,663,663,330,10042};
static const unsigned int light40FanHigh[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,663,330,663,330,663,330,330,663,663,330,330,663,330,663,663,330,330,663,330,663,10044};
static const unsigned int light50FanOff[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,663,330,330,663,330,663,330,663,330,663,663,330,663,330,663,330,330,663,10051};
static const unsigned int light50FanLow[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,663,330,330,663,663,330,663,330,330,663,330,663,330,663,330,663,663,330,10034};
static const unsigned int light50FanMed[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,663,330,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,10036};
static const unsigned int light50FanHigh[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,663,330,330,663,330,663,663,330,330,663,663,330,663,330,663,330,663,330,10045};
static const unsigned int light60FanOff[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,663,330,330,663,330,663,330,663,663,330,330,663,330,663,663,330,10041};
static const unsigned int light60FanLow[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,663,330,663,330,663,330,330,663,663,330,663,330,330,663,330,663,10038};
static const unsigned int light60FanMed[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,663,330,663,330,330,663,330,663,663,330,330,663,663,330,663,330,10034};
static const unsigned int light60FanHigh[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,663,330,330,663,663,330,330,663,663,330,330,663,663,330,330,663,10047};
static const unsigned int light70FanOff[] PROGMEM = {329,329,664,329,664,329,664,329,664,329,664,329,664,329,664,329,664,329,664,664,329,329,664,329,664,329,664,329,664,329,664,329,664,329,664,329,664,664,329,329,664,329,664,10052};
static const unsigned int light70FanLow[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,663,330,663,330,663,330,10037};
static const unsigned int light70FanMed[] PROGMEM = {329,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,663,329,329,663,329,663,329,663,329,663,663,329,329,663,329,663,329,663,663,329,663,329,329,663,10050};
static const unsigned int light70FanHigh[] PROGMEM = {329,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,663,329,329,663,329,663,329,663,329,663,329,663,663,329,329,663,329,663,663,329,329,663,663,329,10041};
static const unsigned int light80FanOff[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,663,330,330,663,330,663,330,663,663,330,663,330,663,330,330,663,10039};
static const unsigned int light80FanLow[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,663,330,663,330,663,330,330,663,330,663,330,663,330,663,663,330,10045};
static const unsigned int light80FanMed[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,663,330,663,330,330,663,330,663,330,663,330,663,330,663,330,663,10037};
static const unsigned int light80FanHigh[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,663,330,330,663,663,330,330,663,663,330,663,330,663,330,663,330,10033};
static const unsigned int light90FanOff[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,330,663,663,330,330,663,330,663,663,330,10038};
static const unsigned int light90FanLow[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,663,330,663,330,330,663,663,330,663,330,330,663,330,663,10043};
static const unsigned int light90FanMed[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,663,330,330,663,330,663,663,330,330,663,663,330,663,330,10047};
static const unsigned int light90FanHigh[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,663,330,330,663,663,330,330,663,663,330,330,663,10051};
static const unsigned int light100FanOff[] PROGMEM = {329,329,664,329,664,329,664,329,664,329,664,329,664,329,664,329,664,329,664,329,664,329,664,329,664,329,664,664,329,329,664,329,664,329,664,329,664,664,329,329,664,329,664,10057};
static const unsigned int light100FanLow[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,663,330,330,663,330,663,663,330,663,330,663,330,10043};
static const unsigned int light100FanMed[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,663,330,663,330,330,663,10034};
static const unsigned int light100FanHigh[] PROGMEM = {330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,330,663,663,330,330,663,663,330,10038};
  
  server.send(204,"");
  String lastFanSpeed = read_String(150);
  String lastLightState = read_String(155);  
  String fanSpeed = server.arg("fanSpeed");
  String lightState = server.arg("lightState");
  
  if(fanSpeed == "same"){
    fanSpeed = lastFanSpeed;
  }
  else{
    lastFanSpeed = fanSpeed;
    writeString(150, fanSpeed);
  }
  
  if(lightState == "same"){
    lightState = lastLightState;
  }
  else{
    lastLightState = lightState;
    writeString(155, lightState);
  } 
  
  for (int i = 0; i <= IRrepeat; i++) {
     yield(); 
    if (lightState == "off") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(lightOffFanOff, 44,38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(lightOffFanLow, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(lightOffFanMed, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(lightOffFanHigh, 44, 38); // Send a raw data capture at 38kHz
        }
      }    
  else if (lightState == "20") {
        if(fanSpeed == "off"){
            sendRAW_Flash(light20FanOff, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light20FanLow, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light20FanMed, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light20FanHigh, 44, 38); // Send a raw data capture at 38kHz
        }   
  }
  else if (lightState == "30") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light30FanOff, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light20FanLow, 44, 38); // Send a raw data capture at 38kHz
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light30FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light30FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "40") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light40FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light40FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light40FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light40FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "50") {
        if(fanSpeed == "off"){
            sendRAW_Flash(light50FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light50FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light50FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light50FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "60") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light60FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light60FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light60FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light60FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "70") {
        yield();
        if(fanSpeed == "off"){
            sendRAW_Flash(light70FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light70FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light70FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light70FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "80") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light80FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light80FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light80FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light80FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }
    
  }
  else if (lightState == "90") {
        if(fanSpeed == "off"){
            sendRAW_Flash(light90FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light90FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light90FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light90FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }    
  }
  else if (lightState == "100") { 
        if(fanSpeed == "off"){
            sendRAW_Flash(light100FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            sendRAW_Flash(light100FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            sendRAW_Flash(light100FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            sendRAW_Flash(light100FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }
      }    
  }
}
