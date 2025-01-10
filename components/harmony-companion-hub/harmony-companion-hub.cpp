#include "esphome/core/log.h"
#include "harmony-companion-hub.h"

namespace esphome {
    namespace harmony_companion_hub
    {

        static const char *TAG = "harmony-companion-hub.component";

        void HarmonyCompanionHub::setup()
        {
        }

        void HarmonyCompanionHub::loop()
        {
        }

        void HarmonyCompanionHub::dump_config()
        {
            ESP_LOGCONFIG(TAG, "harmony-companion-hub component");
        }

    } // namespace harmony_companion_hub
}  // namespace esphome