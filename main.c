#include <pic32mx.h>
#include "ili9341.h"
#include "spi.h"
#include "assets.h"
#include "control.h"

#define PADDLE_COLOR MAGENTA
#define BG_COLOR BLACK
#define GAME_SPEED 100
#define PADDLE_Y 270
#define PADDLE_THICKNESS 10
#define PADDLE_LENGTH 50
#define BLOCK_THICC 15
#define BLOCK_LEN 30
#define MENUTEXTCOL BLACK
#define MENUTEXTBGCOL WHITE

#define BALL_R 5

int ballX = 130;
int ballY = 220;
int updateX = 1;
int updateY = -1;
int ballCounter = 0;

int xCord;
int lastxCord;
int counter = 0;



void updateBall() {
    drawCircle(ballX, ballY, BALL_R, BG_COLOR);
    ballX = ballX + updateX;
    ballY = ballY + updateY;
    drawCircle(ballX, ballY, BALL_R, WHITE);
}

void advance () {
    int i;
    for(i = 0; i < 48; i++){
        if(level1[i][0] == 1){
            if
            (
                ballX >= level1[i][1] - BALL_R &&
                ballX <= (level1[i][1] + BLOCK_LEN + BALL_R) &&
                ballY >= level1[i][2] - BALL_R &&
                ballY <= (level1[i][2] + BLOCK_THICC + BALL_R)
            )
                {   
                    if(ballX + BALL_R == level1[i][1] || ballX - BALL_R == level1[i][1] + BLOCK_LEN)
                    {
                        updateX = updateX * -1;
                        goto over;
                    }
                    updateY = updateY * -1;
                    over:
                    level1[i][0] = 0;
                    drawBlock(level1[i][1], level1[i][2], BG_COLOR);
                    goto out;
                }
        }
    }
    out:

    if(
        ballX >= xCord - BALL_R &&
        ballX <= (xCord + PADDLE_LENGTH / 2 + BALL_R) &&
        ballY >= PADDLE_Y - BALL_R - 1 &&
        ballY <= (PADDLE_Y + PADDLE_THICKNESS + BALL_R)
    )
        {
            if(updateX > 0){
                updateX = updateX * -1;
            }
            updateY = updateY * -1;
        }

    if(
        ballX > xCord + PADDLE_LENGTH/2 - BALL_R &&
        ballX <= (xCord + PADDLE_LENGTH + BALL_R) &&
        ballY >= PADDLE_Y - BALL_R - 1 &&
        ballY <= (PADDLE_Y + PADDLE_THICKNESS + BALL_R)
    )
        {
            if(updateX < 0){
                updateX = updateX * -1;
            }
            updateY = updateY * -1;
        }


    if(ballX >= 240 - BALL_R || ballX == BALL_R){
        updateX = updateX * -1;
    }

    if(ballY >= 320 - BALL_R || ballY == BALL_R){
        updateY = updateY * -1;
    }

    updateBall();
}

int calcCord(int c){
    return c > 0 ? ((191 * c)/1024) : 0;
}

void inputRead() { 
    int analogIN1;
    int analogIN2;

    IFSCLR(1) = 0x2; //clears the ADC interrupt flag
    AD1CON1SET = 0x4; //Start sampling automatically
    while(!IFS(1) & 0x2); //While sampling, do nothing
            
    if (AD1CON2 & 0x80){
        analogIN1 = ADC1BUF0;
        analogIN2 = ADC1BUF1;   
    }
    else{
        analogIN1 = ADC1BUF8;
        analogIN2 = ADC1BUF9;
    }
    
    lastxCord = xCord;
    xCord = calcCord(analogIN1);


}

void drawLevel(char x){
    int i;
    if(x == 1){
        for(i = 0; i< 48 ;i++){
            drawBlock(level1[i][1], level1[i][2], level1[i][3]);
        }
    }
     if(x == 2){
        for(i = 0; i< 26 ;i++){
            drawBlock(level2[i][1], level2[i][2], level2[i][3]);
        }
    }
     if(x == 3){
        for(i = 0; i< 51 ;i++){
            drawBlock(level3[i][1], level3[i][2], level3[i][3]);
        }
    }
}

