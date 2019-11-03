/**
 *  Hampton Bay Fan
 * 
 *  Copyright 2019 Jason Brown
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

ESP8266WebServer server;
const char* ssid = ""; // your router login mame
const char* password = ""; // your router password
const uint16_t kIrLed = 12;  // ESP8266 GPIO pin 12 (D6) output.
IRsend irsend(kIrLed);  // Set the GPIO to be used to sending the message.
const int IRrepeat = 30; // Number times to transmit signal

//FAN CHQ8BT7096T DIP SWITCHES ALL UP OR 1111 Note: light only dims to 20%
uint16_t lightOffFanOff[44] = {327,327,666,327,666,327,666,327,666,327,666,327,666,327,666,327,666,327,666,327,666,327,666,327,666,327,666,327,666,327,666,327,666,327,666,327,666,327,666,327,666,327,666,10031};
uint16_t lightOffFanLow[44] = {329,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,663,329,663,329,329,663,329,663,329,663,663,329,663,329,10076};
uint16_t lightOffFanMed[44] = {329,329,664,329,664,329,664,329,664,329,664,329,664,329,664,329,664,329,664,329,664,329,664,329,664,329,664,329,664,664,329,329,664,329,664,329,664,329,664,664,329,329,664,10038};
uint16_t lightOffFanHigh[44] = {329,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,663,329,329,663,329,663,329,663,329,663,663,329,10048};
uint16_t light20FanOff[44] = {330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,330,663,663,330,330,663,330,663,330,663,663,330,663,330,663,330,330,663,10042};
uint16_t light20FanLow[44] = {330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,330,663,663,330,663,330,663,330,330,663,330,663,330,663,330,663,663,330,10042};
uint16_t light20FanMed[44] = {330,330,664,330,664,330,664,330,664,330,664,330,664,330,664,330,664,664,330,330,664,664,330,330,664,330,664,664,330,664,330,330,664,330,664,330,664,330,664,330,664,330,664,10037};
uint16_t light20FanHigh[44] = {330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,330,663,663,330,330,663,663,330,330,663,663,330,663,330,663,330,663,330,10043};
uint16_t light30FanOff[44] = {330,330,664,330,664,330,664,330,664,330,664,330,664,330,664,330,664,664,330,330,664,330,664,664,330,330,664,330,664,330,664,330,664,330,664,664,330,330,664,330,664,664,330,10038};
uint16_t light30FanLow[44] = {330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,663,330,330,663,330,663,663,330,663,330,330,663,663,330,663,330,330,663,330,663,10050};
uint16_t light30FanMed[44] = {330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,663,330,330,663,330,663,663,330,330,663,330,663,663,330,330,663,663,330,663,330,10042};
uint16_t light30FanHigh[44] = {330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,663,330,330,663,330,663,330,663,663,330,330,663,663,330,330,663,663,330,330,663,10044};
uint16_t light40FanOff[44] = {330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,663,330,663,330,663,330,330,663,330,663,330,663,330,663,330,663,663,330,663,330,10057};
uint16_t light40FanLow[44] = {331,331,663,331,663,331,663,331,663,331,663,331,663,331,663,331,663,331,663,663,331,663,331,663,331,663,331,663,331,663,331,663,331,331,663,331,663,663,331,663,331,331,663,10050};
uint16_t light40FanMed[44] = {330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,663,330,663,330,663,330,663,330,330,663,330,663,330,663,663,330,330,663,663,330,10042};
uint16_t light40FanHigh[44] = {330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,663,330,663,330,663,330,330,663,663,330,330,663,330,663,663,330,330,663,330,663,10044};
uint16_t light50FanOff[44] = {330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,663,330,330,663,330,663,330,663,330,663,663,330,663,330,663,330,330,663,10051};
uint16_t light50FanLow[44] = {330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,663,330,330,663,663,330,663,330,330,663,330,663,330,663,330,663,663,330,10034};
uint16_t light50FanMed[44] = {330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,663,330,330,663,663,330,330,663,330,663,330,663,330,663,330,663,330,663,10036};
uint16_t light50FanHigh[44] = {330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,663,330,330,663,330,663,663,330,330,663,663,330,663,330,663,330,663,330,10045};
uint16_t light60FanOff[44] = {330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,663,330,330,663,330,663,330,663,663,330,330,663,330,663,663,330,10041};
uint16_t light60FanLow[44] = {330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,663,330,663,330,663,330,330,663,663,330,663,330,330,663,330,663,10038};
uint16_t light60FanMed[44] = {330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,663,330,663,330,330,663,330,663,663,330,330,663,663,330,663,330,10034};
uint16_t light60FanHigh[44] = {330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,663,330,330,663,663,330,330,663,663,330,330,663,663,330,330,663,10047};
uint16_t light70FanOff[44] = {329,329,664,329,664,329,664,329,664,329,664,329,664,329,664,329,664,329,664,664,329,329,664,329,664,329,664,329,664,329,664,329,664,329,664,329,664,664,329,329,664,329,664,10052};
uint16_t light70FanLow[44] = {330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,663,330,663,330,663,330,10037};
uint16_t light70FanMed[44] = {329,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,663,329,329,663,329,663,329,663,329,663,663,329,329,663,329,663,329,663,663,329,663,329,329,663,10050};
uint16_t light70FanHigh[44] = {329,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,329,663,663,329,329,663,329,663,329,663,329,663,329,663,663,329,329,663,329,663,663,329,329,663,663,329,10041};
uint16_t light80FanOff[44] = {330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,663,330,330,663,330,663,330,663,663,330,663,330,663,330,330,663,10039};
uint16_t light80FanLow[44] = {330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,663,330,663,330,663,330,330,663,330,663,330,663,330,663,663,330,10045};
uint16_t light80FanMed[44] = {330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,663,330,663,330,330,663,330,663,330,663,330,663,330,663,330,663,10037};
uint16_t light80FanHigh[44] = {330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,663,330,330,663,663,330,330,663,663,330,663,330,663,330,663,330,10033};
uint16_t light90FanOff[44] = {330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,330,663,663,330,330,663,330,663,663,330,10038};
uint16_t light90FanLow[44] = {330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,663,330,663,330,330,663,663,330,663,330,330,663,330,663,10043};
uint16_t light90FanMed[44] = {330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,663,330,330,663,330,663,663,330,330,663,663,330,663,330,10047};
uint16_t light90FanHigh[44] = {330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,663,330,330,663,663,330,330,663,663,330,330,663,10051};
uint16_t light100FanOff[44] = {329,329,664,329,664,329,664,329,664,329,664,329,664,329,664,329,664,329,664,329,664,329,664,329,664,329,664,664,329,329,664,329,664,329,664,329,664,664,329,329,664,329,664,10057};
uint16_t light100FanLow[44] = {330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,663,330,330,663,330,663,663,330,663,330,663,330,10043};
uint16_t light100FanMed[44] = {330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,663,330,330,663,330,663,330,663,663,330,663,330,330,663,10034};
uint16_t light100FanHigh[44] = {330,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,330,663,663,330,330,663,663,330,330,663,330,663,663,330,330,663,663,330,10038};

void setup()
{
  irsend.begin();// For the RF transmiter
  WiFi.begin(ssid,password);
  Serial.begin(115200);
  while(WiFi.status()!=WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/fan",setFan);
  server.begin();
}

void loop()
{
  server.handleClient();
}

void setFan()
{
  static String fanSpeed = "off";
  static String lightState = "off";
  static String lastFanSpeed = "off";
  static String lastLightState = "off";  
  String newFanSpeed = server.arg("fanSpeed");
  String newLightState = server.arg("lightState");

  if((newFanSpeed != "same") && (newFanSpeed != "off") && (newFanSpeed != "on")){
    fanSpeed = newFanSpeed;
    lastFanSpeed = newFanSpeed;
  }
  else if((newFanSpeed == "on") || (newFanSpeed == "same")){
    fanSpeed = lastFanSpeed;
  }
  else if(newFanSpeed == "off"){
    fanSpeed = "off";
  }
  
  if((newLightState != "same") && (newLightState != "off") && (newLightState != "on")){
    lightState = newLightState;
    lastLightState = newLightState;
  }
  else if((newLightState == "on") || (newLightState == "same")){
    lightState = lastLightState;
  }
  else if(newLightState == "off"){
    lightState = "off";
  }  
  server.send(204,"");
 
  if (lightState == "off") { 
     for (int i = 0; i <= IRrepeat; i++) {
        yield();
        if(fanSpeed == "off"){
            irsend.sendRaw(lightOffFanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            irsend.sendRaw(lightOffFanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            irsend.sendRaw(lightOffFanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            irsend.sendRaw(lightOffFanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }
      }    
    }
  else if (lightState == "20") {
      for (int i = 0; i <= IRrepeat; i++) {
        yield();
        if(fanSpeed == "off"){
            irsend.sendRaw(light20FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            irsend.sendRaw(light20FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            irsend.sendRaw(light20FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            irsend.sendRaw(light20FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }
      }    
  }
  else if (lightState == "30") { 
      for (int i = 0; i <= IRrepeat; i++) {
        yield();
        if(fanSpeed == "off"){
            irsend.sendRaw(light30FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            irsend.sendRaw(light30FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            irsend.sendRaw(light30FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            irsend.sendRaw(light30FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }
      }    
  }
  else if (lightState == "40") { 
      for (int i = 0; i <= IRrepeat; i++) {
        yield();
        if(fanSpeed == "off"){
            irsend.sendRaw(light40FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            irsend.sendRaw(light40FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            irsend.sendRaw(light40FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            irsend.sendRaw(light40FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }
      }    
  }
  else if (lightState == "50") {
      for (int i = 0; i <= IRrepeat; i++) {
        yield();
        if(fanSpeed == "off"){
            irsend.sendRaw(light50FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            irsend.sendRaw(light50FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            irsend.sendRaw(light50FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            irsend.sendRaw(light50FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }
      }    
  }
  else if (lightState == "60") { 
      for (int i = 0; i <= IRrepeat; i++) {
        yield();
        if(fanSpeed == "off"){
            irsend.sendRaw(light60FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            irsend.sendRaw(light60FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            irsend.sendRaw(light60FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            irsend.sendRaw(light60FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }
      }    
  }
  else if (lightState == "70") {
      for (int i = 0; i <= IRrepeat; i++) {
        yield();
        if(fanSpeed == "off"){
            irsend.sendRaw(light70FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            irsend.sendRaw(light70FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            irsend.sendRaw(light70FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            irsend.sendRaw(light70FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }
      }    
  }
  else if (lightState == "80") { 
      for (int i = 0; i <= IRrepeat; i++) {
        yield();
        if(fanSpeed == "off"){
            irsend.sendRaw(light80FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            irsend.sendRaw(light80FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            irsend.sendRaw(light80FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            irsend.sendRaw(light80FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }
      }    
  }
  else if (lightState == "90") {
      for (int i = 0; i <= IRrepeat; i++) {
        yield();
        if(fanSpeed == "off"){
            irsend.sendRaw(light90FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            irsend.sendRaw(light90FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            irsend.sendRaw(light90FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            irsend.sendRaw(light90FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }
      }    
  }
  else if (lightState == "100") { 
      for (int i = 0; i <= IRrepeat; i++) {
        yield();
        if(fanSpeed == "off"){
            irsend.sendRaw(light100FanOff, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "low"){
            irsend.sendRaw(light100FanLow, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "med"){
            irsend.sendRaw(light100FanMed, 44, 38);  // Send a raw data capture at 38kHz.
        }
        else if(fanSpeed == "high"){
            irsend.sendRaw(light100FanHigh, 44, 38);  // Send a raw data capture at 38kHz.
        }
      }    
  }
}
