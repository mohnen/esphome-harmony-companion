#include "esphome/core/log.h"
#include "harmony-companion-hub.h"

namespace esphome {
    namespace harmony_companion_hub
    {

        static const char *TAG = "harmony-companion-hub.component";
        void HarmonyCompanionHub::setup() {
            ESP_LOGCONFIG(TAG, "harmony-companion-hub setup()");
            this->ce_pin_->setup();
            this->csn_pin_->setup();
            this->radio_ = RF24(esphome::spi::Utility::get_pin_no(this->ce_pin_), 
                                esphome::spi::Utility::get_pin_no(this->csn_pin_));
            if (!this->radio_.begin()) {
                ESP_LOGE(TAG, "Failed to start radio");
            }
        }

        void HarmonyCompanionHub::loop() {
        }

        void HarmonyCompanionHub::dump_config() {
            ESP_LOGCONFIG(TAG, "harmony-companion-hub dump_config()");
            LOG_PIN("  CE Pin: ", this->ce_pin_);
            LOG_PIN("  CSN Pin: ", this->csn_pin_);
            ESP_LOGCONFIG(TAG, "  Radio available: %s", this->radio_.isChipConnected()?"Yes":"No");
        }

    } // namespace harmony_companion_hub
}  // namespace esphome