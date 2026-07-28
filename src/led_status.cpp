/*
 * @Author: 无序熵增
 * @Date: 2026-03-05 13:37:41
 * @LastEditors: 无序熵增
 * @LastEditTime: 2026-05-02 19:54:07
 * @Description:
 *
 * Copyright (c) 2026 by 无序熵增, All Rights Reserved.
 */

#include "led_status.h"
Adafruit_NeoPixel status_leds = Adafruit_NeoPixel(ws2812_number, ws2812_pin, NEO_GRB + NEO_KHZ800);

bool LED_STATUS::begin()
{
    status_leds.begin();

    return true;
}
bool LED_STATUS::set_color(uint8_t led_index, uint8_t r, uint8_t g, uint8_t b)
{
    if (led_index >= ws2812_number)
    {
        return false;
    }
    if (r > led_brightness_max)
        r = led_brightness_max;
    if (g > led_brightness_max)
        g = led_brightness_max;
    if (b > led_brightness_max)
        b = led_brightness_max;
    led_color[led_index][0] = r;
    led_color[led_index][1] = g;
    led_color[led_index][2] = b;
    status_leds.setPixelColor(led_index,
                              status_leds.Color(r, g, b));
    return true;
}
bool LED_STATUS::set_fuction(uint8_t led_index, uint8_t function)
{
    if (led_index >= ws2812_number)
    {
        return false;
    }
    else if (function >= ws2812_function_max)
    {
        return false;
    }
    led_function[led_index] = function;
    return true;
}
bool LED_STATUS::calculate()
{
    // 遍历所有LED
    for (uint8_t i = 0; i < ws2812_number; i++)
    {
        // 根据每个LED的功能类型更新颜色
        switch (led_function[i])
        {
        case no_function:
            // 无功能，保持灭灯
            led_color[i][0] = 0;
            led_color[i][1] = 0;
            led_color[i][2] = 0;
#if debug
            debug_serial.print("LED ");
            debug_serial.print(i);
            debug_serial.println(" no function, turned off");
#endif
            break;

        case fault_alarm:
            fault_alarm_update(i);
#if debug
            debug_serial.print("LED ");
            debug_serial.print(i);
            debug_serial.println(" fault alarm");
#endif
            break;

        case keyboard_signal:
            keyboard_signal_update(i);
#if debug
            debug_serial.print("LED ");
            debug_serial.print(i);
            debug_serial.println(" keyboard signal");
#endif
            break;

        case touch_signal:
            touch_signal_update(i);
#if debug
            debug_serial.print("LED ");
            debug_serial.print(i);
            debug_serial.println(" touch signal");
#endif
            break;

        case capslock_status:
            capslock_status_update(i);
#if debug
            debug_serial.print("LED ");
            debug_serial.print(i);
            debug_serial.println(" capslock status");
#endif
            break;

        case red_breath:
            breath(i, breath_red);
            break;

        case green_breath:
            breath(i, breath_green);
            break;

        case blue_breath:
            breath(i, breath_blue);
            break;

        case cyan_breath:
            breath(i, breath_cyan);
            break;

        case magenta_breath:
            breath(i, breath_magenta);
            break;

        case yellow_breath:
            breath(i, breath_yellow);
            break;

        case white_breath:
            breath(i, breath_white);
            break;

        case fan_speed:
            fan_speed_update(i);
            break;

        case backlight_brightness:
            backlight_brightness_update(i);
            break;

        case random_breath:
            random_breath_update(i);
            break;

        case battery_status:
            battery_status_update(i);
            break;

        case pi_power_status:
            pi_power_status_update(i);
            break;

        case backlight_adc_startus:
            backlight_adc_status_update(i);
            break;

        case rpi_cpu_status:
            rpi_cpu_status_update(i);
            break;

        case rpi_temp_status:
            rpi_temp_status_update(i);
            break;

        case rpi_ram_status:
            rpi_ram_status_update(i);
            break;

        case rpi_disk_status:
            rpi_disk_status_update(i);
            break;

        case rpi_net_status:
            rpi_network_status_update(i);
            break;

        default:
            // 未知功能，关闭LED
            led_color[i][0] = 0;
            led_color[i][1] = 0;
            led_color[i][2] = 0;
            break;
        }

        // 将计算出的颜色设置到WS2812
        if (led_color[i][0] > led_brightness_max)
        {
            led_color[i][0] = led_brightness_max;
        }
        if (led_color[i][1] > led_brightness_max)
        {
            led_color[i][1] = led_brightness_max;
        }
        if (led_color[i][2] > led_brightness_max)
        {
            led_color[i][2] = led_brightness_max;
        }
        status_leds.setPixelColor(i,
                                  status_leds.Color(
                                      led_color[i][0],
                                      led_color[i][1],
                                      led_color[i][2]));
#if debug
        debug_serial.print("LED ");
        debug_serial.print(i);
        debug_serial.print(" color set to (");
        debug_serial.print(led_color[i][0]);
        debug_serial.print(", ");
        debug_serial.print(led_color[i][1]);
        debug_serial.print(", ");
        debug_serial.print(led_color[i][2]);
        debug_serial.println(")");
#endif
    }

    return true;
}
bool LED_STATUS::flash()
{
    if (system_status.ssd1306_mode == 3)
    {
        // set_color(0, 0, 0, 0);
        set_color(1, 0, 0, 0);
        set_color(2, 0, 0, 0);
        set_color(3, 0, 0, 0);
    }
    else if (system_status.ssd1306_mode == 4)
    {
        set_color(0, 0, 0, 0);
        //set_color(1, 0, 0, 0);
        set_color(2, 0, 0, 0);
        set_color(3, 0, 0, 0);
    }
    else if (system_status.ssd1306_mode == 5)
    {
        set_color(0, 0, 0, 0);
        set_color(1, 0, 0, 0);
        //set_color(2, 0, 0, 0);
        set_color(3, 0, 0, 0);
    }
    else if (system_status.ssd1306_mode == 6)
    {
        set_color(0, 0, 0, 0);
        set_color(1, 0, 0, 0);
        set_color(2, 0, 0, 0);
        //set_color(3, 0, 0, 0);
    }
    status_leds.show();
    return true;
}
bool LED_STATUS::routine()
{
    set_fuction(0, system_status.ws2812_1_function);
    set_fuction(1, system_status.ws2812_2_function);
    set_fuction(2, system_status.ws2812_3_function);
    set_fuction(3, system_status.ws2812_4_function);

    calculate();
    flash();
    return true;
}

