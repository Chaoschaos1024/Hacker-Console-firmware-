/*
 * @Author: 无序熵增
 * @Date: 2026-03-04 21:20:17
 * @LastEditors: 无序熵增
 * @LastEditTime: 2026-04-29 18:43:04
 * @Description:
 *
 * Copyright (c) 2026 by 无序熵增, All Rights Reserved.
 */
#include "ssd1306.h"

Adafruit_SSD1306 display(iic_display_width, iic_display_height, &Wire1, iic_display_reset);

const String old_key_map[old_keyboard_key_count] =
    {
        "SPACE     ",
        "SPACE     ",
        "F5        ",
        "F4        ",
        "F3        ",
        "F2        ",
        "F1        ",
        "N         ",
        "B         ",
        "V         ",
        "C         ",
        "X         ",
        "Z         ",
        "SHIFT     ",
        "H         ",
        "G         ",
        "F         ",
        "D         ",
        "S         ",
        "A         ",
        "CAPSLOCK  ",
        "Y         ",
        "T         ",
        "R         ",
        "E         ",
        "W         ",
        "Q         ",
        "TAB       ",
        "`/~       ",
        "          ",
        "          ",
        "WHEEL_U   ",
        "MOUSE_L   ",
        "MOUSE_R   ",
        "WHEEL_M   ",
        "1/!       ",
        "3/#       ",
        "5/%       ",
        "7/&       ",
        "9/(       ",
        "-/_       ",
        "BACKSP    ",
        "2/@       ",
        "4/$       ",
        "6/^       ",
        "8/*       ",
        "0/)       ",
        "=/+       ",
        "ESC       ",
        "U         ",
        "I         ",
        "O         ",
        "P         ",
        "[/{       ",
        "]/}       ",
        "DELETE    ",
        "J         ",
        "K         ",
        "L         ",
        ";/:       ",
        "'/\"      ",
        "\\/|      ",
        "ENTER     ",
        "M         ",
        ",/<       ",
        "./>       ",
        "//?       ",
        "UP        ",
        "SHIFT     ",
        "HOME      ",
        "ALT       ",
        "CTRL      ",
        "GUI       ",
        "LEFT      ",
        "DOWN      ",
        "RIGHT     ",
        "END       ",
};
const String new_key_map[new_keyboard_key_count] =
    {
        "SPACE    ",
        "SPACE    ",
        "PAGE_DN  ",
        "PAGE_UP  ",
        "ALT      ",
        "GUI      ",
        "CTRL     ",
        "N        ",
        "B        ",
        "V        ",
        "C        ",
        "X        ",
        "Z        ",
        "SHIFT    ",
        "H        ",
        "G        ",
        "F        ",
        "D        ",
        "S        ",
        "A        ",
        "CAPSLOCK ",
        "Y        ",
        "T        ",
        "R        ",
        "E        ",
        "W        ",
        "Q        ",
        "TAB      ",
        "6/^      ",
        "5/%      ",
        "4/$      ",
        "3/#      ",
        "2/@      ",
        "1/!      ",
        "`/~      ",
        "F7       ",
        "-/_      ",
        "=/+      ",
        "BACKSP   ",
        "         ",
        "         ",
        "         ",
        "7/&      ",
        "8/*      ",
        "9/(      ",
        "0/)      ",
        "MOUSE_L  ",
        "         ",
        "MOUSE_R  ",
        "U        ",
        "I        ",
        "O        ",
        "P        ",
        "[/{      ",
        "]/}      ",
        "DELETE   ",
        "J        ",
        "K        ",
        "L        ",
        ";/:      ",
        "'/\"     ",
        "\\/|     ",
        "ENTER    ",
        "M        ",
        ",/<      ",
        "./>      ",
        "//?      ",
        "UP       ",
        "SHIFT    ",
        "HOME     ",
        "ALT      ",
        "CTRL     ",
        "GUI      ",
        "LEFT     ",
        "DOWN     ",
        "RIGHT    ",
        "END      ",
        "F6       ",
        "F5       ",
        "F4       ",
        "F3       ",
        "F2       ",
        "F1       ",
        "ESC      ",

};

bool SECONDARY_DISPLAY::begin()
{
    Wire1.beginTransmission(iic_display_address);
    if (Wire1.endTransmission() == 0)
    {
        system_status.ssd1306_status = true;
        system_status.ssd1306_mode = iic_display_routine_mode;
        display.begin(SSD1306_SWITCHCAPVCC, iic_display_address);
        display.setRotation(2);
        display.clearDisplay();
        display.display();
        display.drawBitmap(0, 0, bootup_logo, bootup_logo_width, bootup_logo_height, 1);
        display.setTextSize(1);
        display.setTextColor(SSD1306_WHITE);
        display.cp437(true);
        display.setCursor(35, 0);
        display.print("HACKER ");
        display.print("COMSOLE");
        display.setCursor(35, 8);
        display.print("Ver:");
        display.print(system_status.software_version_float);
#if debug
        display.print("(debug)");
#endif
        display.setFont(&front1);
        display.setCursor(35, 20);
        display.print("Hardware Ver: ");
        if (system_status.hardware_version == 0)
        {
            display.print("ERROR");
        }
        else if (system_status.hardware_version == 1)
        {
            display.print("OLD");
        }
        else if (system_status.hardware_version == 2)
        {
            display.print("NEW");
        }
        else
        {
            display.print("Unknown");
        }
        display.setCursor(35, 25);
        display.print("Compile Date:");
        display.setCursor(35, 31);
        display.print(__DATE__);
        display.print(":");
        display.print(__TIME__);
        display.display();
        display.setRotation(1);
        Wire1.endTransmission();
        delay(2000);
    }
    else
    {
        system_status.ssd1306_status = false;
        return false;
    }
    return true;
}

