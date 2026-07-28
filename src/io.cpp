/*
   @Author: 无序熵增
   @Date: 2026-02-28 15:09:49
   @LastEditors: 无序熵增
   @LastEditTime: 2026-04-30 17:00:50
   @Description:

   Copyright (c) 2026 by 无序熵增, All Rights Reserved.
*/
#include "io.h"

uint32_t pwm_pins[] = {fan_pwm_pin, screen_backlight_pwm_pin};
RP2040_PWM *pwm_instance[2];

#if (battery_voltage_filter == FIR_mode)
FIR_filter battery_filter;
#elif (battery_voltage_filter == IIR_mode)
IIR_filter battery_filter;
#endif

#if (backlight_voltage_filter == FIR_mode)
FIR_filter backlight_filter;
#elif (backlight_voltage_filter == IIR_mode)
IIR_filter backlight_filter;
#endif

#if (main_power_voltage_filter == FIR_mode)
FIR_filter main_power_filter;
#elif (main_power_voltage_filter == IIR_mode)
IIR_filter main_power_filter;
#endif

#if (pi_3v3_voltage_filter == FIR_mode)
FIR_filter pi_3v3_filter;
#elif (pi_3v3_voltage_filter == IIR_mode)
IIR_filter pi_3v3_filter;
#endif

#if debug
bool IO_CONFIG::serial_setup()
{
  debug_serial.setRX(debug_rx_pin);
  debug_serial.setTX(debug_tx_pin);
  debug_serial.setFIFOSize(128);
  debug_serial.begin(115200);
  Serial.begin(115200);
#if debug
  debug_serial.println("Serial setup complete");
#endif
  return true;
}
#endif
bool IO_CONFIG::iic_setup()
{
  Wire1.setSDA(iic_sda_pin);
  Wire1.setSCL(iic_scl_pin);
  Wire1.begin();
  // Wire1.setClock(3400000);
  for (int i = 0; i < iic_buffer_length; i++)
  {
    iic_buffer[i] = 0;
  }
#if debug
  debug_serial.println("IIC setup complete");
#endif
  return true;
}

bool IO_CONFIG::pin_setup()
{
  pinMode(keyboard_int, INPUT_PULLUP);
  // pinMode(fan_pwm_pin, OUTPUT);
  pinMode(hdmi_signal_detect_pin, INPUT);
  pinMode(led1_pin, OUTPUT);
  pinMode(led2_pin, OUTPUT);
  // pinMode(screen_backlight_pwm_pin, OUTPUT);
  pinMode(screen_enable_pin, OUTPUT);
#if debug
  digitalWrite(screen_enable_pin, HIGH);
#endif
#if power_module == old_
  pinMode(charge_status_pin, INPUT_PULLUP);
  pinMode(charge_done_pin, INPUT_PULLUP);
#endif
#if power_module == new_
  pinMode(charge_status_pin, INPUT);
  pinMode(charge_done_pin, INPUT);
#endif
  pinMode(ws2812_pin, OUTPUT);
#if debug
  debug_serial.println("Pin setup complete");
#endif
  return true;
}

bool IO_CONFIG::adc_setup()
{
  analogReadResolution(adc_accuracy);

#if (battery_voltage_filter == FIR_mode)
  battery_filter.begin();
#elif (battery_voltage_filter == IIR_mode)
  battery_filter.begin(analogRead(battery_adc_pin));
#endif

#if (backlight_voltage_filter == FIR_mode)
  backlight_filter.begin();
#elif (backlight_voltage_filter == IIR_mode)
  backlight_filter.begin(analogRead(backlight_adc_pin));
#endif

#if (main_power_voltage_filter == FIR_mode)
  main_power_filter.begin();
#elif (main_power_voltage_filter == II_mode)
  main_power_filter.begin(analogRead(main_power_pin));
#endif

#if (pi_3v3_voltage_filter == FIR_mode)
  pi_3v3_filter.begin();
#elif (pi_3v3_voltage_filter == IIR_mode)
  pi_3v3_filter.begin(analogRead(pi_3V3_pin));
#endif

#if debug
  debug_serial.println("ADC setup complete");
#endif
  return true;
}
bool IO_CONFIG::pwm_setup()
{
  pwm_instance[0] = new RP2040_PWM(fan_pwm_pin, fan_pwm_frequency, fan_default_speed);
#if debug
  debug_serial.println("fan pwm setup complete");
#endif
  pwm_instance[1] = new RP2040_PWM(screen_backlight_pwm_pin, backlight_pwm_frequency, backlight_default_brightness);
#if debug
  debug_serial.println("backlight pwm setup complete");
#endif
  return true;
}

