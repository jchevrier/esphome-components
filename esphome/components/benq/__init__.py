import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import uart
from esphome.const import CONF_ID

DEPENDENCIES = ["uart"]

CONF_BENQ_ID = "benq_id"
CONF_BENQ_CMD_NAME = "command"
CONF_BENQ_RETRY_TIMEOUT = "retry_timeout_second"
benq_ns = cg.esphome_ns.namespace("benq")
Benq = benq_ns.class_("Benq", cg.Component, uart.UARTDevice)

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(Benq),
            cv.Optional(CONF_BENQ_RETRY_TIMEOUT, default=5): cv.uint8_t,
        }
    )
    .extend(cv.polling_component_schema("10s"))
    .extend(uart.UART_DEVICE_SCHEMA)
)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)
    cg.add(var.set_retry_timeout_value(config[CONF_BENQ_RETRY_TIMEOUT]))
