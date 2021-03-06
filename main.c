#include <pic32mx.h>
#include <stdlib.h>
#include "ili9341.h"
#include "spi.h"
#include "assets.h"
#include "control.h"

#define PADDLE_COLOR ORANGE
#define PADDLE2_COLOR LIGHTBLUE
#define BG_COLOR BLACK
// #define SCORE_COLOR YELLOW
#define GAME_SPEED 100
#define PADDLE_Y 270
#define PADDLE2_Y 40
#define PADDLE_THICKNESS 10
#define PADDLE_LENGTH 50
#define BLOCK_THICC 15
#define BLOCK_LEN 30
#define MENUTEXTCOL BLACK
#define MENUTEXTBGCOL WHITE
#define XSTART 120
#define YSTART 260
#define X2START 120
#define Y2START 60 

//Ball radius in pixels
#define BALL_R 5

int scoreInd = 0;
int scoreIndprev = -1;
int scoreInd2 = 0;
int scoreIndprev2 = -1;
int lifecount = 2;
int lifecount2 = 2;
int maxYHit;
int level = 0;

char hit = 0;
char p1Scorefix = 0;
char tophit = 0;

int ballX = XSTART;
int ballY = YSTART;
int ballSpeed;
int updateX = 1;
int updateY = -1;
int ballCounter = 0;
int multiPlayer = 0;
int hitInt = 0;

uint16_t xCord;
uint16_t x2Cord;
uint16_t lastxCord;
uint16_t lastx2Cord;
int counter = 0;



void updateBall() {
    drawCircleNF(ballX, ballY, BALL_R, BG_COLOR);
    if (updateX > 0 && updateY < 0 ){
        drawPixel(ballX-BALL_R+3, ballY + BALL_R-1, BG_COLOR);
        drawPixel(ballX-BALL_R+2, ballY + BALL_R-2, BG_COLOR);
        drawPixel(ballX-BALL_R+1, ballY + BALL_R-3, BG_COLOR);
    }
    else if(updateX < 0 && updateY > 0){
        drawPixel(ballX+BALL_R-3, ballY - BALL_R+1, BG_COLOR);
        drawPixel(ballX+BALL_R-2, ballY - BALL_R+2, BG_COLOR);
        drawPixel(ballX+BALL_R-1, ballY - BALL_R+3, BG_COLOR);
    }
    else if(updateX < 0 && updateY < 0){
        drawPixel(ballX+BALL_R-3, ballY + BALL_R-1, BG_COLOR);
        drawPixel(ballX+BALL_R-2, ballY + BALL_R-2, BG_COLOR);
        drawPixel(ballX+BALL_R-1, ballY + BALL_R-3, BG_COLOR);
    }
    else if(updateX > 0 && updateY > 0){
        drawPixel(ballX-BALL_R+3, ballY - BALL_R+1, BG_COLOR);
        drawPixel(ballX-BALL_R+2, ballY - BALL_R+2, BG_COLOR);
        drawPixel(ballX-BALL_R+1, ballY - BALL_R+3, BG_COLOR);
    }

    ballX = ballX + updateX;
    ballY = ballY + updateY;
    drawCircle(ballX, ballY, BALL_R, WHITE);
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
    xCord = calcCord(1024 -analogIN1);
    lastx2Cord = x2Cord;
    x2Cord = calcCord(1024 -analogIN2);


}


