#include "WifiConnectionMng.h"

#include <ESP8266WiFiAP.h>
#include <WiFiManager.h>

void SetupWifi(){
    WiFi.mode(WIFI_STA);
    WiFi.setAutoReconnect(true);
 
    WiFiManager WifiSetupManager;
    WifiSetupManager.setConfigPortalBlocking(true);
    WifiSetupManager.setConfigPortalTimeout(180); //wait for 180 before retry.
    WifiSetupManager.setConnectTimeout(60);

    if (!WifiSetupManager.autoConnect(DEFAULT_AP_NAME, DEFAULT_AP_PASS)){
        debug_print("FATAL: Failed to start config portal");
        ESP.restart(); //restart will cause device to retry wifi connection.
        /**
         * ToDo: this will cause device to restart eternally if WiFi is never restored
         * handle this differently
         * **/
    }
}