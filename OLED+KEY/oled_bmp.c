#include "oled_font.h"

// 114x64 kb
const uint8_t bmp1[][16] = {
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x06,0x1F,0xB8,0x00,0x00,0x00,0x00,0x00,0x3E,0x00,0x36,0x80,0x00,0x00,0x00},
{0x00,0xC0,0x00,0x17,0xE0,0x00,0x00,0x00,0x01,0x03,0xFF,0xC7,0x8C,0x00,0x00,0x00},
{0x02,0x3F,0xFF,0xFC,0x80,0x80,0x00,0x00,0x03,0xFF,0xFF,0xFE,0x00,0x10,0x10,0x00},
{0x03,0xFF,0xFF,0xFD,0x00,0x04,0x02,0x00,0x03,0xFF,0xFF,0x7C,0x00,0x00,0x00,0x40},
{0x03,0xFF,0xFF,0x78,0x00,0x00,0x00,0x00,0x03,0xFF,0xFF,0xFA,0x00,0x00,0x00,0x00},
{0x01,0xFF,0xFF,0xFE,0x00,0x00,0x00,0x00,0x01,0xFF,0xFF,0xFC,0x00,0x00,0x00,0x01},
{0x00,0xFF,0xFF,0xFC,0x00,0x20,0x00,0x00,0x00,0x7F,0xF8,0x7C,0x00,0x80,0x00,0x00},
{0x00,0x7F,0xF8,0x01,0x80,0x00,0x00,0x00,0x00,0x3F,0xF8,0x00,0xFC,0x00,0x00,0x40},
{0x00,0x3F,0xFC,0x00,0x7F,0xC7,0xE0,0x00,0x00,0x1F,0xFC,0x00,0xFF,0xFA,0x00,0x00},
{0x00,0x1F,0xFC,0x7F,0xFF,0xFF,0xC0,0x00,0x00,0x0F,0xFF,0xFF,0xFF,0xFF,0xF8,0x00},
{0x00,0x0F,0xFF,0xFF,0xFF,0xFF,0xFC,0x00,0x00,0x04,0xFF,0xFF,0xFF,0xFE,0x7F,0xFF},
{0x00,0x01,0xFF,0xFF,0xFF,0xFF,0xFF,0x80,0x00,0x27,0xFF,0xFF,0xFF,0xFD,0xFF,0x81},
{0x00,0x0F,0xFF,0xFC,0x07,0xFF,0xFF,0xFC,0x00,0x0F,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8},
{0x00,0x0F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFA,0x02,0x0F,0xFF,0xFF,0xC6,0x0B,0xFF,0xFF},
{0x00,0x1F,0xFF,0xC0,0x00,0x81,0xFF,0xFF,0x04,0x63,0xFC,0x40,0x00,0x41,0xF9,0xFF},
{0x0D,0xCF,0xF8,0x60,0x00,0x20,0xF8,0x7F,0x0F,0x0F,0xF0,0x40,0x00,0x00,0xFC,0xFF},
{0x0E,0x47,0xE0,0xE0,0x00,0x00,0x7E,0xFF,0x1D,0xFB,0xC0,0xE0,0x00,0x00,0x7E,0xFF},
{0x1F,0xE7,0x9E,0xE0,0x00,0x00,0x7E,0xFF,0x1F,0xCF,0xFE,0x60,0x00,0x00,0xFE,0xFF},
{0x1F,0xFF,0xFE,0x40,0x00,0x00,0xFE,0xFF,0x1F,0xFF,0xFF,0xA0,0x00,0x00,0xFE,0x7F},
{0x5F,0xF3,0xFF,0x80,0x00,0x00,0xFD,0xFF,0xFF,0xF3,0xFF,0x00,0x00,0x01,0xFF,0xFF},
{0x9F,0xF3,0xFF,0xC0,0x00,0x01,0xFF,0xFF,0x9F,0xFB,0xFF,0xC0,0x00,0x01,0xFF,0xFF},
{0x1F,0xFD,0xFF,0xC0,0x00,0x03,0xFF,0xFF,0x1F,0xFD,0xFF,0xC0,0x00,0x03,0xFF,0xF3},
{0x0F,0xFF,0xFF,0xE0,0x00,0x03,0xFF,0xD0,0x0F,0xFE,0xFF,0xE0,0x00,0x07,0xFF,0x80},
{0x0F,0xFE,0xFF,0xF1,0x80,0x07,0xF8,0x00,0x07,0xFF,0xFF,0xE3,0xA0,0x0F,0xF0,0x00},
{0x07,0xFD,0x7F,0xFB,0x80,0x1F,0xC0,0x00,0x03,0xFF,0xFF,0xF9,0x00,0x3F,0xF8,0x00},
{0x03,0xFF,0xFF,0xF1,0x80,0xFF,0xFF,0x00,0x01,0xFF,0xBF,0xFC,0xD3,0xFF,0xFF,0xE0},
{0x00,0xFF,0xBF,0xF0,0x37,0xFF,0xFE,0xFC,0x00,0x7F,0xFF,0x01,0xFF,0xFF,0xFF,0x87},
{0x00,0x3F,0xFF,0xFF,0xFF,0xFF,0xFF,0xE4,0x00,0x1F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
{0x00,0x07,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x00,0x0F,0xFF,0xFF,0xFF,0x1F,0x00,0x01},
{0x00,0x0F,0xFF,0xFF,0xFF,0xC0,0x80,0x00,0x00,0x0F,0xFC,0x3C,0x00,0x00,0x40,0x00},
{0x00,0x1F,0xFE,0x68,0x00,0x00,0x20,0x00,0x00,0x1F,0xFF,0x09,0x80,0x00,0x10,0x40},
{0x00,0x3F,0xF9,0x0F,0x00,0x01,0x21,0x00,0x00,0x3C,0x5F,0x7F,0x40,0x00,0x44,0x00},
{0x00,0x30,0x7F,0x7F,0xC0,0x01,0xC0,0x00,0x00,0x20,0xFF,0xFF,0xE0,0x0F,0x00,0x00},
{0x00,0x67,0xFF,0xFF,0xD0,0x00,0x00,0x00,0x00,0x7F,0xFF,0xFB,0xFC,0x00,0x00,0x00},
{0x00,0x7F,0xFF,0xDF,0xFC,0x00,0x00,0x00,0x00,0x7F,0xFF,0xCF,0xE0,0x00,0x00,0x00},
{0x00,0x3F,0xFF,0xFE,0xC0,0x00,0x00,0x00,0x00,0x03,0xFF,0x82,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"E:\STM8_Project\444.bmp",0*/
};

// 64x64 misaka mikato
const uint8_t bmp2[][16] = {
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x24,0x00,0x00,0x00,0x00,0x00,0x30,0x40,0x00,0x00,0x00,0x00,0x00},
{0x00,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x80,0x00,0x00,0x00,0x00,0x00,0x00},
{0x07,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0x00,0x00,0x07,0xC0,0x00,0x00,0x00},
{0x1E,0x00,0x00,0x07,0x90,0x00,0x00,0x00,0x3E,0x00,0x00,0x07,0xF4,0x00,0x00,0x00},
{0x7E,0x00,0x00,0x07,0x98,0x00,0x00,0x00,0x7E,0x00,0x00,0x07,0xE4,0x00,0x00,0x03},
{0xFE,0x00,0x00,0x07,0xFC,0x00,0x00,0x0F,0xFE,0x00,0x00,0x07,0x7E,0x00,0x00,0x1F},
{0xFE,0x00,0x00,0x0F,0x8B,0x00,0x00,0x3F,0xFE,0x00,0x00,0x03,0x02,0x80,0x07,0xFF},
{0xFE,0x00,0x00,0x1C,0x11,0x00,0x1F,0xFF,0xFE,0x00,0x00,0x30,0x00,0x20,0x3F,0xFF},
{0xFE,0x00,0x00,0x04,0x00,0x40,0x7F,0xFF,0xFE,0x00,0x00,0x10,0x00,0x00,0x7F,0xFF},
{0xFE,0x00,0x00,0xC0,0x00,0x00,0x7F,0xFF,0xFF,0x00,0x01,0xE0,0x00,0x00,0xFF,0xFF},
{0xFF,0x00,0x03,0x80,0x00,0x00,0xC7,0xFF,0xFF,0x00,0x06,0x80,0x00,0x00,0x00,0x3F},
{0xFF,0xC0,0x07,0xF0,0x00,0x00,0x80,0x3F,0xFF,0xF0,0x0D,0xF0,0x00,0x00,0x00,0x1F},
{0xFF,0xFC,0x1F,0xE0,0x00,0x01,0x00,0x1F,0xFF,0xFF,0xC1,0xC8,0x01,0x00,0x00,0x3F},
{0xFF,0xFF,0xFF,0x80,0x02,0x00,0x00,0x3F,0xFF,0xFF,0xF8,0x00,0x0C,0xE4,0x00,0x3F},
{0xFF,0xFF,0xFB,0xFC,0x71,0x88,0x00,0x7F,0xFF,0xFF,0xE0,0x7F,0x83,0x00,0x00,0xFF},
{0xFF,0xFF,0xF0,0xFE,0x04,0x00,0x00,0xFF,0xFF,0xFF,0xFB,0x80,0x00,0x00,0x01,0xFF},
{0xFF,0xFF,0xFF,0xFC,0x00,0x00,0x01,0xFF,0xFF,0xFF,0xFE,0x00,0x00,0x00,0x03,0x8F},
{0xFF,0xFF,0xFC,0x08,0x00,0x00,0x07,0x87,0x7F,0xFE,0xFC,0x03,0xA0,0x00,0x1F,0x8F},
{0x1F,0xFE,0xFE,0x0C,0x40,0x00,0x5F,0xDF,0x0F,0xFF,0xFF,0xF8,0x40,0x00,0x7F,0xFF},
{0x1F,0xFC,0xFF,0xE0,0x00,0x00,0xFF,0xFF,0x1F,0x3E,0xFF,0x40,0x00,0x01,0xFF,0xFF},
{0x1F,0x82,0x63,0x00,0x00,0x03,0xFF,0xFF,0x0F,0x80,0x00,0x00,0x00,0x03,0xFF,0xFF},
{0x03,0x80,0x00,0x00,0x00,0x07,0xFF,0xFF,0x03,0xC0,0x00,0x00,0x00,0x0F,0xFF,0xFF},
{0x01,0xE0,0x00,0x00,0x00,0x0F,0xFF,0xFF,0x01,0xB0,0x00,0x00,0x00,0x1F,0xFF,0xFF},
{0x01,0x8C,0x00,0x00,0x00,0x0F,0xFF,0xFF,0x01,0x80,0x00,0x00,0x00,0x0F,0xFF,0xFF},
{0x00,0x80,0x00,0x00,0x00,0x07,0xFF,0xFC,0x01,0xC0,0x00,0x00,0x00,0x07,0xFF,0xF8},
{0x00,0xE0,0x00,0x00,0x00,0x03,0xFF,0xF0,0x00,0x58,0x00,0x00,0x00,0x01,0xCF,0xF0},
{0x00,0x20,0x00,0x00,0x00,0x00,0xF7,0xE0,0x00,0x00,0x80,0x00,0x00,0x00,0x3F,0xF0},
{0x00,0x00,0x00,0x00,0x00,0x00,0x07,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0xFF},
{0x00,0x00,0x00,0x00,0x00,0x00,0x01,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF},/*"E:\STM8_Project\555.bmp",0*/
};

