import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from esphome.const import CONF_UPDATE_INTERVAL
from . import DS1624

DEPENDENCIES = ['i2c']

ds1624_ns = cg.esphome_ns.namespace('sensor').namespace('ds1624')

DS1624Sensor = ds1624_ns.class_('DS1624Sensor', sensor.Sensor, cg.Component)

CONFIG_SCHEMA = sensor.sensor_schema().extend({
    cv.GenerateID(): cv.declare_id(DS1624Sensor),
}).extend(cv.polling_component_schema()).extend({
    cv.GenerateID(): cv.declare_id(DS1624.DS1624),
}).extend(cv.polling_component_schema('60s')).extend(i2c.i2c_device_schema(CONF_I2C_ADDR))

def to_code(config):
    var = cg.new_Pvariable(config[CONF_DS1624_ID])
    yield cg.register_component(var, config)
    cg.add(var.set_i2c_component(config[CONF_I2C_ID]))
    yield sensor.register_sensor(var, config)
    yield i2c.register_i2c_device(var, config)
