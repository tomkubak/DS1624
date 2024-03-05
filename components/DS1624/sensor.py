import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import i2c, sensor
from esphome.const import CONF_ID, UNIT_EMPTY, ICON_EMPTY

DEPENDENCIES = ['i2c']

CONF_DS1624_ADDR = 0x48

ds1624_ns = cg.esphome_ns.namespace('ds1624')
DS1624Sensor = ds1624_ns.class_('DS1624Sensor', cg.PollingComponent, i2c.I2CDevice)

CONFIG_SCHEMA = sensor.sensor_schema(UNIT_EMPTY, ICON_EMPTY, 1).extend({
    cv.GenerateID(): cv.declare_id(DS1624Sensor),
}).extend(cv.polling_component_schema('60s')).extend(i2c.i2c_device_schema(CONF_DS1624_ADDR))

def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)
    yield sensor.register_sensor(var, config)
    yield i2c.register_i2c_device(var, config)
