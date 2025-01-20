#include "esphome/core/log.h"
#include "harmony-companion-hub.h"

namespace esphome {
    namespace harmony_companion_hub
    {

        void HarmonyCompanionHub::setup() {
            ESP_LOGCONFIG(TAG, "harmony-companion-hub setup()");
            this->ce_pin_->setup();
            this->csn_pin_->setup();
            this->radio_ = RF24(esphome::spi::Utility::get_pin_no(this->ce_pin_), 
                                esphome::spi::Utility::get_pin_no(this->csn_pin_));
            
            if (!this->radio_.begin()) {
                ESP_LOGE(TAG, "Failed to start radio");
                this->mark_failed();
                return;
            }

            this->radio_.setDataRate(RF24_2MBPS);
            this->radio_.enableDynamicPayloads();
            this->radio_.enableAckPayload();
            this->radio_.setCRCLength(RF24_CRC_16);

            ESP_LOGCONFIG(TAG, "Radio started succesfully");
            if (this->address_==0) {
                ESP_LOGE(TAG, "Missing address, should enter finde address mode ");   // TODO
                this->mark_failed();
                return;
            }

            this->radio_.setChannel(5);
            this->radio_.openReadingPipe(1, this->address_ & 0xFFFFFFFF00);
            this->radio_.openReadingPipe(2, this->address_ & 0xFFFFFFFFFF);
            this->radio_.startListening();
        }

        void HarmonyCompanionHub::loop() {
            uint8_t pipeNum = 0;
            if (pipeNum && this->radio_.available(&pipeNum)) {
                // Read packet
                int payloadSize = this->radio_.getDynamicPayloadSize();
                uint8_t dataReceived[payloadSize];
                this->radio_.read(&dataReceived, payloadSize);

                // Print contents
                // Serial.print("0x");
                // for (int i = 0; i < payloadSize; i++)
                // {
                //     char tmp[3];
                //     sprintf(tmp, "%.2X", dataReceived[i]);
                //     Serial.print(tmp);
                //     if (i < payloadSize - 1)
                //         Serial.print(".");
                // }
                // Serial.print(" (");
                ESP_LOGD(TAG, "%u bytes on pipe %u", payloadSize, pipeNum);
            }
        }

        void HarmonyCompanionHub::dump_config() {
            ESP_LOGCONFIG(TAG, "harmony-companion-hub dump_config()");
            LOG_PIN("  CE Pin: ", this->ce_pin_);
            LOG_PIN("  CSN Pin: ", this->csn_pin_);
            ESP_LOGCONFIG(TAG, "  Radio available: %s", this->radio_.isChipConnected()?"Yes":"No");
            ESP_LOGCONFIG(TAG, "  Address: 0x%llX", this->address_);
        }

    } // namespace harmony_companion_hub
}  // namespace esphome