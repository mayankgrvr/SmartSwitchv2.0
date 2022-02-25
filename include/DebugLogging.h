//#define DEBUG_SERIAL

#ifdef DEBUG_SERIAL
#define debug_init() Serial.begin(115200)
#else
#define debug_init() /* no debugging */
#endif

#ifdef DEBUG_SERIAL
#define debug_print(fmt, args...) Serial.printf(fmt, ## args)
#else
#define debug_print(fmt, args...) /* no debugging */
#endif

/** LED defs for inidications **/
#define HEARTBEAT_LED   LED_BUILTIN
#define OTA_IND_LED     5
