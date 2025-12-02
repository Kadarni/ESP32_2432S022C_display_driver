#include "esphome/core/component.h"
#include "esphome/components/display/display_buffer.h"

#include "lovyangfx/LovyanGFX.hpp"

namespace esphome {
namespace custom_display {

class CustomDisplay : public PollingComponent, public display::DisplayBuffer {
 public:
  CustomDisplay() : PollingComponent(1000) {}

  void setup() override;
  void update() override;
  void draw_absolute_pixel_internal(int x, int y, Color color) override;
  int get_width() override { return 240; }
  int get_height() override { return 320; }

 protected:
  lgfx::Panel_ST7789 panel_; // Use ILI9488, ILI9341, or your specific panel class
  lgfx::Bus_Parallel8 bus_; // 8-bit parallel bus
  LovyanGFX gfx_;
};

} // namespace custom_display
} // namespace esphome