bool IO_CONFIG::iic_device_detect()
{
#if debug
  debug_serial.println("Detecting IIC devices on the bus...");
#endif
  for (int i = 0; i < 127; i++)
  {
    iic_device_address_list[i] = is_this_address_have_a_device(i);
  }
#if debug
  debug_serial.println("IIC device detection complete");
  debug_serial.println("Detected IIC devices at addresses:");
  for (int i = 1; i < 127; i++)
  {
    if (iic_device_address_list[i])
    {
      debug_serial.print("0x");
      debug_serial.println(i, HEX);
    }
  }
#endif
  return true;
}

bool IO_CONFIG::is_this_address_have_a_device(uint8_t address)
{
  Wire1.beginTransmission(address);
  bool device = Wire1.endTransmission();
#if debug
  /*debug_serial.print("Detecting IIC device at address 0x");
  debug_serial.println(address, HEX);
  if (device)
  {
    debug_serial.println("No device found at this address");
  }
  else
  {
    debug_serial.println("Device found at this address");
  }*/
#endif
  return !device;
}

bool IO_CONFIG::iic_read(uint8_t device_address, uint8_t length)
{
  if (length > iic_buffer_length)
  {

#if debug
    debug_serial.print("IIC read error: requested length ");
    debug_serial.print(length);
    debug_serial.print(" exceeds buffer length ");
    debug_serial.println(iic_buffer_length);
#endif
    return false;
  }
  Wire1.requestFrom(device_address, length);
  uint8_t index = 0;
  while (Wire1.available() && index < length)
  {
    iic_buffer[index++] = Wire1.read();
  }
#if debug
  debug_serial.print("IIC read from device 0x");
  debug_serial.print(device_address, HEX);
  debug_serial.print(" length ");
  debug_serial.println(length);
#endif
  return true;
}

bool IO_CONFIG::begin()
{
  iic_setup();
  pin_setup();
  adc_setup();
  pwm_setup();
  iic_device_detect();
#if debug
  debug_serial.println("IO_CONFIG begin complete");
#endif
  return true;
}

uint8_t IO_CONFIG::hardware_version_detect()
{
  if (iic_device_address_list[touch_panel_address_1] || iic_device_address_list[touch_panel_address_2])
  {
#if debug
    debug_serial.println("Detected old hardware version");
#endif
    return old_hardware_version;
  }
  else if (!iic_device_address_list[touch_panel_address_1] && !iic_device_address_list[touch_panel_address_2])
  {
#if debug
    debug_serial.println("Detected new hardware version");
#endif
    return new_hardware_version;
  }
  else
  {
#if debug
    debug_serial.println("Unable to determine hardware version");
#endif
    return 0; // 无法确定硬件版本
  }
}

bool IO_CONFIG::led1_set(bool led_status)
{
  digitalWrite(led1_pin, led_status ? HIGH : LOW);
  return true;
}

bool IO_CONFIG::led2_set(bool led_status)
{
  digitalWrite(led2_pin, led_status ? HIGH : LOW);
  return true;
}

bool IO_CONFIG::led1_flip()
{
  digitalWrite(led1_pin, !digitalRead(led1_pin));
  return true;
}

