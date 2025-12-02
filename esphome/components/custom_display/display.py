from esphome.components import display
import esphome.config_validation as cv

CONFIG_SCHEMA = display.BASIC_DISPLAY_SCHEMA.extend({}).extend(cv.COMPONENT_SCHEMA)

def to_code(config):
    return