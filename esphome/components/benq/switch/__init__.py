from esphome.components import switch
import esphome.config_validation as cv
import esphome.codegen as cg
from esphome.const import CONF_ID
from .. import benq_ns, CONF_BENQ_ID, Benq, CONF_BENQ_CMD_NAME

DEPENDENCIES = ["benq"]

CONF_BENQ_ON_VALUE = "on_value"
CONF_BENQ_OFF_VALUE = "off_value"
CONF_BENQ_REPEAT_OFF_VALUE = "repeat_off"

BenqSwitch = benq_ns.class_("BenqSwitch", switch.Switch, cg.Component)

CONFIG_SCHEMA = (
    switch.switch_schema(BenqSwitch)
    .extend(
        {
            cv.GenerateID(CONF_BENQ_ID): cv.use_id(Benq),
            cv.Required(CONF_BENQ_CMD_NAME): cv.string,
            cv.Required(CONF_BENQ_ON_VALUE): cv.string,
            cv.Required(CONF_BENQ_OFF_VALUE): cv.string,
            cv.Optional(CONF_BENQ_REPEAT_OFF_VALUE, default=False): cv.boolean,
        }
    )
    .extend(cv.COMPONENT_SCHEMA)
)


async def to_code(config):
    var = await switch.new_switch(config)
    await cg.register_component(var, config)

    parent = await cg.get_variable(config[CONF_BENQ_ID])
    cg.add(var.set_benq_parent(parent))
    
    cg.add(var.set_on_value(config[CONF_BENQ_ON_VALUE]))
    cg.add(var.set_off_value(config[CONF_BENQ_OFF_VALUE]))
    cg.add(var.set_repeat_off_value(config[CONF_BENQ_REPEAT_OFF_VALUE]))
    cg.add(var.set_benq_command(config[CONF_BENQ_CMD_NAME]))

