#include "iic_keyboard.h"

Key old_keyboard_key[old_keyboard_key_count] =
    {

        {old_keyboard, false, 0, 0b00000001, false, false, 0x20, 0x20, 0x20, "SPACE     ", 0, 0, 0},                        // iic_byte  0 , byte 0b00000001 , line  0
        {old_keyboard, false, 0, 0b00000010, false, false, 0x20, 0x20, 0x20, "SPACE     ", 0, 0, 0},                        // iic_byte  0 , byte 0b00000010 , line  1
        {old_keyboard, false, 0, 0b00000100, false, false, 0xC6, 0xC6, 0xC6, "F5        ", 0, 0, 0},                        // iic_byte  0 , byte 0b00000100 , line  2
        {old_keyboard, false, 0, 0b00001000, false, false, 0xC5, 0xC5, 0xC5, "F4        ", 0, 0, 0},                        // iic_byte  0 , byte 0b00001000 , line  3
        {old_keyboard, false, 0, 0b00010000, false, false, 0xC4, 0xC4, 0xC4, "F3        ", 0, 0, 0},                        // iic_byte  0 , byte 0b00010000 , line  4
        {old_keyboard, false, 0, 0b00100000, false, false, 0xC3, 0xC3, 0xC3, "F2        ", 0, 0, 0},                        // iic_byte  0 , byte 0b00100000 , line  5
        {old_keyboard, false, 0, 0b01000000, false, false, 0xC2, 0xC2, 0xC2, "F1        ", 0, 0, 0},                        // iic_byte  0 , byte 0b01000000 , line  6
        {old_keyboard, false, 1, 0b00000001, false, false, 0x6E, 0x4E, 0x4E, "N         ", 0, 0, 0},                        // iic_byte  1 , byte 0b00000001 , line  7
        {old_keyboard, false, 1, 0b00000010, false, false, 0x62, 0x42, 0x42, "B         ", 0, 0, 0},                        // iic_byte  1 , byte 0b00000010 , line  8
        {old_keyboard, false, 1, 0b00000100, false, false, 0x76, 0x56, 0x56, "V         ", 0, 0, 0},                        // iic_byte  1 , byte 0b00000100 , line  9
        {old_keyboard, false, 1, 0b00001000, false, false, 0x63, 0x43, 0x43, "C         ", 0, 0, 0},                        // iic_byte  1 , byte 0b00001000 , line 10
        {old_keyboard, false, 1, 0b00010000, false, false, 0x78, 0x58, 0x58, "X         ", 0, 0, 0},                        // iic_byte  1 , byte 0b00010000 , line 11
        {old_keyboard, false, 1, 0b00100000, false, false, 0x7A, 0x5A, 0x5A, "Z         ", 0, 0, 0},                        // iic_byte  1 , byte 0b00100000 , line 12
        {old_keyboard, false, 1, 0b01000000, true, false, 0x81, 0x81, 0x81, "SHIFT     ", 0, 0, 0},                         // iic_byte  1 , byte 0b01000000 , line 13
        {old_keyboard, false, 2, 0b00000001, false, false, 0x68, 0x48, 0x48, "H         ", 0, 0, 0},                        // iic_byte  2 , byte 0b00000001 , line 14
        {old_keyboard, false, 2, 0b00000010, false, false, 0x67, 0x47, 0x47, "G         ", 0, 0, 0},                        // iic_byte  2 , byte 0b00000010 , line 15
        {old_keyboard, false, 2, 0b00000100, false, false, 0x66, 0x46, 0x46, "F         ", 0, 0, 0},                        // iic_byte  2 , byte 0b00000100 , line 16
        {old_keyboard, false, 2, 0b00001000, false, false, 0x64, 0x44, 0x44, "D         ", 0, 0, 0},                        // iic_byte  2 , byte 0b00001000 , line 17
        {old_keyboard, false, 2, 0b00010000, false, false, 0x73, 0x53, 0x53, "S         ", 0, 0, 0},                        // iic_byte  2 , byte 0b00010000 , line 18
        {old_keyboard, false, 2, 0b00100000, false, false, 0x61, 0x41, 0x41, "A         ", 0, 0, 0},                        // iic_byte  2 , byte 0b00100000 , line 19
        {old_keyboard, false, 2, 0b01000000, false, true, 0xC1, 0xC1, 0xC1, "CAPSLOCK  ", 0, 0, 0},                         // iic_byte  2 , byte 0b01000000 , line 20
        {old_keyboard, false, 3, 0b00000001, false, false, 0x79, 0x59, 0x59, "Y         ", 0, 0, 0},                        // iic_byte  3 , byte 0b00000001 , line 21
        {old_keyboard, false, 3, 0b00000010, false, false, 0x74, 0x54, 0x54, "T         ", 0, 0, 0},                        // iic_byte  3 , byte 0b00000010 , line 22
        {old_keyboard, false, 3, 0b00000100, false, false, 0x72, 0x52, 0x52, "R         ", 0, 0, 0},                        // iic_byte  3 , byte 0b00000100 , line 23
        {old_keyboard, false, 3, 0b00001000, false, false, 0x65, 0x45, 0x45, "E         ", 0, 0, 0},                        // iic_byte  3 , byte 0b00001000 , line 24
        {old_keyboard, false, 3, 0b00010000, false, false, 0x77, 0x57, 0x57, "W         ", 0, 0, 0},                        // iic_byte  3 , byte 0b00010000 , line 25
        {old_keyboard, false, 3, 0b00100000, false, false, 0x71, 0x51, 0x51, "Q         ", 0, 0, 0},                        // iic_byte  3 , byte 0b00100000 , line 26
        {old_keyboard, false, 3, 0b01000000, false, false, 0xB3, 0xB3, 0xB3, "TAB       ", 0, 0, 0},                        // iic_byte  3 , byte 0b01000000 , line 27
        {old_keyboard, false, 4, 0b00000001, false, false, 0x60, 0x7E, 0x60, "`/~       ", 0, 0, 0},                        // iic_byte  4 , byte 0b00000001 , line 28
        {old_keyboard, false, 4, 0b00000010, false, false, 0x00, 0x00, 0x00, "          ", 0, 0, 0},                        // iic_byte  4 , byte 0b00000010 , line 29
        {old_keyboard, false, 4, 0b00000100, false, false, 0x00, 0x00, 0x00, "          ", 0, 0, 0},                        // iic_byte  4 , byte 0b00000100 , line 30
        {old_keyboard, true, 4, 0b00001000, false, false, 0x05, 0x05, 0x05, "WHEEL_U   ", 0, 0, 0},                         // iic_byte  4 , byte 0b00001000 , line 31
        {old_keyboard, true, 4, 0b00010000, false, false, 0x01, 0x01, 0x01, "MOUSE_L   ", 0, 0, 0},                         // iic_byte  4 , byte 0b00010000 , line 32
        {old_keyboard, true, 4, 0b00100000, false, false, 0x02, 0x02, 0x02, "MOUSE_R   ", 0, 0, 0},                         // iic_byte  4 , byte 0b00100000 , line 33
        {old_keyboard, true, 4, 0b01000000, false, false, 0x06, 0x06, 0x06, "WHEEL_M   ", 0, 0, 0},                         // iic_byte  4 , byte 0b01000000 , line 34
        {old_keyboard, false, 5, 0b00000001, false, false, 0x31, 0x21, 0x31, "1/!       ", 0, 0, 0},                        // iic_byte  5 , byte 0b00000001 , line 35
        {old_keyboard, false, 5, 0b00000010, false, false, 0x33, 0x23, 0x33, "3/#       ", 0, 0, 0},                        // iic_byte  5 , byte 0b00000010 , line 36
        {old_keyboard, false, 5, 0b00000100, false, false, 0x35, 0x25, 0x35, "5/%       ", 0, 0, 0},                        // iic_byte  5 , byte 0b00000100 , line 37
        {old_keyboard, false, 5, 0b00001000, false, false, 0x37, 0x26, 0x37, "7/&       ", 0, 0, 0},                        // iic_byte  5 , byte 0b00001000 , line 38
        {old_keyboard, false, 5, 0b00010000, false, false, 0x39, 0x28, 0x39, "9/(       ", 0, 0, 0},                        // iic_byte  5 , byte 0b00010000 , line 39
        {old_keyboard, false, 5, 0b00100000, false, false, 0x2D, 0x5F, 0x2D, "-/_       ", 0, 0, 0},                        // iic_byte  5 , byte 0b00100000 , line 40
        {old_keyboard, false, 5, 0b01000000, false, false, 0xB2, 0xB2, 0xB2, "BACKSP    ", 0, 0, 0},                        // iic_byte  5 , byte 0b01000000 , line 41
        {old_keyboard, false, 6, 0b00000001, false, false, 0x32, 0x40, 0x32, "2/@       ", 0, 0, 0},                        // iic_byte  6 , byte 0b00000001 , line 42
        {old_keyboard, false, 6, 0b00000010, false, false, 0x34, 0x24, 0x34, "4/$       ", 0, 0, 0},                        // iic_byte  6 , byte 0b00000010 , line 43
        {old_keyboard, false, 6, 0b00000100, false, false, 0x36, 0x5E, 0x36, "6/^       ", 0, 0, 0},                        // iic_byte  6 , byte 0b00000100 , line 44
        {old_keyboard, false, 6, 0b00001000, false, false, 0x38, 0x2A, 0x38, "8/*       ", 0, 0, 0},                        // iic_byte  6 , byte 0b00001000 , line 45
        {old_keyboard, false, 6, 0b00010000, false, false, 0x30, 0x29, 0x30, "0/)       ", 0, 0, 0},                        // iic_byte  6 , byte 0b00010000 , line 46
        {old_keyboard, false, 6, 0b00100000, false, false, 0x3D, 0x2B, 0x3D, "=/+       ", 0, 0, 0},                        // iic_byte  6 , byte 0b00100000 , line 47
        {old_keyboard, false, 6, 0b01000000, false, false, 0xB1, 0xB1, 0xB1, "ESC       ", 0, 0, 0},                        // iic_byte  6 , byte 0b01000000 , line 48
        {old_keyboard, false, 7, 0b00000001, false, false, 0x75, 0x55, 0x55, "U         ", 0, 0, 0},                        // iic_byte  7 , byte 0b00000001 , line 49
        {old_keyboard, false, 7, 0b00000010, false, false, 0x69, 0x49, 0x49, "I         ", 0, 0, 0},                        // iic_byte  7 , byte 0b00000010 , line 50
        {old_keyboard, false, 7, 0b00000100, false, false, 0x6F, 0x4F, 0x4F, "O         ", 0, 0, 0},                        // iic_byte  7 , byte 0b00000100 , line 51
        {old_keyboard, false, 7, 0b00001000, false, false, 0x70, 0x50, 0x50, "P         ", 0, 0, 0},                        // iic_byte  7 , byte 0b00001000 , line 52
        {old_keyboard, false, 7, 0b00010000, false, false, 0x5B, 0x7B, 0x5B, "[/{       ", 0, 0, 0},                        // iic_byte  7 , byte 0b00010000 , line 53
        {old_keyboard, false, 7, 0b00100000, false, false, 0x5D, 0x7D, 0x5D, "]/}       ", 0, 0, 0},                        // iic_byte  7 , byte 0b00100000 , line 54
        {old_keyboard, false, 7, 0b01000000, false, false, 0xD4, 0xD4, 0xD4, "DELETE    ", 0, 0, 0},                        // iic_byte  7 , byte 0b01000000 , line 55
        {old_keyboard, false, 8, 0b00000001, false, false, 0x6A, 0x4A, 0x4A, "J         ", 0, 0, 0},                        // iic_byte  8 , byte 0b00000001 , line 56
        {old_keyboard, false, 8, 0b00000010, false, false, 0x6B, 0x4B, 0x4B, "K         ", 0, 0, 0},                        // iic_byte  8 , byte 0b00000010 , line 57
        {old_keyboard, false, 8, 0b00000100, false, false, 0x6C, 0x4C, 0x4C, "L         ", 0, 0, 0},                        // iic_byte  8 , byte 0b00000100 , line 58
        {old_keyboard, false, 8, 0b00001000, false, false, 0x3B, 0x3A, 0x3B, ";/:       ", 0, 0, 0},                        // iic_byte  8 , byte 0b00001000 , line 59
        {old_keyboard, false, 8, 0b00010000, false, false, 0x27, 0x22, 0x27, "'/\"      ", 0, 0, 0},                        // iic_byte  8 , byte 0b00010000 , line 60
        {old_keyboard, false, 8, 0b00100000, false, false, 0x5C, 0x7C, 0x5C, "\\/|      ", 0, 0, 0},                        // iic_byte  8 , byte 0b00100000 , line 61
        {old_keyboard, false, 8, 0b01000000, false, false, 0xE0, 0xE0, 0xE0, "ENTER     ", set_mode_function_ok, 0, 0},     // iic_byte  8 , byte 0b01000000 , line 62
        {old_keyboard, false, 9, 0b00000001, false, false, 0x6D, 0x4D, 0x4D, "M         ", 0, 0, 0},                        // iic_byte  9 , byte 0b00000001 , line 63
        {old_keyboard, false, 9, 0b00000010, false, false, 0x2C, 0x3C, 0x2C, ",/<       ", 0, 0, 0},                        // iic_byte  9 , byte 0b00000010 , line 64
        {old_keyboard, false, 9, 0b00000100, false, false, 0x2E, 0x3E, 0x2E, "./>       ", 0, 0, 0},                        // iic_byte  9 , byte 0b00000100 , line 65
        {old_keyboard, false, 9, 0b00001000, false, false, 0x2F, 0x3F, 0x2F, "//?       ", 0, 0, 0},                        // iic_byte  9 , byte 0b00001000 , line 66
        {old_keyboard, false, 9, 0b00010000, false, false, 0xDA, 0xDA, 0xDA, "UP        ", set_mode_function_up, 0, 0},     // iic_byte  9 , byte 0b00010000 , line 67
        {old_keyboard, false, 9, 0b00100000, true, false, 0x85, 0x85, 0x85, "SHIFT     ", 0, 0, 0},                         // iic_byte  9 , byte 0b00100000 , line 68
        {old_keyboard, false, 9, 0b01000000, false, false, 0xD2, 0xD2, 0xD2, "HOME      ", 0, 0, 0},                        // iic_byte  9 , byte 0b01000000 , line 69
        {old_keyboard, false, 10, 0b00000001, false, false, 0x86, 0x86, 0x86, "ALT       ", 0, 0, 0},                       // iic_byte 10 , byte 0b00000001 , line 70
        {old_keyboard, false, 10, 0b00000010, false, false, 0x84, 0x84, 0x84, "CTRL      ", 0, 0, 0},                       // iic_byte 10 , byte 0b00000010 , line 71
        {old_keyboard, false, 10, 0b00000100, false, false, 0x87, 0x87, 0x87, "GUI       ", 0, 0, 0},                       // iic_byte 10 , byte 0b00000100 , line 72
        {old_keyboard, false, 10, 0b00001000, false, false, 0xD8, 0xD8, 0xD8, "LEFT      ", set_mode_function_left, 0, 0},  // iic_byte 10 , byte 0b00001000 , line 73
        {old_keyboard, false, 10, 0b00010000, false, false, 0xD9, 0xD9, 0xD9, "DOWN      ", set_mode_function_down, 0, 0},  // iic_byte 10 , byte 0b00010000 , line 74
        {old_keyboard, false, 10, 0b00100000, false, false, 0xD7, 0xD7, 0xD7, "RIGHT     ", set_mode_function_right, 0, 0}, // iic_byte 10 , byte 0b00100000 , line 75
        {old_keyboard, false, 10, 0b01000000, false, false, 0xD5, 0xD5, 0xD5, "END       ", set_mode_function_back, 0, 0},  // iic_byte 10 , byte 0b01000000 , line 76

};
Key new_keyboard_key[new_keyboard_key_count] =
    {
        {new_keyboard, false, 0, 0b00000001, false, false, 0x20, 0x20, 0x20, "SPACE    ", 0, 0, 0},                        // iic_byte  0 , byte 0b00000001 , line  0
        {new_keyboard, false, 0, 0b00000010, false, false, 0x20, 0x20, 0x20, "SPACE    ", 0, 0, 0},                        // iic_byte  0 , byte 0b00000010 , line  1
        {new_keyboard, false, 0, 0b00000100, false, false, 0xD6, 0xD6, 0xD6, "PAGE_DN  ", 0, 0, 0},                        // iic_byte  0 , byte 0b00000100 , line  2
        {new_keyboard, false, 0, 0b00001000, false, false, 0xD3, 0xD3, 0xD3, "PAGE_UP  ", 0, 0, 0},                        // iic_byte  0 , byte 0b00001000 , line  3
        {new_keyboard, false, 0, 0b00010000, false, false, 0x82, 0x82, 0x82, "ALT      ", 0, 0, 0},                        // iic_byte  0 , byte 0b00010000 , line  4
        {new_keyboard, false, 0, 0b00100000, false, false, 0x83, 0x83, 0x83, "GUI      ", 0, 0, 0},                        // iic_byte  0 , byte 0b00100000 , line  5
        {new_keyboard, false, 0, 0b01000000, false, false, 0x80, 0x80, 0x80, "CTRL     ", 0, 0, 0},                        // iic_byte  0 , byte 0b01000000 , line  6
        {new_keyboard, false, 1, 0b00000001, false, false, 0x6E, 0x4E, 0x4E, "N        ", 0, 0, 0},                        // iic_byte  1 , byte 0b00000001 , line  7
        {new_keyboard, false, 1, 0b00000010, false, false, 0x62, 0x42, 0x42, "B        ", 0, 0, 0},                        // iic_byte  1 , byte 0b00000010 , line  8
        {new_keyboard, false, 1, 0b00000100, false, false, 0x76, 0x56, 0x56, "V        ", 0, 0, 0},                        // iic_byte  1 , byte 0b00000100 , line  9
        {new_keyboard, false, 1, 0b00001000, false, false, 0x63, 0x43, 0x43, "C        ", 0, 0, 0},                        // iic_byte  1 , byte 0b00001000 , line 10
        {new_keyboard, false, 1, 0b00010000, false, false, 0x78, 0x58, 0x58, "X        ", 0, 0, 0},                        // iic_byte  1 , byte 0b00010000 , line 11
        {new_keyboard, false, 1, 0b00100000, false, false, 0x7A, 0x5A, 0x5A, "Z        ", 0, 0, 0},                        // iic_byte  1 , byte 0b00100000 , line 12
        {new_keyboard, false, 1, 0b01000000, true, false, 0x81, 0x81, 0x81, "SHIFT    ", 0, 0, 0},                         // iic_byte  1 , byte 0b01000000 , line 13
        {new_keyboard, false, 2, 0b00000001, false, false, 0x68, 0x48, 0x48, "H        ", 0, 0, 0},                        // iic_byte  2 , byte 0b00000001 , line 14
        {new_keyboard, false, 2, 0b00000010, false, false, 0x67, 0x47, 0x47, "G        ", 0, 0, 0},                        // iic_byte  2 , byte 0b00000010 , line 15
        {new_keyboard, false, 2, 0b00000100, false, false, 0x66, 0x46, 0x46, "F        ", 0, 0, 0},                        // iic_byte  2 , byte 0b00000100 , line 16
        {new_keyboard, false, 2, 0b00001000, false, false, 0x64, 0x44, 0x44, "D        ", 0, 0, 0},                        // iic_byte  2 , byte 0b00001000 , line 17
        {new_keyboard, false, 2, 0b00010000, false, false, 0x73, 0x53, 0x53, "S        ", 0, 0, 0},                        // iic_byte  2 , byte 0b00010000 , line 18
        {new_keyboard, false, 2, 0b00100000, false, false, 0x61, 0x41, 0x41, "A        ", 0, 0, 0},                        // iic_byte  2 , byte 0b00100000 , line 19
        {new_keyboard, false, 2, 0b01000000, false, true, 0xC1, 0xC1, 0xC1, "CAPSLOCK ", 0, 0, 0},                         // iic_byte  2 , byte 0b01000000 , line 20
        {new_keyboard, false, 3, 0b00000001, false, false, 0x79, 0x59, 0x59, "Y        ", 0, 0, 0},                        // iic_byte  3 , byte 0b00000001 , line 21
        {new_keyboard, false, 3, 0b00000010, false, false, 0x74, 0x54, 0x54, "T        ", 0, 0, 0},                        // iic_byte  3 , byte 0b00000010 , line 22
        {new_keyboard, false, 3, 0b00000100, false, false, 0x72, 0x52, 0x52, "R        ", 0, 0, 0},                        // iic_byte  3 , byte 0b00000100 , line 23
        {new_keyboard, false, 3, 0b00001000, false, false, 0x65, 0x45, 0x45, "E        ", 0, 0, 0},                        // iic_byte  3 , byte 0b00001000 , line 24
        {new_keyboard, false, 3, 0b00010000, false, false, 0x77, 0x57, 0x57, "W        ", 0, 0, 0},                        // iic_byte  3 , byte 0b00010000 , line 25
        {new_keyboard, false, 3, 0b00100000, false, false, 0x71, 0x51, 0x51, "Q        ", 0, 0, 0},                        // iic_byte  3 , byte 0b00100000 , line 26
        {new_keyboard, false, 3, 0b01000000, false, false, 0xB3, 0xB3, 0xB3, "TAB      ", 0, 0, 0},                        // iic_byte  3 , byte 0b01000000 , line 27
        {new_keyboard, false, 4, 0b00000001, false, false, 0x36, 0x5E, 0x36, "6/^      ", 0, 0, 0},                        // iic_byte  4 , byte 0b00000001 , line 28
        {new_keyboard, false, 4, 0b00000010, false, false, 0x35, 0x25, 0x35, "5/%      ", 0, 0, 0},                        // iic_byte  4 , byte 0b00000010 , line 29
        {new_keyboard, false, 4, 0b00000100, false, false, 0x34, 0x24, 0x34, "4/$      ", 0, 0, 0},                        // iic_byte  4 , byte 0b00000100 , line 30
        {new_keyboard, false, 4, 0b00001000, false, false, 0x33, 0x23, 0x33, "3/#      ", 0, 0, 0},                        // iic_byte  4 , byte 0b00001000 , line 31
        {new_keyboard, false, 4, 0b00010000, false, false, 0x32, 0x40, 0x32, "2/@      ", 0, 0, 0},                        // iic_byte  4 , byte 0b00010000 , line 32
        {new_keyboard, false, 4, 0b00100000, false, false, 0x31, 0x21, 0x31, "1/!      ", 0, 0, 0},                        // iic_byte  4 , byte 0b00100000 , line 33
        {new_keyboard, false, 4, 0b01000000, false, false, 0x60, 0x7E, 0x60, "`/~      ", 0, 0, 0},                        // iic_byte  4 , byte 0b01000000 , line 34
        {new_keyboard, false, 5, 0b00000001, false, false, 0xC8, 0xC8, 0xC8, "F7       ", 0, 0, 0},                        // iic_byte  5 , byte 0b00000001 , line 35
        {new_keyboard, false, 5, 0b00000010, false, false, 0x2D, 0x5F, 0x2D, "-/_      ", 0, 0, 0},                        // iic_byte  5 , byte 0b00000010 , line 36
        {new_keyboard, false, 5, 0b00000100, false, false, 0x3D, 0x2B, 0x3D, "=/+      ", 0, 0, 0},                        // iic_byte  5 , byte 0b00000100 , line 37
        {new_keyboard, false, 5, 0b00001000, false, false, 0xB2, 0xB2, 0xB2, "BACKSP   ", 0, 0, 0},                        // iic_byte  5 , byte 0b00001000 , line 38
        {new_keyboard, false, 5, 0b00010000, false, false, 0x00, 0x00, 0x00, "         ", 0, 0, 0},                        // iic_byte  5 , byte 0b00010000 , line 39
        {new_keyboard, false, 5, 0b00100000, false, false, 0x00, 0x00, 0x00, "         ", 0, 0, 0},                        // iic_byte  5 , byte 0b00100000 , line 40
        {new_keyboard, false, 5, 0b01000000, false, false, 0x00, 0x00, 0x00, "         ", 0, 0, 0},                        // iic_byte  5 , byte 0b01000000 , line 41
        {new_keyboard, false, 6, 0b00000001, false, false, 0x37, 0x26, 0x37, "7/&      ", 0, 0, 0},                        // iic_byte  6 , byte 0b00000001 , line 42
        {new_keyboard, false, 6, 0b00000010, false, false, 0x38, 0x2A, 0x38, "8/*      ", 0, 0, 0},                        // iic_byte  6 , byte 0b00000010 , line 43
        {new_keyboard, false, 6, 0b00000100, false, false, 0x39, 0x28, 0x39, "9/(      ", 0, 0, 0},                        // iic_byte  6 , byte 0b00000100 , line 44
        {new_keyboard, false, 6, 0b00001000, false, false, 0x30, 0x29, 0x30, "0/)      ", 0, 0, 0},                        // iic_byte  6 , byte 0b00001000 , line 45
        {new_keyboard, true, 6, 0b00010000, false, false, 0x01, 0x01, 0x01, "MOUSE_L  ", 0, 0, 0},                         // iic_byte  6 , byte 0b00010000 , line 46
        {new_keyboard, false, 6, 0b00100000, false, false, 0x00, 0x00, 0x00, "         ", 0, 0, 0},                        // iic_byte  6 , byte 0b00100000 , line 47
        {new_keyboard, true, 6, 0b01000000, false, false, 0x02, 0x02, 0x02, "MOUSE_R  ", 0, 0, 0},                         // iic_byte  6 , byte 0b01000000 , line 48
        {new_keyboard, false, 7, 0b00000001, false, false, 0x75, 0x55, 0x55, "U        ", 0, 0, 0},                        // iic_byte  7 , byte 0b00000001 , line 49
        {new_keyboard, false, 7, 0b00000010, false, false, 0x69, 0x49, 0x49, "I        ", 0, 0, 0},                        // iic_byte  7 , byte 0b00000010 , line 50
        {new_keyboard, false, 7, 0b00000100, false, false, 0x6F, 0x4F, 0x4F, "O        ", 0, 0, 0},                        // iic_byte  7 , byte 0b00000100 , line 51
        {new_keyboard, false, 7, 0b00001000, false, false, 0x70, 0x50, 0x50, "P        ", 0, 0, 0},                        // iic_byte  7 , byte 0b00001000 , line 52
        {new_keyboard, false, 7, 0b00010000, false, false, 0x5B, 0x7B, 0x5B, "[/{      ", 0, 0, 0},                        // iic_byte  7 , byte 0b00010000 , line 53
        {new_keyboard, false, 7, 0b00100000, false, false, 0x5D, 0x7D, 0x5D, "]/}      ", 0, 0, 0},                        // iic_byte  7 , byte 0b00100000 , line 54
        {new_keyboard, false, 7, 0b01000000, false, false, 0xD4, 0xD4, 0xD4, "DELETE   ", 0, 0, 0},                        // iic_byte  7 , byte 0b01000000 , line 55
        {new_keyboard, false, 8, 0b00000001, false, false, 0x6A, 0x4A, 0x4A, "J        ", 0, 0, 0},                        // iic_byte  8 , byte 0b00000001 , line 56
        {new_keyboard, false, 8, 0b00000010, false, false, 0x6B, 0x4B, 0x4B, "K        ", 0, 0, 0},                        // iic_byte  8 , byte 0b00000010 , line 57
        {new_keyboard, false, 8, 0b00000100, false, false, 0x6C, 0x4C, 0x4C, "L        ", 0, 0, 0},                        // iic_byte  8 , byte 0b00000100 , line 58
        {new_keyboard, false, 8, 0b00001000, false, false, 0x3B, 0x3A, 0x3B, ";/:      ", 0, 0, 0},                        // iic_byte  8 , byte 0b00001000 , line 59
        {new_keyboard, false, 8, 0b00010000, false, false, 0x27, 0x22, 0x27, "'/\"     ", 0, 0, 0},                        // iic_byte  8 , byte 0b00010000 , line 60
        {new_keyboard, false, 8, 0b00100000, false, false, 0x5C, 0x7C, 0x5C, "\\/|     ", 0, 0, 0},                        // iic_byte  8 , byte 0b00100000 , line 61
        {new_keyboard, false, 8, 0b01000000, false, false, 0xE0, 0xE0, 0xE0, "ENTER    ", set_mode_function_ok, 0, 0},     // iic_byte  8 , byte 0b01000000 , line 62
        {new_keyboard, false, 9, 0b00000001, false, false, 0x6D, 0x4D, 0x4D, "M        ", 0, 0, 0},                        // iic_byte  9 , byte 0b00000001 , line 63
        {new_keyboard, false, 9, 0b00000010, false, false, 0x2C, 0x3C, 0x2C, ",/<      ", 0, 0, 0},                        // iic_byte  9 , byte 0b00000010 , line 64
        {new_keyboard, false, 9, 0b00000100, false, false, 0x2E, 0x3E, 0x2E, "./>      ", 0, 0, 0},                        // iic_byte  9 , byte 0b00000100 , line 65
        {new_keyboard, false, 9, 0b00001000, false, false, 0x2F, 0x3F, 0x2F, "//?      ", 0, 0, 0},                        // iic_byte  9 , byte 0b00001000 , line 66
        {new_keyboard, false, 9, 0b00010000, false, false, 0xDA, 0xDA, 0xDA, "UP       ", set_mode_function_up, 0, 0},     // iic_byte  9 , byte 0b00010000 , line 67
        {new_keyboard, false, 9, 0b00100000, true, false, 0x85, 0x85, 0x85, "SHIFT    ", 0, 0, 0},                         // iic_byte  9 , byte 0b00100000 , line 68
        {new_keyboard, false, 9, 0b01000000, false, false, 0xD2, 0xD2, 0xD2, "HOME     ", 0, 0, 0},                        // iic_byte  9 , byte 0b01000000 , line 69
        {new_keyboard, false, 10, 0b00000001, false, false, 0x86, 0x86, 0x86, "ALT      ", 0, 0, 0},                       // iic_byte 10 , byte 0b00000001 , line 70
        {new_keyboard, false, 10, 0b00000010, false, false, 0x84, 0x84, 0x84, "CTRL     ", 0, 0, 0},                       // iic_byte 10 , byte 0b00000010 , line 71
        {new_keyboard, false, 10, 0b00000100, false, false, 0x87, 0x87, 0x87, "GUI      ", 0, 0, 0},                       // iic_byte 10 , byte 0b00000100 , line 72
        {new_keyboard, false, 10, 0b00001000, false, false, 0xD8, 0xD8, 0xD8, "LEFT     ", set_mode_function_left, 0, 0},  // iic_byte 10 , byte 0b00001000 , line 73
        {new_keyboard, false, 10, 0b00010000, false, false, 0xD9, 0xD9, 0xD9, "DOWN     ", set_mode_function_down, 0, 0},  // iic_byte 10 , byte 0b00010000 , line 74
        {new_keyboard, false, 10, 0b00100000, false, false, 0xD7, 0xD7, 0xD7, "RIGHT    ", set_mode_function_right, 0, 0}, // iic_byte 10 , byte 0b00100000 , line 75
        {new_keyboard, false, 10, 0b01000000, false, false, 0xD5, 0xD5, 0xD5, "END      ", set_mode_function_back, 0, 0},  // iic_byte 10 , byte 0b01000000 , line 76
        {new_keyboard, false, 11, 0b00000001, false, false, 0xC7, 0xC7, 0xC7, "F6       ", 0, 0, 0},                       // iic_byte 11 , byte 0b00000001 , line 77
        {new_keyboard, false, 11, 0b00000010, false, false, 0xC6, 0xC6, 0xC6, "F5       ", 0, 0, 0},                       // iic_byte 11 , byte 0b00000010 , line 78
        {new_keyboard, false, 11, 0b00000100, false, false, 0xC5, 0xC5, 0xC5, "F4       ", 0, 0, 0},                       // iic_byte 11 , byte 0b00000100 , line 79
        {new_keyboard, false, 11, 0b00001000, false, false, 0xC4, 0xC4, 0xC4, "F3       ", 0, 0, 0},                       // iic_byte 11 , byte 0b00001000 , line 80
        {new_keyboard, false, 11, 0b00010000, false, false, 0xC3, 0xC3, 0xC3, "F2       ", 0, 0, 0},                       // iic_byte 11 , byte 0b00010000 , line 81
        {new_keyboard, false, 11, 0b00100000, false, false, 0xC2, 0xC2, 0xC2, "F1       ", 0, 0, 0},                       // iic_byte 11 , byte 0b00100000 , line 82
        {new_keyboard, false, 11, 0b01000000, false, false, 0xB1, 0xB1, 0xB1, "ESC      ", 0, 0, 0},                       // iic_byte 11 , byte 0b01000000 , line 83

};

