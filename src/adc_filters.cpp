/*
   @Author: 无序熵增
   @Date: 2026-03-01 22:35:48
   @LastEditors: 无序熵增
   @LastEditTime: 2026-04-30 15:20:47
   @Description:

   Copyright (c) 2026 by 无序熵增, All Rights Reserved.
*/
#include "adc_filters.h"

bool FIR_filter::begin()
{

  for (int i = 0; i < fir_filters_buffer_length; i++)
  {
    shift_amount += shift_bits[i];
  }
  write_pointer = 0;
  return true;
}
uint16_t FIR_filter::filter(uint16_t adc_value)
{
  buffer[write_pointer] = adc_value;

  uint32_t sum = 0;
  uint8_t j = fir_filters_buffer_length - 1;
  for (int i = write_pointer; i < fir_filters_buffer_length; i++)
  {
    sum += buffer[i] * shift_bits[j];
    j--;
  }
  for (int i = 0; i < write_pointer; i++)
  {
    sum += buffer[i] * shift_bits[j];
    j--;
  }
  write_pointer++;
  if (write_pointer > fir_filters_buffer_length)
  {
    write_pointer = 0;
  }

  return sum / shift_amount;
}

bool IIR_filter::begin(uint16_t adc_value)
{
  buffer = adc_value;
  return true;
}
uint16_t IIR_filter::filter(uint16_t adc_value)
{
  buffer = (adc_value * 1 + buffer * 31) >> 5;
  return buffer;
}