bool IO_CONFIG::led2_flip()
{
  digitalWrite(led2_pin, !digitalRead(led2_pin));
  return true;
}

bool IO_CONFIG::set_fan_speed(uint8_t speed)
{
  if (speed < fan_speed_minimum)
  {
    speed = fan_speed_minimum;
  }
  else if (speed > fan_speed_maximum)
  {
    speed = fan_speed_maximum;
  }
  pwm_instance[0]->setPWM(fan_pwm_pin, fan_pwm_frequency, speed);
  fan_speed = speed;
  system_status.fan_speed = speed;
  return true;
}
float IO_CONFIG::read_fan_speed()
{
  return fan_speed;
}
bool IO_CONFIG::set_backlight_brightness(float brightness)
{
  if (brightness < backlight_brightness_minimum)
  {
    brightness = backlight_brightness_minimum;
  }
  else if (brightness > backlight_brightness_maximum)
  {
    brightness = backlight_brightness_maximum;
  }
  pwm_instance[1]->setPWM(screen_backlight_pwm_pin, backlight_pwm_frequency, brightness);
  backlight_brightness = brightness;
  system_status.backlight_brightness = brightness;
  float backlight_brightness_ui_percentage = (backlight_brightness_maximum - brightness) * (100.0 / (backlight_brightness_maximum - backlight_brightness_minimum));
  system_status.backlight_bightness_percentage = backlight_brightness_ui_percentage;
  return true;
}
float IO_CONFIG::read_backlight_brightness()
{
  return backlight_brightness;
}
float IO_CONFIG::read_backlight_brightness_ui_percentage()
{
  return backlight_brightness_ui_percentage;
}

bool IO_CONFIG::enable_or_disable_backlight(bool enable_or_disable)
{
  digitalWrite(screen_enable_pin, enable_or_disable ? HIGH : LOW);
  return enable_or_disable;
}
bool IO_CONFIG::read_hdmi_status()
{
  system_status.hdmi_signal_detected = digitalRead(hdmi_signal_detect_pin) == HIGH ? true : false;
  return system_status.hdmi_signal_detected;
}
#if power_module == new_
bool IO_CONFIG::is_charging()
{
  if (digitalRead(charge_status_pin) == HIGH)
  {
    charge_status = charge_status + 2;
  }
  else
  {
    if (charge_status > 1)
    {
      charge_status = charge_status - 1;
    }
  }
  if (charge_status > 10)
  {
    charge_status = 10;
  }
  system_status.is_battery_charging = charge_status > 3 ? true : false;

  return system_status.is_battery_charging;
}

bool IO_CONFIG::is_charge_done()
{
  if (system_status.is_battery_charging)
  {
    if (digitalRead(charge_done_pin) == HIGH)
    {
      charge_done_status = charge_done_status + 2;
    }
    else
    {
      if (charge_done_status)
      {
        charge_done_status = charge_done_status - 1;
      }
    }
    if (charge_done_status > 10)
    {
      charge_done_status = 10;
    }
    system_status.is_battery_charge_done = charge_done_status > 3 ? true : false;
  }
  else
  {
    system_status.is_battery_charge_done = false;
  }
  return system_status.is_battery_charge_done;
}
#endif
#if power_module == old_
bool IO_CONFIG::is_charging()
{
  system_status.is_battery_charging = digitalRead(charge_status_pin) == HIGH ? true : false;
  return system_status.is_battery_charging;
}

bool IO_CONFIG::is_charge_done()
{
  if (system_status.is_battery_charging)
  {
    system_status.is_battery_charge_done = digitalRead(charge_done_pin) == HIGH ? true : false;
  }
  else
  {
    system_status.is_battery_charge_done = false;
  }
  return system_status.is_battery_charge_done;
}
#endif