bool SECONDARY_DISPLAY::update()
{
    system_status.ssd1306_set_instruction_old = system_status.ssd1306_set_instruction;
    if (system_status.ssd1306_mode >= iic_display_set_mode)
    {
        set_mode();
    }
    else if (system_status.ssd1306_mode == iic_display_routine_mode)
    {
        routine_mode();
    }
    else
    {
#if debug
        debug_serial.println("Unknown iic display mode");
        delay(1000);
        return false;
#endif
    }
    return true;
}

bool SECONDARY_DISPLAY::routine_mode()
{
    if (!system_status.ssd1306_status)
    {
        return false;
    }
    display.clearDisplay();

    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 8);
    display.cp437(true);
#if debug
    display.print(system_status.ssd1306_heart_beat_frame);
#endif
    display.drawBitmap(0, 0, heart_beat_wave[system_status.ssd1306_heart_beat_frame], logo_width, logo_height, 1);
    system_status.ssd1306_heart_beat_frame++;
    if (system_status.ssd1306_heart_beat_frame >= heart_beat_frame_max)
    {
        system_status.ssd1306_heart_beat_frame = 0;
    }
    if (system_status.is_battery_charging)
    {
        int battery_pixel = map(system_status.battery_percentage, 0, 100, 2, 28);
        for (int i = 2; i < battery_pixel; i++)
        {
            display.drawPixel(i, 26, SSD1306_WHITE);
            display.drawPixel(i, 27, SSD1306_WHITE);
            display.drawPixel(i, 28, SSD1306_WHITE);
            display.drawPixel(i, 29, SSD1306_WHITE);
        }
        for (int i = 12; i < 20; i++)
        {
            display.drawPixel(i, 26, SSD1306_BLACK);
            display.drawPixel(i, 27, SSD1306_BLACK);
            display.drawPixel(i, 28, SSD1306_BLACK);
            display.drawPixel(i, 29, SSD1306_BLACK);
        }
        display.drawBitmap(0, 24, battery_logo_charge, battery_logo_width, battery_logo_hight, 1);
        display.setTextSize(1);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(0, 37);
        display.cp437(true);
        if (system_status.is_battery_charge_done)
        {
            display.print("FULL");
        }
        else
        {
            display.print("CHARG");
        }
    }
    else
    {
        display.drawBitmap(0, 24, battery_logo_empty, battery_logo_width, battery_logo_hight, 1);
        int battery_pixel = map(system_status.battery_percentage, 0, 100, 2, 28);
        for (int i = 2; i < battery_pixel; i++)
        {
            display.drawPixel(i, 26, SSD1306_WHITE);
            display.drawPixel(i, 27, SSD1306_WHITE);
            display.drawPixel(i, 28, SSD1306_WHITE);
            display.drawPixel(i, 29, SSD1306_WHITE);
        }
        if (system_status.battery_percentage >= 100)
        {
            display.setTextSize(1);
            display.setTextColor(SSD1306_WHITE);
            display.setCursor(5, 37);
            display.cp437(true);
            display.print("FULL");
        }
        else if (system_status.battery_percentage >= 75)
        {
            display.setTextSize(1);
            display.setTextColor(SSD1306_WHITE);
            display.setCursor(3, 37);
            display.cp437(true);
            display.print(">");
            display.print(system_status.battery_percentage);
            display.print("%");
            display.print("<");
        }
        else if (system_status.battery_percentage >= 50)
        {
            display.setTextSize(1);
            display.setTextColor(SSD1306_WHITE);
            display.setCursor(3, 37);
            display.cp437(true);
            display.print(">");
            display.print(system_status.battery_percentage);
            display.print("%");
            display.print("<");
        }
        else if (system_status.battery_percentage >= 25)
        {
            display.setTextSize(1);
            display.setTextColor(SSD1306_WHITE);
            display.setCursor(3, 37);
            display.cp437(true);
            display.print(">");
            display.print(system_status.battery_percentage);
            display.print("%");
            display.print("<");
        }
        else if (system_status.battery_percentage >= 10)
        {
            display.setTextSize(1);
            display.setTextColor(SSD1306_WHITE);
            display.setCursor(3, 37);
            display.cp437(true);
            display.print(">");
            display.print(system_status.battery_percentage);
            display.print("%");
            display.print("<");
        }
        else
        {
            display.setTextSize(1);
            display.setTextColor(SSD1306_WHITE);
            display.setCursor(6, 37);
            display.cp437(true);
            display.print("-!");
            display.print(system_status.battery_percentage);
            display.print("%");
            display.print("!-");
        }
    }
    display.setFont(&front1);
    display.drawLine(0, 40, 31, 40, SSD1306_WHITE);
    display.setCursor(0, 46);
    display.setTextSize(1);
    display.print("HDMI:");
    if (system_status.hdmi_signal_detected)
    {
        display.print("Y");
    }
    else
    {
        display.print("N");
    }
    display.setTextSize(1);

    display.print("BL:");

    display.print(system_status.backlight_brightness_percentage);
    display.setCursor(0, 60);
    display.setTextSize(1);
    display.print("FAN:");
    display.print(system_status.fan_speed);
    display.drawLine(0, 62, 31, 62, SSD1306_WHITE);
    /*
        #if debug
        display.print("CPU :");
        display.println(system_status.rpi_cpu);
        display.print("TEMP :");
        display.println(system_status.rpi_temp);
        display.print("RAM :");
        display.println(system_status.rpi_ram);
        display.print("DISK:");
        display.println(system_status.rpi_disk);
        display.print("NET :");
        display.println(system_status.rpi_net);
        display.print("6 :");
        display.println(system_status.rpi_net);
        display.print("7:");
        display.println(system_status.rpi_net);
        display.print("8 :");
        display.println(system_status.rpi_net);
        display.print("9 :");
        display.println(system_status.rpi_net);
        display.print("10 :");
        display.println(system_status.rpi_net);
    #endif
    */
    display.setCursor(0, 68);
    display.setTextSize(1);
    display.setFont(&front1);
    display.print("CPU :");
