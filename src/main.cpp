/*
 * @Author: 无序熵增
 * @Date: 2025-12-29 09:30:49
 * @LastEditors: 无序熵增
 * @LastEditTime: 2026-05-02 23:00:51
 * @Description:
 *
 * Copyright (c) 2026 by 无序熵增, All Rights Reserved.
 */
/*
设计要求，以前的全部设计要求都实现，
副屏分页，实现日常模式和设置模式的区分
键盘程序重新设计，带有int引脚的程序
尽量给键盘设置为能够ota的模式，然后后面更新程序都放在主设备上
*/

#include "config.h"
#include "io.h"
#include "adc_filters.h"
#include "ssd1306.h"
#include "iic_keyboard.h"
#include "flash.h"
#include "led_status.h"
#include "pin_definitions.h"
#include "system_status.h"

#if debug
#include "iic_ec11.h"

EC11 ec11;
#endif

IO_CONFIG io;
Flash flash;
LED_STATUS led_status;
IIC_Keyboard iic_keyboard;
SECONDARY_DISPLAY ssd1306;

int i = 0;

void setup()
{
#if debug
  io.serial_setup();
  debug_serial.println("    ");
  debug_serial.println("    ");
  debug_serial.println("    ");
  debug_serial.println("-------------------------   setup start  -----------------------------");
  debug_serial.println("IO_CONFIG begin");
#endif
  system_status_setup();
  flash.begin();
  flash.load(system_status);

  io.begin();
  system_status.hardware_version = io.hardware_version_detect();

  io.set_fan_speed(system_status.fan_speed);
  io.set_backlight_brightness(system_status.backlight_brightness);

  led_status.begin();
  led_status.set_fuction(0, system_status.ws2812_1_function);
  led_status.set_fuction(1, system_status.ws2812_2_function);
  led_status.set_fuction(2, system_status.ws2812_3_function);
  led_status.set_fuction(3, system_status.ws2812_4_function);
  led_status.routine();

  ssd1306.begin();

  iic_keyboard.begin();

#if debug
  ec11.begin(&Wire1);
#endif

  flash.save(system_status);

  io.led1_set(HIGH);
  io.led2_flip();
  system_status.loop_count = 0;
  ssd1306_status_empty();
  rpi_status_empty();

  // system_status.ssd1306_mode =12;

#if debug
  system_status_report();
  delay(5);
#endif
}

void loop()
{
#if debug
  debug_serial.println("-------------------------   Loop start  -----------------------------");
  debug_serial.print("System status: ");
#endif
  system_status.loop_count++;
#if debug
  debug_serial.println(system_status.loop_count);
  system_status_report();
#endif
  if ((system_status.loop_count & 1023) == 0)
  {
    flash.save(system_status);
  }
  iic_keyboard.routine();
  io.routine();
  led_status.routine();
  ssd1306.update();

  io.led2_flip();
#if debug
  delay(0);
#endif
}

#if debug
bool report_ec11_status()
{
  if (ec11.update())
  {
    debug_serial.println("EC11 update");
    debug_serial.print("EC11 encoder 0 count: ");
    debug_serial.print(ec11.getNumber(0));
    debug_serial.print(" key: ");
    debug_serial.println(ec11.getKey(0));
    debug_serial.print("EC11 encoder 1 count: ");
    debug_serial.print(ec11.getNumber(1));
    debug_serial.print(" key: ");
    debug_serial.println(ec11.getKey(1));
    debug_serial.print("EC11 encoder 2 count: ");
    debug_serial.print(ec11.getNumber(2));
    debug_serial.print(" key: ");
    debug_serial.println(ec11.getKey(2));
    debug_serial.print("EC11 encoder 3 count: ");
    debug_serial.print(ec11.getNumber(3));
    debug_serial.print(" key: ");
    debug_serial.println(ec11.getKey(3));
    debug_serial.print("EC11 encoder 4 count: ");
    debug_serial.print(ec11.getNumber(4));
    debug_serial.print(" key: ");
    debug_serial.println(ec11.getKey(4));
    debug_serial.print("EC11 encoder 5 count: ");
    debug_serial.print(ec11.getNumber(5));
    debug_serial.print(" key: ");
    debug_serial.println(ec11.getKey(5));
    debug_serial.print("EC11 encoder 6 count: ");
    debug_serial.print(ec11.getNumber(6));
    debug_serial.print(" key: ");
    debug_serial.println(ec11.getKey(6));
    debug_serial.print("EC11 encoder 7 count: ");
    debug_serial.print(ec11.getNumber(7));
    debug_serial.print(" key: ");
    debug_serial.println(ec11.getKey(7));
    debug_serial.println("ec11 report finished");
    return true;
  }
  else
  {
    debug_serial.println("EC11 update failed");
    return false;
  }
  return false;
}
#endif