uint16_t IO_CONFIG::battery_voltage_read_raw()
{
  uint16_t raw_value = analogRead(battery_adc_pin);
#if battery_voltage_filter == FIR_mode
  system_status.battery_voltage_raw = battery_filter.filter(raw_value);
  if (system_status.battery_voltage_raw_record_pointer > 31)
  {
    system_status.battery_voltage_raw_record_pointer = 0;
  }
  system_status.battery_voltage_raw_record[system_status.battery_voltage_raw_record_pointer] = system_status.battery_voltage_raw;
  system_status.battery_voltage_raw_record_pointer++;
#if debug
  debug_serial.print("Battery voltage ADC value: ");
  debug_serial.print(system_status.battery_voltage_raw);
  debug_serial.println(" raw");
#endif
  return system_status.battery_voltage_raw;
#elif battery_voltage_filter == IIR_mode
  system_status.battery_voltage_raw = battery_filter.filter(raw_value);
  if (system_status.battery_voltage_raw_record_pointer > 31)
  {
    system_status.battery_voltage_raw_record_pointer = 0;
  }
  system_status.battery_voltage_raw_record[system_status.battery_voltage_raw_record_pointer] = system_status.battery_voltage_raw;
  system_status.battery_voltage_raw_record_pointer++;
#if debug
  debug_serial.print("Battery voltage ADC value: ");
  debug_serial.print(system_status.battery_voltage_raw);
  debug_serial.println(" raw");
#endif
  return system_status.battery_voltage_raw;
#else
  return raw_value;
#endif
}

uint32_t IO_CONFIG::battery_voltage_read_mv()
{
  uint32_t raw_value = battery_voltage_read_raw();
  uint32_t mv = (raw_value * 3300 * 11) >> 12;
  system_status.battery_voltage_mv = mv;
#if debug
  debug_serial.print("Battery voltage ADC value: ");
  debug_serial.print(mv);
  debug_serial.println(" mV");
#endif
  return mv;
}

float IO_CONFIG::battery_voltage_read_v()
{
  uint32_t mv = battery_voltage_read_mv();
  float v = mv / 1000.0f;
  system_status.battery_voltage_v = v;
#if debug
  debug_serial.print("Battery voltage ADC value: ");
  debug_serial.print(v);
  debug_serial.println(" V");
#endif
  return v;
}

float IO_CONFIG::battery_percentage_read()
{
  battery_voltage_read_v();
  uint16_t voltage_mv = system_status.battery_voltage_mv;

  const int num_levels = sizeof(battery_voltage_levels) / sizeof(battery_voltage_levels[0]);

  // 边界检查
  if (voltage_mv >= battery_voltage_levels[num_levels - 1])
  {
    system_status.battery_percentage = 100;
#if debug
    debug_serial.print("Battery percentage: ");
    debug_serial.print(system_status.battery_percentage);
    debug_serial.println(" %");
#endif
    return 100.0f;
  }
  if (voltage_mv <= battery_voltage_levels[0])
  {
    system_status.battery_percentage = 0;
#if debug
    debug_serial.print("Battery percentage: ");
    debug_serial.print(system_status.battery_percentage);
    debug_serial.println(" %");
    Serial.println(system_status.battery_percentage);
#endif
    return 0.0f;
  }

  // 线性插值查找对应百分比
  float percentage = 0.0f;
  for (int i = 0; i < num_levels - 1; i++)
  {
    if (voltage_mv >= battery_voltage_levels[i] && voltage_mv <= battery_voltage_levels[i + 1])
    {
      // 电压在 battery_voltage_levels[i] 和 battery_voltage_levels[i+1] 之间
      float voltage_range = battery_voltage_levels[i + 1] - battery_voltage_levels[i];
      float percent_range = 5.0f; // 表格中每档差5%
      float offset = voltage_mv - battery_voltage_levels[i];
      percentage = (i * 5.0f) + (offset / voltage_range) * percent_range;
      system_status.battery_percentage = percentage;

      break;
    }
  }

#if debug
  debug_serial.print("Battery percentage: ");
  debug_serial.print(system_status.battery_percentage);
  debug_serial.println(" %");
#endif

  return percentage;
}

