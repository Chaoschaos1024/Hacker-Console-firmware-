/*
 * @Author: 无序熵增
 * @Date: 2026-03-05 13:37:41
 * @LastEditors: 无序熵增
 * @LastEditTime: 2026-05-02 20:10:47
 * @Description:
 *
 * Copyright (c) 2026 by 无序熵增, All Rights Reserved.
 */
#ifndef LED_STATUS_H
#define LED_STATUS_H

#include <Adafruit_NeoPixel.h>
#include "config.h"
#include "pin_definitions.h"
#include "system_status.h"

#define key_color_count_max 10

class LED_STATUS
{
public:
    bool begin();
    bool set_color(uint8_t led_index, uint8_t r, uint8_t g, uint8_t b);
    bool set_fuction(uint8_t led_index, uint8_t function);
    bool calculate();
    bool flash();
    bool routine();

private:
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
    uint8_t led_function[ws2812_number] = {ws2812_1_default_function, ws2812_2_default_function, ws2812_3_default_function, ws2812_4_default_function};
    uint8_t led_color[ws2812_number][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    const uint8_t led_brightness_max = 10;

    bool fault_alarm_update(uint8_t led_index);
    uint8_t fault_alarm_led_index = 0;
    uint8_t last_error = 0;

    bool keyboard_signal_update(uint8_t led_index);
    uint8_t keyboard_signal_index = 0;
    uint8_t last_key_index = 1;
    uint8_t key_color_count = 1;
    uint8_t key_color_map[key_color_count_max] = {0b0001, 0b0010, 0b0100, 0b0011, 0b0101, 0b0110}; // 蓝、绿、红、青、品红、黄、白

    bool touch_signal_update(uint8_t led_index);
    uint8_t touch_signal_led_index = 0;
    int last_touch_x = 0;
    int last_touch_y = 0;

    bool capslock_status_update(uint8_t led_index);
    uint8_t capslock_status_led_index = 0;
    bool capslock_blink_status = false;

    bool breath(uint8_t led_index, uint8_t color);
    enum ws2812_breath_color
    {
        // 单色
        breath_blue = 0b0001,  // 蓝色
        breath_green = 0b0010, // 绿色
        breath_red = 0b0100,   // 红色

        // 双色混合
        breath_cyan = 0b0011,    // 青色 = 蓝+绿
        breath_magenta = 0b0101, // 品红 = 蓝+红
        breath_yellow = 0b0110,  // 黄色 = 红+绿

        // 三色混合
        breath_white = 0b0111, // 白色 = 红+绿+蓝

        // 也可以定义无颜色
        breath_off = 0b0000 // 关闭
    };
    uint8_t breath_status = 0;
    uint8_t breath_counter = 0;
    const uint8_t breath_speed = 10;
    bool breath_direction = true;

    bool fan_speed_update(uint8_t led_index);
    uint8_t fan_speed_led_index = 0;
    float last_fan_speed = 0;
    const float fan_speed_max = 100;

    bool backlight_brightness_update(uint8_t led_index);
    uint8_t backlight_brightness_led_index = 0;
    float last_backlight_brightness = 0;
    const float backlight_brightness_max = 100;

    bool random_breath_update(uint8_t led_index);

    bool battery_status_update(uint8_t led_index);
    uint8_t battery_status_led_index = 0;
    uint8_t last_battery_percentage = 0;

    bool pi_power_status_update(uint8_t led_index);
    uint8_t pi_power_status_led_index = 0;
    uint16_t last_pi_power_voltage_mv = 0;

    bool backlight_adc_status_update(uint8_t led_index);
    uint8_t backlight_adc_status_led_index = 0;
    uint16_t last_backlight_voltage_mv = 0;

    bool rpi_cpu_status_update(uint8_t led_index);

    bool rpi_temp_status_update(uint8_t led_index);

    bool rpi_ram_status_update(uint8_t led_index);

    bool rpi_disk_status_update(uint8_t led_index);

    bool rpi_network_status_update(uint8_t led_index);

    bool empty(uint8_t led_index);
};

#endif