void gameOver(){
    if (multiPlayer == 0){
        if (lifecount == -1){
            fillSceen(RED);
            setCursor(60, 135);
            setTextColor(BLACK, RED);
            writeString("GAME OVER!");
            setCursor(70, 165);
            writeString("FINAL SCORE:");
            setCursor(25, 165);
            writeString(scoreOut[scoreInd]);
        }
        else{
            fillSceen(GREEN);
            setCursor(90, 135);
            setTextColor(BLACK, GREEN);
            writeString("WIN!");
            setCursor(70, 165);
            writeString("FINAL SCORE:");
            setCursor(25, 165);
            writeString(scoreOut[scoreInd]);
        }
    }
    else if(multiPlayer == 1){
        if (lifecount == -1 || lifecount2 == -1){
            fillSceen(RED);
            setCursor(60, 120);
            setTextColor(BLACK, RED);
            writeString("GAME OVER!");
            setCursor(60, 145);
            writeString("PLAYER1 SCORE:");
            setCursor(15, 145);
            setTextColor(PADDLE_COLOR, RED);
            writeString(scoreOut[scoreInd]);
            setCursor(60, 170);
            setTextColor(BLACK, RED);
            writeString("PLAYER2 SCORE:");
            setCursor(15, 170);
            setTextColor(PADDLE2_COLOR, RED);
            writeString(scoreOut[scoreInd2]);
            setTextColor(BLACK, RED);
            if (lifecount == -1) {
                setCursor(50, 195);
                writeString("PLAYER2 WINS!");
            }
            else if(lifecount2 == -1){
                setCursor(50, 195);
                writeString("PLAYER1 WINS!");
            }
            // else{
            //     setCursor(80, 195);
            //     writeString("DRAW!");
            // }
            
        }
        else{
            fillSceen(GREEN);
            setCursor(90, 120);
            setTextColor(BLACK, GREEN);
            writeString("WIN!");
            setCursor(60, 145);
            writeString("PLAYER1 SCORE:");
            setCursor(15, 145);
            setTextColor(PADDLE_COLOR, GREEN);
            writeString(scoreOut[scoreInd]);
            setCursor(60, 170);
            setTextColor(BLACK, GREEN);
            writeString("PLAYER2 SCORE:");
            setCursor( 15, 170);
            setTextColor(PADDLE2_COLOR, GREEN);
            writeString(scoreOut[scoreInd2]);
            setTextColor(BLACK, GREEN);
            if (scoreInd2 > scoreInd) {
                setCursor(50, 195);
                writeString("PLAYER2 WINS!");
            }
            else if(scoreInd2 < scoreInd){
                setCursor(50, 195);
                writeString("PLAYER1 WINS!");
            }
            else{
                setCursor(80, 195);
                writeString("DRAW!");
            }
        }
    }
for(;;);
}

int paddle1Hit = 0;
int paddle2Hit = 0;

void drawLife1(char c){
    if (c == 2){
    fillRect(226,0,14,14,PADDLE_COLOR);
    fillRect(211,0,14,14,PADDLE_COLOR);
    fillRect(196,0,14,14,PADDLE_COLOR);
    }
    else if(c == 1){
    fillRect(226,0,14,14,PADDLE_COLOR);
    fillRect(211,0,14,14,PADDLE_COLOR);
    }
    else if(c == 0){
      fillRect(226,0,14,14,PADDLE_COLOR);  
    }
}

void drawScoreText(){
    setCursor(34,0);
    setTextSize(2);
    setTextColor(PADDLE_COLOR, BG_COLOR);
    writeString("SCORE: ");
}

void drawScore(uint32_t color, uint32_t bg_color, int index){
    setCursor(1,0);
    setTextSize(2);
    setTextColor(color, bg_color);
    writeString(scoreOut[index]);
}



