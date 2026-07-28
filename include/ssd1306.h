/*
 * @Author: 无序熵增
 * @Date: 2026-03-04 21:20:17
 * @LastEditors: 无序熵增
 * @LastEditTime: 2026-03-06 11:00:14
 * @Description:
 *
 * Copyright (c) 2026 by 无序熵增, All Rights Reserved.
 */
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/Picopixel.h>     // 像素风格，约 3x5 像素（极小）
#include <Fonts/Org_01.h>        // 点阵风格，约 4x6 像素
#include <Fonts/Tiny3x3a2pt7b.h> // 极小字体，约 3x3 像素
#include <Fonts/TomThumb.h>      // 拇指字体，约 5x7 像素

// === FreeMono 系列（等宽字体） ===
#include <Fonts/FreeMono9pt7b.h>  // 9pt 常规
#include <Fonts/FreeMono12pt7b.h> // 12pt 常规
#include <Fonts/FreeMono18pt7b.h> // 18pt 常规
#include <Fonts/FreeMono24pt7b.h> // 24pt 常规

#include <Fonts/FreeMonoBold9pt7b.h>  // 9pt 粗体
#include <Fonts/FreeMonoBold12pt7b.h> // 12pt 粗体
#include <Fonts/FreeMonoBold18pt7b.h> // 18pt 粗体
#include <Fonts/FreeMonoBold24pt7b.h> // 24pt 粗体

#include <Fonts/FreeMonoOblique9pt7b.h>  // 9pt 斜体
#include <Fonts/FreeMonoOblique12pt7b.h> // 12pt 斜体
#include <Fonts/FreeMonoOblique18pt7b.h> // 18pt 斜体
#include <Fonts/FreeMonoOblique24pt7b.h> // 24pt 斜体

#include <Fonts/FreeMonoBoldOblique9pt7b.h>  // 9pt 粗斜体
#include <Fonts/FreeMonoBoldOblique12pt7b.h> // 12pt 粗斜体
#include <Fonts/FreeMonoBoldOblique18pt7b.h> // 18pt 粗斜体
#include <Fonts/FreeMonoBoldOblique24pt7b.h> // 24pt 粗斜体

// === FreeSans 系列（无衬线字体） ===
#include <Fonts/FreeSans9pt7b.h>  // 9pt 常规
#include <Fonts/FreeSans12pt7b.h> // 12pt 常规
#include <Fonts/FreeSans18pt7b.h> // 18pt 常规
#include <Fonts/FreeSans24pt7b.h> // 24pt 常规

#include <Fonts/FreeSansBold9pt7b.h>  // 9pt 粗体
#include <Fonts/FreeSansBold12pt7b.h> // 12pt 粗体
#include <Fonts/FreeSansBold18pt7b.h> // 18pt 粗体
#include <Fonts/FreeSansBold24pt7b.h> // 24pt 粗体

#include <Fonts/FreeSansOblique9pt7b.h>  // 9pt 斜体
#include <Fonts/FreeSansOblique12pt7b.h> // 12pt 斜体
#include <Fonts/FreeSansOblique18pt7b.h> // 18pt 斜体
#include <Fonts/FreeSansOblique24pt7b.h> // 24pt 斜体

#include <Fonts/FreeSansBoldOblique9pt7b.h>  // 9pt 粗斜体
#include <Fonts/FreeSansBoldOblique12pt7b.h> // 12pt 粗斜体
#include <Fonts/FreeSansBoldOblique18pt7b.h> // 18pt 粗斜体
#include <Fonts/FreeSansBoldOblique24pt7b.h> // 24pt 粗斜体

// === FreeSerif 系列（衬线字体） ===
#include <Fonts/FreeSerif9pt7b.h>  // 9pt 常规
#include <Fonts/FreeSerif12pt7b.h> // 12pt 常规
#include <Fonts/FreeSerif18pt7b.h> // 18pt 常规
#include <Fonts/FreeSerif24pt7b.h> // 24pt 常规

