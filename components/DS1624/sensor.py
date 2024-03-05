import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from esphome.const import (
    CONF_ID,
    DEVICE_CLASS_TEMPERATURE,
    UNIT_EMPTY,
    ICON_EMPTY,
    UNIT_CELSIUS,
)

ds1624_ns = cg.esphome_ns.namespace("ds1624")
DS1624Temperature = ds1624_ns.class_("DS1624Temperature", sensor.Sensor, cg.Component)

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(DS1624Temperature),
        cv.Optional(CONF_UPDATE_INTERVAL, default="15s"): cv.positive_time_period_milliseconds,
        cv.Optional(CONF_ADDRESS, default=0x48): cv.hex_uint8_t,
    }
).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await sensor.register_sensor(var, config)

    cg.add(var.set_update_interval(config[CONF_UPDATE_INTERVAL]))
    cg.add(var.set_address(config[CONF_ADDRESS]))
    cg.add(var.set_device_class(DEVICE_CLASS_TEMPERATURE))
    cg.add(var.set_unit_of_measurement(UNIT_CELSIUS))
    cg.add(var.set_icon(ICON_EMPTY))
