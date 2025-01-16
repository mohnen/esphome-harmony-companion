#include "esphome/core/log.h"
#include "harmony-companion-hub.h"

#include <nRF24L01.h>
#include <RF24.h>

namespace esphome {
    namespace harmony_companion_hub
    {

        static const char *TAG = "harmony-companion-hub.component";

        void HarmonyCompanionHub::setup()
        {
            ESP_LOGCONFIG(TAG, "harmony-companion-hub setup()");
            this->ce_pin_->setup();
            this->csn_pin_->setup();
        }

        void HarmonyCompanionHub::loop()
        {
        }

        void HarmonyCompanionHub::dump_config()
        {
            ESP_LOGCONFIG(TAG, "harmony-companion-hub dump_config()");
        }

    } // namespace harmony_companion_hub
}  // namespace esphome