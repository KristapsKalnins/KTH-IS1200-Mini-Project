#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h> 
#include "ili9341.h"
#define FIRST_BLOCK_CORD_X 180
#define FIRST_BLOCK_CORD_Y 40
#define BLOCK_THICC 15
#define BLOCK_LEN 30

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

uint32_t level1[25][4] =
    {
        {1, FIRST_BLOCK_CORD_X, FIRST_BLOCK_CORD_Y, RED},
        {1, FIRST_BLOCK_CORD_X - BLOCK_LEN - 2, FIRST_BLOCK_CORD_Y, RED},
        {1, FIRST_BLOCK_CORD_X - 2*BLOCK_LEN - 4, FIRST_BLOCK_CORD_Y, RED},
        {1, FIRST_BLOCK_CORD_X - 3*BLOCK_LEN - 6, FIRST_BLOCK_CORD_Y, RED},
        {1, FIRST_BLOCK_CORD_X - 4*BLOCK_LEN - 8, FIRST_BLOCK_CORD_Y, RED},

        {1, FIRST_BLOCK_CORD_X, FIRST_BLOCK_CORD_Y + BLOCK_THICC + 2, YELLOW},
        {1, FIRST_BLOCK_CORD_X - BLOCK_LEN - 2, FIRST_BLOCK_CORD_Y + BLOCK_THICC + 2, YELLOW},
        {1, FIRST_BLOCK_CORD_X - 2*BLOCK_LEN - 4, FIRST_BLOCK_CORD_Y + BLOCK_THICC + 2, YELLOW},
        {1, FIRST_BLOCK_CORD_X - 3*BLOCK_LEN - 6, FIRST_BLOCK_CORD_Y + BLOCK_THICC + 2, YELLOW},
        {1, FIRST_BLOCK_CORD_X - 4*BLOCK_LEN - 8, FIRST_BLOCK_CORD_Y + BLOCK_THICC + 2, YELLOW},

        {1, FIRST_BLOCK_CORD_X, FIRST_BLOCK_CORD_Y + 2*BLOCK_THICC + 4, GREEN},
        {1, FIRST_BLOCK_CORD_X - BLOCK_LEN - 2, FIRST_BLOCK_CORD_Y + 2*BLOCK_THICC + 4, GREEN},
        {1, FIRST_BLOCK_CORD_X - 2*BLOCK_LEN - 4, FIRST_BLOCK_CORD_Y + 2*BLOCK_THICC + 4, GREEN},
        {1, FIRST_BLOCK_CORD_X - 3*BLOCK_LEN - 6, FIRST_BLOCK_CORD_Y + 2*BLOCK_THICC + 4, GREEN},
        {1, FIRST_BLOCK_CORD_X - 4*BLOCK_LEN - 8, FIRST_BLOCK_CORD_Y + 2*BLOCK_THICC + 4, GREEN},

        {1, FIRST_BLOCK_CORD_X, FIRST_BLOCK_CORD_Y + 3*BLOCK_THICC + 6, BLUE},
        {1, FIRST_BLOCK_CORD_X - BLOCK_LEN - 2, FIRST_BLOCK_CORD_Y + 3*BLOCK_THICC + 6, BLUE},
        {1, FIRST_BLOCK_CORD_X - 2*BLOCK_LEN - 4, FIRST_BLOCK_CORD_Y + 3*BLOCK_THICC + 6, BLUE},
        {1, FIRST_BLOCK_CORD_X - 3*BLOCK_LEN - 6, FIRST_BLOCK_CORD_Y + 3*BLOCK_THICC + 6, BLUE},
        {1, FIRST_BLOCK_CORD_X - 4*BLOCK_LEN - 8, FIRST_BLOCK_CORD_Y + 3*BLOCK_THICC + 6, BLUE},

        {1, FIRST_BLOCK_CORD_X, FIRST_BLOCK_CORD_Y + 4*BLOCK_THICC + 8, PURPLE},
        {1, FIRST_BLOCK_CORD_X - BLOCK_LEN - 2, FIRST_BLOCK_CORD_Y + 4*BLOCK_THICC + 8, PURPLE},
        {1, FIRST_BLOCK_CORD_X - 2*BLOCK_LEN - 4, FIRST_BLOCK_CORD_Y + 4*BLOCK_THICC + 8, PURPLE},
        {1, FIRST_BLOCK_CORD_X - 3*BLOCK_LEN - 6, FIRST_BLOCK_CORD_Y + 4*BLOCK_THICC + 8, PURPLE},
        {1, FIRST_BLOCK_CORD_X - 4*BLOCK_LEN - 8, FIRST_BLOCK_CORD_Y + 4*BLOCK_THICC + 8, PURPLE}
}