#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h> 
#include "ili9341.h"
#define FIRST_BLOCK_CORD_X1 210
#define FIRST_BLOCK_CORD_Y1 40
#define BLOCK_THICC 15
#define BLOCK_LEN 30
#define FIRST_BLOCK_CORD_X2 195
#define FIRST_BLOCK_CORD_Y2 25
#define FIRST_BLOCK_CORD_X3 210
#define FIRST_BLOCK_CORD_Y3 10

const uint8_t const font[] = {
  0x00, 0x00, 0x00, 0x00, 0x00,
	0x3E, 0x5B, 0x4F, 0x5B, 0x3E,
	0x3E, 0x6B, 0x4F, 0x6B, 0x3E,
	0x1C, 0x3E, 0x7C, 0x3E, 0x1C,
	0x18, 0x3C, 0x7E, 0x3C, 0x18,
	0x1C, 0x57, 0x7D, 0x57, 0x1C,
	0x1C, 0x5E, 0x7F, 0x5E, 0x1C,
	0x00, 0x18, 0x3C, 0x18, 0x00,
	0xFF, 0xE7, 0xC3, 0xE7, 0xFF,
	0x00, 0x18, 0x24, 0x18, 0x00,
	0xFF, 0xE7, 0xDB, 0xE7, 0xFF,
	0x30, 0x48, 0x3A, 0x06, 0x0E,
	0x26, 0x29, 0x79, 0x29, 0x26,
	0x40, 0x7F, 0x05, 0x05, 0x07,
	0x40, 0x7F, 0x05, 0x25, 0x3F,
	0x5A, 0x3C, 0xE7, 0x3C, 0x5A,
	0x7F, 0x3E, 0x1C, 0x1C, 0x08,
	0x08, 0x1C, 0x1C, 0x3E, 0x7F,
	0x14, 0x22, 0x7F, 0x22, 0x14,
	0x5F, 0x5F, 0x00, 0x5F, 0x5F,
	0x06, 0x09, 0x7F, 0x01, 0x7F,
	0x00, 0x66, 0x89, 0x95, 0x6A,
	0x60, 0x60, 0x60, 0x60, 0x60,
	0x94, 0xA2, 0xFF, 0xA2, 0x94,
	0x08, 0x04, 0x7E, 0x04, 0x08,
	0x10, 0x20, 0x7E, 0x20, 0x10,
	0x08, 0x08, 0x2A, 0x1C, 0x08,
	0x08, 0x1C, 0x2A, 0x08, 0x08,
	0x1E, 0x10, 0x10, 0x10, 0x10,
	0x0C, 0x1E, 0x0C, 0x1E, 0x0C,
	0x30, 0x38, 0x3E, 0x38, 0x30,
	0x06, 0x0E, 0x3E, 0x0E, 0x06,
	0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x5F, 0x00, 0x00,
	0x00, 0x07, 0x00, 0x07, 0x00,
	0x14, 0x7F, 0x14, 0x7F, 0x14,
	0x24, 0x2A, 0x7F, 0x2A, 0x12,
	0x23, 0x13, 0x08, 0x64, 0x62,
	0x36, 0x49, 0x56, 0x20, 0x50,
	0x00, 0x08, 0x07, 0x03, 0x00,
	0x00, 0x1C, 0x22, 0x41, 0x00,
	0x00, 0x41, 0x22, 0x1C, 0x00,
	0x2A, 0x1C, 0x7F, 0x1C, 0x2A,
	0x08, 0x08, 0x3E, 0x08, 0x08,
	0x00, 0x80, 0x70, 0x30, 0x00,
	0x08, 0x08, 0x08, 0x08, 0x08,
	0x00, 0x00, 0x60, 0x60, 0x00,
	0x20, 0x10, 0x08, 0x04, 0x02,
	0x3E, 0x51, 0x49, 0x45, 0x3E,
	0x00, 0x42, 0x7F, 0x40, 0x00,
	0x72, 0x49, 0x49, 0x49, 0x46,
	0x21, 0x41, 0x49, 0x4D, 0x33,
	0x18, 0x14, 0x12, 0x7F, 0x10,
	0x27, 0x45, 0x45, 0x45, 0x39,
	0x3C, 0x4A, 0x49, 0x49, 0x31,
	0x41, 0x21, 0x11, 0x09, 0x07,
	0x36, 0x49, 0x49, 0x49, 0x36,
	0x46, 0x49, 0x49, 0x29, 0x1E,
	0x00, 0x00, 0x14, 0x00, 0x00,
	0x00, 0x40, 0x34, 0x00, 0x00,
	0x00, 0x08, 0x14, 0x22, 0x41,
	0x14, 0x14, 0x14, 0x14, 0x14,
	0x00, 0x41, 0x22, 0x14, 0x08,
	0x02, 0x01, 0x59, 0x09, 0x06,
	0x3E, 0x41, 0x5D, 0x59, 0x4E,
	0x7C, 0x12, 0x11, 0x12, 0x7C,
	0x7F, 0x49, 0x49, 0x49, 0x36,
	0x3E, 0x41, 0x41, 0x41, 0x22,
	0x7F, 0x41, 0x41, 0x41, 0x3E,
	0x7F, 0x49, 0x49, 0x49, 0x41,
	0x7F, 0x09, 0x09, 0x09, 0x01,
	0x3E, 0x41, 0x41, 0x51, 0x73,
	0x7F, 0x08, 0x08, 0x08, 0x7F,
	0x00, 0x41, 0x7F, 0x41, 0x00,
	0x20, 0x40, 0x41, 0x3F, 0x01,
	0x7F, 0x08, 0x14, 0x22, 0x41,
	0x7F, 0x40, 0x40, 0x40, 0x40,
	0x7F, 0x02, 0x1C, 0x02, 0x7F,
	0x7F, 0x04, 0x08, 0x10, 0x7F,
	0x3E, 0x41, 0x41, 0x41, 0x3E,
	0x7F, 0x09, 0x09, 0x09, 0x06,
	0x3E, 0x41, 0x51, 0x21, 0x5E,
	0x7F, 0x09, 0x19, 0x29, 0x46,
	0x26, 0x49, 0x49, 0x49, 0x32,
	0x03, 0x01, 0x7F, 0x01, 0x03,
	0x3F, 0x40, 0x40, 0x40, 0x3F,
	0x1F, 0x20, 0x40, 0x20, 0x1F,
	0x3F, 0x40, 0x38, 0x40, 0x3F,
	0x63, 0x14, 0x08, 0x14, 0x63,
	0x03, 0x04, 0x78, 0x04, 0x03,
	0x61, 0x59, 0x49, 0x4D, 0x43,
	0x00, 0x7F, 0x41, 0x41, 0x41,
	0x02, 0x04, 0x08, 0x10, 0x20,
	0x00, 0x41, 0x41, 0x41, 0x7F,
	0x04, 0x02, 0x01, 0x02, 0x04,
	0x40, 0x40, 0x40, 0x40, 0x40,
	0x00, 0x03, 0x07, 0x08, 0x00,
	0x20, 0x54, 0x54, 0x78, 0x40,
	0x7F, 0x28, 0x44, 0x44, 0x38,
	0x38, 0x44, 0x44, 0x44, 0x28,
	0x38, 0x44, 0x44, 0x28, 0x7F,
	0x38, 0x54, 0x54, 0x54, 0x18,
	0x00, 0x08, 0x7E, 0x09, 0x02,
	0x18, 0xA4, 0xA4, 0x9C, 0x78,
	0x7F, 0x08, 0x04, 0x04, 0x78,
	0x00, 0x44, 0x7D, 0x40, 0x00,
	0x20, 0x40, 0x40, 0x3D, 0x00,
	0x7F, 0x10, 0x28, 0x44, 0x00,
	0x00, 0x41, 0x7F, 0x40, 0x00,
	0x7C, 0x04, 0x78, 0x04, 0x78,
	0x7C, 0x08, 0x04, 0x04, 0x78,
	0x38, 0x44, 0x44, 0x44, 0x38,
	0xFC, 0x18, 0x24, 0x24, 0x18,
	0x18, 0x24, 0x24, 0x18, 0xFC,
	0x7C, 0x08, 0x04, 0x04, 0x08,
	0x48, 0x54, 0x54, 0x54, 0x24,
	0x04, 0x04, 0x3F, 0x44, 0x24,
	0x3C, 0x40, 0x40, 0x20, 0x7C,
	0x1C, 0x20, 0x40, 0x20, 0x1C,
	0x3C, 0x40, 0x30, 0x40, 0x3C,
	0x44, 0x28, 0x10, 0x28, 0x44,
	0x4C, 0x90, 0x90, 0x90, 0x7C,
	0x44, 0x64, 0x54, 0x4C, 0x44,
	0x00, 0x08, 0x36, 0x41, 0x00,
	0x00, 0x00, 0x77, 0x00, 0x00,
	0x00, 0x41, 0x36, 0x08, 0x00,
	0x02, 0x01, 0x02, 0x04, 0x02,
	0x3C, 0x26, 0x23, 0x26, 0x3C,
	0x1E, 0xA1, 0xA1, 0x61, 0x12,
	0x3A, 0x40, 0x40, 0x20, 0x7A,
	0x38, 0x54, 0x54, 0x55, 0x59,
	0x21, 0x55, 0x55, 0x79, 0x41,
	0x21, 0x54, 0x54, 0x78, 0x41,
	0x21, 0x55, 0x54, 0x78, 0x40,
	0x20, 0x54, 0x55, 0x79, 0x40,
	0x0C, 0x1E, 0x52, 0x72, 0x12,
	0x39, 0x55, 0x55, 0x55, 0x59,
	0x39, 0x54, 0x54, 0x54, 0x59,
	0x39, 0x55, 0x54, 0x54, 0x58,
	0x00, 0x00, 0x45, 0x7C, 0x41,
	0x00, 0x02, 0x45, 0x7D, 0x42,
	0x00, 0x01, 0x45, 0x7C, 0x40,
	0xF0, 0x29, 0x24, 0x29, 0xF0,
	0xF0, 0x28, 0x25, 0x28, 0xF0,
	0x7C, 0x54, 0x55, 0x45, 0x00,
	0x20, 0x54, 0x54, 0x7C, 0x54,
	0x7C, 0x0A, 0x09, 0x7F, 0x49,
	0x32, 0x49, 0x49, 0x49, 0x32,
	0x32, 0x48, 0x48, 0x48, 0x32,
	0x32, 0x4A, 0x48, 0x48, 0x30,
	0x3A, 0x41, 0x41, 0x21, 0x7A,
	0x3A, 0x42, 0x40, 0x20, 0x78,
	0x00, 0x9D, 0xA0, 0xA0, 0x7D,
	0x39, 0x44, 0x44, 0x44, 0x39,
	0x3D, 0x40, 0x40, 0x40, 0x3D,
	0x3C, 0x24, 0xFF, 0x24, 0x24,
	0x48, 0x7E, 0x49, 0x43, 0x66,
	0x2B, 0x2F, 0xFC, 0x2F, 0x2B,
	0xFF, 0x09, 0x29, 0xF6, 0x20,
	0xC0, 0x88, 0x7E, 0x09, 0x03,
	0x20, 0x54, 0x54, 0x79, 0x41,
	0x00, 0x00, 0x44, 0x7D, 0x41,
	0x30, 0x48, 0x48, 0x4A, 0x32,
	0x38, 0x40, 0x40, 0x22, 0x7A,
	0x00, 0x7A, 0x0A, 0x0A, 0x72,
	0x7D, 0x0D, 0x19, 0x31, 0x7D,
	0x26, 0x29, 0x29, 0x2F, 0x28,
	0x26, 0x29, 0x29, 0x29, 0x26,
	0x30, 0x48, 0x4D, 0x40, 0x20,
	0x38, 0x08, 0x08, 0x08, 0x08,
	0x08, 0x08, 0x08, 0x08, 0x38,
	0x2F, 0x10, 0xC8, 0xAC, 0xBA,
	0x2F, 0x10, 0x28, 0x34, 0xFA,
	0x00, 0x00, 0x7B, 0x00, 0x00,
	0x08, 0x14, 0x2A, 0x14, 0x22,
	0x22, 0x14, 0x2A, 0x14, 0x08,
	0xAA, 0x00, 0x55, 0x00, 0xAA,
	0xAA, 0x55, 0xAA, 0x55, 0xAA,
	0x00, 0x00, 0x00, 0xFF, 0x00,
	0x10, 0x10, 0x10, 0xFF, 0x00,
	0x14, 0x14, 0x14, 0xFF, 0x00,
	0x10, 0x10, 0xFF, 0x00, 0xFF,
	0x10, 0x10, 0xF0, 0x10, 0xF0,
	0x14, 0x14, 0x14, 0xFC, 0x00,
	0x14, 0x14, 0xF7, 0x00, 0xFF,
	0x00, 0x00, 0xFF, 0x00, 0xFF,
	0x14, 0x14, 0xF4, 0x04, 0xFC,
	0x14, 0x14, 0x17, 0x10, 0x1F,
	0x10, 0x10, 0x1F, 0x10, 0x1F,
	0x14, 0x14, 0x14, 0x1F, 0x00,
	0x10, 0x10, 0x10, 0xF0, 0x00,
	0x00, 0x00, 0x00, 0x1F, 0x10,
	0x10, 0x10, 0x10, 0x1F, 0x10,
	0x10, 0x10, 0x10, 0xF0, 0x10,
	0x00, 0x00, 0x00, 0xFF, 0x10,
	0x10, 0x10, 0x10, 0x10, 0x10,
	0x10, 0x10, 0x10, 0xFF, 0x10,
	0x00, 0x00, 0x00, 0xFF, 0x14,
	0x00, 0x00, 0xFF, 0x00, 0xFF,
	0x00, 0x00, 0x1F, 0x10, 0x17,
	0x00, 0x00, 0xFC, 0x04, 0xF4,
	0x14, 0x14, 0x17, 0x10, 0x17,
	0x14, 0x14, 0xF4, 0x04, 0xF4,
	0x00, 0x00, 0xFF, 0x00, 0xF7,
	0x14, 0x14, 0x14, 0x14, 0x14,
	0x14, 0x14, 0xF7, 0x00, 0xF7,
	0x14, 0x14, 0x14, 0x17, 0x14,
	0x10, 0x10, 0x1F, 0x10, 0x1F,
	0x14, 0x14, 0x14, 0xF4, 0x14,
	0x10, 0x10, 0xF0, 0x10, 0xF0,
	0x00, 0x00, 0x1F, 0x10, 0x1F,
	0x00, 0x00, 0x00, 0x1F, 0x14,
	0x00, 0x00, 0x00, 0xFC, 0x14,
	0x00, 0x00, 0xF0, 0x10, 0xF0,
	0x10, 0x10, 0xFF, 0x10, 0xFF,
	0x14, 0x14, 0x14, 0xFF, 0x14,
	0x10, 0x10, 0x10, 0x1F, 0x00,
	0x00, 0x00, 0x00, 0xF0, 0x10,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
	0xFF, 0xFF, 0xFF, 0x00, 0x00,
	0x00, 0x00, 0x00, 0xFF, 0xFF,
	0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
	0x38, 0x44, 0x44, 0x38, 0x44,
	0x7C, 0x2A, 0x2A, 0x3E, 0x14,
	0x7E, 0x02, 0x02, 0x06, 0x06,
	0x02, 0x7E, 0x02, 0x7E, 0x02,
	0x63, 0x55, 0x49, 0x41, 0x63,
	0x38, 0x44, 0x44, 0x3C, 0x04,
	0x40, 0x7E, 0x20, 0x1E, 0x20,
	0x06, 0x02, 0x7E, 0x02, 0x02,
	0x99, 0xA5, 0xE7, 0xA5, 0x99,
	0x1C, 0x2A, 0x49, 0x2A, 0x1C,
	0x4C, 0x72, 0x01, 0x72, 0x4C,
	0x30, 0x4A, 0x4D, 0x4D, 0x30,
	0x30, 0x48, 0x78, 0x48, 0x30,
	0xBC, 0x62, 0x5A, 0x46, 0x3D,
	0x3E, 0x49, 0x49, 0x49, 0x00,
	0x7E, 0x01, 0x01, 0x01, 0x7E,
	0x2A, 0x2A, 0x2A, 0x2A, 0x2A,
	0x44, 0x44, 0x5F, 0x44, 0x44,
	0x40, 0x51, 0x4A, 0x44, 0x40,
	0x40, 0x44, 0x4A, 0x51, 0x40,
	0x00, 0x00, 0xFF, 0x01, 0x03,
	0xE0, 0x80, 0xFF, 0x00, 0x00,
	0x08, 0x08, 0x6B, 0x6B, 0x08,
	0x36, 0x12, 0x36, 0x24, 0x36,
	0x06, 0x0F, 0x09, 0x0F, 0x06,
	0x00, 0x00, 0x18, 0x18, 0x00,
	0x00, 0x00, 0x10, 0x10, 0x00,
	0x30, 0x40, 0xFF, 0x01, 0x01,
	0x00, 0x1F, 0x01, 0x01, 0x1E,
	0x00, 0x19, 0x1D, 0x17, 0x12,
	0x00, 0x3C, 0x3C, 0x3C, 0x3C,
	0x00, 0x00, 0x00, 0x00, 0x00
};




