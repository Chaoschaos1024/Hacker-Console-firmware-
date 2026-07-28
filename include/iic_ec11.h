#ifndef IIC_EC11_H
#define IIC_EC11_H

#ifdef __cplusplus
#include <Arduino.h>
#include <Wire.h>

#define ec11_address 0x16

class EC11 {
public:
    // 初始化 I2C 通信
    bool begin(TwoWire *twi = &Wire, uint8_t deviceAddress = 0x16); // 默认地址 0x50

    // 获取编码器的当前计数值 (0-255)
    int getNumber(uint8_t encoderIndex);

    // 获取编码器的按键状态 (true: 按下, false: 释放)
    bool getKey(uint8_t encoderIndex);

    // 更新所有编码器数据（从 I2C 设备读取最新值）
    bool update();

private:
    TwoWire *_wire;       // I2C 接口指针（默认 Wire）
    uint8_t _deviceAddress; // I2C 设备地址

    uint8_t _encoderCounts[8]; // 8 个编码器的计数值 (0-255)
    bool _keyStates[8];        // 8 个编码器的按键状态
};

#else
#error "This library requires C++ support."
#endif

#endif