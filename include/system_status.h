/*
 * @Author: 无序熵增
 * @Date: 2026-05-02 22:58:16
 * @LastEditors: 无序熵增
 * @LastEditTime: 2026-05-11 17:33:20
 * @Description:
 *
 * Copyright (c) 2026 by 无序熵增, All Rights Reserved.
 */
#ifndef SYSTEM_STATUS_H
#define SYSTEM_STATUS_H

#include <SoftwareSerial.h>

#include "config.h"

typedef struct
{
    uint8_t hardware_version;
    uint8_t software_version_major;
    uint8_t software_version_minor;
    float software_version_float;
    uint32_t loop_count;

    uint8_t fan_speed;
    float backlight_brightness;
    float backlight_bightness_percentage;

    uint8_t ws2812_1_function;
    uint8_t ws2812_2_function;
    uint8_t ws2812_3_function;
    uint8_t ws2812_4_function;
    uint8_t ws2812_max_brightness;

    uint16_t battery_voltage_raw;
    uint16_t battery_voltage_raw_record[32];
    uint8_t battery_voltage_raw_record_pointer;
    uint16_t battery_voltage_mv;
    float battery_voltage_v;
    uint8_t battery_percentage;
    uint16_t battery_maximum_voltage_mv;
    uint16_t battery_minimum_voltage_mv;
    bool is_battery_charging;
    bool is_battery_charge_done;

    uint16_t backlight_voltage_raw;
    uint16_t backlight_voltage_raw_record[32];
    uint8_t backlight_voltage_raw_record_pointer;
    uint16_t backlight_voltage_mv;
    float backlight_voltage_v;
    uint8_t backlight_brightness_percentage;

    uint16_t main_power_voltage_raw;
    uint16_t main_power_voltage_raw_record[32];
    uint8_t main_power_voltage_raw_record_pointer;
    uint16_t main_power_voltage_mv;
    float main_power_voltage_v;

    uint16_t pi_3v3_voltage_raw;
    uint16_t pi_3v3_voltage_raw_record[32];
    uint8_t pi_3v3_voltage_raw_record_pointer;
    uint16_t pi_3v3_voltage_mv;
    float pi_3v3_voltage_v;

    bool hdmi_signal_detected;

    bool touch_status;
    int touch_x;
    int touch_y;

    uint8_t keyboard_slot_1;
    uint8_t keyboard_slot_2;
    uint8_t keyboard_slot_3;
    bool is_usb_ready_4_communication;
    bool capslock_status;
    bool shift_status;
    uint16_t last_key_value;
    uint8_t last_key_index;
    uint8_t key_buffer[keyboard_iic_length];
    uint8_t mouse_x;
    uint8_t mouse_y;

    uint8_t ssd1306_status;
    uint8_t ssd1306_mode;
    uint8_t ssd1306_heart_beat_frame;
    uint8_t ssd1306_set_instruction;
    uint8_t ssd1306_set_instruction_old;

    uint8_t rpi_cpu;
    uint8_t rpi_temp;
    uint8_t rpi_ram;
    uint8_t rpi_disk;
    uint8_t rpi_net;
    uint8_t rpi_distribution;
    bool rpi_communicated;

    uint8_t error_code[100];

    bool is_this_struct_set_up_correctly;

    bool need_to_record_to_eeprom;
    uint32_t magic_number;

} System_Status;

extern System_Status system_status;

bool system_status_setup();
bool ssd1306_status_empty();
bool rpi_status_empty();
bool system_status_report();

#endif