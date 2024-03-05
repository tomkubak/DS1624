import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor, i2c
from esphome.const import CONF_ADDRESS, UNIT_EMPTY, ICON_EMPTY

DEPENDENCIES = ['i2c']

ds1624_ns = cg.esphome_ns.namespace('sensor').namespace('ds1624')

DS1624Sensor = ds1624_ns.class_('DS1624Sensor', sensor.Sensor, cg.Component)

CONFIG_SCHEMA = sensor.sensor_schema(unit_of_measurement=UNIT_EMPTY, icon=ICON_EMPTY).extend({
    cv.GenerateID(): cv.declare_id(DS1624Sensor),
    cv.Required(CONF_ADDRESS): cv.i2c_address,
}).extend(i2c.i2c_device_schema(CONF_ADDRESS))

def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)
    cg.add(var.set_address(config[CONF_ADDRESS]))
    yield sensor.register_sensor(var, config)
    yield i2c.register_i2c_device(var, config)