// 60x64 typhoon
const uint8_t bmp3[][16] = {
{0xFF,0xC0,0x31,0xFF,0xFF,0xFE,0x1A,0x00,0xFF,0xC0,0x7F,0xFF,0xFF,0xFE,0xDE,0x00},
{0x7F,0x83,0xFF,0xFE,0x1F,0x7F,0xFE,0x00,0xFF,0x3F,0xF8,0x40,0x06,0x0F,0xEF,0x00},
{0x7E,0x07,0xF8,0x00,0x01,0x0F,0xFE,0x00,0x78,0x07,0xF8,0x00,0x00,0x07,0xFF,0x00},
{0x70,0x07,0xE0,0x00,0x00,0x07,0xFF,0x40,0x1F,0x8F,0x00,0x00,0x00,0x03,0xFF,0xE0},
{0x1F,0x3C,0x00,0x00,0x00,0x01,0xFF,0xE0,0x3C,0x78,0x00,0x00,0x00,0x00,0xFF,0xF0},
{0x40,0xF0,0x00,0x00,0x00,0x00,0x7F,0xF8,0x00,0xC0,0x00,0x00,0x00,0x00,0x3F,0xFC},
{0x01,0x80,0x00,0x00,0x00,0x00,0x1F,0xFF,0x0F,0x00,0x00,0x00,0x00,0x00,0x07,0xFF},
{0x1F,0x00,0x00,0x00,0x00,0x00,0x07,0xFF,0x3C,0x00,0x00,0x00,0x00,0x00,0x07,0xFF},
{0x3C,0x00,0x00,0x00,0x00,0x00,0x03,0xFF,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0xFF},
{0x60,0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0x60,0x00,0x00,0x00,0x00,0x00,0x00,0x3F},
{0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x1F},
{0xE0,0x00,0x07,0x40,0x00,0x00,0x00,0x1B,0xE0,0x00,0x07,0xE0,0x00,0x00,0x00,0x01},
{0xC0,0x00,0x1F,0xFC,0x00,0x00,0x00,0x01,0x80,0x00,0x7F,0xFF,0x00,0x00,0x00,0x01},
{0x80,0x00,0x7C,0x0F,0x80,0x00,0x00,0x01,0x80,0x00,0x70,0xC3,0x80,0x00,0x00,0x01},
{0x00,0x00,0xE3,0x11,0xC0,0x00,0x00,0x03,0x00,0x00,0xE8,0x2D,0xE0,0x00,0x00,0x03},
{0x00,0x00,0xC8,0x05,0xE0,0x00,0x00,0x03,0x80,0x01,0xDA,0x08,0xE0,0x00,0x00,0x03},
{0x80,0x00,0xD8,0x02,0xE0,0x00,0x00,0x03,0x80,0x00,0x48,0x10,0xC0,0x00,0x00,0x07},
{0x80,0x00,0x48,0x04,0xC0,0x00,0x00,0x07,0x80,0x00,0x24,0x09,0x80,0x00,0x00,0x0F},
{0x80,0x00,0x0B,0x16,0x00,0x00,0x00,0x0F,0x80,0x00,0x03,0x58,0x00,0x00,0x00,0x1F},
{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x3F},
{0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x7F},
{0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xF0,0x00,0x00,0x00,0x00,0x00,0x01,0xFF},
{0x70,0x00,0x00,0x00,0x00,0x00,0x03,0xFE,0x78,0x00,0x00,0x00,0x00,0x00,0x0F,0xFF},
{0x78,0x00,0x00,0x00,0x00,0x00,0x1F,0xF0,0x3C,0x00,0x00,0x00,0x00,0x00,0x3F,0xFC},
{0x3E,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x3F,0x00,0x00,0x00,0x00,0x00,0xFF,0xFE},
{0x1F,0x80,0x00,0x00,0x00,0x03,0xFF,0xF0,0x0F,0xC0,0x00,0x00,0x00,0x0F,0xFF,0xE0},
{0x0F,0xF8,0x00,0x00,0x00,0x3F,0xFF,0xFF,0x47,0xFE,0x00,0x00,0x00,0x7F,0xFF,0xFC},
{0x43,0xFF,0x80,0x00,0x01,0xFF,0xFF,0xE0,0x41,0xFF,0xF0,0x00,0x1F,0xFF,0xE7,0xE0},
{0x10,0x7F,0xFF,0x00,0x0F,0xFF,0xBE,0xC0,0x08,0x03,0xFF,0xFF,0xFF,0xF8,0x7E,0xC0},
{0x18,0x00,0xFF,0xFF,0xFF,0xC1,0xE2,0x00,0xFF,0x0E,0x3F,0xFF,0xFF,0x10,0xC1,0x00},/*"E:\STM8_Project\888.bmp",0*/
};

