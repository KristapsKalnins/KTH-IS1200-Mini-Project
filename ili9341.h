#ifndef _ILI9341_H_
#define _ILI9341_H_

#include <stdint.h>

#define DISPLAY_VDD_PORT PORTF
#define DISPLAY_VDD_MASK 0x2
#define DISPLAY_VLED_PORT PORTD
#define DISPLAT_VLED_MASK 0x4
#define DISPLAY_COMMAND_DATA_PORT PORTD
#define DISPLAY_COMMAND_DATA_MASK 0x2
#define DISPLAY_RESET_PORT PORTD
#define DISPLAY_RESET_MASK 0x200
#define DISPLAY_SELECT_PORT PORTD
#define DISPLAY_SELECT_MASK 0x1

#define BLACK       0x0000      
#define NAVY        0x7800        
#define DARKGREEN   0x03E0      
#define DARKCYAN    0xFD20 
#define MAROON      0x000F    
#define PURPLE      0x780F      
#define OLIVE       0x7BE0      
#define LIGHTGREY   0xC618      
#define DARKGREY    0x7BEF      
#define BLUE        0xF800     
#define GREEN       0x07E0      
#define CYAN        0xFFE0
#define RED         0x001F     
#define MAGENTA     0xF81F      
#define YELLOW      0x07FF   
#define WHITE       0xFFFF      
#define ORANGE      0x03EF  
#define GREENYELLOW 0xAFE5     
#define PINK        0xF81F

void delay_ms(int c);
void spi_initialize(void);
void setAddress(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);
void hard_reset(void);
void display_init(void);
void drawPixel(uint16_t x1, uint16_t y1, uint32_t color);
//void clear(uint16_t colour);
void write_data_8(uint8_t data);
void write_cmd_8(uint8_t com);
void fillSceen(uint16_t color);
void fillRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h,uint16_t color);
void drawPaddle(uint16_t x, uint16_t y, uint16_t color);
void drawBitmap(const uint8_t* icon);
void drawCircle(int16_t x0, int16_t y0, int16_t r, uint32_t color);


#endif