bool IIC_Keyboard::begin()
{
    Keyboard.begin();
    delay(1);
    Mouse.begin();
    find_keyboard_type();
    return true;
}
bool IIC_Keyboard::is_usb_ready()
{

    return false;
}
uint8_t IIC_Keyboard::find_keyboard_type()
{
#if debug
    debug_serial.println("Finding keyboard type...");
#endif
    keyboard_address_1_slot = 0;
    keyboard_address_2_slot = 0;
    keyboard_address_3_slot = 0;

    bool device_detected = false;
    Wire1.beginTransmission(old_keyboard_iic_address);
    device_detected = !Wire1.endTransmission();
    if (device_detected)
    {
        get_buffer(old_keyboard_iic_address);
        if (iic_buffer[keyboard_iic_length - 1] == new_keyboard_crc)
        {
            keyboard_address_1_slot = new_keyboard_old_program;
#if debug
            debug_serial.println("New keyboard with old program detected at old keyboard address");
#endif
        }
        else if (iic_buffer[keyboard_iic_length - 1] == new_keyboard_with_new_program_crc)
        {
            keyboard_address_1_slot = new_keyboard_new_program;
#if debug
            debug_serial.println("New keyboard with new program detected at old keyboard address");
#endif
        }
        else if (iic_buffer[keyboard_iic_length - 1] == old_keyboard_crc)
        {
            keyboard_address_1_slot = old_keyboard;
#if debug
            debug_serial.println("Old keyboard detected at old keyboard address");
#endif
        }
    }
    Wire1.beginTransmission(new_keyboard_iic_address);
    device_detected = !Wire1.endTransmission();
    if (device_detected)
    {
        get_buffer(new_keyboard_iic_address);
        if (iic_buffer[keyboard_iic_length - 1] == new_keyboard_crc)
        {
            keyboard_address_2_slot = new_keyboard_old_program;
#if debug
            debug_serial.println("New keyboard with old program detected at new keyboard address");
#endif
        }
        else if (iic_buffer[keyboard_iic_length - 1] == new_keyboard_with_new_program_crc)
        {
            keyboard_address_2_slot = new_keyboard_new_program;
#if debug
            debug_serial.println("New keyboard with new program detected at new keyboard address");
#endif
        }
        else if (iic_buffer[keyboard_iic_length - 1] == old_keyboard_crc)
        {
            keyboard_address_2_slot = old_keyboard;
#if debug
            debug_serial.println("Old keyboard detected at new keyboard address");
#endif
        }
    }
    Wire1.beginTransmission(new_keyboard_with_new_program_iic_address);
    device_detected = !Wire1.endTransmission();
    if (device_detected)
    {
        get_buffer(new_keyboard_with_new_program_iic_address);
        if (iic_buffer[keyboard_iic_length - 1] == new_keyboard_crc)
        {
            keyboard_address_3_slot = new_keyboard_old_program;
#if debug
            debug_serial.println("New keyboard with old program detected at new keyboard with new program address");
#endif
        }
        else if (iic_buffer[keyboard_iic_length - 1] == new_keyboard_with_new_program_crc)
        {
            keyboard_address_3_slot = new_keyboard_new_program;
#if debug
            debug_serial.println("New keyboard with new program detected at new keyboard with new program address");
#endif
        }
        else if (iic_buffer[keyboard_iic_length - 1] == old_keyboard_crc)
        {
            keyboard_address_3_slot = old_keyboard;
#if debug
            debug_serial.println("Old keyboard detected at new keyboard with new program address");
#endif
        }
    }
#if debug
    debug_serial.println("Keyboard type detection complete.");
    if (keyboard_address_1_slot == 0 && keyboard_address_2_slot == 0 && keyboard_address_3_slot == 0)
    {
        debug_serial.println("No keyboard detected on any address.");
    }
    else
    {
        if (keyboard_address_1_slot != 0)
        {
            debug_serial.print("Keyboard detected at address 1 slot: ");
            debug_serial.println(keyboard_address_1_slot);
        }
        if (keyboard_address_2_slot != 0)
        {
            debug_serial.print("Keyboard detected at address 2 slot: ");
            debug_serial.println(keyboard_address_2_slot);
        }
        if (keyboard_address_3_slot != 0)
        {
            debug_serial.print("Keyboard detected at address 3 slot: ");
            debug_serial.println(keyboard_address_3_slot);
        }
    }
    debug_serial.println("Keyboard type detection finished.");
    debug_serial.println("--------------------------------------------------");
#endif

    return 0;
}

