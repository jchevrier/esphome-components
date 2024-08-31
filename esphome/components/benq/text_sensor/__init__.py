from esphome.components import text_sensor
import esphome.config_validation as cv
import esphome.codegen as cg
from esphome.const import CONF_SENSOR_DATAPOINT
from .. import benq_ns, CONF_BENQ_ID, Benq, CONF_BENQ_CMD_NAME

DEPENDENCIES = ["benq"]

BenqTextSensor = benq_ns.class_("BenqTextSensor", text_sensor.TextSensor, cg.Component)

CONFIG_SCHEMA = (
    text_sensor.text_sensor_schema()
    .extend(
        {
            cv.GenerateID(): cv.declare_id(BenqTextSensor),
            cv.GenerateID(CONF_BENQ_ID): cv.use_id(Benq),
            cv.Required(CONF_BENQ_CMD_NAME): cv.string,
        }
    )
    .extend(cv.COMPONENT_SCHEMA)
)


async def to_code(config):
    var = await text_sensor.new_text_sensor(config)
    await cg.register_component(var, config)

    parent = await cg.get_variable(config[CONF_BENQ_ID])
    cg.add(var.set_benq_parent(parent))
    cg.add(var.set_benq_command(config[CONF_BENQ_CMD_NAME]))