bool LED_STATUS::fault_alarm_update(uint8_t led_index)
{
    if (led_index >= ws2812_number)
    {
        return false;
    }
    int error = 0;
    for (int i = 0; i < sizeof(system_status.error_code); i++)
    {
        error += system_status.error_code[i];
    }

    if (error > 0)
    {
        led_color[led_index][0] = led_brightness_max;
        led_color[led_index][1] = 0;
        led_color[led_index][2] = 0;
    }
    else
    {
        led_color[led_index][0] = 0;
        led_color[led_index][1] = led_brightness_max;
        led_color[led_index][2] = 0;
    }
    last_error = error;
    return true;
}

bool LED_STATUS::keyboard_signal_update(uint8_t led_index)
{
    if (led_index >= ws2812_number)
    {
        return false;
    }
    else if (system_status.last_key_value == last_key_index)
    {
        return true;
    }
    else if (system_status.last_key_value > 0)
    {
        uint8_t color_code = key_color_map[system_status.last_key_value % key_color_count_max];
        led_color[led_index][0] = (color_code & 0b0100) ? led_brightness_max : 0;
        led_color[led_index][1] = (color_code & 0b0010) ? led_brightness_max : 0;
        led_color[led_index][2] = (color_code & 0b0001) ? led_brightness_max : 0;
    }
    else
    {
        led_color[led_index][0] = 0;
        led_color[led_index][1] = 0;
        led_color[led_index][2] = 0;
    }
    last_key_index = system_status.last_key_value;
    return true;
}

