from esphome.components import number
import esphome.config_validation as cv
import esphome.codegen as cg
from esphome.const import (
    CONF_ID,
    CONF_MAX_VALUE,
    CONF_MIN_VALUE,
    CONF_STEP,
)
from .. import benq_ns, CONF_BENQ_ID, Benq, CONF_BENQ_CMD_NAME

DEPENDENCIES = ["benq"]

BenqNumber = benq_ns.class_("BenqNumber", number.Number, cg.Component)


def validate_min_max(config):
    max_value = config[CONF_MAX_VALUE]
    min_value = config[CONF_MIN_VALUE]
    if max_value <= min_value:
        raise cv.Invalid("max_value must be greater than min_value")
    return config


CONFIG_SCHEMA = cv.All(
    number.number_schema(BenqNumber)
    .extend(
        {
            cv.GenerateID(CONF_BENQ_ID): cv.use_id(Benq),
            cv.Required(CONF_BENQ_CMD_NAME): cv.string,
            cv.Required(CONF_MAX_VALUE): cv.uint8_t,
            cv.Required(CONF_MIN_VALUE): cv.uint8_t,
            cv.Required(CONF_STEP): cv.uint8_t,
        }
    )
    .extend(cv.COMPONENT_SCHEMA),
    validate_min_max,
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await number.register_number(
        var,
        config,
        min_value=config[CONF_MIN_VALUE],
        max_value=config[CONF_MAX_VALUE],
        step=config[CONF_STEP],
    )

    parent = await cg.get_variable(config[CONF_BENQ_ID])
    cg.add(var.set_benq_parent(parent))

    cg.add(var.set_benq_command(config[CONF_BENQ_CMD_NAME]))
