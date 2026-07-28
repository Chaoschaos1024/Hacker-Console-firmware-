/*
   @Author: 无序熵增
   @Date: 2026-03-05 13:33:37
 * @LastEditors: 无序熵增
 * @LastEditTime: 2026-04-29 19:06:57
   @Description:

   Copyright (c) 2026 by 无序熵增, All Rights Reserved.
*/
#ifndef IIC_KEYBOARD_H
#define IIC_KEYBOARD_H

//#include <USB.h>
#include <Keyboard.h>
#include <Mouse.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include "config.h"
#include "pin_definitions.h"
#include "system_status.h"

typedef struct
{
    uint8_t new_keyboard_or_old_keyboard = old_keyboard;
    bool mouse_or_keyboard = false; // 0键盘1鼠标
    uint8_t iic_byte = 0;
    uint8_t iic_byte_mask = 0b00000000;
    bool is_shift = false;
    bool is_capslock = false;
    char key_value = 0;
    char key_value_shift = 0;
    char key_value_capslock = 0;
    char key_debug[16] = {0};
    uint8_t set_function = 0;
    bool last_time_status = false; // 上次状态
    bool press_or_release = false; // 0按下1松开
} Key;

class IIC_Keyboard
{
public:
    bool begin();
    bool usb_set();
    bool is_usb_ready();
    uint8_t find_keyboard_type();
    uint8_t routine();
    bool new_keyboard_new_program_flag = false;
    bool new_keyboard_old_program_flag = false;
    bool old_keyboard_flag = false;
    uint8_t keyboard_type = 0;

    bool capsLock_status = false;
    bool shift_status = false;

    const float mouse_sensitivity = 0.12f;

    const int radius = 91;
    const int x_center = 0;
    const int y_center = 0;
    uint8_t mouse_direction[16] =
        {0b10000000, 0b11000000, 0b01000000, 0b01100000, 0b00100000, 0b00110000, 0b00010000, 0b00011000, 0b00001000, 0b00001100, 0b00000100, 0b00000110, 0b00000010, 0b00000011, 0b00000001, 0b10000001};
    const int new_keyboard_angle[16] = {
        int(90),
        int(90 - 22.5),
        int(90 - 45),
        int(90 - 67.5),
        int(0),
        int(0 - 22.5),
        int(0 - 45),
        int(0 - 67.5),
        int(-90),
        int(-90 - 22.5),
        int(-90 - 45),
        int(-90 - 67.5),
        int(-180),
        int(-180 - 22.5),
        int(-180 - 45),
        int(-180 - 67.5)};
    const int new_keyboard_angle_sin_y[16] = {
        y_center - 128, // sin(90) * 91 + 128 = 128
        y_center - 113, // sin(67.5) * 91 + 128 = 113.98
        y_center - 90,  // sin(45) * 91 + 128 = 90.99
        y_center - 64,  // sin(22.5) * 91 + 128 = 63.64
        y_center - 0,   // sin(0) * 91 + 128 = 0
        y_center + 64,  // sin(-22.5) * 91 + 128 = -64.36
        y_center + 90,  // sin(-45) * 91 + 128 = -89.99
        y_center + 113, // sin(-67.5) * 91 + 128 = -113.98
        y_center + 128, // sin(-90) * 91 + 128 = -128
        y_center + 113, // sin(-112.5) * 91 + 128 = -113.98
        y_center + 90,  // sin(-135) * 91 + 128 = -89.99
        y_center - 0,   // sin(-180) * 91 + 128 = 0
        y_center - 64,  // sin(-157.5) * 91 + 128 = 64
        y_center - 90,  // sin(-135) * 91 + 128 = 89.99
        y_center - 113, // sin(-112.5) * 91 + 128 = 113.98
        y_center - 128  // sin(-90) * 91 + 128 = 128
    };
    const int new_keyboard_angle_cos_x[16] = {
        x_center + 0,   // cos(90) * 91 + 128 = 0
        x_center + 45,  // cos(67.5) * 91 + 128 = 45.25
        x_center + 90,  // cos(45) * 91 + 128 = 89.99
        x_center + 114, // cos(22.5) * 91 + 128 = 113.98
        x_center + 128, // cos(0) * 91 + 128 = 128
        x_center + 114, // cos(-22.5) * 91 + 128 = 113.98
        x_center + 90,  // cos(-45) * 91 + 128 = 89.99
        x_center + 45,  // cos(-67.5) * 91 + 128 = 45.25
        x_center + 0,   // cos(-90) * 91 + 128 = 0
        x_center - 45,  // cos(-112.5) * 91 + 128 = -45.25
        x_center - 90,  // cos(-135) * 91 + 128 = -89.99
        x_center - 128, // cos(-180) * 91 + 128 = -128
        x_center - 114, // cos(-157.5) * 91 + 128 = -113.98
        x_center - 90,  // cos(-135) * 91 + 128 = -89.99
        x_center - 45,  // cos(-112.5) * 91 + 128 = -45.25
        x_center + 0    // cos(-90) * 91 + 128 = 0
    };

private:
    bool get_buffer(uint8_t address);
    uint8_t old_keyboard_routine();
    uint8_t new_keyboard_routine();
    bool read_serial();

    uint8_t iic_buffer[keyboard_iic_length] = {0};
    uint8_t iic_buffer_new_keyboard_last_time[keyboard_iic_length] = {0};
    uint8_t iic_buffer_new_keyboard_with_new_program_last_time[keyboard_iic_length] = {0};
    uint8_t iic_buffer_old_keyboard_last_time[keyboard_iic_length] = {0};
};

#endif // IIC_KEYBOARD_H