void advance () {

   if(multiPlayer == 0)
   {
        if(level == 1)
            if(scoreInd == 48)
                gameOver();
        if(level == 2)
            if(scoreInd == 25)
                gameOver();
        if(level == 3)
            if(scoreInd == 34)
                gameOver();



        if(hitInt == 1)
        {
            int i;
            for(i = 0; i < 48; i++){
                if(level1[i][0] == 1){
                    if(i == 7 || i == 15 || i == 23 || i == 31 || i == 39 || i == 47)
                        {
                            if
                            (
                                ballX >= level1[i][1] &&
                                ballX <= (level1[i][1] + BLOCK_LEN + BALL_R) &&
                                ballY >= level1[i][2] &&
                                ballY <= (level1[i][2] + BLOCK_THICC + BALL_R) 
                            )
                            goto yeet;
                        }
                    if
                    (
                        ballX >= level1[i][1] - BALL_R &&
                        ballX <= (level1[i][1] + BLOCK_LEN + BALL_R) &&
                        ballY >= level1[i][2] - BALL_R &&
                        ballY <= (level1[i][2] + BLOCK_THICC + BALL_R)
                    )
                        {   
                            yeet: ;
                            if(ballX + BALL_R == level1[i][1] || ballX - BALL_R == level1[i][1] + BLOCK_LEN)
                            {
                                updateX = updateX * -1;
                                goto over;
                            }
                            updateY = updateY * -1;
                            over:
                            level1[i][0] = 0;
                            drawBlock(level1[i][1], level1[i][2], BG_COLOR);
                            scoreIndprev = scoreInd;
                            scoreInd++;

                            goto out;
                        }
                }
            }
            out: ;
        }

        if(hitInt == 2)
        {
            int i;
            for(i = 0; i < 26; i++){
                if(level2[i][0] == 1){
                    if
                    (
                        ballX >= level2[i][1] - BALL_R &&
                        ballX <= (level2[i][1] + BLOCK_LEN + BALL_R) &&
                        ballY >= level2[i][2] - BALL_R &&
                        ballY <= (level2[i][2] + BLOCK_THICC + BALL_R)
                    )
                        {   
                            if(ballX + BALL_R == level2[i][1] || ballX - BALL_R == level2[i][1] + BLOCK_LEN)
                            {
                                updateX = updateX * -1;
                                goto over2;
                            }
                            updateY = updateY * -1;
                            over2:
                            level2[i][0] = 0;
                            drawBlock(level2[i][1], level2[i][2], BG_COLOR);
                            scoreIndprev = scoreInd;
                            scoreInd++;

                            goto out2;
                        }
                }
            }
            out2: ;
        }

        if(hitInt == 3)
        {
            int i;
            for(i = 0; i < 34; i++){
                if(level3[i][0] == 1){
                    if
                    (
                        ballX >= level3[i][1] - BALL_R &&
                        ballX <= (level3[i][1] + BLOCK_LEN + BALL_R) &&
                        ballY >= level3[i][2] - BALL_R &&
                        ballY <= (level3[i][2] + BLOCK_THICC + BALL_R)
                    )
                        {   
                            if(ballX + BALL_R == level3[i][1] || ballX - BALL_R == level3[i][1] + BLOCK_LEN)
                            {
                                updateX = updateX * -1;
                                goto over3;
                            }
                            updateY = updateY * -1;
                            over3:
                            level3[i][0] = 0;
                            drawBlock(level3[i][1], level3[i][2], BG_COLOR);
                            scoreIndprev = scoreInd;
                            scoreInd++;

                            goto out3;
                        }
                }
            }
            out3: ;
        }
    }

    if(multiPlayer == 1)
   {
        if(hitInt == 1)
        {
            int i;
            for(i = 0; i < 48; i++){
                if(mullevel1[i][0] == 1){
                    if(i == 7 || i == 15 || i == 23 || i == 31 || i == 39 || i == 47)
                        {
                            if
                            (
                                ballX >= mullevel1[i][1] &&
                                ballX <= (mullevel1[i][1] + BLOCK_LEN + BALL_R) &&
                                ballY >= mullevel1[i][2] &&
                                ballY <= (mullevel1[i][2] + BLOCK_THICC + BALL_R) 
                            )
                            goto yeetm;
                        }
                    if
                    (
                        ballX >= mullevel1[i][1] - BALL_R &&
                        ballX <= (mullevel1[i][1] + BLOCK_LEN + BALL_R) &&
                        ballY >= mullevel1[i][2] - BALL_R &&
                        ballY <= (mullevel1[i][2] + BLOCK_THICC + BALL_R)
                    )
                        {   
                            yeetm: ;
                            if(ballX + BALL_R == mullevel1[i][1] || ballX - BALL_R == mullevel1[i][1] + BLOCK_LEN)
                            {
                                updateX = updateX * -1;
                                goto overm;
                            }
                            updateY = updateY * -1;
                            overm:
                            mullevel1[i][0] = 0;
                            drawBlock(mullevel1[i][1], mullevel1[i][2], BG_COLOR);
                            if(hit == 0){
                            scoreIndprev = scoreInd;
                            scoreInd++;
                            }
                            else{
                            scoreIndprev2 = scoreInd2;
                            scoreInd2++;
                            }

                            goto outm;
                        }
                }
            }
            outm: ;
        }

        if(hitInt == 2)
        {
            int i;
            for(i = 0; i < 26; i++){
                if(mullevel2[i][0] == 1){
                    if
                    (
                        ballX >= mullevel2[i][1] - BALL_R &&
                        ballX <= (mullevel2[i][1] + BLOCK_LEN + BALL_R) &&
                        ballY >= mullevel2[i][2] - BALL_R &&
                        ballY <= (mullevel2[i][2] + BLOCK_THICC + BALL_R)
                    )
                        {   
                            if(ballX + BALL_R == mullevel2[i][1] || ballX - BALL_R == mullevel2[i][1] + BLOCK_LEN)
                            {
                                updateX = updateX * -1;
                                goto over2m;
                            }
                            updateY = updateY * -1;
                            over2m:
                            mullevel2[i][0] = 0;
                            drawBlock(mullevel2[i][1], mullevel2[i][2], BG_COLOR);
                            if(hit == 0){
                            scoreIndprev = scoreInd;
                            scoreInd++;
                            }
                            else{
                            scoreIndprev2 = scoreInd2;
                            scoreInd2++;
                            }

                            goto out2m;
                        }
                }
            }
            out2m: ;
        }

        if(hitInt == 3)
        {
            int i;
            for(i = 0; i < 34; i++){
                if(mullevel3[i][0] == 1){
                    if
                    (
                        ballX >= mullevel3[i][1] - BALL_R &&
                        ballX <= (mullevel3[i][1] + BLOCK_LEN + BALL_R) &&
                        ballY >= mullevel3[i][2] - BALL_R &&
                        ballY <= (mullevel3[i][2] + BLOCK_THICC + BALL_R)
                    )
                        {   
                            if(ballX + BALL_R == mullevel3[i][1] || ballX - BALL_R == mullevel3[i][1] + BLOCK_LEN)
                            {
                                updateX = updateX * -1;
                                goto over3m;
                            }
                            updateY = updateY * -1;
                            over3m:
                            mullevel3[i][0] = 0;
                            drawBlock(mullevel3[i][1], mullevel3[i][2], BG_COLOR);
                            if(hit == 0){
                            scoreIndprev = scoreInd;
                            scoreInd++;
                            }
                            else{
                            scoreIndprev2 = scoreInd2;
                            scoreInd2++;
                            }
                            goto out3m;
                        }
                }
            }
            out3m: ;
        }
    }

    if(multiPlayer == 0 || multiPlayer == 1){
        if(paddle1Hit == 0)
        {
            if(
                ballX >= xCord - BALL_R &&
                ballX < (xCord + PADDLE_LENGTH / 2 + BALL_R) &&
                ballY >= PADDLE_Y - BALL_R - 1 &&
                ballY <= (PADDLE_Y + PADDLE_THICKNESS + BALL_R)
            )
                {
                    if(updateX > 0){
                        updateX = updateX * -1;
                    }
                    updateY = updateY * -1;
                    paddle1Hit = 5;
                    hit = 0;
                    goto yamero;
                }

            if(
                ballX >= xCord + PADDLE_LENGTH/2 - BALL_R &&
                ballX <= (xCord + PADDLE_LENGTH + BALL_R) &&
                ballY >= PADDLE_Y - BALL_R - 1 &&
                ballY <= (PADDLE_Y + PADDLE_THICKNESS + BALL_R)
            )
                {
                    
                    if(ballX + BALL_R == xCord || ballX - BALL_R == xCord + PADDLE_LENGTH)
                        {
                            updateX = updateX * -1;
                            paddle1Hit = 5;
                            hit = 0;
                            goto yey;
                        }
                    if(updateX < 0)
                    {
                        updateX = updateX * -1;
                    }
                    updateY = updateY * -1;
                    paddle1Hit = 5;
                    hit = 0;
                    yey:;
                    yamero: ;
                }
        }


        if(ballX >= 240 - BALL_R || ballX == BALL_R)
        {
            if(maxYHit == 0){
                updateX = updateX * -1;
                maxYHit = 1;
            }
        }

        if(ballY == BALL_R)
        {
            
                updateY = updateY * -1;
                tophit = 1;

            
        }
        if(ballY >= 305 - BALL_R)
        {
            fillRect(ballX - BALL_R, ballY - BALL_R , BALL_R*2 + 1, BALL_R*2 + 1 , BG_COLOR);
            if(multiPlayer == 0)
            {
                ballX = XSTART;
                ballY = YSTART;
                updateX = 1;
                updateY = -1;
                hit = 0;
            }
            if(multiPlayer == 1)
            {
                ballX = X2START;
                ballY = Y2START;
                updateX = -1;
                updateY = 1;
                hit = 1;
            }
            if (lifecount == 2)
                fillRect(196, 0,14,14,BG_COLOR);
            else if (lifecount == 1)
                fillRect(211, 0, 14, 14, BG_COLOR);
            else{
                lifecount--;
                gameOver();
            }
            lifecount--;
            
        }
        if(tophit == 1)
            p1Scorefix++;
        if (p1Scorefix == 15){
            if (lifecount == 2)
                drawLife1(2);
            if (lifecount == 1)
                drawLife1(1);
            if (lifecount == 0)
                drawLife1(0);
            drawScoreText();
            drawScore(PADDLE_COLOR, BG_COLOR, scoreInd);
            p1Scorefix = 0;
            tophit = 0;
        }
    }

/*************************paddle2**********************************/

    if(multiPlayer == 1){

         if(level == 1){
            if((scoreInd + scoreInd2) == 48){
                gameOver();
            }
         }
        if(level == 2){
            if((scoreInd + scoreInd2) == 25){
                gameOver();
            }
        }
        if(level == 3){
            if((scoreInd + scoreInd2) == 34){
                gameOver();
            }
        }

        if(paddle2Hit == 0)
        {
            if(
                ballX >= x2Cord - BALL_R &&
                ballX < (x2Cord + PADDLE_LENGTH / 2 + BALL_R) &&
                ballY >= PADDLE2_Y - BALL_R - 1 &&
                ballY <= (PADDLE2_Y + PADDLE_THICKNESS + BALL_R)
            )
                {
                    if(updateX > 0){
                        updateX = updateX * -1;
                    }
                    updateY = updateY * -1;
                    paddle2Hit = 5;
                    hit = 1;      //score meme Kristaps
                    goto yamero2;
                }

            if(
                ballX >= x2Cord + PADDLE_LENGTH/2 - BALL_R &&
                ballX <= (x2Cord + PADDLE_LENGTH + BALL_R) &&
                ballY >= PADDLE2_Y - BALL_R - 1 &&
                ballY <= (PADDLE2_Y + PADDLE_THICKNESS + BALL_R)
            )
                {
                    
                    if(ballX + BALL_R == x2Cord || ballX - BALL_R == x2Cord + PADDLE_LENGTH)
                        {
                            updateX = updateX * -1;
                            paddle2Hit = 5;
                            hit = 1; // score meme Kristaps
                            goto yey2;
                        }
                    if(updateX < 0)
                    {
                        updateX = updateX * -1;
                    }
                    updateY = updateY * -1;
                    paddle2Hit = 5;
                    hit = 1;
                    yey2:;
                    yamero2: ;
                }
        }

        if(ballX >= 240 - BALL_R || ballX == BALL_R)
        {
            if(maxYHit == 0){
                updateX = updateX * -1;
                maxYHit = 1;
            }
        }

        if(ballY == BALL_R)
        {
            
                updateY = updateY * -1;
                
            
        }
        if(ballY <= 15 + BALL_R)
        {
            fillRect(ballX - BALL_R, ballY - BALL_R , BALL_R*2 + 1, BALL_R*2 + 1, BG_COLOR);
            ballX = XSTART;
            ballY = YSTART;
            hit = 0;
            updateX = 1;
            updateY = -1;
            if (lifecount2 == 2)
                fillRect(30, 306,14,14,BG_COLOR);
            else if (lifecount2 == 1)
                fillRect(15, 306, 14, 14, BG_COLOR);
            else{
                lifecount2--;
                gameOver();
            }
            lifecount2--;
        }
    }
    if(paddle1Hit > 0)
    {
        paddle1Hit = paddle1Hit - 1;
    }
    if(paddle2Hit > 0)
    {
        paddle2Hit = paddle2Hit - 1;
    }
    maxYHit = 0;

    updateBall();
}

