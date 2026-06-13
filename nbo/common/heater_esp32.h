#pragma once

#define ADC_MIN_VALUE 5.0
#define ADC_MAX_VALUE 30.0

#define MAX_INTERNAL_TEMPERATURE    65
#define INTERNAL_TEMPERATURE_RESUME 50

#define DHT_SOURCE              "DHT"
#define INTAKE_SOURCE           "Intake"
#define HOME_ASSISTANT_SOURCE   "Home Assistant"

#define STATUS_OVERHEATING      "Overheating"
#define STATUS_OK               "OK"
#define STATUS_INTAKE_FALLBACK  "Intake Source"
#define STATUS_DHT_FALLBACK     "DHT Source"
#define STATUS_MIX_FALLBACK     "Mix Source"
#define STATUS_SOURCE_ERROR     "Source Error"

#define INTAKE_ICON "󰸂"
#define DHT_ICON "󰸃"
#define REMOTE_ICON "󰽕"

#define WIFI_CONNECTED "󰖩"
#define WIFI_DISCONNECTED "󰖪"

#define OK_ICON "󰄬"
 // mdi-eye-off-outline
#define ERROR_ICON "󰛑"
#define INTAKE_FALLBACK_ICON "󱀧"
#define DHT_FALLBACK_ICON "󰩕"
#define OVERHEATING_ICON "󱗗"

#define MODE_HEATING "󰐸"
#define MODE_HEAT "󰫗"
#define MODE_OFF "󰍷"

#define SAFETY_STOP_ICON "󱜢"
#define SAFETY_OK_ICON "󱃙"

void paint_display(display::Display & it) {
  // auto &it = *screen;
  if (!id(screen_saver_script).is_running()) {
    it.fill(COLOR_OFF);
  }
  else {
    auto src_state = id(temperature_source).state;
    auto status_state = id(source_state).state;
    auto src_icon = src_state == INTAKE_SOURCE ? INTAKE_ICON : (src_state == DHT_SOURCE ? DHT_ICON : REMOTE_ICON);
    auto mode_icon = id(heater).mode == climate::CLIMATE_MODE_HEAT ? (id(heater).action == climate::CLIMATE_ACTION_HEATING ? MODE_HEATING : MODE_HEAT) : MODE_OFF;
    auto safety_icon = id(safety_stop).state ? SAFETY_STOP_ICON : SAFETY_OK_ICON;
    const char* status_icon;
    if (status_state == STATUS_OK) {
      status_icon = OK_ICON;
    }
    else if (status_state == STATUS_SOURCE_ERROR) {
      status_icon = ERROR_ICON;
    }
    else if (status_state == STATUS_INTAKE_FALLBACK) {
      status_icon = INTAKE_FALLBACK_ICON;
    }
    else if (status_state == STATUS_DHT_FALLBACK) {
      status_icon = DHT_FALLBACK_ICON;
    }
    else {
      status_icon = OVERHEATING_ICON;
    }
    it.print(0, 0, font_icon, TextAlign::TOP_LEFT, src_icon);
    it.print(20, 0, font_icon, TextAlign::TOP_LEFT, id(wifi_obj).is_connected() ? WIFI_CONNECTED : WIFI_DISCONNECTED);
    it.print(40, 0, font_icon, TextAlign::TOP_LEFT, status_icon);
    if (id(safety_stop).state) {
      it.print(60, 0, font_icon, TextAlign::TOP_LEFT, safety_icon);
    } else {
      it.print(60, 0, font_icon, TextAlign::TOP_LEFT, safety_icon);
    }
    it.print(100, 0, font_icon, TextAlign::TOP_LEFT, mode_icon);
    if (id(ambient_temperature).has_state() && id(ambient_temperature).state < 99) {
      it.printf(0, 25, font_temp, "%-2.0f°C", id(ambient_temperature).state);
    }
    else {
      it.printf(0, 25, font_temp, "--°C");
    }
    if (id(heater).mode == climate::CLIMATE_MODE_HEAT) {
      it.printf(80, 32, font_set, "%-2.0f°C", id(heater).target_temperature);
    }
    else {
      it.print(80, 32, font_set, "OFF ");
    }
  }
}