uint16_t IO_CONFIG::backlight_voltage_read_raw()
{
  uint16_t raw_value = analogRead(backlight_adc_pin);
#if (backlight_voltage_filter == FIR_mode)
  system_status.backlight_voltage_raw = backlight_filter.filter(raw_value);
  if (system_status.backlight_voltage_raw_record_pointer > 31)
  {
    system_status.backlight_voltage_raw_record_pointer = 0;
  }
  system_status.backlight_voltage_raw_record[system_status.backlight_voltage_raw_record_pointer] = system_status.backlight_voltage_raw;
  system_status.backlight_voltage_raw_record_pointer++;
  return system_status.backlight_voltage_raw;
#elif (backlight_voltage_filter == IIR_mode)
  system_status.backlight_voltage_raw = backlight_filter.filter(raw_value);
  if (system_status.backlight_voltage_raw_record_pointer > 31)
  {
    system_status.backlight_voltage_raw_record_pointer = 0;
  }
  system_status.backlight_voltage_raw_record[system_status.backlight_voltage_raw_record_pointer] = system_status.backlight_voltage_raw;
  system_status.backlight_voltage_raw_record_pointer++;
  return system_status.backlight_voltage_raw;
#else
  return raw_value;
#endif
}

uint32_t IO_CONFIG::backlight_voltage_read_mv()
{
  uint32_t raw_value = backlight_voltage_read_raw();
  uint32_t mv = (raw_value * 3300 * 11) >> 12;
  system_status.backlight_voltage_mv = mv;
#if debug
  debug_serial.print("Backlight voltage ADC value: ");
  debug_serial.print(mv);
  debug_serial.println(" mV");
#endif
  return mv;
}

float IO_CONFIG::backlight_voltage_read_v()
{
  uint32_t mv = backlight_voltage_read_mv();
  float v = mv / 1000.0f;
  system_status.backlight_voltage_v = v;
#if debug
  debug_serial.print("Backlight voltage ADC value: ");
  debug_serial.print(v);
  debug_serial.println(" V");
#endif
  return v;
}

uint16_t IO_CONFIG::main_power_voltage_read_raw()
{
  uint16_t raw_value = analogRead(main_power_pin);
#if (main_power_voltage_filter == FIR_mode)
  system_status.main_power_voltage_raw = main_power_filter.filter(raw_value);
  if (system_status.main_power_voltage_raw_record_pointer > 31)
  {
    system_status.main_power_voltage_raw_record_pointer = 0;
  }
  system_status.main_power_voltage_raw_record[system_status.main_power_voltage_raw_record_pointer] = system_status.main_power_voltage_raw;
  system_status.main_power_voltage_raw_record_pointer++;
  return system_status.main_power_voltage_raw;
#elif (main_power_voltage_filter == IIR_mode)
  system_status.main_power_voltage_raw = main_power_filter.filter(raw_value);
  if (system_status.main_power_voltage_raw_record_pointer > 31)
  {
    system_status.main_power_voltage_raw_record_pointer = 0;
  }
  system_status.main_power_voltage_raw_record[system_status.main_power_voltage_raw_record_pointer] = system_status.main_power_voltage_raw;
  system_status.main_power_voltage_raw_record_pointer++;
  return system_status.main_power_voltage_raw;
#else
  return raw_value;
#endif
}
uint32_t IO_CONFIG::main_power_voltage_read_mv()
{
  uint32_t raw_value = main_power_voltage_read_raw();
  uint32_t mv = (raw_value * 3300 * 2) >> 12;
  system_status.main_power_voltage_mv = mv;
#if debug
  debug_serial.print("Main power voltage ADC value: ");
  debug_serial.print(mv);
  debug_serial.println(" mV");
#endif
  return mv;
}
float IO_CONFIG::main_power_voltage_read_v()
{
  uint32_t mv = main_power_voltage_read_mv();
  float v = mv / 1000.0f;
  system_status.main_power_voltage_v = v;
#if debug
  debug_serial.print("Main power voltage ADC value: ");
  debug_serial.print(v);
  debug_serial.println(" V");
#endif
  return v;
}

