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




const uint8_t const icon[] = {
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x83, 0x83, 0x83, 0x83, 0x1b, 0x1b, 0x1b, 0x83, 0x83, 0x38, 0x65, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x83, 0x83, 0x02, 0x72, 0x5e, 0x8a, 0x03, 0x4d, 0x03, 0x8a, 0x5e, 0x72, 0x02, 0x83, 0x65, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x83, 0x83, 0x5c, 0x05, 0x4d, 0x7a, 0x4b, 0x3d, 0x4f, 0x6a, 0x4f, 0x3d, 0x4b, 0x7a, 0x4d, 0x05, 0x5c, 0x38, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x1b, 0x82, 0x81, 0x4d, 0x10, 0x20, 0x4c, 0x4c, 0x4c, 0x4c, 0x4c, 0x4c, 0x4c, 0x4c, 0x4c, 0x20, 0x10, 0x4d, 0x81, 0x32, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x1b, 0x02, 0x45, 0x7a, 0x92, 0x4c, 0x4c, 0x4c, 0x4c, 0x4c, 0x4c, 0x4c, 0x4c, 0x4c, 0x4c, 0x4c, 0x4c, 0x4c, 0x92, 0x7a, 0x45, 0x02, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x1b, 0x02, 0x3f, 0x51, 0x4c, 0x4c, 0x4c, 0x4c, 0x4c, 0x4c, 0x4c, 0x4c, 0x4c, 0x4c, 0x4c, 0x4c, 0x4c, 0x4c, 0x4c, 0x4c, 0x4c, 0x10, 0x8a, 0x02, 0x0f, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x83, 0x82, 0x45, 0x51, 0x4c, 0x4c, 0x4c, 0x4c, 0x14, 0x14, 0x4c, 0x4c, 0x4c, 0x4c, 0x4c, 0x4c, 0x4c, 0x4c, 0x14, 0x14, 0x4c, 0x4c, 0x4c, 0x66, 0x45, 0x32, 0x40, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x83, 0x81, 0x7a, 0x4c, 0x4c, 0x4c, 0x4c, 0x4f, 0x35, 0x2c, 0x14, 0x4c, 0x4c, 0x4c, 0x4c, 0x4c, 0x4c, 0x4f, 0x01, 0x79, 0x14, 0x4c, 0x4c, 0x4c, 0x7a, 0x81, 0x65, 0x5a, 0x00, 0x00, 
  0x00, 0x83, 0x5c, 0x4d, 0x92, 0x4c, 0x4c, 0x4c, 0x4f, 0x07, 0x29, 0x37, 0x35, 0x4f, 0x4c, 0x6a, 0x14, 0x4c, 0x4f, 0x8f, 0x09, 0x6c, 0x14, 0x4f, 0x4c, 0x4c, 0x92, 0x4d, 0x5c, 0x84, 0x00, 0x00, 
  0x00, 0x83, 0x05, 0x10, 0x4c, 0x4c, 0x4c, 0x4f, 0x07, 0x5f, 0x23, 0x23, 0x46, 0x35, 0x14, 0x6a, 0x4c, 0x4f, 0x35, 0x87, 0x23, 0x23, 0x42, 0x6a, 0x14, 0x4c, 0x4c, 0x10, 0x05, 0x65, 0x00, 0x00, 
  0x83, 0x02, 0x4d, 0x20, 0x4c, 0x4c, 0x14, 0x8f, 0x46, 0x23, 0x23, 0x23, 0x23, 0x0d, 0x35, 0x3b, 0x4f, 0x49, 0x87, 0x23, 0x23, 0x23, 0x23, 0x3c, 0x79, 0x14, 0x4c, 0x20, 0x4d, 0x02, 0x76, 0x00, 
  0x83, 0x72, 0x7a, 0x4c, 0x4c, 0x4c, 0x14, 0x01, 0x43, 0x23, 0x23, 0x23, 0x23, 0x23, 0x63, 0x0b, 0x0b, 0x25, 0x23, 0x23, 0x23, 0x23, 0x23, 0x93, 0x26, 0x14, 0x4c, 0x4c, 0x7a, 0x72, 0x84, 0x00, 
  0x83, 0x5e, 0x4b, 0x4c, 0x4c, 0x4c, 0x4c, 0x3b, 0x2a, 0x2b, 0x23, 0x23, 0x23, 0x23, 0x23, 0x25, 0x78, 0x23, 0x23, 0x23, 0x23, 0x23, 0x19, 0x4f, 0x14, 0x4c, 0x4c, 0x4c, 0x4b, 0x5e, 0x65, 0x00, 
  0x83, 0x8a, 0x7f, 0x4c, 0x4c, 0x4c, 0x4c, 0x6a, 0x4f, 0x2a, 0x7d, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x19, 0x14, 0x4f, 0x14, 0x14, 0x4c, 0x4c, 0x3d, 0x8a, 0x38, 0x00, 
  0x1b, 0x03, 0x54, 0x20, 0x4c, 0x6a, 0x4c, 0x14, 0x14, 0x4f, 0x2a, 0x53, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x89, 0x92, 0x58, 0x58, 0x20, 0x14, 0x4c, 0x4c, 0x92, 0x03, 0x83, 0x00, 
  0x1b, 0x4d, 0x8b, 0x91, 0x7f, 0x6a, 0x6a, 0x4f, 0x3d, 0x66, 0x5d, 0x60, 0x85, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x19, 0x6b, 0x4d, 0x10, 0x7f, 0x92, 0x4f, 0x6a, 0x7f, 0x91, 0x4d, 0x1b, 0x00, 
  0x1b, 0x03, 0x12, 0x8b, 0x6d, 0x54, 0x92, 0x75, 0x3d, 0x4b, 0x27, 0x0a, 0x67, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x36, 0x48, 0x74, 0x7a, 0x4b, 0x3d, 0x7f, 0x15, 0x6d, 0x12, 0x03, 0x83, 0x00, 
  0x83, 0x8a, 0x17, 0x8b, 0x8b, 0x8b, 0x17, 0x7e, 0x27, 0x10, 0x64, 0x4a, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x52, 0x22, 0x4d, 0x15, 0x91, 0x8e, 0x8b, 0x8b, 0x17, 0x8a, 0x38, 0x00, 
  0x83, 0x5e, 0x50, 0x8b, 0x8b, 0x8b, 0x8b, 0x8b, 0x6e, 0x04, 0x0c, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x52, 0x8c, 0x41, 0x8b, 0x8b, 0x8b, 0x8b, 0x50, 0x5e, 0x65, 0x00, 
  0x38, 0x72, 0x91, 0x8b, 0x8b, 0x8b, 0x8b, 0x6e, 0x1d, 0x11, 0x23, 0x23, 0x23, 0x23, 0x23, 0x6f, 0x16, 0x23, 0x23, 0x23, 0x23, 0x23, 0x90, 0x44, 0x41, 0x8b, 0x8b, 0x8b, 0x91, 0x72, 0x40, 0x00, 
  0x65, 0x02, 0x64, 0x8e, 0x8b, 0x8b, 0x28, 0x57, 0x06, 0x23, 0x23, 0x23, 0x23, 0x23, 0x71, 0x47, 0x91, 0x59, 0x23, 0x23, 0x23, 0x23, 0x23, 0x88, 0x8e, 0x41, 0x8b, 0x8e, 0x64, 0x02, 0x21, 0x00, 
  0x00, 0x83, 0x05, 0x8d, 0x8b, 0x8b, 0x41, 0x62, 0x39, 0x23, 0x23, 0x23, 0x23, 0x1c, 0x6d, 0x6e, 0x6e, 0x54, 0x93, 0x23, 0x23, 0x23, 0x23, 0x7c, 0x68, 0x41, 0x8b, 0x8d, 0x05, 0x65, 0x00, 0x00, 
  0x00, 0x65, 0x5c, 0x0e, 0x8e, 0x8b, 0x8b, 0x41, 0x7b, 0x24, 0x23, 0x23, 0x77, 0x6d, 0x6e, 0x8b, 0x41, 0x6e, 0x54, 0x16, 0x23, 0x23, 0x5b, 0x6e, 0x41, 0x8b, 0x8e, 0x0e, 0x5c, 0x76, 0x00, 0x00, 
  0x00, 0x21, 0x38, 0x81, 0x91, 0x8b, 0x8b, 0x8b, 0x41, 0x68, 0x3e, 0x1c, 0x8e, 0x41, 0x12, 0x12, 0x12, 0x8b, 0x6e, 0x15, 0x2b, 0x2a, 0x18, 0x41, 0x8b, 0x8b, 0x91, 0x81, 0x0f, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x0f, 0x32, 0x45, 0x8d, 0x8b, 0x8b, 0x8b, 0x8b, 0x6d, 0x56, 0x3a, 0x2f, 0x31, 0x31, 0x2f, 0x2f, 0x3a, 0x8e, 0x30, 0x17, 0x8b, 0x8b, 0x8b, 0x8d, 0x45, 0x32, 0x21, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x0f, 0x02, 0x45, 0x8d, 0x8b, 0x8b, 0x8b, 0x8e, 0x17, 0x2f, 0x31, 0x80, 0x80, 0x80, 0x31, 0x3a, 0x3a, 0x17, 0x8e, 0x12, 0x8b, 0x8d, 0x45, 0x02, 0x40, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x0f, 0x02, 0x45, 0x91, 0x8e, 0x8b, 0x12, 0x3a, 0x31, 0x80, 0x61, 0x61, 0x61, 0x80, 0x3a, 0x12, 0x12, 0x8b, 0x8e, 0x91, 0x45, 0x02, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x32, 0x81, 0x0e, 0x8d, 0x8e, 0x3a, 0x80, 0x08, 0x13, 0x13, 0x61, 0x08, 0x31, 0x12, 0x8e, 0x8d, 0x0e, 0x81, 0x32, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x65, 0x5c, 0x05, 0x1f, 0x54, 0x2d, 0x55, 0x69, 0x13, 0x69, 0x55, 0x91, 0x54, 0x1f, 0x05, 0x5c, 0x0f, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5a, 0x84, 0x65, 0x02, 0x33, 0x73, 0x86, 0x1a, 0x92, 0x2e, 0x34, 0x1e, 0x33, 0x02, 0x65, 0x76, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x84, 0x38, 0x1b, 0x70, 0x4e, 0x70, 0x83, 0x65, 0x84, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
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
        {1, FIRST_BLOCK_CORD_X3, - BLOCK_LEN, FIRST_BLOCK_CORD_Y3 + 5*BLOCK_THICC, YELLOW},
        {1, FIRST_BLOCK_CORD_X3 - 2*BLOCK_LEN, FIRST_BLOCK_CORD_Y3 + 5*BLOCK_THICC, YELLOW},

        {1, FIRST_BLOCK_CORD_X3, FIRST_BLOCK_CORD_Y3 + 6*BLOCK_THICC, YELLOW},
        {1, FIRST_BLOCK_CORD_X3 - BLOCK_LEN, FIRST_BLOCK_CORD_Y3 + 6*BLOCK_THICC, YELLOW},
        {1, FIRST_BLOCK_CORD_X3 - 2*BLOCK_LEN, FIRST_BLOCK_CORD_Y3 + 6*BLOCK_THICC, YELLOW},
        {1, FIRST_BLOCK_CORD_X3 - 3*BLOCK_LEN, FIRST_BLOCK_CORD_Y3 + 6*BLOCK_THICC, YELLOW},

        {1, FIRST_BLOCK_CORD_X3, FIRST_BLOCK_CORD_Y3 + BLOCK_THICC, YELLOW},
        {1, FIRST_BLOCK_CORD_X3 - BLOCK_LEN, FIRST_BLOCK_CORD_Y3 + 7*BLOCK_THICC, YELLOW},
        {1, FIRST_BLOCK_CORD_X3 - 2*BLOCK_LEN, FIRST_BLOCK_CORD_Y3 + 7*BLOCK_THICC, YELLOW},
        {1, FIRST_BLOCK_CORD_X3 - 3*BLOCK_LEN, FIRST_BLOCK_CORD_Y3 + 7*BLOCK_THICC, YELLOW},
        {1, FIRST_BLOCK_CORD_X3 - 4*BLOCK_LEN, FIRST_BLOCK_CORD_Y3 + 7*BLOCK_THICC, YELLOW},

        {1, FIRST_BLOCK_CORD_X3 - BLOCK_LEN, FIRST_BLOCK_CORD_Y3 + 8*BLOCK_THICC, YELLOW},
        {1, FIRST_BLOCK_CORD_X3 - 2*BLOCK_LEN, FIRST_BLOCK_CORD_Y3 + 8*BLOCK_THICC, YELLOW},
        {1, FIRST_BLOCK_CORD_X3 - 3*BLOCK_LEN, FIRST_BLOCK_CORD_Y3 + 8*BLOCK_THICC, YELLOW},      
};