int calcCord(int c){
    return c > 0 ? ((191 * c)/1024) : 0;
}



void drawLevel(char x){
    int i;
    if(multiPlayer == 0){
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
            for(i = 0; i< 34 ;i++){
                drawBlock(level3[i][1], level3[i][2], level3[i][3]);
            }
        }
    }

    if(multiPlayer == 1){
        if(x == 1){
            for(i = 0; i< 48 ;i++){
                drawBlock(mullevel1[i][1], mullevel1[i][2], mullevel1[i][3]);
            }
        }
        if(x == 2){
            for(i = 0; i< 26 ;i++){
                drawBlock(mullevel2[i][1], mullevel2[i][2], mullevel2[i][3]);
            }
        }
        if(x == 3){
            for(i = 0; i< 34 ;i++){
                drawBlock(mullevel3[i][1], mullevel3[i][2], mullevel3[i][3]);
            }
        }
    }
}

void updatePaddle(uint16_t x, uint16_t last, uint16_t height, uint32_t color){
    int diff = 0;
    diff = x - last;
    if ((diff < 50) | (diff > -50)){
        if(diff > 0){
            fillRect(last,
                    height,
                    diff,
                    10,
                    BG_COLOR);

            fillRect(x + (50 - diff),
                    height,
                    diff,
                    10,
                    color);
        }
        else{
            fillRect(last + (50+diff),
                    height,
                    (diff * -1),
                    10,
                    BG_COLOR);
            
            fillRect(x,
                    height,
                    (diff * -1),
                    10,
                    color);
        }
    }
    else{
        drawPaddle(last, height, BG_COLOR);
        drawPaddle(x, height, color);
    }
}


