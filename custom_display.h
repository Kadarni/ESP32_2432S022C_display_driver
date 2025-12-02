#include "esphome.h"
#include <LovyanGFX.hpp>

class LGFXCustom : public LovyanGFX {
  lgfx::Panel_ILI9488 _panel_instance;
  lgfx::Bus_Parallel8 _bus_instance;
public:
  LGFXCustom(void) {
    auto cfg = _bus_instance.config();
    cfg.freq_write = 16000000;
    cfg.pin_wr = 4;
    cfg.pin_rd = 2;
    cfg.pin_rs = 16;  // DC
    cfg.pin_d0 = 15;
    cfg.pin_d1 = 13;
    cfg.pin_d2 = 12;
    cfg.pin_d3 = 14;
    cfg.pin_d4 = 27;
    cfg.pin_d5 = 25;
    cfg.pin_d6 = 33;
    cfg.pin_d7 = 32;
    _bus_instance.config(cfg);
    _panel_instance.setBus(&_bus_instance);

    auto panel_cfg = _panel_instance.config();
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
    _panel_instance.config(panel_cfg);

    setPanel(&_panel_instance);
  }
};

class CustomDisplay : public PollingComponent, public DisplayBuffer {
public:
  LGFXCustom gfx;

  CustomDisplay() : PollingComponent(1000) {}

  void setup() override {
    gfx.init();
    gfx.setBrightness(128); // optional
  }

  void update() override {
    this->gfx.startWrite();
    this->gfx.fillScreen(TFT_BLACK);
    this->gfx.setTextColor(TFT_GREEN);
    this->gfx.setTextSize(2);
    this->gfx.setCursor(20, 20);
    this->gfx.print("ESPHome + LGFX");
    this->gfx.endWrite();
  }

  int get_width() override { return 240; }
  int get_height() override { return 320; }

  void draw_absolute_pixel_internal(int x, int y, Color color) override {
    gfx.drawPixel(x, y, color.raw_888());
  }
};