// 64x64 elania1
const uint8_t bmp4[][16] = {
{0x00,0x00,0x00,0x00,0x00,0x40,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x20,0x20,0x00,0x00,0x00},
{0x00,0xF0,0x00,0x00,0x10,0x00,0x04,0x00,0x00,0x40,0x00,0x08,0x00,0x00,0x04,0x00},
{0x00,0xE3,0x00,0x04,0x10,0x00,0x00,0x00,0x00,0x90,0x00,0x03,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x00,0x00,0x02,0x00},
{0x00,0x00,0x00,0x00,0x80,0x00,0x02,0x00,0x00,0x00,0x03,0xF0,0x40,0x00,0x3F,0xF0},
{0x00,0x00,0x30,0x04,0x20,0x03,0xFC,0x02,0x00,0x00,0x82,0x07,0x30,0x1F,0xFC,0x00},
{0x00,0x00,0x00,0x00,0xEF,0xFF,0xFC,0x0B,0x00,0x00,0x00,0x00,0x0B,0xFF,0xFC,0x02},
{0x00,0x00,0x00,0x00,0x03,0xFF,0xFC,0x00,0x00,0x00,0x00,0x0C,0x07,0xFF,0xFE,0x07},
{0x00,0x00,0x00,0x11,0x00,0xFF,0xFE,0x7F,0x01,0x00,0x03,0x7E,0xC3,0xFF,0xFF,0xFF},
{0x80,0x00,0x13,0x80,0x21,0xFF,0xF7,0xC0,0x40,0x00,0x13,0x00,0x11,0xFF,0xC0,0x00},
{0x00,0x00,0xE6,0x00,0x09,0xFF,0x02,0x00,0x20,0x04,0xB6,0xE0,0x09,0xFE,0x10,0x00},
{0x20,0x00,0x07,0x38,0x00,0xFC,0x00,0x00,0x28,0x00,0x87,0xF8,0x04,0xF8,0x04,0x01},
{0x00,0x08,0x67,0xF8,0x00,0x88,0x49,0xC0,0x00,0x00,0x4F,0xE0,0x01,0x12,0x50,0x1F},
{0x10,0x00,0x0A,0x00,0x02,0x28,0x00,0x00,0x10,0x00,0x01,0x00,0x10,0x23,0xFD,0x00},
{0x00,0x00,0x00,0x00,0xC0,0x0D,0x40,0x00,0x00,0x00,0x00,0x00,0x80,0x02,0x1C,0x00},
{0x00,0x00,0x00,0x00,0x00,0x15,0x63,0x80,0x00,0x00,0x00,0x00,0x00,0x0A,0x71,0xE0},
{0x00,0x00,0x00,0x00,0x00,0x21,0x00,0x20,0x00,0x00,0x02,0x00,0x02,0x00,0xE3,0xC1},
{0x00,0x00,0x16,0x00,0x02,0x40,0xFF,0x07,0x00,0x40,0x1A,0x98,0x04,0x80,0xFF,0xFF},
{0x00,0x20,0x0B,0xFD,0x09,0x01,0xFF,0xFF,0x00,0x03,0x03,0xFC,0x22,0x01,0xFF,0xFF},
{0x10,0x00,0x1F,0xF8,0x44,0x03,0xFF,0xFF,0x10,0x00,0x01,0xF5,0x08,0x03,0xFF,0xFF},
{0x00,0x03,0xE0,0xFC,0x10,0x03,0xFF,0xFF,0x08,0x00,0x00,0xC0,0x00,0x07,0xFF,0xFF},
{0x00,0x00,0x00,0x00,0x00,0x1F,0xFF,0xFF,0x04,0x00,0x00,0x00,0x04,0x2F,0xFF,0xFF},
{0x02,0x08,0x00,0x00,0x20,0x5F,0x9F,0xFF,0x00,0x03,0x80,0x03,0x00,0xF7,0x8F,0xFF},
{0x00,0x00,0x07,0xC0,0x06,0x00,0x07,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0xFF},
{0x00,0x20,0x00,0x00,0x00,0x00,0x01,0xFF,0x00,0x10,0x00,0x00,0x00,0x03,0x80,0x7F},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0x00,0x00,0x80,0x00,0x00,0x00,0x00,0x3F},
{0x01,0x80,0x18,0x00,0xB0,0x00,0x00,0xBF,0x03,0x00,0x00,0x60,0x03,0x00,0x03,0xC0},
{0x01,0x80,0x00,0x00,0x00,0x30,0x00,0x00,0x03,0x40,0x40,0x00,0x00,0x03,0x00,0x50},
{0x02,0x00,0x00,0x00,0x00,0x00,0x1F,0x00,0x03,0xC0,0x00,0x00,0x00,0x00,0x00,0x00},
{0x02,0x40,0x00,0x00,0x00,0x00,0x00,0x08,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"E:\STM8_Project\333.bmp",0*/ 
};