void splash(){
	fillSceen(WHITE);
    drawBitmap(64,95,logo, 128, 128, BLUE);
	setCursor(10,50);
  setTextSize(4);
  setTextColor(BLACK, WHITE);
  setWrap(0);
  writeString("BREAKOUT!");
	while(1){
		if(getbtns() & 0x4){
            while(getbtns() & 0x4);
			break;
        }
		setCursor(60, 260);
		setTextSize(1);
		setTextColor(BLACK, WHITE);
		writeString("Press BTN4 to START!");
		delay_sp(150);
		if(getbtns() & 0x4){
            while(getbtns() & 0x4);
			break;
        }
		setCursor(60, 260);
		setTextSize(1);
		setTextColor(WHITE, WHITE);
		writeString("Press BTN4 to START!");
		delay_sp(150);
		}
}
void drawMenuSPtext(uint32_t tcol, uint32_t bcol){
    setTextColor(tcol, bcol);
    setCursor(45,116);
    writeString("Single-Player");
}
void drawMenuMPtext(uint32_t tcol, uint32_t bcol){
    setTextColor(tcol, bcol);
    setCursor(50, 194);
	writeString("Multi-Player");
}
void drawLevelText1(uint32_t tcol, uint32_t bcol){
    setTextColor(tcol, bcol);
    setCursor(80,80);
    writeString("Level 1");
}
void drawLevelText2(uint32_t tcol, uint32_t bcol){
    setTextColor(tcol, bcol);
    setCursor(80, 155);
	writeString("Level 2");
}
void drawLevelText3(uint32_t tcol, uint32_t bcol){
    setTextColor(tcol, bcol);
    setCursor(80, 230);
	writeString("Level 3");
}

