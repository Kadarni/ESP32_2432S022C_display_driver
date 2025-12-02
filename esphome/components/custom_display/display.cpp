#include "display.h"
#include "esphome/core/log.h"

namespace esphome {
namespace custom_display {

static const char *const TAG = "custom_display";

void CustomDisplay::setup() {
  ESP_LOGI(TAG, "Setting up Custom Display (240x320 8-bit parallel)");

  auto bus_cfg = bus_.config();
  bus_cfg.freq_write = 16000000;  // 16 MHz is usually stable
  bus_cfg.pin_wr = 4;
  bus_cfg.pin_rd = 2;
  bus_cfg.pin_rs = 16;  // RS = DC

  // 8-bit data lines
  bus_cfg.pin_d0 = 15;
  bus_cfg.pin_d1 = 13;
  bus_cfg.pin_d2 = 12;
  bus_cfg.pin_d3 = 14;
  bus_cfg.pin_d4 = 27;
  bus_cfg.pin_d5 = 25;
  bus_cfg.pin_d6 = 33;
  bus_cfg.pin_d7 = 32;

  bus_.config(bus_cfg);

  panel_.setBus(&bus_);
  auto panel_cfg = panel_.config();

  panel_cfg.pin_cs = 17;
  panel_cfg.pin_rst = 1;
  panel_cfg.pin_busy = -1;

  panel_cfg.memory_width = 240;
  panel_cfg.memory_height = 320;
  panel_cfg.panel_width = 240;
  panel_cfg.panel_height = 320;
  panel_cfg.offset_x = 0;
  panel_cfg.offset_y = 0;
  panel_cfg.offset_rotation = 0;
  panel_cfg.dummy_read_pixel = 8;
  panel_cfg.dummy_read_bits = 1;

  panel_cfg.readable = false;
  panel_cfg.invert = false;
  panel_cfg.rgb_order = false;
  panel_cfg.dlen_16bit = false;
  panel_cfg.bus_shared = false;

  panel_.config(panel_cfg);
  gfx_.setPanel(&panel_);

  gfx_.init();
}

void CustomDisplay::update() {
  gfx_.fillScreen(TFT_BLACK);
  gfx_.setCursor(30, 30);
  gfx_.setTextSize(2);
  gfx_.setTextColor(TFT_GREEN);
  gfx_.print("Hello 8-bit");
}

void CustomDisplay::draw_absolute_pixel_internal(int x, int y, Color color) {
  gfx_.drawPixel(x, y, color.raw_888());
}

}  // namespace custom_display
}  // namespace esphome
ESPHOME_REGISTER_COMPONENT(CustomDisplay,display::DisplayBuffer);