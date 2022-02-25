#include "OTAMngr.h"
#include <ArduinoOTA.h>

static uint8_t OTA_PROGRESS_LED;
static unsigned long PrgMillis = 0;

void OTAProgressCallback(size_t arg1, size_t arg2){
    if (millis() - PrgMillis >= 50){
        digitalWrite(OTA_PROGRESS_LED, !digitalRead(OTA_PROGRESS_LED));
        PrgMillis = millis();
    }
}

void OTAEndCallback(){
    digitalWrite(OTA_PROGRESS_LED, HIGH);
    PrgMillis = 0;
}

void OTAErrorCallback(ota_error_t error){
    digitalWrite(OTA_PROGRESS_LED, HIGH);
    PrgMillis = 0;
    ESP.restart();
}

void SetupOTAMngr(uint8_t ota_gpio_ind){
    pinMode(ota_gpio_ind, OUTPUT);
    digitalWrite(ota_gpio_ind, HIGH); /* HIGH - SWITCHOFF */

    ArduinoOTA.onError([](ota_error_t error) {
    debug_print("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      debug_print("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      debug_print("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      debug_print("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      debug_print("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      debug_print("End Failed");
    }
    OTAErrorCallback(error);
    });

    ArduinoOTA.onProgress(OTAProgressCallback);
    ArduinoOTA.onEnd(OTAEndCallback);

    ArduinoOTA.begin();
    OTA_PROGRESS_LED = ota_gpio_ind;
    debug_print("INFO: OTA server started\n");
}

void OTAMngrTaskLoop(){
    ArduinoOTA.handle();
}