bool LED_STATUS::touch_signal_update(uint8_t led_index)
{
    if (led_index >= ws2812_number)
    {
        return false;
    }
    else if (system_status.touch_x == last_touch_x && system_status.touch_y == last_touch_y && system_status.mouse_x == 0 && system_status.mouse_y == 0)
    {
        return true;
    }
    else if (system_status.touch_x != 0 || system_status.touch_y != 0)
    {
        // 根据触摸位置计算颜色，这里只是一个示例，可以根据实际需求调整
        led_color[led_index][0] = (system_status.touch_x % 100 * led_brightness_max) / 100;                                 // 红色强度与X坐标成正比
        led_color[led_index][1] = (system_status.touch_y % 100 * led_brightness_max) / 100;                                 // 绿色强度与Y坐标成正比
        led_color[led_index][2] = ((system_status.touch_x % 100 + system_status.touch_y % 100) * led_brightness_max) / 200; // 蓝色强度与X和Y坐标的平均值成正比
        last_touch_x = system_status.touch_x;
        last_touch_y = system_status.touch_y;
    }
    else if (system_status.mouse_x != 0 || system_status.mouse_y != 0)
    {
        // 根据触摸位置计算颜色，这里只是一个示例，可以根据实际需求调整
        led_color[led_index][0] = (system_status.mouse_x % 100 * led_brightness_max) / 100;                                 // 红色强度与X坐标成正比
        led_color[led_index][1] = (system_status.mouse_y % 100 * led_brightness_max) / 100;                                 // 绿色强度与Y坐标成正比
        led_color[led_index][2] = ((system_status.mouse_x % 100 + system_status.mouse_y % 100) * led_brightness_max) / 200; // 蓝色强度与X和Y坐标的平均值成正比
        last_touch_x = system_status.mouse_x;
        last_touch_y = system_status.mouse_y;
    }
    else
    {
        led_color[led_index][0] = 1;
        led_color[led_index][1] = 1;
        led_color[led_index][2] = 1;
    }
    return true;
}

bool LED_STATUS::capslock_status_update(uint8_t led_index)
{
    if (led_index >= ws2812_number)
    {
        return false;
    }
    else if (system_status.capslock_status)
    {
        led_color[led_index][0] = led_brightness_max;
        led_color[led_index][1] = 0;
        led_color[led_index][2] = 0;
    }
    else
    {
        led_color[led_index][0] = 0;
        led_color[led_index][1] = led_brightness_max;
        led_color[led_index][2] = 0;
    }
    capslock_blink_status = system_status.capslock_status;
    return true;
}

bool LED_STATUS::breath(uint8_t led_index, uint8_t color)
{
    if (led_index >= ws2812_number)
    {
        return false;
    }
    else if (color)
    {
        uint8_t r = (color & 0b0100) ? breath_status : 0;
        uint8_t g = (color & 0b0010) ? breath_status : 0;
        uint8_t b = (color & 0b0001) ? breath_status : 0;
        led_color[led_index][0] = r;
        led_color[led_index][1] = g;
        led_color[led_index][2] = b;
        breath_counter++;
        if (breath_counter >= breath_speed)
        {
            breath_counter = 0;
            if (breath_direction)
            {
                breath_status++;
                if (breath_status >= led_brightness_max)
                {
                    breath_status = led_brightness_max;
                    breath_direction = false;
                }
            }
            else
            {
                breath_status--;
                if (breath_status <= 0)
                {
                    breath_status = 0;
                    breath_direction = true;
                }
            }
        }
    }
    else
    {
        led_color[led_index][0] = 0;
        led_color[led_index][1] = 0;
        led_color[led_index][2] = 0;
    }
    return true;
}

bool LED_STATUS::fan_speed_update(uint8_t led_index)
{
    if (led_index >= ws2812_number)
    {
        return false;
    }
    else if (system_status.fan_speed == last_fan_speed)
    {
        return true;
    }
    else
    {
        uint8_t brightness = system_status.fan_speed * led_brightness_max / fan_speed_max;
        led_color[led_index][0] = brightness; // 红色强度与风扇速度成正比
        led_color[led_index][1] = 0;
        led_color[led_index][2] = 0;
        last_fan_speed = system_status.fan_speed;
    }
    return true;
}

