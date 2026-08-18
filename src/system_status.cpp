#include "system_status.h"

System_Status system_status;

bool system_status_setup()
{
    system_status.hardware_version = 0;
    system_status.software_version_major = 0;
    system_status.software_version_minor = 0;
    system_status.software_version_float = 0;
    system_status.loop_count = 0;

    system_status.fan_speed = 0;
    system_status.backlight_brightness = 0;
    system_status.backlight_bightness_percentage = 0;

    system_status.ws2812_1_function = 0;
    system_status.ws2812_2_function = 0;
    system_status.ws2812_3_function = 0;
    system_status.ws2812_4_function = 0;
    system_status.ws2812_max_brightness = ws2812_brightness_maximum;

    system_status.battery_voltage_raw = 0;
    system_status.battery_voltage_mv = 0;
    system_status.battery_voltage_v = 0;
    system_status.battery_percentage = 0;
    system_status.battery_maximum_voltage_mv = 0;
    system_status.battery_minimum_voltage_mv = 0;
    system_status.is_battery_charging = 0;
    system_status.is_battery_charge_done = 0;
    system_status.backlight_voltage_raw = 0;
    system_status.backlight_voltage_mv = 0;
    system_status.backlight_voltage_v = 0;
    system_status.backlight_brightness_percentage = 0;
    system_status.main_power_voltage_raw = 0;
    system_status.main_power_voltage_mv = 0;
    system_status.main_power_voltage_v = 0;
    system_status.pi_3v3_voltage_raw = 0;
    system_status.pi_3v3_voltage_mv = 0;
    system_status.pi_3v3_voltage_v = 0;
    for (int i = 0; i < 32; i++)
    {
        system_status.battery_voltage_raw_record[i] = 0;
        system_status.backlight_voltage_raw_record[i] = 0;
        system_status.main_power_voltage_raw_record[i] = 0;
        system_status.pi_3v3_voltage_raw_record[i] = 0;
    }
    system_status.battery_voltage_raw_record_pointer = 0;
    system_status.backlight_voltage_raw_record_pointer = 0;
    system_status.main_power_voltage_raw_record_pointer = 0;
    system_status.pi_3v3_voltage_raw_record_pointer = 0;

    system_status.hdmi_signal_detected = 0;
    system_status.touch_status = 0;
    system_status.touch_x = 0;
    system_status.touch_y = 0;

    system_status.keyboard_slot_1 = 0;
    system_status.keyboard_slot_2 = 0;
    system_status.keyboard_slot_3 = 0;
    system_status.is_usb_ready_4_communication = 0;
    system_status.capslock_status = 0;
    system_status.shift_status = 0;
    system_status.last_key_value = 0;
    system_status.last_key_index = 0;
    for (int i = 0; i < keyboard_iic_length; i++)
    {
        system_status.key_buffer[i] = 0;
    }
    system_status.mouse_x = 0;
    system_status.mouse_y = 0;
    system_status.ssd1306_status = 0;
    system_status.ssd1306_mode = 0;
    system_status.ssd1306_heart_beat_frame = 0;
    system_status.ssd1306_set_instruction = 0;
    system_status.ssd1306_set_instruction_old = 0;

    system_status.rpi_cpu = 0;
    system_status.rpi_temp = 0;
    system_status.rpi_disk = 0;
    system_status.rpi_ram = 0;
    system_status.rpi_net = 0;
    system_status.rpi_distribution = 0;
    system_status.rpi_communicated = false;
    for (int i = 0; i < 100; i++)
    {
        system_status.error_code[i] = 0;
    }
    system_status.is_this_struct_set_up_correctly = 0;
    system_status.need_to_record_to_eeprom = 0;
    system_status.magic_number = 0;

    return 0;
}

bool ssd1306_status_empty()
{
    system_status.ssd1306_mode = iic_display_routine_mode;
    system_status.ssd1306_heart_beat_frame = 0;
    system_status.ssd1306_set_instruction = 0;
    system_status.ssd1306_set_instruction_old=0;
    return 0;
}

bool rpi_status_empty()
{
    system_status.rpi_cpu = 0;
    system_status.rpi_temp = 0;
    system_status.rpi_ram = 0;
    system_status.rpi_disk = 0;
    system_status.rpi_net = 0;
    system_status.rpi_distribution = 0;
    system_status.rpi_communicated = 0;
    return 0;
}

