/*
 * @Author: 无序熵增
 * @Date: 2026-03-01 22:35:48
 * @LastEditors: 无序熵增
 * @LastEditTime: 2026-04-30 15:19:32
 * @Description:
 *
 * Copyright (c) 2026 by 无序熵增, All Rights Reserved.
 */
#ifndef ADC_FILTER_H
#define ADC_FILTER_H

#include <SoftwareSerial.h>
#include "config.h"

#define fir_filters_buffer_length 16
#define iir_filters_smoothing_factor 4

class FIR_filter
{
public:
    bool begin();
    uint16_t filter(uint16_t adc_value);

private:
    uint16_t buffer[fir_filters_buffer_length];
    uint8_t write_pointer;
    uint8_t shift_bits[fir_filters_buffer_length] = {1, 1, 1, 2, 3, 4, 5, 5, 5, 5, 4, 3, 2, 1, 1, 1};
    uint16_t shift_amount = 0;
};

class IIR_filter
{
public:
    bool begin(uint16_t adc_value);
    uint16_t filter(uint16_t adc_value);

private:
    uint16_t buffer = 0;
};



#endif