const uint8_t const logo[] = {
  0x42, 0x4d, 0x3e, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x28, 0x00, 
  0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x02, 0xf3, 0xcf, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x7f, 0xc2, 0x43, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x01, 0xfb, 0x03, 0xc0, 0xdf, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x03, 0xfe, 0x03, 0xc0, 0x7f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x0f, 0xfe, 0x06, 0x60, 0x7f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x0b, 0x26, 0x07, 0xe0, 0x64, 0xd0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x3e, 0x3e, 0x07, 0xe0, 0x7c, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x6c, 0x3e, 0x06, 0x60, 0x7c, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x68, 0x22, 0x07, 0xe0, 0x44, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x38, 0x2e, 0x03, 0xc0, 0x74, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xf8, 0x1f, 0x07, 0xe0, 0xf8, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x98, 0x1f, 0xce, 0x73, 0xf8, 0x19, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xf8, 0x39, 0xce, 0x73, 0x9c, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x7f, 0x3f, 0xcf, 0xf3, 0xfc, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x3f, 0xbf, 0xd1, 0x8b, 0xfd, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x27, 0x9b, 0x3f, 0xfc, 0xd9, 0xe4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x37, 0x67, 0xff, 0xff, 0xe6, 0xec, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0xe7, 0x1c, 0x7f, 0x01, 0x80, 0xfe, 0x38, 0xe7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x01, 0xef, 0x87, 0xf1, 0xff, 0xff, 0x8f, 0xe1, 0xf7, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x03, 0x38, 0x83, 0x9e, 0x7f, 0xfe, 0x79, 0xc1, 0x1c, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x03, 0x3e, 0xc0, 0xff, 0xfd, 0xbf, 0xff, 0x03, 0x7c, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x01, 0x2d, 0x81, 0xfe, 0x07, 0xe0, 0x7f, 0x81, 0xb4, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x0f, 0x1f, 0x81, 0xe3, 0xff, 0xff, 0xc7, 0x81, 0xf8, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x1b, 0x6c, 0x00, 0x5f, 0x80, 0x01, 0xfa, 0x00, 0x36, 0xd8, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x18, 0xc7, 0x00, 0x78, 0x00, 0x00, 0x1e, 0x00, 0xe3, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x19, 0xa3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc5, 0x98, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x3b, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xdc, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x07, 0x3e, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7e, 0x7c, 0xe0, 0x00, 0x00, 0x00, 0x00, 
  0x05, 0x27, 0xb0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0d, 0xe4, 0xa0, 0x00, 0x00, 0x00, 0x00, 
  0x05, 0xbb, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xdd, 0xa0, 0x00, 0x00, 0x00, 0x00, 
  0x05, 0xdf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfb, 0xa0, 0x00, 0x00, 0x00, 0x00, 
  0x07, 0xdf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfb, 0xe0, 0x00, 0x00, 0x00, 0x00, 
  0x07, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xe0, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x9f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf9, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x03, 0x39, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x9c, 0xc0, 0x00, 0x00, 0x00, 0x00, 
  0x07, 0xd9, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x9b, 0xe0, 0x00, 0x00, 0x00, 0x00, 
  0x0c, 0xdf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfb, 0x30, 0x00, 0x00, 0x00, 0x00, 
  0x6c, 0x68, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0x36, 0x00, 0x00, 0x00, 0x00, 
  0xfe, 0xc0, 0x3f, 0xe7, 0xfe, 0x7f, 0xff, 0xcf, 0xe7, 0xfc, 0x03, 0x7f, 0x00, 0x00, 0x00, 0x00, 
  0x9f, 0xc0, 0x3f, 0xe7, 0xfe, 0x7f, 0xff, 0xcf, 0xe7, 0xfc, 0x03, 0xf9, 0x00, 0x00, 0x00, 0x00, 
  0x87, 0xe0, 0x0f, 0x00, 0xf8, 0x70, 0xe1, 0xc3, 0xc1, 0xe0, 0x07, 0xe1, 0x00, 0x00, 0x00, 0x00, 
  0xc5, 0xf0, 0x07, 0x00, 0x70, 0x60, 0xe0, 0xc0, 0xe1, 0xe0, 0x0f, 0xa3, 0x00, 0x00, 0x00, 0x00, 
  0x6c, 0x30, 0x07, 0x00, 0x70, 0x40, 0xe0, 0x40, 0x61, 0xe0, 0x0c, 0x36, 0x00, 0x00, 0x00, 0x01, 
  0xed, 0xf0, 0x07, 0x00, 0x70, 0x40, 0xe0, 0x40, 0x31, 0xe0, 0x0f, 0xb7, 0x80, 0x00, 0x00, 0x01, 
  0xeb, 0xe0, 0x07, 0x00, 0x70, 0x00, 0xe0, 0x00, 0x19, 0xe0, 0x07, 0xd7, 0x80, 0x00, 0x00, 0x01, 
  0x9b, 0x80, 0x07, 0x00, 0x70, 0x00, 0xe0, 0x00, 0x0d, 0xe0, 0x01, 0xd9, 0x80, 0x00, 0x00, 0x01, 
  0x99, 0x80, 0x07, 0xff, 0x70, 0x00, 0xe0, 0x00, 0x0f, 0xe0, 0x01, 0x99, 0x80, 0x00, 0x00, 0x00, 
  0xd3, 0x80, 0x07, 0xff, 0xf0, 0x00, 0xe0, 0x00, 0x0f, 0xe0, 0x01, 0xcb, 0x00, 0x00, 0x00, 0x00, 
  0xff, 0x00, 0x07, 0x7f, 0x70, 0x00, 0xe0, 0x00, 0x1f, 0xe0, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 
  0x9e, 0x00, 0x07, 0x00, 0x70, 0x00, 0xe0, 0x00, 0x3d, 0xe0, 0x00, 0x79, 0x00, 0x00, 0x00, 0x00, 
  0xf6, 0x00, 0x07, 0x00, 0x70, 0x00, 0xe0, 0x00, 0x79, 0xe0, 0x00, 0x6f, 0x00, 0x00, 0x00, 0x0e, 
  0x7c, 0x00, 0x07, 0x00, 0x70, 0x00, 0xe0, 0x00, 0xf1, 0xe0, 0x00, 0x3e, 0x70, 0x00, 0x00, 0x0f, 
  0xa3, 0x80, 0x07, 0x00, 0x70, 0x00, 0xe0, 0x01, 0xf1, 0xe0, 0x01, 0xc5, 0xf0, 0x00, 0x00, 0x09, 
  0x8e, 0xc0, 0x07, 0x00, 0x70, 0x00, 0xe0, 0x03, 0xe1, 0xe0, 0x03, 0x71, 0x90, 0x00, 0x00, 0x0f, 
  0x8c, 0x80, 0x0f, 0x00, 0x70, 0x00, 0xe0, 0x07, 0xc1, 0xe0, 0x01, 0x31, 0xf0, 0x00, 0x00, 0x07, 
  0xdf, 0x80, 0x1f, 0xc1, 0xfc, 0x03, 0xf8, 0x0f, 0x83, 0xf0, 0x01, 0xfb, 0xe0, 0x00, 0x00, 0x03, 
  0x0f, 0x00, 0x7f, 0xe7, 0xfe, 0x0f, 0xfe, 0x3e, 0x0f, 0xfc, 0x00, 0xf0, 0xc0, 0x00, 0x00, 0x00, 
  0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x00, 0x00, 
  0xd8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1b, 0x00, 0x00, 0x00, 0x01, 
  0x8c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x31, 0x80, 0x00, 0x00, 0x01, 
  0xac, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x35, 0x80, 0x00, 0x00, 0x02, 
  0xfb, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xdf, 0x40, 0x00, 0x00, 0x07, 
  0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xe0, 0x00, 0x00, 0x05, 
  0xed, 0x80, 0x1e, 0x18, 0xcc, 0xe2, 0x73, 0xdf, 0x79, 0x98, 0x01, 0xb7, 0xa0, 0x00, 0x00, 0x04, 
  0x33, 0x80, 0x3e, 0x38, 0x6c, 0xb2, 0x72, 0xdf, 0x3d, 0x98, 0x01, 0xcc, 0x20, 0x00, 0x00, 0x06, 
  0x37, 0x00, 0x36, 0x3c, 0x3c, 0x72, 0xf3, 0xc6, 0x39, 0xb0, 0x00, 0xec, 0x60, 0x00, 0x00, 0x03, 
  0xd7, 0x80, 0x1e, 0x3c, 0x3d, 0xe3, 0xf3, 0xc6, 0x78, 0xf0, 0x01, 0xeb, 0xc0, 0x00, 0x00, 0x00, 
  0xd7, 0x80, 0x0e, 0x7e, 0x7d, 0x83, 0xb0, 0xc6, 0x08, 0xf0, 0x01, 0xeb, 0x00, 0x00, 0x00, 0x01, 
  0xd1, 0x80, 0x06, 0x66, 0xed, 0xf3, 0x33, 0xc6, 0x7c, 0x60, 0x01, 0x8b, 0x80, 0x00, 0x00, 0x03, 
  0x1b, 0x00, 0x02, 0x42, 0xc8, 0x63, 0x33, 0x84, 0x78, 0x60, 0x00, 0xd8, 0xc0, 0x00, 0x00, 0x01, 
  0xde, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7b, 0x80, 0x00, 0x00, 0x00, 
  0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0x00, 0x00, 0x00, 0x00, 
  0x3d, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0xbc, 0x00, 0x00, 0x00, 0x00, 
  0x6f, 0x70, 0x1f, 0x71, 0x18, 0xe3, 0x60, 0xcc, 0xe1, 0xe0, 0x0e, 0xf6, 0x00, 0x00, 0x00, 0x00, 
  0x3e, 0xd8, 0x1f, 0x79, 0xb9, 0xf3, 0x60, 0xcc, 0xf3, 0xf0, 0x1b, 0x7c, 0x00, 0x00, 0x00, 0x00, 
  0x05, 0xd0, 0x0c, 0x19, 0xfb, 0x19, 0xe0, 0xcc, 0x1b, 0x30, 0x0b, 0xa0, 0x00, 0x00, 0x00, 0x00, 
  0x79, 0xf0, 0x0c, 0x79, 0xfb, 0x18, 0xe0, 0xfc, 0x1b, 0x10, 0x0f, 0x9e, 0x00, 0x00, 0x00, 0x00, 
  0xfd, 0xf0, 0x0c, 0xe1, 0xdb, 0x19, 0xe0, 0xcc, 0x1b, 0x30, 0x0f, 0xbf, 0x00, 0x00, 0x00, 0x00, 
  0x9e, 0x00, 0x0c, 0x79, 0xd9, 0xfb, 0x60, 0xcc, 0xf3, 0xf0, 0x00, 0x79, 0x00, 0x00, 0x00, 0x00, 
  0xfd, 0xf0, 0x0c, 0x79, 0x98, 0xf3, 0x60, 0xcc, 0xe1, 0xe0, 0x0f, 0xbf, 0x00, 0x00, 0x00, 0x00, 
  0x3b, 0x37, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xec, 0xdc, 0x00, 0x00, 0x00, 0x00, 
  0x03, 0x17, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xe8, 0xc0, 0x00, 0x00, 0x00, 0x00, 
  0x03, 0x5d, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xba, 0xc0, 0x00, 0x00, 0x00, 0x00, 
  0x01, 0xfd, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xbf, 0x80, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0xf3, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0xcf, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x03, 0xdb, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xdb, 0xc0, 0x00, 0x00, 0x00, 0x00, 
  0x03, 0x8f, 0xa0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0xf1, 0xc0, 0x00, 0x00, 0x00, 0x00, 
  0x03, 0x04, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x20, 0xc0, 0x00, 0x00, 0x00, 0x00, 
  0x03, 0xfe, 0x63, 0x80, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc6, 0x7f, 0xc0, 0x00, 0x00, 0x00, 0x00, 
  0x01, 0xfb, 0x76, 0x80, 0x00, 0x00, 0x00, 0x00, 0x01, 0x6e, 0xdf, 0x80, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x31, 0x9e, 0x80, 0x00, 0x00, 0x00, 0x00, 0x01, 0x79, 0x8c, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x37, 0xf7, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x03, 0xef, 0xec, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x1f, 0x77, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x03, 0xee, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x01, 0xf3, 0x83, 0x00, 0x00, 0x00, 0x00, 0xc1, 0xcf, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x01, 0xc2, 0x67, 0x80, 0x00, 0x00, 0x01, 0xe6, 0x43, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x31, 0xf4, 0x80, 0x00, 0x00, 0x01, 0x2f, 0x8c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0xfd, 0x9e, 0xf8, 0x00, 0x00, 0x1f, 0x79, 0xbf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x99, 0x0c, 0xe9, 0xdc, 0x3b, 0x97, 0x30, 0x99, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x01, 0x99, 0x88, 0xee, 0x76, 0x66, 0x77, 0x11, 0x99, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0xf9, 0xf7, 0x0f, 0x13, 0xc8, 0xf0, 0xef, 0x9f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x19, 0xe5, 0x89, 0x99, 0xa7, 0x98, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x30, 0x7f, 0x8f, 0xf1, 0xfe, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x63, 0x8f, 0xe6, 0x67, 0xf1, 0xc6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x67, 0x9d, 0x0f, 0xf0, 0xb9, 0xe6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x3d, 0xbf, 0x19, 0x98, 0xfd, 0xbc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x01, 0xe6, 0x33, 0xcc, 0x67, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0xee, 0x77, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};