bool system_status_report()
{
    debug_serial.println("-----------------------------------------");
    debug_serial.println("System Status Report:");
    debug_serial.print("Hardware Version: ");
    debug_serial.println(system_status.hardware_version);
    debug_serial.print("Software Version: ");
    debug_serial.print(system_status.software_version_major);
    debug_serial.print(".");
    debug_serial.print(system_status.software_version_minor);
    debug_serial.print(" (");
    debug_serial.print(system_status.software_version_float);
    debug_serial.println(")");
    debug_serial.print("Loop Count: ");
    debug_serial.println(system_status.loop_count);

    debug_serial.print("Fan Speed: ");
    debug_serial.println(system_status.fan_speed);
    debug_serial.print("Backlight Brightness: ");
    debug_serial.println(system_status.backlight_brightness);

    debug_serial.print("WS2812 Functions: ");
    debug_serial.print(system_status.ws2812_1_function);
    debug_serial.print(", ");
    debug_serial.print(system_status.ws2812_2_function);
    debug_serial.print(", ");
    debug_serial.print(system_status.ws2812_3_function);
    debug_serial.print(", ");
    debug_serial.println(system_status.ws2812_4_function);
    debug_serial.print("WS2812 Max Brightness: ");
    debug_serial.println(system_status.ws2812_max_brightness);

    debug_serial.print("Battery Voltage: ");
    debug_serial.print(system_status.battery_voltage_mv);
    debug_serial.print(" mV (");
    debug_serial.print(system_status.battery_voltage_v);
    debug_serial.print(" V, ");
    debug_serial.print(system_status.battery_percentage);
    debug_serial.println("%)");
    debug_serial.print("Battery Voltage Range: ");
    debug_serial.print(system_status.battery_minimum_voltage_mv);
    debug_serial.print(" mV - ");
    debug_serial.print(system_status.battery_maximum_voltage_mv);
    debug_serial.println(" mV");
    debug_serial.print("Battery Charging Status: ");
    debug_serial.println(system_status.is_battery_charging ? "Charging" : "Not Charging");
    debug_serial.print("Battery Charge Done Status: ");
    debug_serial.println(system_status.is_battery_charge_done ? "Done" : "Not Done");
    debug_serial.print("Battey Voltage record : ");
    for (int i = 0; i < 32; i++)
    {
        debug_serial.print(system_status.battery_voltage_raw_record[i]);
        debug_serial.print("/");
    }
    debug_serial.println();

    debug_serial.print("Backlight Voltage: ");
    debug_serial.print(system_status.backlight_voltage_mv);
    debug_serial.println(" mV");
    debug_serial.print("Backlight Voltage record : ");
    for (int i = 0; i < 32; i++)
    {
        debug_serial.print(system_status.backlight_voltage_raw_record[i]);
        debug_serial.print("/");
    }
    debug_serial.println();

    debug_serial.print("Main Power Voltage: ");
    debug_serial.print(system_status.main_power_voltage_mv);
    debug_serial.println(" mV");
    debug_serial.print("Main Voltage record : ");
    for (int i = 0; i < 32; i++)
    {
        debug_serial.print(system_status.main_power_voltage_raw_record[i]);
        debug_serial.print("/");
    }
    debug_serial.println();

    debug_serial.print("Pi 3.3V Voltage: ");
    debug_serial.print(system_status.pi_3v3_voltage_mv);
    debug_serial.println(" mV");
    debug_serial.print("Pi 3v3 Voltage record : ");
    for (int i = 0; i < 32; i++)
    {
        debug_serial.print(system_status.pi_3v3_voltage_raw_record[i]);
        debug_serial.print("/");
    }
    debug_serial.println();

    debug_serial.print("HDMI Signal Detected: ");
    debug_serial.println(system_status.hdmi_signal_detected ? "Yes" : "No");

    debug_serial.print("Touch Status: ");
    debug_serial.println(system_status.touch_status ? "Active" : "Inactive");
    debug_serial.print("Touch Coordinates: (");
    debug_serial.print(system_status.touch_x);
    debug_serial.print(", ");
    debug_serial.print(system_status.touch_y);
    debug_serial.println(")");

    debug_serial.print("Keyboard Slot 1: ");
    debug_serial.println(system_status.keyboard_slot_1);
    debug_serial.print("Keyboard Slot 2: ");
    debug_serial.println(system_status.keyboard_slot_2);
    debug_serial.print("Keyboard Slot 3: ");
    debug_serial.println(system_status.keyboard_slot_3);
    debug_serial.print("Is USB ready for communication: ");
    debug_serial.println(system_status.is_usb_ready_4_communication);
    debug_serial.print("Caps Lock Status: ");
    debug_serial.println(system_status.capslock_status ? "On" : "Off");
    debug_serial.print("Shift Status: ");
    debug_serial.println(system_status.shift_status ? "Pressed" : "Not Pressed");
    debug_serial.print("Last Key Value: ");
    debug_serial.println(system_status.last_key_value);
    debug_serial.print("Key Buffer: ");
    for (size_t i = 0; i < keyboard_iic_length; i++)
    {
        debug_serial.print(system_status.key_buffer[i], HEX);
        if (i < keyboard_iic_length - 1)
            debug_serial.print(" ");
    }
    debug_serial.println();

    debug_serial.print("SSD1306 Status: ");
    debug_serial.println(system_status.ssd1306_status);
    debug_serial.print("SSD1306 Mode: ");
    debug_serial.println(system_status.ssd1306_mode);
    debug_serial.print("SSD1306 Heart Beat Frame: ");
    debug_serial.println(system_status.ssd1306_heart_beat_frame);
    debug_serial.print("SSD1306 Instruction: ");
    debug_serial.println(system_status.ssd1306_set_instruction);
    debug_serial.print("SSD1306 Instruction old: ");
    debug_serial.println(system_status.ssd1306_set_instruction_old);

    debug_serial.print("raspberry pi CPU: ");
    debug_serial.println(system_status.rpi_cpu);
    debug_serial.print("raspberry pi Temp: ");
    debug_serial.println(system_status.rpi_temp);
    debug_serial.print("raspberry pi RAM: ");
    debug_serial.println(system_status.rpi_ram);
    debug_serial.print("raspberry pi DISK: ");
    debug_serial.println(system_status.rpi_disk);
    debug_serial.print("raspberry pi NET: ");
    debug_serial.println(system_status.rpi_net);
    debug_serial.print("raspberry pi communicated : ");
    debug_serial.println(system_status.rpi_communicated ? "YES" : "NO");
    debug_serial.println("-----------------------------------------");
    return true;
}