#if debug
    display.println(system_status.rpi_cpu);
#endif
    display.fillRect(0, 70, system_status.rpi_cpu, 3, SSD1306_WHITE);

    display.setCursor(0, 78);
    display.setTextSize(1);
    display.setFont(&front1);
    display.print("TEMP :");
#if debug
    display.println(system_status.rpi_temp);
#endif
    display.fillRect(0, 80, system_status.rpi_temp, 3, SSD1306_WHITE);

    display.setCursor(0, 88);
    display.setTextSize(1);
    display.setFont(&front1);
    display.print("RAM :");
#if debug
    display.println(system_status.rpi_ram);
#endif
    display.fillRect(0, 90, system_status.rpi_ram, 3, SSD1306_WHITE);

    display.setCursor(0, 98);
    display.setTextSize(1);
    display.setFont(&front1);
    display.print("DISK:");
#if debug
    display.println(system_status.rpi_disk);
#endif
    display.fillRect(0, 100, system_status.rpi_disk, 3, SSD1306_WHITE);

    display.setCursor(0, 108);
    display.setTextSize(1);
    display.setFont(&front1);
    display.print("NET :");
#if debug
    display.println(system_status.rpi_net);
#endif
    display.fillRect(0, 110, system_status.rpi_net, 3, SSD1306_WHITE);

    display.display();
    return true;
}
bool SECONDARY_DISPLAY::set_mode()
{
    if (!system_status.ssd1306_status)
    {
        return false;
    }
    display.clearDisplay();
    // display.fillRect(0, 0, 32, 128, SSD1306_WHITE); // SSD1306_INVERSE);

    if (system_status.ssd1306_set_instruction == set_mode_function_right)
    {
        system_status.ssd1306_mode++;
        if (system_status.ssd1306_mode >= iic_display_set_page_max)
        {
            system_status.ssd1306_mode = 1;
        }
        system_status.ssd1306_set_instruction = 0;
    }
    if (system_status.ssd1306_set_instruction == set_mode_function_left)
    {
        if (system_status.ssd1306_mode > 1)
        {
            system_status.ssd1306_mode--;
        }
        else
        {
            system_status.ssd1306_mode = iic_display_set_page_max - 1;
        }
        system_status.ssd1306_set_instruction = 0;
    }
    if (system_status.ssd1306_set_instruction == set_mode_function_ok)
    {
        system_status.ssd1306_set_instruction = 0;
        system_status.ssd1306_mode = 0;
        return 0;
    }
    if (system_status.ssd1306_set_instruction == set_mode_function_back)
    {
        system_status.ssd1306_set_instruction = 0;
        system_status.ssd1306_mode = 0;
        return 0;
    }

#if debug
    display.setCursor(0, 6);
    display.setTextSize(1);
    display.println(system_status.ssd1306_mode);
#endif
    if (system_status.ssd1306_mode == iic_display_set_fan_speed_value)
    {
        set_fan_speed_mode();
    }
    else if (system_status.ssd1306_mode == iic_display_set_backlight_brightness_value)
    {
        set_display_brightness_mode();
    }
    else if (system_status.ssd1306_mode == iic_display_set_ws2812_1_function_value)
    {
        set_ws2812_1_function_mode();
    }
    else if (system_status.ssd1306_mode == iic_display_set_ws2812_2_function_value)
    {
        set_ws2812_2_function_mode();
    }
    else if (system_status.ssd1306_mode == iic_display_set_ws2812_3_function_value)
    {
        set_ws2812_3_function_mode();
    }
    else if (system_status.ssd1306_mode == iic_display_set_ws2812_4_function_value)
    {
        set_ws2812_4_function_mode();
    }
    else if (system_status.ssd1306_mode == iic_display_battery_information_value)
    {
        show_battery_information();
    }
    else if (system_status.ssd1306_mode == iic_display_power_information_value)
    {
        show_power_information();
    }
    else if (system_status.ssd1306_mode == iic_display_version_information_value)
    {
        show_version_information();
    }
    else if (system_status.ssd1306_mode == iic_display_keyboard_information_value)
    {
        show_keyboard_information();
    }
    else if (system_status.ssd1306_mode == iic_display_hdmi_status)
    {
        show_hdmi_active_status();
    }
    else if (system_status.ssd1306_mode == iic_display_raspberry_status)
    {
        show_rpi_status();
    }
    else if (system_status.ssd1306_mode == iic_display_reboot_status)
    {
        reboot_chip();
    }
    else if (system_status.ssd1306_mode == iic_display_reboot_to_bootloader)
    {
        reboot_to_bootloader();
    }
    else if (system_status.ssd1306_mode == iic_display_chip_information)
    {
        show_chip_information();
    }

#if debug
    else if (system_status.ssd1306_mode == iic_display_set_page_max)
    {
        y = 0;
        line(2);
        y = y + 10;
        line(1);
        y = y + 10;
        // square(30);
        // y=y+30;
        show_big_text("FU");
        show_big_text((uint16_t)1, "x");
        show_big_text((float)1.0);
        show_big_text((float)1.0, "x");
    }
#endif
    else
    {
        system_status.ssd1306_mode = 0;
    }

    display.display();

    return true;
}