uint32_t level1[48][4] ={
        {1, FIRST_BLOCK_CORD_X1, FIRST_BLOCK_CORD_Y1, RED},
        {1, FIRST_BLOCK_CORD_X1 - BLOCK_LEN, FIRST_BLOCK_CORD_Y1, RED},
        {1, FIRST_BLOCK_CORD_X1 - 2*BLOCK_LEN, FIRST_BLOCK_CORD_Y1, RED},
        {1, FIRST_BLOCK_CORD_X1 - 3*BLOCK_LEN, FIRST_BLOCK_CORD_Y1, RED},
        {1, FIRST_BLOCK_CORD_X1 - 4*BLOCK_LEN, FIRST_BLOCK_CORD_Y1, RED},
        {1, FIRST_BLOCK_CORD_X1 - 5*BLOCK_LEN, FIRST_BLOCK_CORD_Y1, RED},
        {1, FIRST_BLOCK_CORD_X1 - 6*BLOCK_LEN, FIRST_BLOCK_CORD_Y1, RED},
        {1, FIRST_BLOCK_CORD_X1 - 7*BLOCK_LEN, FIRST_BLOCK_CORD_Y1, RED},

        {1, FIRST_BLOCK_CORD_X1, FIRST_BLOCK_CORD_Y1 + BLOCK_THICC, ORANGE},
        {1, FIRST_BLOCK_CORD_X1 - BLOCK_LEN, FIRST_BLOCK_CORD_Y1 + BLOCK_THICC, ORANGE},
        {1, FIRST_BLOCK_CORD_X1 - 2*BLOCK_LEN, FIRST_BLOCK_CORD_Y1 + BLOCK_THICC, ORANGE},
        {1, FIRST_BLOCK_CORD_X1 - 3*BLOCK_LEN, FIRST_BLOCK_CORD_Y1 + BLOCK_THICC, ORANGE},
        {1, FIRST_BLOCK_CORD_X1 - 4*BLOCK_LEN, FIRST_BLOCK_CORD_Y1 + BLOCK_THICC, ORANGE},
        {1, FIRST_BLOCK_CORD_X1 - 5*BLOCK_LEN, FIRST_BLOCK_CORD_Y1 + BLOCK_THICC, ORANGE},
        {1, FIRST_BLOCK_CORD_X1 - 6*BLOCK_LEN, FIRST_BLOCK_CORD_Y1 + BLOCK_THICC, ORANGE},
        {1, FIRST_BLOCK_CORD_X1 - 7*BLOCK_LEN, FIRST_BLOCK_CORD_Y1 + BLOCK_THICC, ORANGE},

        {1, FIRST_BLOCK_CORD_X1, FIRST_BLOCK_CORD_Y1 + 2*BLOCK_THICC, YELLOW},
        {1, FIRST_BLOCK_CORD_X1 - BLOCK_LEN, FIRST_BLOCK_CORD_Y1 + 2*BLOCK_THICC, YELLOW},
        {1, FIRST_BLOCK_CORD_X1 - 2*BLOCK_LEN, FIRST_BLOCK_CORD_Y1 + 2*BLOCK_THICC, YELLOW},
        {1, FIRST_BLOCK_CORD_X1 - 3*BLOCK_LEN, FIRST_BLOCK_CORD_Y1 + 2*BLOCK_THICC, YELLOW},
        {1, FIRST_BLOCK_CORD_X1 - 4*BLOCK_LEN, FIRST_BLOCK_CORD_Y1 + 2*BLOCK_THICC, YELLOW},
        {1, FIRST_BLOCK_CORD_X1 - 5*BLOCK_LEN, FIRST_BLOCK_CORD_Y1 + 2*BLOCK_THICC, YELLOW},
        {1, FIRST_BLOCK_CORD_X1 - 6*BLOCK_LEN, FIRST_BLOCK_CORD_Y1 + 2*BLOCK_THICC, YELLOW},
        {1, FIRST_BLOCK_CORD_X1 - 7*BLOCK_LEN, FIRST_BLOCK_CORD_Y1 + 2*BLOCK_THICC, YELLOW},

        {1, FIRST_BLOCK_CORD_X1, FIRST_BLOCK_CORD_Y1 + 3*BLOCK_THICC, GREEN},
        {1, FIRST_BLOCK_CORD_X1 - BLOCK_LEN, FIRST_BLOCK_CORD_Y1 + 3*BLOCK_THICC, GREEN},
        {1, FIRST_BLOCK_CORD_X1 - 2*BLOCK_LEN, FIRST_BLOCK_CORD_Y1 + 3*BLOCK_THICC, GREEN},
        {1, FIRST_BLOCK_CORD_X1 - 3*BLOCK_LEN, FIRST_BLOCK_CORD_Y1 + 3*BLOCK_THICC, GREEN},
        {1, FIRST_BLOCK_CORD_X1 - 4*BLOCK_LEN, FIRST_BLOCK_CORD_Y1 + 3*BLOCK_THICC, GREEN},
        {1, FIRST_BLOCK_CORD_X1 - 5*BLOCK_LEN, FIRST_BLOCK_CORD_Y1 + 3*BLOCK_THICC, GREEN},
        {1, FIRST_BLOCK_CORD_X1 - 6*BLOCK_LEN, FIRST_BLOCK_CORD_Y1 + 3*BLOCK_THICC, GREEN},
        {1, FIRST_BLOCK_CORD_X1 - 7*BLOCK_LEN, FIRST_BLOCK_CORD_Y1 + 3*BLOCK_THICC, GREEN},

        {1, FIRST_BLOCK_CORD_X1, FIRST_BLOCK_CORD_Y1 + 4*BLOCK_THICC, BLUE},
        {1, FIRST_BLOCK_CORD_X1 - BLOCK_LEN, FIRST_BLOCK_CORD_Y1 + 4*BLOCK_THICC, BLUE},
        {1, FIRST_BLOCK_CORD_X1 - 2*BLOCK_LEN, FIRST_BLOCK_CORD_Y1 + 4*BLOCK_THICC, BLUE},
        {1, FIRST_BLOCK_CORD_X1 - 3*BLOCK_LEN, FIRST_BLOCK_CORD_Y1 + 4*BLOCK_THICC, BLUE},
        {1, FIRST_BLOCK_CORD_X1 - 4*BLOCK_LEN, FIRST_BLOCK_CORD_Y1 + 4*BLOCK_THICC, BLUE},
        {1, FIRST_BLOCK_CORD_X1 - 5*BLOCK_LEN, FIRST_BLOCK_CORD_Y1 + 4*BLOCK_THICC, BLUE},
        {1, FIRST_BLOCK_CORD_X1 - 6*BLOCK_LEN, FIRST_BLOCK_CORD_Y1 + 4*BLOCK_THICC, BLUE},
        {1, FIRST_BLOCK_CORD_X1 - 7*BLOCK_LEN, FIRST_BLOCK_CORD_Y1 + 4*BLOCK_THICC, BLUE},

        {1, FIRST_BLOCK_CORD_X1, FIRST_BLOCK_CORD_Y1 + 5*BLOCK_THICC, PURPLE},
        {1, FIRST_BLOCK_CORD_X1 - BLOCK_LEN, FIRST_BLOCK_CORD_Y1 + 5*BLOCK_THICC, PURPLE},
        {1, FIRST_BLOCK_CORD_X1 - 2*BLOCK_LEN, FIRST_BLOCK_CORD_Y1 + 5*BLOCK_THICC, PURPLE},
        {1, FIRST_BLOCK_CORD_X1 - 3*BLOCK_LEN, FIRST_BLOCK_CORD_Y1 + 5*BLOCK_THICC, PURPLE},
        {1, FIRST_BLOCK_CORD_X1 - 4*BLOCK_LEN, FIRST_BLOCK_CORD_Y1 + 5*BLOCK_THICC, PURPLE},
        {1, FIRST_BLOCK_CORD_X1 - 5*BLOCK_LEN, FIRST_BLOCK_CORD_Y1 + 5*BLOCK_THICC, PURPLE},
        {1, FIRST_BLOCK_CORD_X1 - 6*BLOCK_LEN, FIRST_BLOCK_CORD_Y1 + 5*BLOCK_THICC, PURPLE},
        {1, FIRST_BLOCK_CORD_X1 - 7*BLOCK_LEN, FIRST_BLOCK_CORD_Y1 + 5*BLOCK_THICC, PURPLE}
};