uint8_t IIC_Keyboard::routine()
{
#if debug
    debug_serial.println("IIC_Keyboard routine start");
#endif
    read_serial();
    if (keyboard_address_1_slot)
    {
        if (keyboard_address_1_slot == old_keyboard)
        {
            if (get_buffer(old_keyboard_iic_address))
            {
                old_keyboard_routine();
            }
            else
            {
#if debug
                debug_serial.println("Failed to get buffer from old keyboard at address 1 slot");
#endif
                keyboard_address_1_slot = 0;
            }
        }
        else if (keyboard_address_1_slot == new_keyboard_old_program)
        {
            if (get_buffer(old_keyboard_iic_address))
            {
                new_keyboard_routine();
            }
            else
            {
#if debug
                debug_serial.println("Failed to get buffer from new keyboard with old program at address 1 slot");
#endif
                keyboard_address_1_slot = 0;
            }
        }
        else if (keyboard_address_1_slot == new_keyboard_new_program)
        {
            if (digitalRead(keyboard_int))
            {
#if debug
                debug_serial.println("Keyboard interrupt detected, running new keyboard with new program routine");
#endif
                if (get_buffer(old_keyboard_iic_address))
                {
                    new_keyboard_routine();
                    for (int i = 0; i < keyboard_iic_length; i++)
                    {
                        iic_buffer_new_keyboard_last_time[i] = iic_buffer[i];
                    }
                }
                else
                {
#if debug
                    debug_serial.println("Failed to get buffer from new keyboard with new program at address 1 slot");
#endif
                    keyboard_address_1_slot = 0;
                }
            }
            else
            {
#if debug
                debug_serial.println("No keyboard interrupt detected, skipping new keyboard with new program routine");
#endif
            }
        }
        else
        {
#if debug
            debug_serial.println("Unknown keyboard type detected at address 1 slot, skipping routine");
#endif
            keyboard_address_1_slot = 0;
        }
    }
   if (keyboard_address_2_slot)
    {
        if (keyboard_address_2_slot == old_keyboard)
        {
            if (get_buffer(new_keyboard_iic_address))
            {
                old_keyboard_routine();
            }
            else
            {
#if debug
                debug_serial.println("Failed to get buffer from old keyboard at address 2 slot");
#endif
                keyboard_address_2_slot = 0;
            }
        }
        else if (keyboard_address_2_slot == new_keyboard_old_program)
        {
            if (get_buffer(new_keyboard_iic_address))
            {
                new_keyboard_routine();
            }
            else
            {
#if debug
                debug_serial.println("Failed to get buffer from new keyboard with old program at address 2 slot");
#endif
                keyboard_address_2_slot = 0;
            }
        }
        else if (keyboard_address_2_slot == new_keyboard_new_program)
        {
            if (digitalRead(keyboard_int))
            {
#if debug
                debug_serial.println("Keyboard interrupt detected, running new keyboard with new program routine");
#endif
                if (get_buffer(new_keyboard_iic_address))
                {
                    new_keyboard_routine();
                    for (int i = 0; i < keyboard_iic_length; i++)
                    {
                        iic_buffer_new_keyboard_last_time[i] = iic_buffer[i];
                    }
                }
                else
                {
#if debug
                    debug_serial.println("Failed to get buffer from new keyboard with new program at address 2 slot");
#endif
                    keyboard_address_2_slot = 0;
                }
            }
        }
        else
        {
#if debug
            debug_serial.println("No keyboard interrupt detected, skipping new keyboard with new program routine");
#endif
            keyboard_address_2_slot = 0;
        }
    }
    if (keyboard_address_3_slot)
    {
        if (keyboard_address_3_slot == old_keyboard)
        {
            if (get_buffer(new_keyboard_with_new_program_iic_address))
            {
                old_keyboard_routine();
            }
            else
            {
#if debug
                debug_serial.println("Failed to get buffer from old keyboard at address 3 slot");
#endif
                keyboard_address_3_slot = 0;
            }
        }
        else if (keyboard_address_3_slot == new_keyboard_old_program)
        {
            if (get_buffer(new_keyboard_with_new_program_iic_address))
            {
                new_keyboard_routine();
            }
            else
            {
#if debug
                debug_serial.println("Failed to get buffer from new keyboard with old program at address 3 slot");
#endif
                keyboard_address_3_slot = 0;
            }
        }
        else if (keyboard_address_3_slot == new_keyboard_new_program)
        {
            if (digitalRead(keyboard_int))
            {
#if debug
                debug_serial.println("Keyboard interrupt detected, running new keyboard with new program routine");
#endif
                if (get_buffer(new_keyboard_with_new_program_iic_address))
                {
                    new_keyboard_routine();
                }
                else
                {
#if debug
                    debug_serial.println("Failed to get buffer from new keyboard with new program at address 3 slot");
#endif
                    keyboard_address_3_slot = 0;
                }
            }
        }
        else
        {
#if debug
            debug_serial.println("Unknown keyboard type detected at address 3 slot, skipping routine");
#endif
            keyboard_address_3_slot = 0;
        }
    }
    if(keyboard_address_1_slot == 0 && keyboard_address_2_slot == 0 && keyboard_address_3_slot == 0)
    {
        find_keyboard_type();
    }
#if debug
    debug_serial.println("IIC_Keyboard routine end");
    // delay(5000);
#endif
    return true;
}

