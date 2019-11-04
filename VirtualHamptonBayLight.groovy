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
    definition (name: "Virtual Hampton Bay Light", namespace: "Jason", author: "Jason Brown") {
		capability "Light"
        capability "Switch"
        capability "Switch Level"
        capability "Actuator"
    }
        preferences {
        input(name: "url", type: "string", title:"url", description: "The URL, include forward slash.", defaultValue: "http://192.168.1.4/1010", displayDuringSetup: true)
        input name: "logEnable", type: "bool", title: "Enable debug logging", defaultValue: true
	}  
}
def lastLightLevel = 0

def on(){
    runCmd("on")
	sendEvent(name: "switch", value: "on")
    }

def off(){
    runCmd("off")
	sendEvent(name: "switch", value: "off")
    }

def setLevel(value) {
    lastLightLevel = value
	if (logEnable) log.debug "setLevel >> value: $value"
	def level = Math.max(Math.min(value as Integer, 100), 0)
	if (level > 0) {
		sendEvent(name: "switch", value: "on")
	}
    else{
        runCmd("off")
		sendEvent(name: "switch", value: "off")
	}
    if(level > 0 && level < 25){
        runCmd("20")
		sendEvent(name: "level", value: "20", unit: "%")
        if (logEnable) log.debug "At 20"
	}
    else if(level > 24 && level < 35){
        runCmd("30")
		sendEvent(name: "level", value: "30", unit: "%")
	}
	else if(level > 34 && level < 45){
        runCmd("40")
		sendEvent(name: "level", value: "40", unit: "%")
	}
    else if(level > 44 && level < 55){
        runCmd("50")
		sendEvent(name: "level", value: "40", unit: "%")
	}
    else if(level > 54 && level < 65){
        runCmd("60")
		sendEvent(name: "level", value: "60", unit: "%")
	}
    else if(level > 64 && level < 75){
        runCmd("70")
		sendEvent(name: "level", value: "70", unit: "%")
	}
    else if(level > 74 && level < 85){
        runCmd("80")
		sendEvent(name: "level", value: "80", unit: "%")
	}
    else if(level > 84 && level < 95){
        runCmd("90")
		sendEvent(name: "level", value: "90", unit: "%")
	}
    else if(level > 94 ){
        runCmd("100")
		sendEvent(name: "level", value: "100", unit: "%")
	}
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
