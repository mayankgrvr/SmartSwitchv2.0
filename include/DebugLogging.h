
#ifdef DEBUG_EN
#define debug_init() Serial.begin(115200)
#define debug_print(fmt, args...) Serial.printf(fmt, ## args)
#else
#define debug_init() /* no debugging */
#define debug_print(fmt, args...) /* no debugging */
#endif