// 85x64 rixiang
const uint8_t bmp5[][16] = {
{0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x00,0x00,0x00,0x03,0xFE,0x00,0x00,0x00,0x00},
{0x00,0x03,0x00,0x00,0x04,0x00,0x00,0x00,0x00,0x60,0x00,0x00,0x00,0x00,0x08,0x00},
{0x02,0x00,0x00,0x0F,0x80,0x00,0x02,0x00,0x10,0x00,0x00,0x00,0x08,0x00,0x00,0xC0},
{0xC0,0x00,0x00,0x00,0x02,0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x0F,0xE0,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x40,0x00},
{0x00,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x70,0x01,0xC0,0x80,0x40,0x00,0x00,0x1E,0x20,0x00,0x06,0x00,0x80,0x00},
{0x0F,0x00,0x18,0x0F,0xF1,0x80,0x00,0x00,0x00,0x00,0x01,0xBE,0x00,0x94,0x60,0x02},
{0x00,0x00,0x00,0x38,0x00,0x44,0x20,0x60,0x00,0x00,0x00,0x00,0x00,0x11,0x20,0x01},
{0x00,0x00,0x04,0xC8,0x00,0x00,0x20,0x00,0x00,0x00,0x01,0xC3,0xC0,0x00,0x00,0x00},
{0x00,0x00,0x00,0xC8,0xF8,0x00,0x02,0x01,0x00,0x00,0x00,0x10,0x04,0x00,0x01,0x00},
{0x00,0x00,0x00,0x1C,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x0C,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x00,0x00,0x00,0x05,0xC0,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0xC0,0x00,0x00,0x06,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x20},
{0x00,0x06,0x00,0x00,0x0C,0x00,0x00,0x00,0x00,0x00,0x30,0x01,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x10,0xC0,0x00,0x00,0x10,0x00,0x00,0x00,0x10},
{0x03,0xE0,0x3F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x42,0x00,0x00,0x00,0x00,0x00,0x00,0x07},
{0x24,0x01,0xF8,0x00,0x00,0x00,0x00,0x00,0x08,0x03,0xC0,0x00,0x00,0x00,0x00,0x08},
{0x00,0x07,0x00,0x00,0x00,0x01,0x00,0x0C,0x00,0x0E,0x00,0x00,0x00,0x00,0x00,0x0E},
{0x00,0x1C,0x00,0x00,0x00,0x00,0x00,0x0E,0x00,0x18,0x00,0x00,0x00,0x00,0x00,0x0E},
{0x00,0x38,0x00,0x00,0x00,0x00,0x00,0x0E,0x00,0x30,0x1C,0x00,0x00,0x21,0x00,0x0C},
{0x00,0x30,0x1F,0x00,0x00,0x00,0x00,0x0E,0x18,0x14,0x00,0x80,0x01,0x00,0x00,0x1C},
{0x02,0x0E,0x80,0x40,0x00,0x04,0x00,0x18,0x00,0x87,0x00,0x00,0x04,0x00,0x00,0x30},
{0x04,0x70,0x00,0x00,0x00,0x00,0x00,0x30,0x02,0x6E,0xF0,0x00,0x01,0x80,0x00,0x60},
{0x00,0x6E,0x38,0x00,0x00,0x00,0x00,0x40,0x00,0x6E,0x00,0x00,0x00,0x00,0x00,0xC0},
{0x00,0xE6,0x00,0x00,0x00,0x00,0x01,0xC0,0x00,0x66,0x00,0x00,0x00,0x00,0x01,0xC0},
{0x08,0x33,0x02,0x00,0x00,0x00,0x03,0x82,0x02,0x10,0xFC,0x00,0x00,0x00,0x06,0x04},
{0x00,0x10,0x00,0x00,0x00,0x00,0x0C,0x02,0x00,0x08,0x00,0x00,0x00,0x00,0x18,0x00},
{0x00,0x02,0x00,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x40,0x00,0x00,0x00,0x40,0x00},
{0x00,0x00,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x00,0x02,0x00,0x00},
{0x00,0x00,0x00,0x00,0x10,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x00,0x02},
{0x00,0x00,0x00,0x02,0x03,0x00,0x00,0x04,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x08},
{0x00,0x00,0x00,0x40,0x00,0x00,0x00,0x00,0x40,0x0F,0xFC,0x00,0x03,0x00,0x00,0x00},
{0x18,0x00,0x00,0x00,0x03,0xC0,0x00,0x00,0x03,0x01,0x00,0x00,0x07,0xE0,0x00,0x00},
{0x00,0x60,0x43,0xFF,0x07,0xF8,0x00,0x00,0x00,0x03,0xC0,0x00,0x07,0xFE,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0xFF,0x01,0xC8,0x10,0x00,0x00,0x00,0x00,0x20,0x00,0x10},
{0x02,0x20,0x00,0x00,0x00,0x00,0x00,0x40,0x00,0x40,0x00,0x00,0x00,0x00,0x01,0x00},
{0x04,0x80,0x00,0x00,0x00,0x00,0x04,0x00},/*"E:\STM8_Project\999.bmp",0*/
};
