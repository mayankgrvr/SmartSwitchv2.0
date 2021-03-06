# SmartSwitchV2.0
 

 SmartSwitch v2.0 

Requirements:
-------------
1. The Project is intended to control RO switch on/off logic.
2. Should connect to WiFi to allow [provided by local webserver]
        - control of switch ON/off
        - Update NodeLogic. NodeLogic is on node logic which can switch on/off
           RO using some predetermined rules.
3. Should be able to update OTA. [provided by OTAMngr]
4. Should be able to log and report any crash or errors. [provided by local webserver]
        - Local webserver to show any last error logs. [logging section to be implemented webserver]
        - LED to indicate device is in good state. [provided by heartbeat ticker]
5. VIA Local webserver
        - have command to stop the RO at any time.
        - can start/stop RO anytime.
        - can stop running Nodelogic and make this device into simple on/off switch.

optional:
* Ability to put device in sleep for night/programmable period of time.

NODELOGIC:
----------
- switch on RO at pre-determined/programmable time of day,
    for pre-determined/programmable interval.

ERROR Scenarios:
---------------

1. LOSS of WIFI connectivity
        - Notify the WIFI service clients e.g. mqtt for local cleanup.              [done]
        - Put device in AP_STA mode, to give access to local webserver.             [NI in current version]
        - Switch LED to indicate loss of connectivity.                              [done]
        - Try restoring WiFi connectivity and reconnect if WiFi is available.       [done]
        - On reconnection Notify WiFi restoration clients e.g. mqtt for restart.    [done]

2. MQTT connectivity loss **not implemented                                         [NI in current Version]
        - Try connecting to MQTT Broker (need to check may require restart)
        - Log failure reasons which capture on webserver.

3. POWER loss
        - Start with default switch off state.                                      [In-Progress]
        - RUN nodelogic, if enabled.                                                [In-Progress]
            - as per last state and node logic complete task.

Design:
-------

NODE:
    - WiFiManager [configuration portal support]
        . to configure wifi
        . to configure connection protocols server parameters.
    - AsyncWebServer [status of NODE and Config portal for Node Logic]
        . to configure NodeLogic
        . to provide manual overrides
        . to provide failsafe stop/start buttons
        . to put device in WiFi/Comm config mode
    - MQTT Client [OPENHAB bindings ] **not implemented/required for current version
        . to get commands via public brokers
        . to communicate to Automation server and get config/manual commands
        . to tell status and other sensory data
    - OTA [update sketch remotely]
        . update sketch remotely
        . fix bugs and further development

Host/Controller:
    . will control via a webserver hosted on node
    . no new app requirement only webbrowser requirement


Test cases:
-----------

error scenarios
1. loss of wifi connectvity 
        . device should try to connect back to wifi.
        . device should start in STA mode and local webserver fully functional.
        . device should indicate via modifying HEARTBEAT LED blinking time.

2. loss of power loss
        . device should restore in default state.
        . device connect to WiFi.
        . device re-read node logic and resume from where left.

functional scenario
1. device to host config server
2. device to start local webserver
3. device to control and implement all local webserver requirements


debug-

pio device monitor -f esp8266_exception_decoder