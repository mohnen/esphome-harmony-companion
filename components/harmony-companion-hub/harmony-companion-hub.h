#pragma once

#include "esphome/core/log.h"
#include "esphome/core/component.h"
#include "esphome/components/spi/spi.h"

#include <nRF24L01.h>
#include <RF24.h>

#define TAG "harmony-companion-hub.component"

namespace esphome {
  namespace harmony_companion_hub
  {

    class HarmonyCompanionHub : public Component,
                                public spi::SPIDevice<spi::BIT_ORDER_MSB_FIRST, spi::CLOCK_POLARITY_LOW,
                                                      spi::CLOCK_PHASE_LEADING, spi::DATA_RATE_1KHZ>
    {
    public:
      void setup() override;
      void loop() override;
      void dump_config() override;
      void set_csn_pin(GPIOPin *pin) { this->csn_pin_ = pin; }
      void set_ce_pin(GPIOPin *pin) { this->ce_pin_ = pin; }
      void set_address(uint64_t address) { this->address_ = address; }

    protected:
      GPIOPin *csn_pin_;
      GPIOPin *ce_pin_;
      RF24 radio_;
      uint64_t address_;
    };

  } // namespace harmony_companion_hub
}  // namespace esphome