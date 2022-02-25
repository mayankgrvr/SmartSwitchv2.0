#include "maincpp.h"

/**
 * @brief 
 * 
 * @param ota_gpio_ind - gpio for ota start indication
 */

void SetupOTAMngr(uint8_t ota_gpio_ind);

/**
 * @brief OTA task loop to check OTA available
 * 
 */
void OTAMngrTaskLoop();