uint32_t level2 [26][4] = {
      {1, FIRST_BLOCK_CORD_X2 - 3*BLOCK_LEN, FIRST_BLOCK_CORD_Y2, GREEN},

      {1, FIRST_BLOCK_CORD_X2 - 2*BLOCK_LEN, FIRST_BLOCK_CORD_Y2 + BLOCK_THICC, YELLOW},
      {1, FIRST_BLOCK_CORD_X2 - 3*BLOCK_LEN, FIRST_BLOCK_CORD_Y2 + BLOCK_THICC, YELLOW},
      {1, FIRST_BLOCK_CORD_X2 - 4*BLOCK_LEN, FIRST_BLOCK_CORD_Y2 + BLOCK_THICC, YELLOW},

      {1, FIRST_BLOCK_CORD_X2 - BLOCK_LEN, FIRST_BLOCK_CORD_Y2 + 2*BLOCK_THICC, ORANGE},
      {1, FIRST_BLOCK_CORD_X2 - 2*BLOCK_LEN, FIRST_BLOCK_CORD_Y2 + 2*BLOCK_THICC, ORANGE},
      {1, FIRST_BLOCK_CORD_X2 - 3*BLOCK_LEN, FIRST_BLOCK_CORD_Y2 + 2*BLOCK_THICC, ORANGE},
      {1, FIRST_BLOCK_CORD_X2 - 4*BLOCK_LEN, FIRST_BLOCK_CORD_Y2 + 2*BLOCK_THICC, ORANGE},
      {1, FIRST_BLOCK_CORD_X2 - 5*BLOCK_LEN, FIRST_BLOCK_CORD_Y2 + 2*BLOCK_THICC, ORANGE},

      {1, FIRST_BLOCK_CORD_X2, FIRST_BLOCK_CORD_Y2 + 3*BLOCK_THICC, RED},
      {1, FIRST_BLOCK_CORD_X2 - BLOCK_LEN, FIRST_BLOCK_CORD_Y2 + 3*BLOCK_THICC, RED},
      {1, FIRST_BLOCK_CORD_X2 - 2*BLOCK_LEN, FIRST_BLOCK_CORD_Y2 + 3*BLOCK_THICC, RED},
      {1, FIRST_BLOCK_CORD_X2 - 3*BLOCK_LEN, FIRST_BLOCK_CORD_Y2 + 3*BLOCK_THICC, RED},
      {1, FIRST_BLOCK_CORD_X2 - 4*BLOCK_LEN, FIRST_BLOCK_CORD_Y2 + 3*BLOCK_THICC, RED},
      {1, FIRST_BLOCK_CORD_X2 - 5*BLOCK_LEN, FIRST_BLOCK_CORD_Y2 + 3*BLOCK_THICC, RED},
      {1, FIRST_BLOCK_CORD_X2 - 6*BLOCK_LEN, FIRST_BLOCK_CORD_Y2 + 3*BLOCK_THICC, RED},

      {1, FIRST_BLOCK_CORD_X2 - BLOCK_LEN, FIRST_BLOCK_CORD_Y2 + 4*BLOCK_THICC, PURPLE},
      {1, FIRST_BLOCK_CORD_X2 - 2*BLOCK_LEN, FIRST_BLOCK_CORD_Y2 + 4*BLOCK_THICC, PURPLE},
      {1, FIRST_BLOCK_CORD_X2 - 3*BLOCK_LEN, FIRST_BLOCK_CORD_Y2 + 4*BLOCK_THICC, PURPLE},
      {1, FIRST_BLOCK_CORD_X2 - 4*BLOCK_LEN, FIRST_BLOCK_CORD_Y2 + 4*BLOCK_THICC, PURPLE},
      {1, FIRST_BLOCK_CORD_X2 - 5*BLOCK_LEN, FIRST_BLOCK_CORD_Y2 + 4*BLOCK_THICC, PURPLE},

      {1, FIRST_BLOCK_CORD_X2 - 2*BLOCK_LEN, FIRST_BLOCK_CORD_Y2 + 5*BLOCK_THICC, BLUE},
      {1, FIRST_BLOCK_CORD_X2 - 3*BLOCK_LEN, FIRST_BLOCK_CORD_Y2 + 5*BLOCK_THICC, BLUE},
      {1, FIRST_BLOCK_CORD_X2 - 4*BLOCK_LEN, FIRST_BLOCK_CORD_Y2 + 5*BLOCK_THICC, BLUE},

      {1, FIRST_BLOCK_CORD_X2 - 3*BLOCK_LEN, FIRST_BLOCK_CORD_Y2 + 6*BLOCK_THICC, LIGHTGREY},

};

