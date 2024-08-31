import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor, uart, switch, number, select
from esphome.const import CONF_ID, UNIT_HOUR, CONF_NAME, CONF_OPTIONS

AUTO_LOAD = [ "switch", "sensor", "number", "select" ]

DEPENDENCIES = ["uart"]

th575_ns = cg.esphome_ns.namespace("th575")
TH575 = th575_ns.class_("TH575", cg.PollingComponent, uart.UARTDevice)

DemoSwitch = th575_ns.class_("DemoSwitch", switch.Switch, cg.Component)
Volume = th575_ns.class_("Volume", number.Number, cg.Component)
DemoSensor = th575_ns.class_(
    "DemoSensor", sensor.Sensor, cg.PollingComponent
)
TuyaSelect = th575_ns.class_("TuyaSelect", select.Select, cg.Component)


def ensure_option_map(value):
    cv.check_not_templatable(value)
    option = cv.All(cv.string_strict)
    options_map_schema = cv.Schema([option,])
    value = options_map_schema(value)

    return value

CONF_LAMPHOURS = "lamp_hours"
CONF_ONOFF = "on_off"
CONF_VOLUME = "volume"
CONF_SENSORS = "serial_sensors"
CONF_MYSELECT = "myselect"

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(TH575),
            cv.Optional(CONF_LAMPHOURS): sensor.sensor_schema(
                unit_of_measurement=UNIT_HOUR,
                accuracy_decimals=0,
            ),
            cv.Optional(CONF_ONOFF): switch.switch_schema(DemoSwitch).extend(cv.COMPONENT_SCHEMA),
            cv.Optional(CONF_VOLUME): number.number_schema(
                Volume,
                icon="mdi:volume-high"
                ),
            cv.Optional(
                CONF_SENSORS,
            ): [
                sensor.sensor_schema(DemoSensor).extend(
                    cv.polling_component_schema("60s")
                )
            ],
            cv.Optional(CONF_MYSELECT): select.select_schema(TuyaSelect)
            .extend(
                {
                    cv.Required(CONF_OPTIONS): ensure_option_map,
                }
            )
        }
    )
    .extend(cv.polling_component_schema("10s"))
    .extend(uart.UART_DEVICE_SCHEMA)
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)

    
    if lamp_config := config.get(CONF_LAMPHOURS):
        sens = await sensor.new_sensor(lamp_config)
        cg.add(var.set_lamphours_sensor(sens))

    if switch_config := config.get(CONF_ONOFF):
        sens = await switch.new_switch(switch_config)
        cg.add(var.set_onoff_switch(sens))

    if volume_config := config.get(CONF_VOLUME):
        sens = await number.new_number(volume_config,
                                       min_value=0,
                                       max_value=20,
                                       step=1)
        cg.add(var.set_volume_number(sens))

    if sensors_config := config.get(CONF_SENSORS):
        for conf in sensors_config[CONF_SENSORS]:
            var = await sensor.new_sensor(conf)
            await cg.register_component(var, conf)
    if myselect_config := config.get(CONF_MYSELECT):
        options_map = myselect_config[CONF_OPTIONS]
        var = await select.new_select(myselect_config, options=options_map)
        await cg.register_component(var, myselect_config)