int SECONDARY_DISPLAY::set_fan_speed_mode()
{
    if (system_status.ssd1306_set_instruction == set_mode_function_up)
    {
        if (system_status.fan_speed < 100)
        {
            system_status.fan_speed++;
        }
        system_status.ssd1306_set_instruction = 0;
    }
    else if (system_status.ssd1306_set_instruction == set_mode_function_down)
    {
        if (system_status.fan_speed < 1)
        {
            system_status.fan_speed = 0;
        }
        else
        {
            system_status.fan_speed--;
        }
        system_status.ssd1306_set_instruction = 0;
    }

    y = 32;
    display.drawBitmap(0, 0, fan_logo, set_logo_width, set_logo_height, 1);
    show_small_text("SET");
    show_small_text("FAN");
    show_small_text("SPEED");
    show_defauit_text((uint16_t)system_status.fan_speed, "%");
    line(1);
    show_small_text("POWER:");
    show_small_text((float)system_status.main_power_voltage_v, "v");
    scope_32_32(system_status.main_power_voltage_raw_record, system_status.main_power_voltage_raw_record_pointer);

    return 0;
}
int SECONDARY_DISPLAY::set_display_brightness_mode()
{

    if (system_status.ssd1306_set_instruction == set_mode_function_up)
    {
        if (system_status.backlight_brightness < backlight_brightness_minimum)
        {
            system_status.backlight_brightness = backlight_brightness_minimum;
        }
        else
        {
            system_status.backlight_brightness = system_status.backlight_brightness - backlight_brightness_step;
#if debug
            debug_serial.print("brightness up to ");
            debug_serial.println(system_status.backlight_brightness);
#endif
        }
        system_status.ssd1306_set_instruction = 0;
    }
    else if (system_status.ssd1306_set_instruction == set_mode_function_down)
    {
        if (system_status.backlight_brightness < backlight_brightness_maximum)
        {
            system_status.backlight_brightness = system_status.backlight_brightness + backlight_brightness_step;
#if debug
            debug_serial.print("brightness down to ");
            debug_serial.println(system_status.backlight_brightness);
#endif
        }
        else
        {
            system_status.backlight_brightness = backlight_brightness_maximum;
        }
        system_status.ssd1306_set_instruction = 0;
    }
    y = 32;
    display.drawBitmap(0, 0, backlight_logo, set_logo_width, set_logo_height, 1);
    show_small_text("SET");
    show_small_text("BACK");
    show_small_text("LIGHT");
    show_defauit_text((uint16_t)system_status.backlight_bightness_percentage, "%");
    line(1);
    show_small_text("POWER:");
    show_small_text((float)system_status.backlight_voltage_v, "v");
    scope_32_32(system_status.backlight_voltage_raw_record, system_status.backlight_voltage_raw_record_pointer);
#if debug
    debug_serial.print("backlight percent : ");
    debug_serial.println(system_status.backlight_bightness_percentage);
    debug_serial.print("backlight : ");
    debug_serial.println(system_status.backlight_brightness);
    debug_serial.println(backlight_brightness_step);
#endif
    return 0;
}
int SECONDARY_DISPLAY::set_ws2812_1_function_mode()
{
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setFont(&front1);
    display.cp437(true);
    display.setCursor(16, 21);
    display.print("1");
    y = 36;
    display.drawBitmap(0, 0, ws2812_logo, set_logo_width, set_logo_height, 1);
    if (system_status.ssd1306_set_instruction == set_mode_function_up)
    {
        system_status.ws2812_1_function++;
        if (system_status.ws2812_1_function >= ws2812_function_max)
        {
            system_status.ws2812_1_function = 1;
        }
        system_status.ssd1306_set_instruction = 0;
    }
    else if (system_status.ssd1306_set_instruction == set_mode_function_down)
    {
        if (system_status.ws2812_1_function == 1)
        {
            system_status.ws2812_1_function = ws2812_function_max - 1;
        }
        else
        {
            system_status.ws2812_1_function--;
        }
        system_status.ssd1306_set_instruction = 0;
    }
    show_ws2812_function(system_status.ws2812_1_function);

    return 0;
}
int SECONDARY_DISPLAY::set_ws2812_2_function_mode()
{
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setFont(&front1);
    display.cp437(true);
    display.setCursor(13, 21);
    display.print("2");
    y = 36;
    display.drawBitmap(0, 0, ws2812_logo, set_logo_width, set_logo_height, 1);
    if (system_status.ssd1306_set_instruction == set_mode_function_up)
    {
        system_status.ws2812_2_function++;
        if (system_status.ws2812_2_function >= ws2812_function_max)
        {
            system_status.ws2812_2_function = 1;
        }
        system_status.ssd1306_set_instruction = 0;
    }
    else if (system_status.ssd1306_set_instruction == set_mode_function_down)
    {
        if (system_status.ws2812_2_function = 1)
        {
            system_status.ws2812_2_function = ws2812_function_max - 1;
        }
        else
        {
            system_status.ws2812_2_function--;
        }
        system_status.ssd1306_set_instruction = 0;
    }
    show_ws2812_function(system_status.ws2812_2_function);
    return 0;
}
int SECONDARY_DISPLAY::set_ws2812_3_function_mode()
{
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setFont(&front1);
    display.cp437(true);
    display.setCursor(13, 21);
    display.print("3");
    y = 36;
    display.drawBitmap(0, 0, ws2812_logo, set_logo_width, set_logo_height, 1);
    if (system_status.ssd1306_set_instruction == set_mode_function_up)
    {
        system_status.ws2812_3_function++;
        if (system_status.ws2812_3_function >= ws2812_function_max)
        {
            system_status.ws2812_3_function = 1;
        }
        system_status.ssd1306_set_instruction = 0;
    }
    else if (system_status.ssd1306_set_instruction == set_mode_function_down)
    {
        if (system_status.ws2812_3_function = 1)
        {
            system_status.ws2812_3_function = ws2812_function_max - 1;
        }
        else
        {
            system_status.ws2812_3_function--;
        }
        system_status.ssd1306_set_instruction = 0;
    }
    show_ws2812_function(system_status.ws2812_3_function);
    return 0;
}
int SECONDARY_DISPLAY::set_ws2812_4_function_mode()
{
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setFont(&front1);
    display.cp437(true);
    display.setCursor(13, 21);
    display.print("4");
    y = 36;
    display.drawBitmap(0, 0, ws2812_logo, set_logo_width, set_logo_height, 1);
    if (system_status.ssd1306_set_instruction == set_mode_function_up)
    {
        system_status.ws2812_4_function++;
        if (system_status.ws2812_4_function >= ws2812_function_max)
        {
            system_status.ws2812_4_function = 1;
        }
        system_status.ssd1306_set_instruction = 0;
    }
    else if (system_status.ssd1306_set_instruction == set_mode_function_down)
    {
        if (system_status.ws2812_4_function = 1)
        {
            system_status.ws2812_4_function = ws2812_function_max - 1;
        }
        else
        {
            system_status.ws2812_4_function--;
        }
        system_status.ssd1306_set_instruction = 0;
    }
    show_ws2812_function(system_status.ws2812_4_function);
    return 0;
}
int SECONDARY_DISPLAY::show_battery_information()
{
    y = 32;
    if (system_status.is_battery_charging)
    {
        display.drawBitmap(0, 0, battery_is_charging_logo, set_logo_width, set_logo_height, 1);
    }
    else
    {
        if (system_status.battery_percentage >= 90)
        {
            display.drawBitmap(0, 0, battery_100_percent_logo, set_logo_width, set_logo_height, 1);
        }
        else if (system_status.battery_percentage >= 75)
        {
            display.drawBitmap(0, 0, battery_75_percent_logo, set_logo_width, set_logo_height, 1);
        }
        else if (system_status.battery_percentage >= 50)
        {
            display.drawBitmap(0, 0, battery_50_percent_logo, set_logo_width, set_logo_height, 1);
        }
        else if (system_status.battery_percentage >= 25)
        {
            display.drawBitmap(0, 0, battery_25_percent_logo, set_logo_width, set_logo_height, 1);
        }
        else
        {
            display.drawBitmap(0, 0, battery_0_percent_logo, set_logo_width, set_logo_height, 1);
        }
    }
    show_small_text("BAT : ");
    progress_bar_big(system_status.battery_percentage);
    show_small_text("PER : ");
    show_small_text((uint16_t)system_status.battery_percentage, "%");
    show_small_text("VOL :");
    show_small_text(system_status.battery_voltage_mv);
    show_small_text("MV");
    line(1);
    show_small_text("Scope : ");
    scope_32_32(system_status.battery_voltage_raw_record, system_status.battery_voltage_raw_record_pointer);

    return 0;
}
int SECONDARY_DISPLAY::show_power_information()
{
    y = 32;
    display.drawBitmap(0, 0, power_logo, set_logo_width, set_logo_height, 1);
    show_defauit_text("MAIN");
    show_defauit_text(system_status.main_power_voltage_mv);
    scope_32_32(system_status.main_power_voltage_raw_record, system_status.main_power_voltage_raw_record_pointer);
    show_defauit_text("PI3V3");
    show_defauit_text(system_status.pi_3v3_voltage_mv);
    scope_32_32(system_status.pi_3v3_voltage_raw_record, system_status.pi_3v3_voltage_raw_record_pointer);
    return 0;
}
int SECONDARY_DISPLAY::show_version_information()
{
    y = 32;
    display.drawBitmap(0, 0, pcb_logo, set_logo_width, set_logo_height, 1);
    show_defauit_text("HARD");
    y++;
    show_defauit_text("WARE");
    y = y + 2;
    show_defauit_text("VER:");
    y = y + 2;
    if (system_status.hardware_version == old_hardware_version)
    {
        show_defauit_text("OLD");
    }
    else if (system_status.hardware_version == new_hardware_version)
    {
        show_defauit_text("NEW");
    }
    else
    {
        show_defauit_text("ERROR");
    }
    y = y + 2;
    line(1);
    y = y + 2;
    show_defauit_text("SOFT");
    y++;
    show_defauit_text("WARE");
    y = y + 2;
    show_defauit_text("VER:");
    y = y + 2;
    show_defauit_text((float)software_version);
    return 0;
}
int SECONDARY_DISPLAY::show_keyboard_information()
{
    y = 32;
    display.drawBitmap(0, 0, keyboard_logo, set_logo_width, set_logo_height, 1);
    show_defauit_text("KEY");
    y++;
    show_defauit_text("BOARD");
    y = y + 2;
    show_defauit_text("TYPE:");
    y = y + 3;
    if (system_status.keyboard_type & old_keyboard)
    {
        show_defauit_text("OLD");
    }
    if ((system_status.keyboard_type & new_keyboard_old_program))
    {
        show_defauit_text("NEW");
    }
    if (system_status.keyboard_type & new_keyboard_new_program)
    {
        show_defauit_text("NEW.");
    }
    y = y + 2;
    line(1);
    y = y + 2;
    show_defauit_text("LAST");
    y = y + 2;
    show_defauit_text("KEY :");
    y = y + 3;
    if (system_status.keyboard_type & old_keyboard)
    {
        show_defauit_text(old_key_map[system_status.last_key_index]);
    }
    if (system_status.keyboard_type & new_keyboard_new_program || system_status.keyboard_type & new_keyboard_old_program)
    {
        show_defauit_text(new_key_map[system_status.last_key_index]);
    }
#if debug
    show_defauit_text(system_status.last_key_value);
#endif

    return 0;
}
int SECONDARY_DISPLAY::show_hdmi_active_status()
{
    y = 26;
    display.drawBitmap(0, 0, hdmi_logo, set_logo_width, set_logo_height, 1);
    show_defauit_text("HDMI:");
    y = y + 2;
    if (system_status.hdmi_signal_detected)
    {
        show_defauit_text("YES");
    }
    else
    {
        show_defauit_text("NO");
    }
    y = y + 2;
    line(1);
    y = y + 2;
    show_defauit_text("BACK");
    y++;
    show_defauit_text("LIGHT");
    y++;
    show_defauit_text("VOL:");
    y = y + 3;
    show_defauit_text(system_status.backlight_voltage_mv);
    y++;
    show_defauit_text("MV");
    return 0;
}
int SECONDARY_DISPLAY::show_rpi_status()
{
    // system_status.rpi_communicated = 1;
    y = 28;
    display.drawBitmap(0, 0, pi_logo, set_logo_width, set_logo_height, 1);
    if (system_status.rpi_communicated)
    {
        show_defauit_text("CPU :");
        y++;
        progress_bar_big(system_status.rpi_cpu * 3.3);
        show_defauit_text("TEMP:");
        y++;
        progress_bar_big(system_status.rpi_temp * 3.3);
        y++;
        show_defauit_text("RAM :");
        y++;
        progress_bar_big(system_status.rpi_ram * 3.3);
        show_defauit_text("DISK:");
        y++;
        progress_bar_big(system_status.rpi_disk * 3.3);
        show_defauit_text("NET :");
        y++;
        progress_bar_big(system_status.rpi_net * 3.3);
        // show_defauit_text("DIST:");
        if (system_status.rpi_distribution == ubuntu_distribution)
        {
            show_small_text("UBUN");
        }
        else if (system_status.rpi_distribution == debian_distribution)
        {
            show_small_text("DEBI");
        }
        else if (system_status.rpi_distribution == rhel_distribution)
        {
            show_small_text("RHEL");
        }
        else if (system_status.rpi_distribution == fedora_distribution)
        {
            show_small_text("FEDO");
        }
        else if (system_status.rpi_distribution == arch_distribution)
        {
            show_small_text("ARCH");
        }
        else if (system_status.rpi_distribution == linuxmint_distribution)
        {
            show_small_text("MINT");
        }
        else if (system_status.rpi_distribution == opensuse_distribution)
        {
            show_small_text("SUSE");
        }
        else if (system_status.rpi_distribution == centos_distribution)
        {
            show_small_text("CENT");
        }
        else if (system_status.rpi_distribution == kali_distribution)
        {
            show_small_text("KALI");
        }
        else if (system_status.rpi_distribution == raspbian_distribution)
        {
            show_small_text("RASP");
        }
    }
    else
    {
        show_defauit_text("NO");
        y = y + 4;
        show_defauit_text("INFOR");
        show_defauit_text("MA");
        show_defauit_text("TION");
        y = y + 4;
        show_defauit_text("FROM");
        y = y + 4;
        show_defauit_text("RASP");
        show_defauit_text("BERRY");
        y = y + 4;
        show_defauit_text("PI");
    }

    return 0;
}
bool SECONDARY_DISPLAY::show_ws2812_function(uint8_t function)
{
    switch (function)
    {
    case no_function:
        show_defauit_text("NO");
        y = y + 3;
        show_defauit_text("FUNC");
        show_defauit_text("TION");
        break;

    case fault_alarm:
        show_defauit_text("FAULT");
        y = y + 3;
        show_defauit_text("ALARM");
        break;

    case keyboard_signal:
        show_defauit_text("KEY");
        show_defauit_text("BOARD");
        y = y + 3;
        show_defauit_text("SIG");
        show_defauit_text("NAL");
        break;

    case touch_signal:
        show_defauit_text("TOUCH");
        y = y + 3;
        show_defauit_text("SIG");
        show_defauit_text("NAL");
        break;

    case capslock_status:
        show_defauit_text("CAPS");
        y = y + 3;
        show_defauit_text("LOCK");
        break;

    case red_breath:
        show_defauit_text("RED");
        y = y + 3;
        show_defauit_text("BREA");
        show_defauit_text("TH");
        break;

    case green_breath:
        show_defauit_text("GREEN");
        y = y + 3;
        show_defauit_text("BREA");
        show_defauit_text("TH");
        break;

    case blue_breath:
        show_defauit_text("BLUE");
        y = y + 3;
        show_defauit_text("BREA");
        show_defauit_text("TH");
        break;

    case cyan_breath:
        show_defauit_text("CYAN");
        y = y + 3;
        show_defauit_text("BREA");
        show_defauit_text("TH");
        break;

    case magenta_breath:
        show_defauit_text("MAGEN");
        show_defauit_text("TA");
        y = y + 3;
        show_defauit_text("BREA");
        show_defauit_text("TH");
        break;

    case yellow_breath:
        show_defauit_text("YELL");
        show_defauit_text("OW");
        y = y + 3;
        show_defauit_text("BREA");
        show_defauit_text("TH");
        break;

    case white_breath:
        show_defauit_text("WHITE");
        y = y + 3;
        show_defauit_text("BREA");
        show_defauit_text("TH");
        break;

    case fan_speed:
        show_defauit_text("FAN");
        y = y + 3;
        show_defauit_text("SPEED");
        break;

    case backlight_brightness:
        show_defauit_text("BACK");
        show_defauit_text("LIGHT");
        y = y + 3;
        show_defauit_text("BRIGH");
        show_defauit_text("TNESS");
        break;

    case random_breath:
        show_defauit_text("RAN");
        show_defauit_text("DOM");
        y = y + 3;
        show_defauit_text("BREA");
        show_defauit_text("TH");
        break;

    case battery_status:
        show_defauit_text("BATT");
        show_defauit_text("ERY");
        y = y + 3;
        show_defauit_text("STA");
        show_defauit_text("TUS");
        break;

    case pi_power_status:
        show_defauit_text("PI");
        y = y + 3;
        show_defauit_text("POWER");
        y = y + 3;
        show_defauit_text("STA");
        show_defauit_text("TUS");
        break;

    case backlight_adc_startus:
        show_defauit_text("BACK");
        show_defauit_text("LIGHT");
        y = y + 3;
        show_defauit_text("ADC");
        y = y + 3;
        show_defauit_text("STA");
        show_defauit_text("TUS");
        break;

    case rpi_cpu_status:
        show_defauit_text("RPI");
        y = y + 3;
        show_defauit_text("CPU");
        y = y + 3;
        show_defauit_text("STA");
        show_defauit_text("TUS");
        break;

    case rpi_temp_status:
        show_defauit_text("RPI");
        y = y + 3;
        show_defauit_text("TEMP");
        y = y + 3;
        show_defauit_text("STA");
        show_defauit_text("TUS");
        break;

    case rpi_ram_status:
        show_defauit_text("RPI");
        y = y + 3;
        show_defauit_text("RAM");
        y = y + 3;
        show_defauit_text("STA");
        show_defauit_text("TUS");
        break;

    case rpi_disk_status:
        show_defauit_text("RPI");
        y = y + 3;
        show_defauit_text("DISK");
        y = y + 3;
        show_defauit_text("STA");
        show_defauit_text("TUS");
        break;

    case rpi_net_status:
        show_defauit_text("RPI");
        y = y + 3;
        show_defauit_text("NET");
        y = y + 3;
        show_defauit_text("STA");
        show_defauit_text("TUS");
        break;

    default:
        show_defauit_text("UNKN");
        y = y + 3;
        show_defauit_text("FUNC");
        show_defauit_text("TION");
        break;
    }

    return true;
}
int SECONDARY_DISPLAY::reboot_chip()
{
    y = 32;
    display.drawBitmap(0, 0, reboot_logo, set_logo_width, set_logo_height, 1);
    show_defauit_text("PRESS");
    y = y + 5;
    show_defauit_text("UP");
    y = y + 5;
    show_defauit_text("TO");
    y = y + 5;
    show_defauit_text("RE");
    y = y + 2;
    show_defauit_text("BOOT");
    y = y + 5;
    show_defauit_text("CON");
    y = y + 2;
    show_defauit_text("SOLE");

    if (system_status.ssd1306_set_instruction == set_mode_function_up)
    {
        rp2040.reboot();
        system_status.ssd1306_set_instruction = 0;
    }
    return true;
}
int SECONDARY_DISPLAY::reboot_to_bootloader()
{
    y = 32;
    display.drawBitmap(0, 0, update_software_logo, set_logo_width, set_logo_height, 1);

    show_defauit_text("PRESS");
    y = y + 5;
    show_defauit_text("UP");
    y = y + 5;
    show_defauit_text("TO");
    y = y + 5;
    show_defauit_text("UP");
    y = y + 2;
    show_defauit_text("DATE");
    y = y + 5;
    show_defauit_text("SOFT");
    y = y + 2;
    show_defauit_text("WARE");

    if (system_status.ssd1306_set_instruction == set_mode_function_up)
    {
        display.clearDisplay();
        display.drawBitmap(0, 0, update_software_logo, set_logo_width, set_logo_height, 1);
        y = 32;
        show_defauit_text("UP");
        y = y + 2;
        show_defauit_text("DAT");
        y = y + 2;
        show_defauit_text("ING");
        y = y + 5;
        show_defauit_text("SOFT");
        y = y + 2;
        show_defauit_text("WARE");
        display.display();
        delay(500);
        rp2040.rebootToBootloader();
        system_status.ssd1306_set_instruction = 0;
    }

    return true;
}
int SECONDARY_DISPLAY::show_chip_information()
{
    y = 32;
    display.drawBitmap(0, 0, raspberry_pi_pico_logo, set_logo_width, set_logo_height, 1);
    show_defauit_text("FREQ:");
    show_defauit_text(rp2040.f_cpu() / 1000000);
    show_defauit_text("Mhz");
    y = y + 3;
    show_defauit_text("RAM:");
    uint16_t percent = 100 * rp2040.getUsedHeap() / rp2040.getTotalHeap();
    show_defauit_text(percent, "%");

    return true;
}
bool SECONDARY_DISPLAY::show_small_text(int num)
{
    y = y + 6;
    display.setFont(&front1);
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.cp437(true);
    display.setCursor(0, y);
    display.print(num);
    y = y + 2;
    return 0;
}
bool SECONDARY_DISPLAY::show_small_text(float num)
{
    y = y + 6;
    display.setFont(&front1);
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.cp437(true);
    display.setCursor(0, y);
    display.print(num);
    y = y + 2;
    return 0;
}
bool SECONDARY_DISPLAY::show_small_text(const String &text)
{
    y = y + 6;
    display.setFont(&front1);
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.cp437(true);
    display.setCursor(0, y);
    display.print(text);
    y = y + 2;
    return 0;
}
bool SECONDARY_DISPLAY::show_small_text(uint16_t num, const String &text)
{
    y = y + 6;
    display.setFont(&front1);
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.cp437(true);
    display.setCursor(0, y);
    display.print(num);
    display.print(text);
    y = y + 2;
    return 0;
}
bool SECONDARY_DISPLAY::show_small_text(float num, const String &text)
{
    y = y + 6;
    display.setFont(&front1);
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.cp437(true);
    display.setCursor(0, y);
    display.print(num);
    display.print(text);
    y = y + 2;
    return 0;
}
bool SECONDARY_DISPLAY::show_big_text(int num)
{
    y = y + 15;
    display.setFont(&front4);
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.cp437(true);
    display.setCursor(0, y);
    display.print(num);
    return 0;
}
bool SECONDARY_DISPLAY::show_big_text(float num)
{
    y = y + 15;
    display.setFont(&front4);
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.cp437(true);
    display.setCursor(0, y);
    display.print(num);
    return 0;
}
bool SECONDARY_DISPLAY::show_big_text(const String &text)
{
    y = y + 15;
    display.setFont(&front4);
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.cp437(true);
    display.setCursor(0, y);
    display.print(text);
    return 0;
}
bool SECONDARY_DISPLAY::show_big_text(uint16_t num, const String &text)
{
    y = y + 15;
    display.setFont(&front4);
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.cp437(true);
    display.setCursor(0, y);
    display.print(num);
    display.print(text);
    y = y + 2;
    return 0;
}
bool SECONDARY_DISPLAY::show_big_text(float num, const String &text)
{
    y = y + 15;
    display.setFont(&front4);
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.cp437(true);
    display.setCursor(0, y);
    display.print(num);
    display.print(text);
    y = y + 2;
    return 0;
}
bool SECONDARY_DISPLAY::show_defauit_text(int num)
{
    y++;
    display.setFont(NULL);
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.cp437(true);
    display.setCursor(0, y);
    display.print(num);
    y = y + 7;
    return 0;
}
bool SECONDARY_DISPLAY::show_defauit_text(float num)
{
    y++;
    display.setFont(NULL);
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.cp437(true);
    display.setCursor(0, y);
    display.print(num);
    y = y + 7;
    return 0;
}
bool SECONDARY_DISPLAY::show_defauit_text(const String &text)
{
    y++;
    display.setFont(NULL);
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.cp437(true);
    display.setCursor(0, y);
    display.print(text);
    y = y + 7;
    return 0;
}
bool SECONDARY_DISPLAY::show_defauit_text(uint16_t num, const String &text)
{
    y++;
    display.setFont(NULL);
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.cp437(true);
    display.setCursor(0, y);
    display.print(num);
    display.print(text);
    y = y + 7;
    return 0;
}
bool SECONDARY_DISPLAY::show_defauit_text(float num, const String &text)
{
    y++;
    display.setFont(NULL);
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.cp437(true);
    display.setCursor(0, y);
    display.print(num);
    display.print(text);
    y = y + 7;
    return 0;
}
bool SECONDARY_DISPLAY::scope_32_32(uint16_t record[32], uint8_t pointer)
{

    // 求32个采样平均值作为中心
    uint32_t sum = 0;

    for (uint8_t i = 0; i < 32; i++)
    {
        sum += record[i];
    }

    uint16_t center = sum >> 5; // 除32

    // 设置显示范围
    int32_t min = (int32_t)center - 15;
    int32_t max = (int32_t)center + 16;

    // 防止ADC范围越界
    if (min < 0)
    {
        min = 0;
        max = 31;
    }

    // ------------------------
    // 虚线边框
    // ------------------------

    for (uint8_t x = 0; x < 32; x += 2)
    {
        display.drawPixel(x, y, SSD1306_WHITE);
        display.drawPixel(x, y + 31, SSD1306_WHITE);
    }

    for (uint8_t yy = 0; yy < 32; yy += 2)
    {
        display.drawPixel(0, y + yy, SSD1306_WHITE);
        display.drawPixel(31, y + yy, SSD1306_WHITE);
    }

    // ------------------------
    // 背景参考点阵
    // 每8像素一个参考点
    // ------------------------

    for (uint8_t gy = 8; gy < 31; gy += 8)
    {
        for (uint8_t gx = 8; gx < 31; gx += 8)
        {
            display.drawPixel(gx, y + gy, SSD1306_WHITE);
        }
    }

    // ------------------------
    // 绘制波形
    // ------------------------

    int lastY = -1;

    for (uint8_t x = 0; x < 32; x++)
    {

        // 环形buffer展开
        uint8_t index = (pointer + 1 + x) & 0x1F;

        int32_t value = record[index];

        // 限幅
        if (value < min)
            value = min;

        if (value > max)
            value = max;

        // ADC -> OLED坐标
        uint8_t yy = y + 31 - (value - min);

        // 折线
        if (lastY >= 0)
        {
            display.drawLine(
                x - 1,
                lastY,
                x,
                yy,
                SSD1306_WHITE);
        }

        lastY = yy;

        // 最新点高亮
        if (x == 31)
        {
            uint8_t py;

            if (yy > y)
                py = yy - 1;
            else
                py = yy;

            display.fillRect(
                30,
                py,
                2,
                2,
                SSD1306_WHITE);
        }
    }
    y = y + 32;
    return true;
}