uint32_t level3 [51][4] = {
        {1, FIRST_BLOCK_CORD_X3 - BLOCK_LEN, FIRST_BLOCK_CORD_Y3, YELLOW},
        {1, FIRST_BLOCK_CORD_X3 - 2*BLOCK_LEN, FIRST_BLOCK_CORD_Y3, YELLOW},
        {1, FIRST_BLOCK_CORD_X3 - 3*BLOCK_LEN, FIRST_BLOCK_CORD_Y3, YELLOW},
        
        {1, FIRST_BLOCK_CORD_X3, FIRST_BLOCK_CORD_Y3 + BLOCK_THICC, YELLOW},
        {1, FIRST_BLOCK_CORD_X3 - BLOCK_LEN, FIRST_BLOCK_CORD_Y3 + BLOCK_THICC, YELLOW},
        {1, FIRST_BLOCK_CORD_X3 - 2*BLOCK_LEN, FIRST_BLOCK_CORD_Y3 + BLOCK_THICC, BLUE},
        {1, FIRST_BLOCK_CORD_X3 - 3*BLOCK_LEN, FIRST_BLOCK_CORD_Y3 + BLOCK_THICC, YELLOW},
        {1, FIRST_BLOCK_CORD_X3 - 4*BLOCK_LEN, FIRST_BLOCK_CORD_Y3 + BLOCK_THICC, YELLOW},
       
        {1, FIRST_BLOCK_CORD_X3, FIRST_BLOCK_CORD_Y3 + 2*BLOCK_THICC, YELLOW},
        {1, FIRST_BLOCK_CORD_X3 - BLOCK_LEN, FIRST_BLOCK_CORD_Y3 + 2*BLOCK_THICC, YELLOW},
        {1, FIRST_BLOCK_CORD_X3 - 2*BLOCK_LEN, FIRST_BLOCK_CORD_Y3 + 2*BLOCK_THICC, YELLOW},
        {1, FIRST_BLOCK_CORD_X3 - 3*BLOCK_LEN, FIRST_BLOCK_CORD_Y3 + 2*BLOCK_THICC, YELLOW},

        {1, FIRST_BLOCK_CORD_X3, FIRST_BLOCK_CORD_Y3 + 3*BLOCK_THICC, YELLOW},
        {1, FIRST_BLOCK_CORD_X3 - BLOCK_LEN, FIRST_BLOCK_CORD_Y3 + 3*BLOCK_THICC, YELLOW},
        {1, FIRST_BLOCK_CORD_X3 - 2*BLOCK_LEN, FIRST_BLOCK_CORD_Y3 + 3*BLOCK_THICC, YELLOW},

        {1, FIRST_BLOCK_CORD_X3, FIRST_BLOCK_CORD_Y3 + 4*BLOCK_THICC, YELLOW},
        {1, FIRST_BLOCK_CORD_X3 - BLOCK_LEN, FIRST_BLOCK_CORD_Y3 + 4*BLOCK_THICC, YELLOW},
        {1, FIRST_BLOCK_CORD_X3 - 4*BLOCK_LEN, FIRST_BLOCK_CORD_Y3 + 4*BLOCK_THICC, LIGHTGREY},
        {1, FIRST_BLOCK_CORD_X3 - 6*BLOCK_LEN, FIRST_BLOCK_CORD_Y3 + 4*BLOCK_THICC, LIGHTGREY},

        {1, FIRST_BLOCK_CORD_X3, FIRST_BLOCK_CORD_Y3 + 5*BLOCK_THICC, YELLOW},
        {1, FIRST_BLOCK_CORD_X3 - BLOCK_LEN, FIRST_BLOCK_CORD_Y3 + 5*BLOCK_THICC, YELLOW},
        {1, FIRST_BLOCK_CORD_X3 - 2*BLOCK_LEN, FIRST_BLOCK_CORD_Y3 + 5*BLOCK_THICC, YELLOW},

        {1, FIRST_BLOCK_CORD_X3, FIRST_BLOCK_CORD_Y3 + 6*BLOCK_THICC, YELLOW},
        {1, FIRST_BLOCK_CORD_X3 - BLOCK_LEN, FIRST_BLOCK_CORD_Y3 + 6*BLOCK_THICC, YELLOW},
        {1, FIRST_BLOCK_CORD_X3 - 2*BLOCK_LEN, FIRST_BLOCK_CORD_Y3 + 6*BLOCK_THICC, YELLOW},
        {1, FIRST_BLOCK_CORD_X3 - 3*BLOCK_LEN, FIRST_BLOCK_CORD_Y3 + 6*BLOCK_THICC, YELLOW},

        {1, FIRST_BLOCK_CORD_X3, FIRST_BLOCK_CORD_Y3 + 7*BLOCK_THICC, YELLOW},
        {1, FIRST_BLOCK_CORD_X3 - BLOCK_LEN, FIRST_BLOCK_CORD_Y3 + 7*BLOCK_THICC, YELLOW},
        {1, FIRST_BLOCK_CORD_X3 - 2*BLOCK_LEN, FIRST_BLOCK_CORD_Y3 + 7*BLOCK_THICC, YELLOW},
        {1, FIRST_BLOCK_CORD_X3 - 3*BLOCK_LEN, FIRST_BLOCK_CORD_Y3 + 7*BLOCK_THICC, YELLOW},
        {1, FIRST_BLOCK_CORD_X3 - 4*BLOCK_LEN, FIRST_BLOCK_CORD_Y3 + 7*BLOCK_THICC, YELLOW},

        {1, FIRST_BLOCK_CORD_X3 - BLOCK_LEN, FIRST_BLOCK_CORD_Y3 + 8*BLOCK_THICC, YELLOW},
        {1, FIRST_BLOCK_CORD_X3 - 2*BLOCK_LEN, FIRST_BLOCK_CORD_Y3 + 8*BLOCK_THICC, YELLOW},
        {1, FIRST_BLOCK_CORD_X3 - 3*BLOCK_LEN, FIRST_BLOCK_CORD_Y3 + 8*BLOCK_THICC, YELLOW},      
};