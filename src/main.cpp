#include "maincpp.h"
#include <Ticker.h>

#include "WifiConnectionMng.h"
#include "OTAMngr.h"
#include "WebServerMngr.h"

#define CNTRL_RLY_01 4

Ticker HeartBeat;
#define NO_HB
#ifdef NO_HB
#define HB_ATTACH_NORMAL do { HeartBeat.detach(); \
    digitalWrite(HEARTBEAT_LED, LOW);}while(0);
#else
#define HB_ATTACH_NORMAL do { HeartBeat.detach(); \
    HeartBeat.attach(2, [](){  \
    digitalWrite(HEARTBEAT_LED, !digitalRead(HEARTBEAT_LED)); \
    });} while(0);
#endif
#define HB_ATTACH_FAST do { HeartBeat.detach(); \
    HeartBeat.attach_ms(200, [](){  \
    digitalWrite(HEARTBEAT_LED, !digitalRead(HEARTBEAT_LED)); \
    });} while(0);

void setup() {

  debug_init();
  debug_print("Booting..\n" );

  /** Toggle HEARTBEAT LED every 500ms **/
  pinMode(HEARTBEAT_LED, OUTPUT);
  digitalWrite(HEARTBEAT_LED, LOW);
  HB_ATTACH_FAST;

  //initialize and setup Wifi using WiFiManager
  SetupWifi();
  configTime(TZ_Asia_Kolkata, "0.in.pool.ntp.org",
  "1.in.pool.ntp.org",
  "pool.ntp.org");
  SetupOTAMngr(OTA_IND_LED);
  SetupWSMngr(CNTRL_RLY_01);

  StartWS();
  HB_ATTACH_NORMAL;
}

void loop() {
  if (WiFi.isConnected()) {
    OTAMngrTaskLoop(); 
    
  } else {
    HB_ATTACH_FAST;
  
    /* Notify/Stop clients for wifi lost connectivity if required */
    /* Only house keeping tasks need to do while not connected */
    do {
      delay(2000);
    }while (!WiFi.isConnected());

    /** we are here it means we are connected again **/
    HB_ATTACH_NORMAL;
  }
}