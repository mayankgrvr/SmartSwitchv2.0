#include "maincpp.h"

#include <ESPAsyncWebServer.h>
#include <FS.h>
#include <LittleFS.h>

static AsyncWebServer AsyncWS(80);
uint8_t CntrlPin;

String processor(const String& var){
    String ledState;    

    if(var == "GPIO_STATE"){
        if(digitalRead(CntrlPin)){
            ledState = "OFF";
        } else{
            ledState = "ON";
        }
        return ledState;
    }
  return String();
}

void SetupWSMngr(uint8_t PinToCntrl){
    pinMode(PinToCntrl, OUTPUT);
    digitalWrite(PinToCntrl, HIGH);

    CntrlPin = PinToCntrl;

    // Initialize LittleFS before starting webserver
    if(!LittleFS.begin()){
        debug_print("ERROR: Error mounting LittleFS");
        //TO DO:device will work with base features
    }
 
    AsyncWS.on("/", HTTP_GET, [](AsyncWebServerRequest *req){
        req->send(200, "text/plain", "Connected");
    } );

    AsyncWS.on("/on", HTTP_GET, [](AsyncWebServerRequest *req){
        req->send(200, "text/plain", "ACK_ON");
        digitalWrite(CntrlPin, HIGH);
    } );

    AsyncWS.on("/off", HTTP_GET, [](AsyncWebServerRequest *req){
        req->send(200, "text/plain", "ACK_OFF");
        digitalWrite(CntrlPin, LOW);
    } );

    AsyncWS.on("/state", HTTP_GET, [](AsyncWebServerRequest *req){
        req->send(200, "text/plain", digitalRead(CntrlPin) ? "ON" : "OFF");
    } );

    AsyncWS.on("/reset", HTTP_GET, [](AsyncWebServerRequest *req){
        req->send(200, "text/plain", "ACK_RST");
        delay(100); //reset with some delay.
        ESP.restart();
    } );

    AsyncWS.on("/time", HTTP_GET, [](AsyncWebServerRequest *req){
        time_t Now = time(nullptr);
        struct tm TimeInfo;
        localtime_r(&Now, &TimeInfo);
        req->send(200, "text/plain", asctime(&TimeInfo));
    });

    AsyncWS.on("/html", HTTP_GET, [](AsyncWebServerRequest *req){
        req->send(LittleFS, "/index.html", String(), false, processor);
    });

    // Route to load style.css file
    AsyncWS.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *req){
        req->send(LittleFS, "/style.css", "text/css");
    });

    AsyncWS.onNotFound([](AsyncWebServerRequest *req){
        req->send(200, "text/plain", "NOT FOUND Send -> / /on /off");
    } );
}

void StartWS(){
    AsyncWS.begin();
}

void EndWS(){
    AsyncWS.end();
}