bool SECONDARY_DISPLAY::progress_bar_big(uint8_t percent)
{

    if (percent > 100)
        percent = 100;

    // 绘制外框（32×6）
    display.drawRect(0, y, 32, 6, SSD1306_WHITE);

    // 根据百分比计算内部宽度（0~28）
    uint8_t width = (uint16_t)percent * 28 / 100;

    // 绘制进度条（28×2）
    if (width)
    {
        display.fillRect(
            2,
            y + 2,
            width,
            2,
            SSD1306_WHITE);
    }
    y = y + 6;
    return true;
}
bool SECONDARY_DISPLAY::progress_bar_small(uint8_t percent)
{

    if (percent > 100)
        percent = 100;

    uint8_t width = (uint16_t)percent * 32 / 100;

    if (width)
    {
        display.fillRect(
            0,
            y + 1,
            width,
            2,
            SSD1306_WHITE);
    }
    y = y + 4;
    return true;
}
bool SECONDARY_DISPLAY::line(uint8_t width)
{
    if (width + y > 128)
    {
        width = 128 - y;
    }

    if (width == 0)
    {
        return true;
    }

    display.fillRect(0, y, 31, width, SSD1306_WHITE);
    y = y + width;

    return true;
}
bool SECONDARY_DISPLAY::square(uint8_t width)
{
    if (width + y > 128)
    {
        width = 128 - y;
    }

    if (width == 0)
    {
        return true;
    }

    display.drawRect(0, y, 31, width, SSD1306_WHITE);

    return true;
}