from esphome.components import select
import esphome.config_validation as cv
import esphome.codegen as cg
from esphome.const import CONF_OPTIONS, CONF_OPTIMISTIC
from .. import benq_ns, CONF_BENQ_ID, Benq, CONF_BENQ_CMD_NAME

DEPENDENCIES = ["benq"]
BenqSelect = benq_ns.class_("BenqSelect", select.Select, cg.Component)

def ensure_option_map(value):
    cv.check_not_templatable(value)
    option = cv.All(cv.string_strict)
    options_map_schema = cv.Schema([option,])
    value = options_map_schema(value)

    return value

CONFIG_SCHEMA = (
    select.select_schema(BenqSelect)
    .extend(
        {
            cv.GenerateID(CONF_BENQ_ID): cv.use_id(Benq),
            cv.Required(CONF_BENQ_CMD_NAME): cv.string,
            cv.Required(CONF_OPTIONS): ensure_option_map,
            cv.Optional(CONF_OPTIMISTIC, default=False): cv.boolean,
        }
    )
    .extend(cv.COMPONENT_SCHEMA)
)


async def to_code(config):
    options_map = config[CONF_OPTIONS]
    var = await select.new_select(config, options=list(options_map))
    await cg.register_component(var, config)
    cg.add(var.set_select_mappings(list(options_map)))
    parent = await cg.get_variable(config[CONF_BENQ_ID])
    cg.add(var.set_benq_parent(parent))
    cg.add(var.set_optimistic(config[CONF_OPTIMISTIC]))
    cg.add(var.set_benq_command(config[CONF_BENQ_CMD_NAME]))