uint16_t IO_CONFIG::pi_3v3_voltage_read_raw()
{
  uint16_t raw_value = analogRead(pi_3V3_pin);
#if (pi_3v3_voltage_filter == FIR_mode)
  system_status.pi_3v3_voltage_raw = pi_3v3_filter.filter(raw_value);
  if (system_status.pi_3v3_voltage_raw_record_pointer > 31)
  {
    system_status.pi_3v3_voltage_raw_record_pointer = 0;
  }
  system_status.pi_3v3_voltage_raw_record[system_status.pi_3v3_voltage_raw_record_pointer] = system_status.pi_3v3_voltage_raw;
  system_status.pi_3v3_voltage_raw_record_pointer++;
  return system_status.pi_3v3_voltage_raw;
#elif (pi_3v3_voltage_filter == IIR_mode)
  system_status.pi_3v3_voltage_raw = pi_3v3_filter.filter(raw_value);
  if (system_status.pi_3v3_voltage_raw_record_pointer > 31)
  {
    system_status.pi_3v3_voltage_raw_record_pointer = 0;
  }
  system_status.pi_3v3_voltage_raw_record[system_status.pi_3v3_voltage_raw_record_pointer] = system_status.pi_3v3_voltage_raw;
  system_status.pi_3v3_voltage_raw_record_pointer++;
  return system_status.pi_3v3_voltage_raw;
#else
  return raw_value;
#endif
  return raw_value;
}
uint32_t IO_CONFIG::pi_3v3_voltage_read_mv()
{
  uint32_t raw_value = pi_3v3_voltage_read_raw();
  uint32_t mv = (raw_value * 3300 * 2) >> 12;
  system_status.pi_3v3_voltage_mv = mv;
#if debug
  debug_serial.print("Pi 3.3V voltage ADC value: ");
  debug_serial.print(mv);
  debug_serial.println(" mV");
#endif
  return mv;
}
float IO_CONFIG::pi_3v3_voltage_read_v()
{
  uint32_t mv = pi_3v3_voltage_read_mv();
  float v = mv / 1000.0f;
  system_status.pi_3v3_voltage_v = v;
#if debug
  debug_serial.print("Pi 3.3V voltage ADC value: ");
  debug_serial.print(v);
  debug_serial.println(" V");
#endif
  return v;
}

bool IO_CONFIG::iic_keyboard_read()
{
  if (iic_buffer[new_keyboard_with_new_program_iic_address])
  {
    return iic_read(new_keyboard_with_new_program_iic_address, keyboard_iic_length);
  }
  else if (iic_buffer[new_keyboard_iic_address])
  {
    return iic_read(new_keyboard_iic_address, keyboard_iic_length);
  }
  else if (iic_buffer[old_keyboard_iic_address])
  {
    return iic_read(old_keyboard_iic_address, keyboard_iic_length);
  }
  else
  {
    return false;
  }
}

bool IO_CONFIG::routine()
{
#if debug
  debug_serial.println("IO_CONFIG routine start");
#endif

  if (system_status.fan_speed != fan_speed)
  {
    fan_speed = system_status.fan_speed;
    set_fan_speed(system_status.fan_speed);
  }
  if (system_status.backlight_brightness != backlight_brightness)
  {
    backlight_brightness = system_status.backlight_brightness;
    set_backlight_brightness(system_status.backlight_brightness);
  }
  enable_or_disable_backlight(read_hdmi_status());

  backlight_voltage_read_v();
  main_power_voltage_read_v();
  pi_3v3_voltage_read_v();
  battery_voltage_read_v();
  battery_percentage_read();

  is_charging();
  is_charge_done();

#if debug
  debug_serial.println("IO_CONFIG routine end");
#endif
  return true;
}