void updatePaddle(){
    int diff;
    inputRead();
    diff = xCord - lastxCord;
    if ((diff < 50) || (diff > -50)){
        if(diff > 0){
            fillRect(lastxCord,
                    PADDLE_Y,
                    diff,
                    10,
                    BG_COLOR);

            fillRect(xCord + (50 - diff),
                    PADDLE_Y,
                    diff,
                    10,
                    PADDLE_COLOR);
        }
        else{
            fillRect(lastxCord + (50+diff),
                    PADDLE_Y,
                    (diff * -1),
                    10,
                    BG_COLOR);
            
            fillRect(xCord,
                    PADDLE_Y,
                    (diff * -1),
                    10,
                    PADDLE_COLOR);
        }
    }
    else{
        drawPaddle(lastxCord, PADDLE_Y, BG_COLOR);
        drawPaddle(xCord, PADDLE_Y, PADDLE_COLOR);
    }
}


void splash(){
	fillSceen(WHITE);
	setCursor(10,50);
  setTextSize(4);
  setTextColor(BLACK, WHITE);
  setWrap(0);
  writeString("BREAKOUT!");
	while(1){
		if(getbtns() & 0x2)
			break;
		setCursor(50, 260);
		setTextSize(1);
		setTextColor(BLACK, WHITE);
		writeString("Press BTN1 to START!");
		delay_ms(500);
		if(getbtns() & 0x2)
			break;
		setCursor(50, 260);
		setTextSize(1);
		setTextColor(WHITE, WHITE);
		writeString("Press BTN1 to START!");
		delay_ms(500);
		}
}
void drawMenuSPtext(uint32_t tcol, uint32_t bcol){
    setTextColor(tcol, bcol);
    setCursor(45,50);
    writeString("Single-Player");
}
void drawMenuMPtext(uint32_t tcol, uint32_t bcol){
    setTextColor(tcol, bcol);
    setCursor(52, 125);
	writeString("Multi-Player");
}
void drawMenuSMtext(uint32_t tcol, uint32_t bcol){
    setTextColor(tcol, bcol);
    setCursor(90, 200);
	writeString("Stuff");
}
void drawLevelText1(uint32_t tcol, uint32_t bcol){
    setTextColor(tcol, bcol);
    setCursor(45,50);
    writeString("Level 1");
}
void drawLevelText2(uint32_t tcol, uint32_t bcol){
    setTextColor(tcol, bcol);
    setCursor(52, 125);
	writeString("Level 2");
}
void drawLevelText3(uint32_t tcol, uint32_t bcol){
    setTextColor(tcol, bcol);
    setCursor(90, 200);
	writeString("Level 3");
}

void levelSelect(){
    fillSceen(WHITE);
    setTextSize(2);
    drawLevelText1(MENUTEXTCOL,MENUTEXTBGCOL);
    drawLevelText2(MENUTEXTCOL,MENUTEXTBGCOL);
    drawLevelText3(MENUTEXTCOL,MENUTEXTBGCOL);
    while(1){
        inputRead();
        if(xCord >= 160 && xCord <=240){
            drawLevelText3(MENUTEXTCOL,MENUTEXTBGCOL);
            drawLevelText2(MENUTEXTCOL,MENUTEXTBGCOL);
            drawLevelText1(MENUTEXTBGCOL,MENUTEXTCOL);
            while(xCord >= 160 && xCord <=240){
                inputRead();
                if (getbtns() & 0x2){
                    goto done;
                }
            }
        }
        else if(xCord >= 80 && xCord <=160){
            drawLevelText1(MENUTEXTCOL,MENUTEXTBGCOL);
            drawLevelText3(MENUTEXTCOL,MENUTEXTBGCOL);
            drawLevelText2(MENUTEXTBGCOL,MENUTEXTCOL);
            while(xCord >= 80 && xCord <=160){
                inputRead();
                if (getbtns() & 0x2){
                    goto done;
                }
            }
        }
		else if(xCord >= 0 && xCord <=80){
            drawLevelText1(MENUTEXTCOL,MENUTEXTBGCOL);
            drawLevelText2(MENUTEXTCOL,MENUTEXTBGCOL);
            drawLevelText3(MENUTEXTBGCOL,MENUTEXTCOL);
            while(xCord >= 0 && xCord <=80){
                inputRead();
                if (getbtns() & 0x2){
                    goto done;
                }
            }
        }
	}	
    done:;
}






