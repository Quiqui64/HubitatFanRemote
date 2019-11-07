/**
 *  Virtual Hampton Bay Fan Version 1.0
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


metadata {
    definition (name: "Virtual Hampton Bay Fan G1", namespace: "Jason", author: "Jason Brown") {
        capability "Fan Control"
        capability "Switch"

    }
        preferences {
        input(name: "url", type: "string", title:"url", description: "IP Address and Dip Switch Settings.", defaultValue: "http://192.168.1.4/1010", displayDuringSetup: true)
        input name: "logEnable", type: "bool", title: "Enable debug logging", defaultValue: true
	}  
}
	
def setSpeed(speed){
    if(speed == "off"){
        if (logEnable) log.debug "Setting fan speed to Off"
        runCmd("off")
        sendEvent(name: "speed", value: "off", isStateChange: true)
        sendEvent(name: "switch", value: "off", isStateChange: true)
    }
    else if(speed == "low"){
        if (logEnable) log.debug "Setting fan speed to Low"
        runCmd("low")
        sendEvent(name: "speed", value: "low", isStateChange: true)
        sendEvent(name: "switch", value: "on", isStateChange: true)
    }
    else if(speed == "medium-high" || speed == "medium-low" || speed == "medium"){
        speed = "medium"
        if (logEnable) log.debug "Setting fan speed to Meduim"
        runCmd("med")
        sendEvent(name: "speed", value: "med", isStateChange: true)
        sendEvent(name: "switch", value: "on", isStateChange: true)
    }
    else if(speed == "high"){
        if (logEnable) log.debug("Setting fan speed to High")
        runCmd("high")
        sendEvent(name: "speed", value: "high", isStateChange: true)
        sendEvent(name: "switch", value: "on", isStateChange: true)
    }
}

def on(){
//    runCmd("on")
    def presetSpeed = device.currentValue("speed")
    log.debug ("presetSpeed")
    log.debug (presetSpeed)
    if(presetSpeed == "off"){
        runCmd("high")
        sendEvent(name: "speed", value: "high", isStateChange: true)
    }
    else{
        runCmd(presetSpeed)
    }
	sendEvent(name: "switch", value: "on", isStateChange: true)
    }

def off(){
    runCmd("off")
	sendEvent(name: "switch", value: "off", isStateChange: true)
    }

def updated() {
    log.info "updated..."
    log.warn "debug logging is: ${logEnable == true}"
    if (logEnable) runIn(1800, logsOff)
}

def logsOff() {
    log.warn "debug logging disabled..."
    device.updateSetting("logEnable", [value: "false", type: "bool"])
}
  
def runCmd(String fanSpeed){
    def postParams = [
            uri: url,
            contentType: "application/json",
            body : [lightState : "same", fanSpeed : fanSpeed]        
    	]
        try {
            httpPost(postParams) { resp ->
                log.debug resp.data
            }
        } catch(Exception e) {
            log.debug "error occured calling httpPost ${e}"
        }
}
