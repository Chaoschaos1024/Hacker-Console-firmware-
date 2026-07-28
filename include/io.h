/*
   @Author: 无序熵增
   @Date: 2026-02-28 15:09:49
 * @LastEditors: 无序熵增
 * @LastEditTime: 2026-04-30 16:58:52
   @Description:

   Copyright (c) 2026 by 无序熵增, All Rights Reserved.
*/
#ifndef IO_H
#define IO_H
#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include "RP2040_PWM.h"
#include "config.h"
#include "pin_definitions.h"
#include "adc_filters.h"
#include "system_status.h"

class IO_CONFIG
{
public:
  bool begin();
  uint8_t hardware_version_detect();
  bool led1_set(bool led_status);
  bool led2_set(bool led_status);
  bool led1_flip();
  bool led2_flip();
  bool set_fan_speed(uint8_t speed);
  bool set_backlight_brightness(float brightness);
  float read_fan_speed();
  float read_backlight_brightness();
  float read_backlight_brightness_ui_percentage();
  bool enable_or_disable_backlight(bool enable_or_disable);
  bool read_hdmi_status();
  bool is_charging();
  bool is_charge_done();
#if power_module == new_
  uint8_t charge_status = 0;
  uint8_t charge_done_status = 0;
#endif
  uint16_t battery_voltage_read_raw();
  uint32_t battery_voltage_read_mv();
  float battery_voltage_read_v();
  float battery_percentage_read();
  uint16_t backlight_voltage_read_raw();
  uint32_t backlight_voltage_read_mv();
  float backlight_voltage_read_v();
  uint16_t main_power_voltage_read_raw();
  uint32_t main_power_voltage_read_mv();
  float main_power_voltage_read_v();
  uint16_t pi_3v3_voltage_read_raw();
  uint32_t pi_3v3_voltage_read_mv();
  float pi_3v3_voltage_read_v();
  bool iic_keyboard_read();
  uint8_t iic_keyboard_buffer[keyboard_iic_length];

  bool routine();

#if debug
  bool serial_setup();
#endif

private:
  bool iic_setup();
  bool pin_setup();
  bool adc_setup();
  bool pwm_setup();

  bool iic_device_detect();
  bool is_this_address_have_a_device(uint8_t address);
  bool iic_device_address_list[127] = {0};
  uint8_t iic_buffer[iic_buffer_length];
  bool iic_read(uint8_t device_address, uint8_t length);

  float fan_speed = fan_default_speed;
  float backlight_brightness = backlight_default_brightness;
  float backlight_brightness_ui_percentage = (backlight_default_brightness - backlight_brightness_minimum) * (100 / (backlight_brightness_maximum - backlight_brightness_minimum));

  // 电压(mV) -> 电量(%)，从 0% 到 100% 递增
  static constexpr int battery_voltage_levels[] = {
      3200, // 0%
      3300, // 5%
      3400, // 10%
      3500, // 15%
      3600, // 20%
      3650, // 25%
      3700, // 30%
      3750, // 35%
      3800, // 40%
      3850, // 45%
      3900, // 50%
      3950, // 55%
      4000, // 60%
      4050, // 65%
      4100, // 70%
      4130, // 75%
      4160, // 80%
      4180, // 85%
      4200, // 90%
      4210, // 95%
      4220  // 100%
  };
};

#endif
