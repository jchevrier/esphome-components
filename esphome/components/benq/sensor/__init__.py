from esphome.components import sensor
import esphome.config_validation as cv
import esphome.codegen as cg
from esphome.const import CONF_ID
from .. import benq_ns, CONF_BENQ_ID, Benq, CONF_BENQ_CMD_NAME

DEPENDENCIES = ["benq"]

BenqSensor = benq_ns.class_("BenqSensor", sensor.Sensor, cg.Component)

CONFIG_SCHEMA = (
    sensor.sensor_schema(BenqSensor)
    .extend(
        {
            cv.GenerateID(CONF_BENQ_ID): cv.use_id(Benq),
            cv.Required(CONF_BENQ_CMD_NAME): cv.string,
        }
    )
    .extend(cv.COMPONENT_SCHEMA)
)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await sensor.register_sensor(var, config)

    parent = await cg.get_variable(config[CONF_BENQ_ID])
    cg.add(var.set_benq_parent(parent))

    cg.add(var.set_benq_command(config[CONF_BENQ_CMD_NAME]))