bool LED_STATUS::backlight_brightness_update(uint8_t led_index)
{
    if (led_index >= ws2812_number)
    {
        return false;
    }
    else if (system_status.backlight_brightness == last_backlight_brightness)
    {
        return true;
    }
    else
    {
        float backlight_brightness_ui_percentage = (system_status.backlight_brightness - backlight_brightness_minimum) * (100 / (backlight_brightness_maximum - backlight_brightness_minimum));
        uint8_t brightness = backlight_brightness_ui_percentage * led_brightness_max / 100;
        led_color[led_index][0] = 0;
        led_color[led_index][1] = brightness; // 绿色强度与背光亮度成正比
        led_color[led_index][2] = 0;
        last_backlight_brightness = system_status.backlight_brightness;
    }
    return true;
}

bool LED_STATUS::random_breath_update(uint8_t led_index)
{
    if (led_index >= ws2812_number)
    {
        return false;
    }
    else
    {
        uint8_t color = random(1, 8); // 随机选择一种颜色
        breath(led_index, color);
    }
    return true;
}

bool LED_STATUS::battery_status_update(uint8_t led_index)
{
    if (led_index >= ws2812_number)
    {
        return false;
    }
    else
    {
        uint8_t brightness = system_status.battery_percentage * led_brightness_max / 100;
        led_color[led_index][0] = 0;
        led_color[led_index][1] = brightness; // 绿色强度与电池百分比成正比
        led_color[led_index][2] = 0;
        if (brightness < 2)
        {
            led_color[led_index][0] = led_brightness_max;
            led_color[led_index][1] = 0;
            led_color[led_index][2] = 0;
        }
    }
    return true;
}

bool LED_STATUS::pi_power_status_update(uint8_t led_index)
{
    if (led_index >= ws2812_number)
    {
        return false;
    }
    else if (system_status.main_power_voltage_mv >= main_power_voltage_minimum_mv)
    {
        led_color[led_index][0] = 0;
        led_color[led_index][1] = led_brightness_max;
        led_color[led_index][2] = 0;
    }
    else
    {
        led_color[led_index][0] = led_brightness_max;
        led_color[led_index][1] = 0;
        led_color[led_index][2] = 0;
    }
    return true;
}

bool LED_STATUS::backlight_adc_status_update(uint8_t led_index)
{
    if (led_index >= ws2812_number)
    {
        return false;
    }
    else
    {
        uint8_t brightness = system_status.backlight_voltage_mv * led_brightness_max / 30000;
        led_color[led_index][0] = 0;
        led_color[led_index][1] = brightness;
        led_color[led_index][2] = 0;
    }
    return true;
}

bool LED_STATUS::rpi_cpu_status_update(uint8_t led_index)
{
    if (system_status.rpi_communicated)
    {
        if (system_status.rpi_cpu > 25)
        {
            led_color[led_index][0] = ws2812_brightness_maximum;
            led_color[led_index][1] = 0;
            led_color[led_index][2] = 0;
        }
        else if (system_status.rpi_cpu > 10)
        {
            uint8_t brightness = map(system_status.rpi_cpu, 10, 25, 0, ws2812_brightness_maximum);
            led_color[led_index][0] = brightness;
            led_color[led_index][1] = brightness;
            led_color[led_index][2] = 0;
        }
        else
        {
            led_color[led_index][0] = 0;
            led_color[led_index][1] = system_status.rpi_cpu;
            led_color[led_index][2] = 0;
        }
    }
    else
    {
        led_color[led_index][0] = 0;
        led_color[led_index][1] = 0;
        led_color[led_index][2] = ws2812_brightness_maximum / 3;
    }
    return true;
}