void drawScoreText2(){
    setCursor(156,306);
    setTextSize(2);
    setTextColor(PADDLE2_COLOR, BG_COLOR);
    writeString("SCORE: ");
}



void drawLife2(){
    fillRect(0,306,14,14, PADDLE2_COLOR);
    fillRect(15,306,14,14,PADDLE2_COLOR);
    fillRect(30,306,14,14, PADDLE2_COLOR);
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
                if (getbtns() & 0x4){
                    while(getbtns() & 0x4);
                    level = 1;
                    ballSpeed = 50;
                    fillSceen(BG_COLOR);
                    drawScoreText();
                    if(multiPlayer == 1){
                    drawScoreText2();
                    drawLife2();
                    }
                    drawLife1(2);
                    drawCircle(ballX, ballY, BALL_R, WHITE);
                    hitInt = 1;
                    drawLevel(1);
                    IECSET(1)=0x2;
                    enableTimer2(3, 0x18, 0x111, 1);
                    enable_interrupt();
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
                if (getbtns() & 0x4){
                    while(getbtns() & 0x4);
                    level = 2;
                    ballSpeed = 40;
                    fillSceen(BG_COLOR);
                    drawScoreText();
                    if(multiPlayer == 1){
                    drawScoreText2();
                    drawLife2();
                    }
                    drawLife1(2);
                    drawCircle(ballX, ballY, BALL_R, WHITE);
                    hitInt = 2;
                    drawLevel(2);
                    IECSET(1)=0x2;
                    enableTimer2(3, 0x18, 0x111, 1);
                    enable_interrupt();
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
                if (getbtns() & 0x4){
                    while(getbtns() & 0x4);
                    level = 3;
                    ballSpeed = 30;
                    fillSceen(BG_COLOR);
                    drawScoreText();
                    if(multiPlayer == 1){
                    drawScoreText2();
                    drawLife2();
                    }
                    drawLife1(2);
                    drawCircle(ballX, ballY, BALL_R, WHITE);
                    hitInt = 3;
                    drawLevel(3);
                    IECSET(1)=0x2;
                    enableTimer2(3, 0x18, 0x111, 1);
                    enable_interrupt();
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
	while(1){
        inputRead();
        if(xCord >= 120 && xCord <=240){
            drawMenuMPtext(MENUTEXTCOL, MENUTEXTBGCOL);
            drawMenuSPtext(MENUTEXTBGCOL, MENUTEXTCOL);
            while(xCord >= 120 && xCord <=240){
                inputRead();
                if (getbtns() & 0x4){
                    while(getbtns() & 0x4);
                    multiPlayer = 0;
                    levelSelect();
                }
            }
        }
        else if(xCord >= 0 && xCord <=120){
            inputRead();
            drawMenuSPtext(MENUTEXTCOL, MENUTEXTBGCOL);
            drawMenuMPtext(MENUTEXTBGCOL, MENUTEXTCOL);
            while(xCord >= 0 && xCord <=120){
                inputRead();
                if (getbtns() & 0x4){
                    while(getbtns() & 0x4);
                    multiPlayer = 1;
                    levelSelect();
                }
            }
        }
	}	
}




void drawScore2(uint32_t color, uint32_t bg_color, int index){
    setCursor(123,306);
    setTextSize(2);
    setTextColor(color, bg_color);
    writeString(scoreOut[index]);
}








int main(void){
    display_init();
    rotate(1);
    enablePots();
    splash();
    mainMenu();
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
        
        }
        if(getbtns() & 2)
        {
            //btn3
        }
        if(getbtns() & 1)
        {
            //stuff for BTN2
        }
        
    }
        inputRead();
        updatePaddle(xCord, lastxCord, PADDLE_Y, PADDLE_COLOR);
        if (multiPlayer == 1){
            updatePaddle(x2Cord, lastx2Cord, PADDLE2_Y, PADDLE2_COLOR);
            if(scoreInd2 != scoreIndprev2){
                drawScore2(BG_COLOR, BG_COLOR, scoreIndprev2);
                drawScore2(PADDLE2_COLOR, BG_COLOR, scoreInd2);
                scoreIndprev2 = scoreInd2;
            }
        }
        if (scoreInd != scoreIndprev){
            drawScore(BG_COLOR, BG_COLOR, scoreIndprev);
            drawScore(PADDLE_COLOR, BG_COLOR, scoreInd);
            scoreIndprev = scoreInd;
        }
       

    ballCounter++;

    if(ballCounter == ballSpeed){
        ballCounter = 0;
        
        advance();

    }

}