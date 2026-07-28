/*
 * @Author: 无序熵增
 * @Date: 2026-03-05 13:37:41
 * @LastEditors: 无序熵增
 * @LastEditTime: 2026-03-05 21:10:22
 * @Description:
 *
 * Copyright (c) 2026 by 无序熵增, All Rights Reserved.
 */
#ifndef FLASH_H
#define FLASH_H

#include <EEPROM.h>
#include "config.h"
#include "system_status.h"

class Flash
{
public:
    bool begin();

    // 核心接口：保存/加载整个系统状态
    bool save(System_Status &status); // 保存到Flash
    bool load(System_Status &status); // 从Flash加载
    bool is_valid();                  // 检查Flash中数据是否有效
    bool reset_to_default();          // 重置为默认值（擦除所有配置）


private:
    // EEPROM地址分配
    static const uint16_t STATUS_ADDR = 0;     // 结构体存储起始地址
    static const uint16_t MAGIC_ADDR = eeprom_size-100;    // 魔数存储地址（确保足够空间）
    static const uint16_t CHECKSUM_ADDR = eeprom_size-200; // 校验和地址

    static const uint32_t MAGIC_NUMBER = 0xA5A5A5A5; // 魔数，用于验证数据有效性

    // 辅助函数
    bool write_magic_number();
    bool read_magic_number(uint32_t &magic);
    uint16_t calculate_checksum(const uint8_t *data, size_t len);
    bool write_checksum(uint16_t checksum);
    bool read_checksum(uint16_t &checksum);

    // 初始化默认状态
    void init_default_status(System_Status &status);
};

#endif // FLASH_H
