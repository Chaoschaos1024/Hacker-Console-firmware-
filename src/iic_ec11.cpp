#include "iic_ec11.h"

// 初始化 I2C
bool EC11::begin(TwoWire *twi, uint8_t deviceAddress) {
    _wire = twi;
    _deviceAddress = deviceAddress;

    //_wire->begin(); // 初始化 I2C（主模式）

    // 重置所有数据
    for (uint8_t i = 0; i < 8; i++) {
        _encoderCounts[i] = 0;
        _keyStates[i] = false;
    }

    // 尝试读取一次数据以检测设备是否在线
    return update();
}

// 获取编码器的计数值 (0-255)
int EC11::getNumber(uint8_t encoderIndex) {
    update(); // 每次获取数据前先更新一次
    if (encoderIndex >= 8) return 0; // 防止越界
    return _encoderCounts[encoderIndex];
}

// 获取编码器的按键状态
bool EC11::getKey(uint8_t encoderIndex) {
    update(); // 每次获取数据前先更新一次
    if (encoderIndex >= 8) return false; // 防止越界
    return _keyStates[encoderIndex];
}

// 从 I2C 设备更新所有编码器数据
bool EC11::update() {
    if (_wire->requestFrom(_deviceAddress, 16,true) != 16) {
        return false; // 读取失败（设备未响应）
    }

    // 解析 16 字节数据（8 个编码器 × 2 字节/编码器）
    for (uint8_t i = 0; i < 8; i++) {
        _keyStates[i] = _wire->read();       // 按键状态（1 字节）
        _encoderCounts[i] = _wire->read();   // 编码器计数值（1 字节）
    }

    return true;
}
