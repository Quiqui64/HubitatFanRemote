/**
 *  Virtual Hampton Bay Light Version 1.0
 *  Note Light only dims to 20% and I only recorded the values in 10% steps.
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

metadata {
    definition (name: "Virtual Hampton Bay Light G1", namespace: "Jason", author: "Jason Brown") {
        capability "Actuator"
        capability "Sensor"
        capability "Switch"
        capability "Switch Level"
    }

    preferences {
        input(name: "url", type: "string", title:"url", description: "IP Address and Dip Switch Settings.", defaultValue: "http://192.168.1.4/1010", displayDuringSetup: true)
        input name: "logEnable", type: "bool", title: "Enable debug logging", defaultValue: true
    }
}

def parse(String description) {
}

def on() {
    log.trace "Executing 'on'"
    turnOn()
}

def off() {
    log.trace "Executing 'off'"
    turnOff()
}

def setLevel(value) {
    if (logEnable) log.debug "setLevel value is"
    if (logEnable) log.debug value
    log.trace "Executing setLevel $value"
    Map levelEventMap = buildSetLevelEvent(value)
    if (levelEventMap.value == 0) {
        turnOff()
        // notice that we don't set the level to 0'
    } else {
        implicitOn()
        sendEvent(levelEventMap)
        setESP8266(value)
    }
}
    
private Map buildSetLevelEvent(value) {
    def intValue = value as Integer
    def newLevel = Math.max(Math.min(intValue, 100), 0)
    Map eventMap = [name: "level", value: newLevel, unit: "%", isStateChange: true]
    return eventMap
}

def setLevel(value, duration) {
    log.trace "Executing setLevel $value (ignoring duration)"
    setLevel(value)
}

private implicitOn() {
    if (device.currentValue("switch") != "on") {
        turnOn()
    }
}

private turnOn() {
    sendEvent(name: "switch", value: "on", isStateChange: true)
    def value = device.currentValue("level")
    setESP8266(value)
}

private turnOff() {
    runCmd("off")
    sendEvent(name: "switch", value: "off", isStateChange: true)
}

def installed() {
    setLevel(100)
}

def setESP8266(value){
    if(value > 1 && value < 25){
        runCmd("20")
	}
    else if(value > 24 && value < 35){
        runCmd("30")
	}
	else if(value > 34 && value < 45){
        runCmd("40")
	}
    else if(value > 44 && value < 55){
        runCmd("50")
	}
    else if(value > 54 && value < 65){
        runCmd("60")
	}
    else if(value > 64 && value < 75){
        runCmd("70")
	}
    else if(value > 74 && value < 85){
        runCmd("80")
	}
    else if(value > 84 && value < 95){
        runCmd("90")
	}
    else if(value > 94 ){
        runCmd("100")
	}
}

def runCmd(String lightState){
    def postParams = [
            uri: url,
            contentType: "application/json",
            body : [lightState : lightState, fanSpeed : "same"]        
    	]
        try {
            httpPost(postParams) { resp ->
                log.debug resp.data
            }
        } catch(Exception e) {
            log.debug "error occured calling httpPost ${e}"
        }
}