bool IIC_Keyboard::get_buffer(uint8_t address)
{
#if debug
    debug_serial.print("Getting IIC buffer from address ");
    if (address == old_keyboard_iic_address)
    {
        debug_serial.print("old_keyboard_iic_address: ");
    }
    else if (address == new_keyboard_iic_address)
    {
        debug_serial.print("new_keyboard_iic_address: ");
    }
    else if (address == new_keyboard_with_new_program_iic_address)
    {
        debug_serial.print("new_keyboard_with_new_program_iic_address: ");
    }
    debug_serial.println(address, HEX);
#endif
    uint8_t iic_length = Wire1.requestFrom(address, keyboard_iic_length);
#if debug
    debug_serial.print("IIC requestFrom returned ");
    debug_serial.print(iic_length);
    debug_serial.println(" bytes, expected ");
#endif
    for (int i = 0; i < keyboard_iic_length; i++)
    {
        if (Wire1.available())
        {
            iic_buffer[i] = Wire1.read();
        }
        else
        {
            iic_buffer[i] = 0;
#if debug
            debug_serial.print("IIC read error: expected ");
            debug_serial.print(keyboard_iic_length);
            debug_serial.print(" bytes but only ");
            debug_serial.print(i);
            debug_serial.println(" bytes available");
#endif
            return false;
        }
    }
#if debug
    /*debug_serial.print("IIC buffer in HEX: ");
    for (int i = 0; i < keyboard_iic_length; i++)
    {
        debug_serial.print(iic_buffer[i], HEX);
        debug_serial.print(" * ");
    }
    debug_serial.println();
    debug_serial.print("IIC buffer in BIN: ");
    for (int i = 0; i < keyboard_iic_length; i++)
    {
        debug_serial.print(iic_buffer[i], BIN);
        debug_serial.print(" * ");
    }
    debug_serial.println();*/
    debug_serial.print("IIC buffer in DEC: ");
    for (int i = 0; i < keyboard_iic_length; i++)
    {
        debug_serial.print(iic_buffer[i], DEC);
        debug_serial.print(" * ");
    }
    debug_serial.println();
#endif
    if (iic_buffer[keyboard_iic_length - 1] == old_keyboard_crc || iic_buffer[keyboard_iic_length - 1] == new_keyboard_crc || iic_buffer[keyboard_iic_length - 1] == new_keyboard_with_new_program_crc)
    {
        #if debug
        debug_serial.println("IIC buffer CRC check passed");
        #endif
        return true;
    }

    return false;
}
uint8_t IIC_Keyboard::old_keyboard_routine()
{
    if (iic_buffer[keyboard_iic_length - 1] != old_keyboard_crc)
    {
#if debug
        debug_serial.println("Old keyboard CRC error in old_keyboard_routine");
#endif
        return false;
    }
    if (iic_buffer[old_keyboard_set_mode_byte] == old_keyboard_set_mode_value)
    {
        system_status.ssd1306_mode = iic_display_set_mode;
#if debug
        debug_serial.println("setting Mode,dont run old keyboard routine");
#endif
        return old_keyboard_set_mode_value;
    }
    int mouse_x = iic_buffer[0];
    int mouse_y = iic_buffer[1];
    if (mouse_x != 128 || mouse_y != 128)
    {
        Mouse.move((mouse_x - 128) * mouse_sensitivity, (mouse_y - 128) * mouse_sensitivity);
        system_status.mouse_x = mouse_x - 128;
        system_status.mouse_y = mouse_y - 128;
    }

    for (int i = 3; i < keyboard_iic_length - 1; i++)
    {
        uint8_t diff = iic_buffer[i] ^ iic_buffer_old_keyboard_last_time[i];
        if (diff)
        {
            for (int j = 0; j < 7; j++)
            {
                if (diff & (1 << j))
                {
                    uint8_t key_index = (i - 3) * 7 + 6 - j;
                    if (key_index >= old_keyboard_key_count)
                    {
#if debug
                        debug_serial.print("WARNING: key_index ");
                        debug_serial.print(key_index);
                        debug_serial.print(" exceeds array size ");
                        debug_serial.println(old_keyboard_key_count);
#endif
                        continue; // 跳过这个按键
                    }
                    old_keyboard_key[key_index].press_or_release = (iic_buffer[i] & (1 << j)) ? press_ : release_;
#if debug
                    debug_serial.print("Key index: ");
                    debug_serial.print(key_index);
                    debug_serial.print(" Key value: ");
                    debug_serial.print(old_keyboard_key[key_index].key_value, HEX);
                    debug_serial.print(" Key value with shift: ");
                    debug_serial.print(old_keyboard_key[key_index].key_value_shift, HEX);
                    debug_serial.print(" Key value with capslock: ");
                    debug_serial.print(old_keyboard_key[key_index].key_value_capslock, HEX);
                    debug_serial.print(" Key massage : ");
                    debug_serial.print(old_keyboard_key[key_index].key_debug[0]);
                    debug_serial.print(old_keyboard_key[key_index].key_debug[1]);
                    debug_serial.print(old_keyboard_key[key_index].key_debug[2]);
                    debug_serial.print(old_keyboard_key[key_index].key_debug[3]);
                    debug_serial.print(old_keyboard_key[key_index].key_debug[4]);
                    debug_serial.print(old_keyboard_key[key_index].key_debug[5]);
                    debug_serial.print(old_keyboard_key[key_index].key_debug[6]);
                    debug_serial.print(old_keyboard_key[key_index].key_debug[7]);
                    debug_serial.print(old_keyboard_key[key_index].key_debug[8]);
                    debug_serial.print(old_keyboard_key[key_index].key_debug[9]);
                    debug_serial.print(old_keyboard_key[key_index].key_debug[10]);
                    debug_serial.print(old_keyboard_key[key_index].key_debug[11]);
                    debug_serial.print(old_keyboard_key[key_index].key_debug[12]);
                    debug_serial.print(old_keyboard_key[key_index].key_debug[13]);
                    debug_serial.print(old_keyboard_key[key_index].key_debug[14]);
                    debug_serial.print(old_keyboard_key[key_index].key_debug[15]);
                    debug_serial.print(" Press or release: ");
                    debug_serial.print(old_keyboard_key[key_index].press_or_release ? "Release" : "Press");
                    debug_serial.println();
#endif
                    if (!old_keyboard_key[key_index].mouse_or_keyboard)
                    {
                        if (old_keyboard_key[key_index].is_shift && old_keyboard_key[key_index].press_or_release)
                        {
                            shift_status = true;
                            system_status.shift_status = shift_status;
                        }
                        if (old_keyboard_key[key_index].is_shift && !old_keyboard_key[key_index].press_or_release)
                        {
                            shift_status = false;
                            system_status.shift_status = shift_status;
                        }
                        if (old_keyboard_key[key_index].is_capslock && old_keyboard_key[key_index].press_or_release)
                        {
                            capsLock_status = !capsLock_status;
                            system_status.capslock_status = capsLock_status;
                        }
                        if (old_keyboard_key[key_index].press_or_release)
                        {
#if debug
                            debug_serial.print("press : ");
                            debug_serial.print(old_keyboard_key[key_index].key_debug[0]);
                            debug_serial.print(old_keyboard_key[key_index].key_debug[1]);
                            debug_serial.print(old_keyboard_key[key_index].key_debug[2]);
                            debug_serial.print(old_keyboard_key[key_index].key_debug[3]);
                            debug_serial.print(old_keyboard_key[key_index].key_debug[4]);
                            debug_serial.print(old_keyboard_key[key_index].key_debug[5]);
                            debug_serial.print(old_keyboard_key[key_index].key_debug[6]);
                            debug_serial.print(old_keyboard_key[key_index].key_debug[7]);
                            debug_serial.print(old_keyboard_key[key_index].key_debug[8]);
                            debug_serial.print(old_keyboard_key[key_index].key_debug[9]);
                            debug_serial.print(old_keyboard_key[key_index].key_debug[10]);
                            debug_serial.print(old_keyboard_key[key_index].key_debug[11]);
                            debug_serial.print(old_keyboard_key[key_index].key_debug[12]);
                            debug_serial.print(old_keyboard_key[key_index].key_debug[13]);
                            debug_serial.print(old_keyboard_key[key_index].key_debug[14]);
                            debug_serial.print(old_keyboard_key[key_index].key_debug[15]);
                            debug_serial.println();
#endif
                            if (shift_status && capsLock_status)
                            {
                                Keyboard.press(old_keyboard_key[key_index].key_value);
                            }
                            else if (shift_status && !capsLock_status)
                            {
                                Keyboard.press(old_keyboard_key[key_index].key_value_shift);
                            }
                            else if (!shift_status && capsLock_status)
                            {
                                Keyboard.press(old_keyboard_key[key_index].key_value);
                            }
                            else
                            {
                                Keyboard.press(old_keyboard_key[key_index].key_value);
                            }
                        }
                        else
                        {
#if debug
                            debug_serial.print("release : ");
                            debug_serial.print(old_keyboard_key[key_index].key_debug[0]);
                            debug_serial.print(old_keyboard_key[key_index].key_debug[1]);
                            debug_serial.print(old_keyboard_key[key_index].key_debug[2]);
                            debug_serial.print(old_keyboard_key[key_index].key_debug[3]);
                            debug_serial.print(old_keyboard_key[key_index].key_debug[4]);
                            debug_serial.print(old_keyboard_key[key_index].key_debug[5]);
                            debug_serial.print(old_keyboard_key[key_index].key_debug[6]);
                            debug_serial.print(old_keyboard_key[key_index].key_debug[7]);
                            debug_serial.print(old_keyboard_key[key_index].key_debug[8]);
                            debug_serial.print(old_keyboard_key[key_index].key_debug[9]);
                            debug_serial.print(old_keyboard_key[key_index].key_debug[10]);
                            debug_serial.print(old_keyboard_key[key_index].key_debug[11]);
                            debug_serial.print(old_keyboard_key[key_index].key_debug[12]);
                            debug_serial.print(old_keyboard_key[key_index].key_debug[13]);
                            debug_serial.print(old_keyboard_key[key_index].key_debug[14]);
                            debug_serial.print(old_keyboard_key[key_index].key_debug[15]);
                            debug_serial.println();
#endif
                            if (shift_status && capsLock_status)
                            {
                                Keyboard.release(old_keyboard_key[key_index].key_value);
                                system_status.last_key_value = old_keyboard_key[key_index].key_value;
                                system_status.last_key_index = key_index;
                                if (old_keyboard_key[key_index].set_function)
                                {
                                    system_status.ssd1306_set_instruction = old_keyboard_key[key_index].set_function;
                                }
                            }
                            else if (shift_status && !capsLock_status)
                            {
                                Keyboard.release(old_keyboard_key[key_index].key_value_shift);
                                system_status.last_key_value = old_keyboard_key[key_index].key_value_shift;
                                system_status.last_key_index = key_index;
                                if (old_keyboard_key[key_index].set_function)
                                {
                                    system_status.ssd1306_set_instruction = old_keyboard_key[key_index].set_function;
                                }
                            }
                            else if (!shift_status && capsLock_status)
                            {
                                Keyboard.release(old_keyboard_key[key_index].key_value);
                                system_status.last_key_value = old_keyboard_key[key_index].key_value_capslock;
                                system_status.last_key_index = key_index;
                                if (old_keyboard_key[key_index].set_function)
                                {
                                    system_status.ssd1306_set_instruction = old_keyboard_key[key_index].set_function;
                                }
                            }
                            else
                            {
                                Keyboard.release(old_keyboard_key[key_index].key_value);
                                system_status.last_key_value = old_keyboard_key[key_index].key_value;
                                system_status.last_key_index = key_index;
                                if (old_keyboard_key[key_index].set_function)
                                {
                                    system_status.ssd1306_set_instruction = old_keyboard_key[key_index].set_function;
                                }
                            }
                        }
                    }
                    else
                    {
                        if (old_keyboard_key[key_index].press_or_release)
                        {
                            Mouse.press(old_keyboard_key[key_index].key_value);
                        }
                        else
                        {
                            Mouse.release(old_keyboard_key[key_index].key_value);
                            system_status.last_key_value = old_keyboard_key[key_index].key_value;
                            system_status.last_key_index = key_index;
                            if (old_keyboard_key[key_index].set_function)
                            {
                                system_status.ssd1306_set_instruction = old_keyboard_key[key_index].set_function;
                            }
                        }
                    }
                    old_keyboard_key[key_index].last_time_status = old_keyboard_key[key_index].press_or_release;
                }
            }

            iic_buffer_old_keyboard_last_time[i] = iic_buffer[i];
        }
    }
    return 1;
}
uint8_t IIC_Keyboard::new_keyboard_routine()
{
    if (iic_buffer[keyboard_iic_length - 1] != new_keyboard_crc && iic_buffer[keyboard_iic_length - 1] != new_keyboard_with_new_program_crc)
    {
#if debug
        debug_serial.println("New keyboard CRC error in new_keyboard_routine");
#endif
        return false;
    }
    if (iic_buffer[new_keyboard_set_mode_byte] == new_keyboard_set_mode_value)
    {
        system_status.ssd1306_mode = iic_display_set_mode;
#if debug
        debug_serial.println("setting Mode,dont run new keyboard routine");
#endif
    }
    uint8_t d = iic_buffer[0];
    if (d)
    {
        for (int i = 0; i < 16; i++)
        {
            if (d == mouse_direction[i])
            {
                Mouse.move(new_keyboard_angle_cos_x[i] * mouse_sensitivity, new_keyboard_angle_sin_y[i] * mouse_sensitivity);
                system_status.mouse_x = new_keyboard_angle_cos_x[i];
                system_status.mouse_y = new_keyboard_angle_sin_y[i];
#if debug
                debug_serial.print("Mouse move direction: ");
                debug_serial.print("x: ");
                debug_serial.print(new_keyboard_angle_cos_x[i] * mouse_sensitivity);
                debug_serial.print(" y: ");
                debug_serial.println(new_keyboard_angle_sin_y[i] * mouse_sensitivity);
                debug_serial.println();
#endif
                break;
            }
        }
    }

    for (int i = 2; i < keyboard_iic_length - 1; i++)
    {
        if (iic_buffer_new_keyboard_last_time[i] != iic_buffer[i])
        {
            uint8_t diff = iic_buffer[i] ^ iic_buffer_new_keyboard_last_time[i];
            for (int j = 0; j < 7; j++)
            {
                if (diff & (1 << j))
                {

                    uint8_t key_index = 6 - j + (i - 2) * 7;
#if debug
                    debug_serial.print("key_index : ");
                    debug_serial.println(key_index);
#endif
                    /* if (key_index >= new_keyboard_key_count)
                     {
 #if debug
                         debug_serial.print("WARNING: key_index ");
                         debug_serial.print(key_index);
                         debug_serial.print(" exceeds array size ");
                         debug_serial.println(old_keyboard_key_count);
 #endif
                         continue;
                     }*/
                    new_keyboard_key[key_index].press_or_release = (iic_buffer[i] & (1 << j)) ? press_ : release_;
#if debug
                    debug_serial.print("Key index: ");
                    debug_serial.print(key_index);
                    debug_serial.print(" Key value: ");
                    debug_serial.print(new_keyboard_key[key_index].key_value, HEX);
                    debug_serial.print(" Key value with shift: ");
                    debug_serial.print(new_keyboard_key[key_index].key_value_shift, HEX);
                    debug_serial.print(" Key value with capslock: ");
                    debug_serial.print(new_keyboard_key[key_index].key_value_capslock, HEX);
                    debug_serial.print(" Key massage : ");
                    debug_serial.print(new_keyboard_key[key_index].key_debug[0]);
                    debug_serial.print(new_keyboard_key[key_index].key_debug[1]);
                    debug_serial.print(new_keyboard_key[key_index].key_debug[2]);
                    debug_serial.print(new_keyboard_key[key_index].key_debug[3]);
                    debug_serial.print(new_keyboard_key[key_index].key_debug[4]);
                    debug_serial.print(new_keyboard_key[key_index].key_debug[5]);
                    debug_serial.print(new_keyboard_key[key_index].key_debug[6]);
                    debug_serial.print(new_keyboard_key[key_index].key_debug[7]);
                    debug_serial.print(new_keyboard_key[key_index].key_debug[8]);
                    debug_serial.print(new_keyboard_key[key_index].key_debug[9]);
                    debug_serial.print(new_keyboard_key[key_index].key_debug[10]);
                    debug_serial.print(new_keyboard_key[key_index].key_debug[11]);
                    debug_serial.print(new_keyboard_key[key_index].key_debug[12]);
                    debug_serial.print(new_keyboard_key[key_index].key_debug[13]);
                    debug_serial.print(new_keyboard_key[key_index].key_debug[14]);
                    debug_serial.print(new_keyboard_key[key_index].key_debug[15]);
                    debug_serial.print(" Press or release: ");
                    debug_serial.print(new_keyboard_key[key_index].press_or_release ? "Press" : "Release");
                    debug_serial.println();
#endif
                    if (!new_keyboard_key[key_index].mouse_or_keyboard)
                    {
                        if (new_keyboard_key[key_index].is_shift && new_keyboard_key[key_index].press_or_release)
                        {
                            shift_status = true;
                            system_status.shift_status = shift_status;
#if debug
                            debug_serial.println("shift status changed,now is true");
#endif
                        }
                        if (new_keyboard_key[key_index].is_shift && !new_keyboard_key[key_index].press_or_release)
                        {
                            shift_status = false;
                            system_status.shift_status = shift_status;
#if debug
                            debug_serial.println("shift status changed,now is false");
#endif
                        }
                        if (new_keyboard_key[key_index].is_capslock && new_keyboard_key[key_index].press_or_release)
                        {
                            capsLock_status = !capsLock_status;
                            system_status.capslock_status = capsLock_status;
#if debug
                            debug_serial.print("capslock status is changed,now is ");
                            debug_serial.println(capsLock_status ? "true" : "false");
#endif
                        }
                        if (new_keyboard_key[key_index].press_or_release)
                        {
#if debug
                            debug_serial.print("press : ");
                            debug_serial.print(new_keyboard_key[key_index].key_debug[0]);
                            debug_serial.print(new_keyboard_key[key_index].key_debug[1]);
                            debug_serial.print(new_keyboard_key[key_index].key_debug[2]);
                            debug_serial.print(new_keyboard_key[key_index].key_debug[3]);
                            debug_serial.print(new_keyboard_key[key_index].key_debug[4]);
                            debug_serial.print(new_keyboard_key[key_index].key_debug[5]);
                            debug_serial.print(new_keyboard_key[key_index].key_debug[6]);
                            debug_serial.print(new_keyboard_key[key_index].key_debug[7]);
                            debug_serial.print(new_keyboard_key[key_index].key_debug[8]);
                            debug_serial.print(new_keyboard_key[key_index].key_debug[9]);
                            debug_serial.print(new_keyboard_key[key_index].key_debug[10]);
                            debug_serial.print(new_keyboard_key[key_index].key_debug[11]);
                            debug_serial.print(new_keyboard_key[key_index].key_debug[12]);
                            debug_serial.print(new_keyboard_key[key_index].key_debug[13]);
                            debug_serial.print(new_keyboard_key[key_index].key_debug[14]);
                            debug_serial.print(new_keyboard_key[key_index].key_debug[15]);
                            debug_serial.println();
#endif
                            if (shift_status && capsLock_status)
                            {
                                Keyboard.press(new_keyboard_key[key_index].key_value);
#if debug
                                debug_serial.print("shift and capslock are both true,press key value : ");
                                debug_serial.print(new_keyboard_key[key_index].key_debug[0]);
                                debug_serial.print(new_keyboard_key[key_index].key_debug[1]);
                                debug_serial.print(new_keyboard_key[key_index].key_debug[2]);
                                debug_serial.print(new_keyboard_key[key_index].key_debug[3]);
                                debug_serial.print(new_keyboard_key[key_index].key_debug[4]);
                                debug_serial.print(new_keyboard_key[key_index].key_debug[5]);
                                debug_serial.print(new_keyboard_key[key_index].key_debug[6]);
                                debug_serial.print(new_keyboard_key[key_index].key_debug[7]);
                                debug_serial.print(new_keyboard_key[key_index].key_debug[8]);
                                debug_serial.print(new_keyboard_key[key_index].key_debug[9]);
                                debug_serial.print(new_keyboard_key[key_index].key_debug[10]);
                                debug_serial.print(new_keyboard_key[key_index].key_debug[11]);
                                debug_serial.print(new_keyboard_key[key_index].key_debug[12]);
                                debug_serial.print(new_keyboard_key[key_index].key_debug[13]);
                                debug_serial.print(new_keyboard_key[key_index].key_debug[14]);
                                debug_serial.print(new_keyboard_key[key_index].key_debug[15]);
                                debug_serial.println();
#endif
                            }
                            else if (!shift_status && capsLock_status)
                            {
                                Keyboard.press(new_keyboard_key[key_index].key_value);
#if debug
                                debug_serial.print("capslock is true,press key value : ");
                                debug_serial.print(new_keyboard_key[key_index].key_debug[0]);
                                debug_serial.print(new_keyboard_key[key_index].key_debug[1]);
                                debug_serial.print(new_keyboard_key[key_index].key_debug[2]);
                                debug_serial.print(new_keyboard_key[key_index].key_debug[3]);
                                debug_serial.print(new_keyboard_key[key_index].key_debug[4]);
                                debug_serial.print(new_keyboard_key[key_index].key_debug[5]);
                                debug_serial.print(new_keyboard_key[key_index].key_debug[6]);
                                debug_serial.print(new_keyboard_key[key_index].key_debug[7]);
                                debug_serial.print(new_keyboard_key[key_index].key_debug[8]);
                                debug_serial.print(new_keyboard_key[key_index].key_debug[9]);
                                debug_serial.print(new_keyboard_key[key_index].key_debug[10]);
                                debug_serial.print(new_keyboard_key[key_index].key_debug[11]);
                                debug_serial.print(new_keyboard_key[key_index].key_debug[12]);
                                debug_serial.print(new_keyboard_key[key_index].key_debug[13]);
                                debug_serial.print(new_keyboard_key[key_index].key_debug[14]);
                                debug_serial.print(new_keyboard_key[key_index].key_debug[15]);
                                debug_serial.println();
#endif
                            }
                            else if (shift_status && !capsLock_status)
                            {
                                Keyboard.press(new_keyboard_key[key_index].key_value_shift);
#if debug
                                debug_serial.print("shift is true,press key value : ");
                                debug_serial.print(new_keyboard_key[key_index].key_debug[0]);
                                debug_serial.print(new_keyboard_key[key_index].key_debug[1]);
                                debug_serial.print(new_keyboard_key[key_index].key_debug[2]);
                                debug_serial.print(new_keyboard_key[key_index].key_debug[3]);
                                debug_serial.print(new_keyboard_key[key_index].key_debug[4]);
                                debug_serial.print(new_keyboard_key[key_index].key_debug[5]);
                                debug_serial.print(new_keyboard_key[key_index].key_debug[6]);
                                debug_serial.print(new_keyboard_key[key_index].key_debug[7]);
                                debug_serial.print(new_keyboard_key[key_index].key_debug[8]);
                                debug_serial.print(new_keyboard_key[key_index].key_debug[9]);
                                debug_serial.print(new_keyboard_key[key_index].key_debug[10]);
                                debug_serial.print(new_keyboard_key[key_index].key_debug[11]);
                                debug_serial.print(new_keyboard_key[key_index].key_debug[12]);
                                debug_serial.print(new_keyboard_key[key_index].key_debug[13]);
                                debug_serial.print(new_keyboard_key[key_index].key_debug[14]);
                                debug_serial.print(new_keyboard_key[key_index].key_debug[15]);
                                debug_serial.println();
#endif
                            }
                            else
                            {
                                Keyboard.press(new_keyboard_key[key_index].key_value);
#if debug
                                debug_serial.print("press key value : ");
                                debug_serial.print(new_keyboard_key[key_index].key_debug[0]);
                                debug_serial.print(new_keyboard_key[key_index].key_debug[1]);
                                debug_serial.print(new_keyboard_key[key_index].key_debug[2]);
                                debug_serial.print(new_keyboard_key[key_index].key_debug[3]);
                                debug_serial.print(new_keyboard_key[key_index].key_debug[4]);
                                debug_serial.print(new_keyboard_key[key_index].key_debug[5]);
                                debug_serial.print(new_keyboard_key[key_index].key_debug[6]);
                                debug_serial.print(new_keyboard_key[key_index].key_debug[7]);
                                debug_serial.print(new_keyboard_key[key_index].key_debug[8]);
                                debug_serial.print(new_keyboard_key[key_index].key_debug[9]);
                                debug_serial.print(new_keyboard_key[key_index].key_debug[10]);
                                debug_serial.print(new_keyboard_key[key_index].key_debug[11]);
                                debug_serial.print(new_keyboard_key[key_index].key_debug[12]);
                                debug_serial.print(new_keyboard_key[key_index].key_debug[13]);
                                debug_serial.print(new_keyboard_key[key_index].key_debug[14]);
                                debug_serial.print(new_keyboard_key[key_index].key_debug[15]);
                                debug_serial.println();
#endif
                            }
                        }
                        else
                        {

                            if (shift_status && capsLock_status)
                            {
                                Keyboard.release(new_keyboard_key[key_index].key_value);
                                system_status.last_key_value = new_keyboard_key[key_index].key_value;
                                system_status.last_key_index = key_index;
                                if (new_keyboard_key[key_index].set_function)
                                {
                                    system_status.ssd1306_set_instruction = new_keyboard_key[key_index].set_function;
                                }
                            }
                            else if (!shift_status && capsLock_status)
                            {
                                Keyboard.release(new_keyboard_key[key_index].key_value);
                                system_status.last_key_value = new_keyboard_key[key_index].key_value_capslock;
                                system_status.last_key_index = key_index;
                                if (new_keyboard_key[key_index].set_function)
                                {
                                    system_status.ssd1306_set_instruction = new_keyboard_key[key_index].set_function;
                                }
                            }
                            else if (shift_status && !capsLock_status)
                            {
                                Keyboard.release(new_keyboard_key[key_index].key_value_shift);
                                system_status.last_key_value = new_keyboard_key[key_index].key_value_shift;
                                system_status.last_key_index = key_index;
                                if (new_keyboard_key[key_index].set_function)
                                {
                                    system_status.ssd1306_set_instruction = new_keyboard_key[key_index].set_function;
                                }
                            }
                            else
                            {
                                Keyboard.release(new_keyboard_key[key_index].key_value);
                                system_status.last_key_value = new_keyboard_key[key_index].key_value;
                                system_status.last_key_index = key_index;
                                if (new_keyboard_key[key_index].set_function)
                                {
                                    system_status.ssd1306_set_instruction = new_keyboard_key[key_index].set_function;
                                }
                            }
                        }
                    }
                    else
                    {
                        if (new_keyboard_key[key_index].press_or_release)
                        {
                            Mouse.press(new_keyboard_key[key_index].key_value);
                        }
                        else
                        {
                            Mouse.release(new_keyboard_key[key_index].key_value);
                            system_status.last_key_value = new_keyboard_key[key_index].key_value;
                            system_status.last_key_index = key_index;
                            if (new_keyboard_key[key_index].set_function)
                            {
                                system_status.ssd1306_set_instruction = new_keyboard_key[key_index].set_function;
                            }
                        }
                    }
                    new_keyboard_key[key_index].last_time_status = new_keyboard_key[key_index].press_or_release;
                }
            }
        }
        iic_buffer_new_keyboard_last_time[i] = iic_buffer[i];
    }
    return 1;
}
bool IIC_Keyboard::read_serial()
{
#if debug
    Serial.println("read_seral is running");
#endif
    while (Serial.available() > 0)
    {
        uint8_t byte = Serial.read();
#if debug
        Serial.println("Reading");
#endif

        if (byte == 0xAA)
        {
#if debug
            Serial.println("find title");
#endif
            if (Serial.available() >= 7)
            {
                uint8_t buffer[8];
                for (int i = 0; i < 8; i++)
                {
                    buffer[i] = Serial.read();
                }

                if (buffer[7] == 0xBB)
                {
#if debug
                    Serial.println("find end");
#endif
                    uint8_t cpu = buffer[0] & 0x1F;
                    uint8_t temp = buffer[1] & 0x1F;
                    uint8_t ram = buffer[2] & 0x1F;
                    uint8_t disk = buffer[3] & 0x1F;
                    uint8_t net = buffer[4] & 0x1F;
                    uint8_t linux_distribution = buffer[5] & 0x1F;
                    /*
                    #define ubuntu 0x01
                    #define debian 0x02
                    #define rhel 0x03
                    #define fedora 0x04
                    #define arch 0x05
                    #define linuxmint 0x06
                    #define opensuse 0x07
                    #define centos 0x08
                    #define kali 0x09
                    #define raspbian 0x0A
                    */

                    uint8_t checksum = buffer[6];

                    uint8_t calc_checksum = cpu ^ temp ^ ram ^ disk ^ net ^ linux_distribution;

                    if (checksum == calc_checksum)
                    {
#if debug
                        Serial.println("crc is also ok");
#endif
                        system_status.rpi_cpu = cpu;
                        system_status.rpi_temp = temp;
                        system_status.rpi_ram = ram;
                        system_status.rpi_disk = disk;
                        system_status.rpi_net = net;
                        system_status.rpi_distribution = linux_distribution;
                        system_status.rpi_communicated = true;

                        return true;
                    }
                    else
                    {
#if debug
                        Serial.print(calc_checksum);
                        Serial.println("crc error");
#endif
                        return false;
                    }
                }
            }
            else
            {
                return false;
            }
        }
    }
    return false;
}