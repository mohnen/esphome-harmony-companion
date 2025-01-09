import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import spi
from esphome.const import CONF_ID

DEPENDENCIES = ["spi"]

harmony_companion_hub_ns = cg.esphome_ns.namespace("harmony_companion_hub")
HarmonyCompanionHub = harmony_companion_hub_ns.class_(
    "HarmonyCompanionHub", cg.Component, spi.SPIDevice
)

CONFIG_SCHEMA = (
    cv.Schema({cv.GenerateID(): cv.declare_id(HarmonyCompanionHub)})
    .extend(cv.COMPONENT_SCHEMA)
    .extend(spi.spi_device_schema(cs_pin_required=True))
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await spi.register_spi_device(var, config)
