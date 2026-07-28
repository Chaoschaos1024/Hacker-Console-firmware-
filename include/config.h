/*
   @Author: 无序熵增
   @Date: 2026-03-01 10:51:58
 * @LastEditors: 无序熵增
 * @LastEditTime: 2026-05-02 22:57:43
   @Description:

   Copyright (c) 2026 by 无序熵增, All Rights Reserved.
*/
#ifndef CONFIG_H
#define CONFIG_H

#include <SoftwareSerial.h>

#define software_version 6.00
#define softwareversion_major 6
#define softeware_version_minor 0
#define old_hardware_version 1
#define new_hardware_version 2

#define debug 0
#define debug_delay 100
#define debug_delay_short 10
#define debug_delay_long 1000
#define debug_delay_loop 1000
#define debug_serial Serial1

#define iic_buffer_length 256

#define keyboard_enable 1
#define keyboard_iic_length 15
#define old_keyboard_iic_address 0x30
#define old_keyboard_set_mode_byte 2
#define old_keyboard_set_mode_value 66
#define old_keyboard_crc 0x11
#define new_keyboard_iic_address 0x31
#define new_keyboard_set_mode_byte 1
#define new_keyboard_set_mode_value 66
#define new_keyboard_crc 0x12
#define new_keyboard_with_new_program_iic_address 0x32
#define new_keyboard_with_new_program_crc 0x13
#define no_keyboard 0
#define old_keyboard 0b00000001
#define new_keyboard_old_program 0b00000010
#define new_keyboard_new_program 0b00000100
#define new_keyboard 0b00000110
#define old_keyboard_key_count 7 * 11
#define old_keyboard_byte_mask_count 7
#define old_keyboard_byte_count 11
#define new_keyboard_key_count 7 * 12
#define new_keyboard_byte_mask_count 8
#define new_keyboard_byte_count 10

#define set_mode_function_right 1
#define set_mode_function_left 2
#define set_mode_function_up 3
#define set_mode_function_down 4
#define set_mode_function_ok 5
#define set_mode_function_back 6

#define press_ true
#define release_ false

#define ws2812_enable 1
#define ws2812_number 4
#define ws2812_1_default_function 18
#define ws2812_2_default_function 19
#define ws2812_3_default_function 20
#define ws2812_4_default_function 21
#define ws2812_function_max 23
#define ws2812_brightness_maximum 10

#define fan_enable 1
#define fan_default_speed 50
#define fan_pwm_frequency 10000
#define fan_speed_minimum 0
#define fan_speed_maximum 100

#define backlight_enable
#define backlight_default_brightness 10
#define backlight_pwm_frequency 10000
#define backlight_brightness_minimum 0
#define backlight_brightness_maximum 15
#define backlight_brightness_step 5.0 * (backlight_brightness_maximum - backlight_brightness_minimum) / 100.0

#define iic_display_enable 1
#define iic_display_width 128
#define iic_display_height 32
#define iic_display_reset -1
#define iic_display_address 0x3c
#define iic_display_routine_mode 0
#define iic_display_set_mode 1
#define iic_display_routine_mode_flag 0x00
#define iic_display_set_fan_speed_value 0x01
#define iic_display_set_backlight_brightness_value 0x02
#define iic_display_set_ws2812_1_function_value 0x03
#define iic_display_set_ws2812_2_function_value 0x04
#define iic_display_set_ws2812_3_function_value 0x05
#define iic_display_set_ws2812_4_function_value 0x06
#define iic_display_battery_information_value 0x07
#define iic_display_power_information_value 0x08
#define iic_display_version_information_value 0x09
#define iic_display_keyboard_information_value 0x0A
#define iic_display_hdmi_status 0x0B
#define iic_display_raspberry_status 0x0C
#define iic_display_reboot_status 0x0D
#define iic_display_reboot_to_bootloader 0x0E
#define iic_display_chip_information 0x0F
#define iic_display_set_page_max 0x10

#define touch_panel_address_1 0x14
#define touch_panel_address_2 0x5D

#define adc_enable 1
#define adc_accuracy 12
#define no_filter_mode 0
#define IIR_mode 1
#define FIR_mode 2
#define battery_voltage_filter IIR_mode
#define backlight_voltage_filter IIR_mode
#define main_power_voltage_filter IIR_mode
#define main_power_voltage_minimum_mv 4800
#define pi_3v3_voltage_filter IIR_mode

#define power_module 1
#define new_ 1
#define old_ 0

#define hdmi_active_status 1

#define battery_charging_status 1
#define battery_charge_done_status 1

#define ubuntu_distribution 0x01
#define debian_distribution 0x02
#define rhel_distribution 0x03
#define fedora_distribution 0x04
#define arch_distribution 0x05
#define linuxmint_distribution 0x06
#define opensuse_distribution 0x07
#define centos_distribution 0x08
#define kali_distribution 0x09
#define raspbian_distribution 0x0A

#define eeprom_enable 1
#define eeprom_size 4096
#define eeprom_setup_flag_address 0
#define eeprom_setup_flag_value 0xA5
#define eeprom_address_offset 10
#define eeprom_fan_speed_address eeprom_setup_flag_address + eeprom_address_offset * 1
#define eeprom_backlight_brightness_address eeprom_setup_flag_address + eeprom_address_offset * 2
#define eeprom_ws2812_1_function_address eeprom_setup_flag_address + eeprom_address_offset * 3
#define eeprom_ws2812_2_function_address eeprom_setup_flag_address + eeprom_address_offset * 4
#define eeprom_ws2812_3_function_address eeprom_setup_flag_address + eeprom_address_offset * 5
#define eeprom_ws2812_4_function_address eeprom_setup_flag_address + eeprom_address_offset * 6
#define eeprom_battery_voltage_maximum_address eeprom_setup_flag_address + eeprom_address_offset * 7
#define eeprom_battery_voltage_minimum_address eeprom_setup_flag_address + eeprom_address_offset * 8
#define eeprom_battery_charging_voltage_maxium_address eeprom_setup_flag_address + eeprom_address_offset * 9
#define eeprom_device_hardware_version_address eeprom_setup_flag_address + eeprom_address_offset * 10
#define eeprom_device_software_version_address eeprom_setup_flag_address + eeprom_address_offset * 11
#define eeprom_keyboard_type_address eeprom_setup_flag_address + eeprom_address_offset * 12

#define error_code_no_error 0
#define error_code_unknown_hardware_version 1
#define error_code_no_ssd1306_detected 2
#define error_code_no_keyboard_detected 3
#define error_code_battery_voltage_too_high 4
#define error_code_battery_voltage_too_low 5
#define error_code_main_power_voltage_too_high 6
#define error_code_main_power_voltage_too_low 7
#define error_code_no_raspberry_pi 8
#define error_code_no_hdmi_signal_detected 9
#define error_code_touch_panel_error 10
#define error_code_eeprom_error 11
#endif