void mainMenu(){
	fillSceen(WHITE);
    setTextSize(2);
    drawMenuSPtext(MENUTEXTCOL, MENUTEXTBGCOL);
    drawMenuMPtext(MENUTEXTCOL, MENUTEXTBGCOL);
    drawMenuSMtext(MENUTEXTCOL, MENUTEXTBGCOL);
	while(1){
        inputRead();
        if(xCord >= 160 && xCord <=240){
            drawMenuMPtext(MENUTEXTCOL, MENUTEXTBGCOL);
            drawMenuSMtext(MENUTEXTCOL, MENUTEXTBGCOL);
            drawMenuSPtext(MENUTEXTBGCOL, MENUTEXTCOL);
            while(xCord >= 160 && xCord <=240){
                inputRead();
                if (getbtns() & 0x2){
                    goto done;
                }
            }
        }
        else if(xCord >= 80 && xCord <=160){
            inputRead();
            drawMenuSPtext(MENUTEXTCOL, MENUTEXTBGCOL);
            drawMenuSMtext(MENUTEXTCOL, MENUTEXTBGCOL);
            drawMenuMPtext(MENUTEXTBGCOL, MENUTEXTCOL);
            while(xCord >= 80 && xCord <=160){
                inputRead();
                if (getbtns() & 0x2){
                    goto done;
                }
            }
        }
		else if(xCord >= 0 && xCord <=80){
            drawMenuSPtext(MENUTEXTCOL, MENUTEXTBGCOL);
            drawMenuMPtext(MENUTEXTCOL, MENUTEXTBGCOL);
            drawMenuSMtext(MENUTEXTBGCOL, MENUTEXTCOL);
            while(xCord >= 0 && xCord <=80){
                inputRead();
                if (getbtns() & 0x2){
                    goto done;
                }
            }
        }
	}	
    done:;
}











int main(void){
    display_init();
    rotate(1);
    enablePots();
    splash();
    mainMenu();
    levelSelect();
    fillSceen(BG_COLOR);
    drawCircle(ballX, ballY, BALL_R, WHITE);
    drawLevel(1);
    // setCursor(100,100);
    // setTextSize(5);
    // setTextColor(GREEN, YELLOW);
    // setWrap(0);
    //writeString("TEST");
    //drawBitmap(0, 0, logo, 200, 200, BLUE);

    IECSET(1)=0x2;
    enableTimer2(3, 0x18, 0x111, 1);
    enable_interrupt();

   

   
    return 0;
}

void timer2_interrupt_handler(void)
{
    IFSCLR(0) = 0x100;
    counter++;

    if(counter != GAME_SPEED ){return;}
    counter = 0;

    if(getbtns() != 0)
    {
        if(getbtns() & 4)
        {
            //stuff for BTN4
        }
        if(getbtns() & 2)
        {
            //stuff for BTN3
        }
        if(getbtns() & 1)
        {
            //stuff for BTN2
        }
        
    }
        updatePaddle();
         //drawChar(0,0,'a', BLUE, BLUE, 5);
    ballCounter++;

    if(ballCounter == 50){
        ballCounter = 0;
        advance();

    }

}