#include "flash.h"
#include <EEPROM.h>

#include "flash.h"

bool Flash::begin()
{
    EEPROM.begin(eeprom_size);

    // 检查是否为第一次使用
    if (!is_valid())
    {
        return reset_to_default();
    }
#if debug
    debug_serial.println("Flash begin complete, valid data found");
    init_default_status(system_status);
    save(system_status);
#endif

    return true;
}

// 保存系统状态到Flash
bool Flash::save(System_Status &status)
{
    size_t size = sizeof(System_Status);
    uint8_t *byte_ptr = (uint8_t *)&status;

    // 1. 写入结构体数据
    for (size_t i = 0; i < size; i++)
    {
        EEPROM.write(STATUS_ADDR + i, byte_ptr[i]);
    }

    // 2. 写入魔数
    if (!write_magic_number())
    {
        return false;
    }

    // 3. 写入校验和
    uint16_t checksum = calculate_checksum(byte_ptr, size);
    if (!write_checksum(checksum))
    {
        return false;
    }

    // 4. 提交更改
    return EEPROM.commit();
}

// 从Flash加载系统状态
bool Flash::load(System_Status &status)
{
    // 检查数据有效性
    if (!is_valid())
    {
        return false;
    }

    // 读取结构体数据
    size_t size = sizeof(System_Status);
    uint8_t *byte_ptr = (uint8_t *)&status;

    for (size_t i = 0; i < size; i++)
    {
        byte_ptr[i] = EEPROM.read(STATUS_ADDR + i);
    }

    // 验证校验和
    uint16_t saved_checksum;
    if (!read_checksum(saved_checksum))
    {
        return false;
    }

    uint16_t calculated_checksum = calculate_checksum(byte_ptr, size);
    if (saved_checksum != calculated_checksum)
    {
        return false; // 校验和不匹配，数据可能损坏
    }

    return true;
}

// 检查Flash中数据是否有效
bool Flash::is_valid()
{
    uint32_t magic;
    if (!read_magic_number(magic))
    {
        return false;
    }

    return (magic == MAGIC_NUMBER);
}

// 重置为默认值
bool Flash::reset_to_default()
{
    System_Status default_status;
    init_default_status(default_status);

    // 保存默认状态
    if (!save(default_status))
    {
        return false;
    }

    return EEPROM.commit();
}

// 写入魔数
bool Flash::write_magic_number()
{
    uint32_t magic = MAGIC_NUMBER;
    uint8_t *magic_ptr = (uint8_t *)&magic;

    for (size_t i = 0; i < sizeof(magic); i++)
    {
        EEPROM.write(MAGIC_ADDR + i, magic_ptr[i]);
    }

    return true;
}

// 读取魔数
bool Flash::read_magic_number(uint32_t &magic)
{
    uint8_t *magic_ptr = (uint8_t *)&magic;

    for (size_t i = 0; i < sizeof(magic); i++)
    {
        magic_ptr[i] = EEPROM.read(MAGIC_ADDR + i);
    }

    return true;
}

// 计算校验和（简单的累加和）
uint16_t Flash::calculate_checksum(const uint8_t *data, size_t len)
{
    uint16_t sum = 0;
    for (size_t i = 0; i < len; i++)
    {
        sum += data[i];
    }
    return sum;
}

// 写入校验和
bool Flash::write_checksum(uint16_t checksum)
{
    uint8_t *checksum_ptr = (uint8_t *)&checksum;

    for (size_t i = 0; i < sizeof(checksum); i++)
    {
        EEPROM.write(CHECKSUM_ADDR + i, checksum_ptr[i]);
    }

    return true;
}

// 读取校验和
bool Flash::read_checksum(uint16_t &checksum)
{
    uint8_t *checksum_ptr = (uint8_t *)&checksum;

    for (size_t i = 0; i < sizeof(checksum); i++)
    {
        checksum_ptr[i] = EEPROM.read(CHECKSUM_ADDR + i);
    }

    return true;
}

// 初始化默认状态
void Flash::init_default_status(System_Status &status)
{
    // 清零整个结构体
    memset(&status, 0, sizeof(System_Status));

    // 设置默认值
    status.hardware_version = 1;
    status.software_version_major = 6;
    status.software_version_minor = 0;
    status.software_version_float = 6.0f;
    status.loop_count = 0;

    status.fan_speed = fan_default_speed;
    status.backlight_brightness = backlight_default_brightness;

    status.ws2812_1_function = ws2812_1_default_function;
    status.ws2812_2_function = ws2812_2_default_function;
    status.ws2812_3_function = ws2812_3_default_function;
    status.ws2812_4_function = ws2812_4_default_function;
    status.ws2812_max_brightness = ws2812_brightness_maximum;

    status.battery_maximum_voltage_mv = 0;    // 4.2V
    status.battery_minimum_voltage_mv = 5000; // 3.2V

    status.backlight_brightness_percentage = backlight_default_brightness;

    status.touch_status = true;
    status.touch_x = 0;
    status.touch_y = 0;

    status.keyboard_type = 0;
    status.last_key_value = 0;

    status.ssd1306_status = 0;
    status.ssd1306_mode = 0;
    status.ssd1306_set_instruction = 0;

    for(int i = 0; i < sizeof(status.error_code); i++)
    {
        status.error_code[i] = 0; // 错误码数组初始化为0
    }

}