#include <Fonts/FreeSerifBold9pt7b.h>  // 9pt 粗体
#include <Fonts/FreeSerifBold12pt7b.h> // 12pt 粗体
#include <Fonts/FreeSerifBold18pt7b.h> // 18pt 粗体
#include <Fonts/FreeSerifBold24pt7b.h> // 24pt 粗体

#include <Fonts/FreeSerifItalic9pt7b.h>  // 9pt 斜体
#include <Fonts/FreeSerifItalic12pt7b.h> // 12pt 斜体
#include <Fonts/FreeSerifItalic18pt7b.h> // 18pt 斜体
#include <Fonts/FreeSerifItalic24pt7b.h> // 24pt 斜体

#include <Fonts/FreeSerifBoldItalic9pt7b.h>  // 9pt 粗斜体
#include <Fonts/FreeSerifBoldItalic12pt7b.h> // 12pt 粗斜体
#include <Fonts/FreeSerifBoldItalic18pt7b.h> // 18pt 粗斜体
#include <Fonts/FreeSerifBoldItalic24pt7b.h> // 24pt 粗斜体

#include "config.h"
#include "system_status.h"
#include "ssd1306_image.h"

#define front1 Org_01
#define front2 FreeSerif9pt7b
#define front3 Tiny3x3a2pt7b
#define front4 FreeSans9pt7b

class SECONDARY_DISPLAY
{
public:
    bool begin();
    bool update();
    bool routine_mode();
    bool set_mode();

    int set_fan_speed_mode();
    int set_display_brightness_mode();
    int set_ws2812_1_function_mode();
    int set_ws2812_2_function_mode();
    int set_ws2812_3_function_mode();
    int set_ws2812_4_function_mode();
    int show_battery_information();
    int show_power_information();
    int show_version_information();
    int show_keyboard_information();
    int show_hdmi_active_status();
    int show_rpi_status();
    int reboot_chip();
    int reboot_to_bootloader();
    int show_chip_information();

    bool ssd1306_exist = false;

private:
    uint8_t y = 0;
    bool set_mode_example();
    bool show_small_text(int num);
    bool show_small_text(float num);
    bool show_small_text(const String &text);
    bool show_small_text(uint16_t num, const String &text);
    bool show_small_text(float num, const String &text);
    bool show_big_text(int num);
    bool show_big_text(float num);
    bool show_big_text(const String &text);
    bool show_big_text(uint16_t num, const String &text);
    bool show_big_text(float num, const String &text);
    bool show_defauit_text(int num);
    bool show_defauit_text(float num);
    bool show_defauit_text(const String &text);
    bool show_defauit_text(uint16_t num, const String &text);
    bool show_defauit_text(float num, const String &text);
    bool scope_32_32(uint16_t record[32], uint8_t pointer);
    bool progress_bar_big(uint8_t percent);
    bool progress_bar_small(uint8_t percent);
    bool line(uint8_t width);
    bool square(uint8_t width);

    bool routine_or_set_mode = iic_display_routine_mode;

    enum ws2812_function
    {
        no_function = 0,
        fault_alarm = 1,
        keyboard_signal = 2,
        touch_signal = 3,
        capslock_status = 4,
        red_breath = 5,
        green_breath = 6,
        blue_breath = 7,
        cyan_breath = 8,
        magenta_breath = 9,
        yellow_breath = 10,
        white_breath = 11,
        fan_speed = 12,
        backlight_brightness = 13,
        random_breath = 14,
        battery_status = 15,
        pi_power_status = 16,
        backlight_adc_startus = 17,
        rpi_cpu_status = 18,
        rpi_temp_status = 19,
        rpi_ram_status = 20,
        rpi_disk_status = 21,
        rpi_net_status = 22,
    };
    bool show_ws2812_function(uint8_t led_func);
};