bool LED_STATUS::rpi_temp_status_update(uint8_t led_index)
{
    if (system_status.rpi_communicated)
    {
        if (system_status.rpi_temp > 25)
        {
            led_color[led_index][0] = ws2812_brightness_maximum;
            led_color[led_index][1] = 0;
            led_color[led_index][2] = 0;
        }
        else if (system_status.rpi_temp > 10)
        {
            uint8_t brightness = map(system_status.rpi_temp, 10, 25, 0, ws2812_brightness_maximum);
            led_color[led_index][0] = brightness;
            led_color[led_index][1] = brightness;
            led_color[led_index][2] = 0;
        }
        else
        {
            led_color[led_index][0] = 0;
            led_color[led_index][1] = system_status.rpi_temp;
            led_color[led_index][2] = 0;
        }
    }
    else
    {
        led_color[led_index][0] = 0;
        led_color[led_index][1] = 0;
        led_color[led_index][2] = ws2812_brightness_maximum / 3;
    }
    return true;
}

bool LED_STATUS::rpi_ram_status_update(uint8_t led_index)
{
    if (system_status.rpi_communicated)
    {
        if (system_status.rpi_ram > 25)
        {
            led_color[led_index][0] = ws2812_brightness_maximum;
            led_color[led_index][1] = 0;
            led_color[led_index][2] = 0;
        }
        else if (system_status.rpi_ram > 10)
        {
            uint8_t brightness = map(system_status.rpi_ram, 10, 25, 0, ws2812_brightness_maximum);
            led_color[led_index][0] = brightness;
            led_color[led_index][1] = brightness;
            led_color[led_index][2] = 0;
        }
        else
        {
            led_color[led_index][0] = 0;
            led_color[led_index][1] = system_status.rpi_ram;
            led_color[led_index][2] = 0;
        }
    }
    else
    {
        led_color[led_index][0] = 0;
        led_color[led_index][1] = 0;
        led_color[led_index][2] = ws2812_brightness_maximum / 3;
    }
    return true;
}

bool LED_STATUS::rpi_disk_status_update(uint8_t led_index)
{
    if (system_status.rpi_communicated)
    {
        if (system_status.rpi_disk > 25)
        {
            led_color[led_index][0] = ws2812_brightness_maximum;
            led_color[led_index][1] = 0;
            led_color[led_index][2] = 0;
        }
        else if (system_status.rpi_disk > 10)
        {
            uint8_t brightness = map(system_status.rpi_disk, 10, 25, 0, ws2812_brightness_maximum);
            led_color[led_index][0] = brightness;
            led_color[led_index][1] = brightness;
            led_color[led_index][2] = 0;
        }
        else
        {
            led_color[led_index][0] = 0;
            led_color[led_index][1] = system_status.rpi_disk;
            led_color[led_index][2] = 0;
        }
    }
    else
    {
        led_color[led_index][0] = 0;
        led_color[led_index][1] = 0;
        led_color[led_index][2] = ws2812_brightness_maximum / 3;
    }
    return true;
}

bool LED_STATUS::rpi_network_status_update(uint8_t led_index)
{
    if (system_status.rpi_communicated)
    {
        if (system_status.rpi_net > 25)
        {
            led_color[led_index][0] = ws2812_brightness_maximum;
            led_color[led_index][1] = 0;
            led_color[led_index][2] = 0;
        }
        else if (system_status.rpi_net > 10)
        {
            uint8_t brightness = map(system_status.rpi_net, 10, 25, 0, ws2812_brightness_maximum);
            led_color[led_index][0] = brightness;
            led_color[led_index][1] = brightness;
            led_color[led_index][2] = 0;
        }
        else
        {
            led_color[led_index][0] = 0;
            led_color[led_index][1] = system_status.rpi_net;
            led_color[led_index][2] = 0;
        }
    }
    else
    {
        led_color[led_index][0] = 0;
        led_color[led_index][1] = 0;
        led_color[led_index][2] = ws2812_brightness_maximum / 3;
    }
    return true;
}

bool LED_STATUS::empty(uint8_t led_index)
{
    if (led_index >= ws2812_number)
    {
        return false;
    }
    led_color[led_index][0] = 0;
    led_color[led_index][1] = 0;
    led_color[led_index][2] = 0;
    return 0;
}