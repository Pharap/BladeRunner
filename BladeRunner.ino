#include <Arduboy2.h>
#include "Images.h"
Arduboy2 arduboy;
BeepPin1 beep;
#define ANIMATION_FRAMES 40
#define PI_HALF (3.1415 / 2)

int allMoney, cloudXTwo = 80, cloudXOne = 30, coinsCount, coinRandF = - 10, coinRandS = -10, perfect, gamestate, countPlatform, frames, randFirstWidth = 30, randFirstPos, randSecondWidth = 20, randSecondPos = 65, lineOnX = 29, lineOnY = 54, platformFirstMove, platformSecondMove = 2, lengthBridge;
bool level, flipPlayer, middleOn, countOn, bridgeIsDown, bridgeOnPlatform, buttOn, collFirst, collSecond, playerOnPlatform, allowDrawLine = 1, spriteAnim;
byte  soundTimer5, soundTimer4, coinFonTime, soundTimer3, perfectCount, soundTimer2, soundTimer, soundOn, markerPlayer,  markerPos, lineMarkerX, lineMarkerY, lineMarkerEndX, randCoin, Timer2, frameCoin,Timer;
bool  soundEnable, choseClear,  ningaB = 1, victoriaB, mushB, senseiB, pandaB, filmoteB, MrBlinkyB, PharapB, drummyfishB, VampiricsB, mlxxxpB, ESPboyB;
bool ningaCH = 1, victoriaCH, mushCH, senseiCH, pandaCH, filmoteCH, MrBlinkyCH, PharapCH, drummyfishCH, VampiricsCH, mlxxxpCH, ESPboyCH;
byte ningaC, victoriaC = 20, mushC = 45, senseiC = 50, pandaC = 50, filmoteC = 75, MrBlinkyC = 75, PharapC = 75, drummyfishC = 75, VampiricsC = 75, mlxxxpC = 75, ESPboyC = 75;
uint8_t const *selectedPlayer = nullptr;
uint8_t const *selectedPlayer2 = nullptr;
uint8_t buyPlayer[] = {ningaB, victoriaB, mushB, senseiB, pandaB, filmoteB, MrBlinkyB, PharapB, drummyfishB, VampiricsB, mlxxxpB, ESPboyB};
uint8_t costPlayer[] = {ningaC, victoriaC, mushC, senseiC, pandaC, filmoteC, MrBlinkyC, PharapC, drummyfishC, VampiricsC, mlxxxpC, ESPboyC};
uint8_t chosenPlayer[] = {ningaCH, victoriaCH, mushCH, senseiCH, pandaCH, filmoteCH, MrBlinkyCH, PharapCH, drummyfishCH, VampiricsCH, mlxxxpCH, ESPboyCH};



Rect rectFirst;
Rect rectSecond;
Rect player{15, 41, 8, 15};
Rect endLine{-10, -10, 2, 2};
Rect rectFirstMiddle{13, 55, 4, 2}; 
Rect rectSecondMiddle{83, 55, 4, 2}; 
Rect rectCoin{-10, 45, 5, 5};

void setup() {
  arduboy.begin();
  arduboy.initRandomSeed();
  beep.begin();
  arduboy.setFrameRate(60);
  rectFirst.x = 0;
  rectFirst.y = 54;
  rectFirst.width = 30;
  rectFirst.height = 10;
  
  rectSecond.x = 65;
  rectSecond.y = 54;
  rectSecond.width = 20;
  rectSecond.height = 10;


}

void loop() {
if(!arduboy.nextFrame()) {
    return;
  }    
  beep.timer();
  arduboy.pollButtons();
  arduboy.clear();
  YorPlayer();
  
  switch (gamestate){
   
  case 0: 
  Sprites::drawOverwrite (0, 0, tittle, 0);
  coinFonTime++;
  if(coinFonTime > 15){
    Sprites::drawOverwrite (96,33, coinFon, 0);
    Sprites::drawOverwrite (16,33, coinFon, 0);
  }
  if(coinFonTime == 30) coinFonTime = 0;
  
  Menu();
  if (arduboy.justPressed(A_BUTTON) && markerPos == 0){
    if(soundEnable == 0) beep.tone(beep.freq(1000), 1);
    perfectCount = 0;
    gamestate = 1;
    soundOn = 0;
  }
  if (arduboy.justPressed(A_BUTTON) && markerPos == 1){
    if(soundEnable == 0) beep.tone(beep.freq(1000), 1);
    gamestate = 2;
  }
  break;
  
  case 1:
  if (player.y > 64 || player.x > 128){
    if(soundEnable == 0) beep.tone(beep.freq(50), 3);
    gamestate = 4;
  }
  gameBar();
  MovePlayer();
  Platform();
  DrawLine();
  Bonus();
  DrawPlayer();
  Sound();

  
  
    if (arduboy.justPressed(A_BUTTON)){
   
    gamestate = 3;
    }
  break;

 //player
  case 2:
  Players();
  Sound();
  if (arduboy.justPressed(A_BUTTON)) gamestate = 0;
  break;

  case 3:

  arduboy.setCursor(26, 23);
  arduboy.print(F("Quit the game?"));
  arduboy.setCursor(0, 55);
  arduboy.print(F("LEFT-yes"));
  arduboy.setCursor(80, 55);
  arduboy.print(F("RIGHT-no"));
  arduboy.drawRoundRect(23, 20, 88, 13, 3);
  
  if (arduboy.justPressed(RIGHT_BUTTON)) {
    gamestate = 1; 
  }
  if (arduboy.justPressed(LEFT_BUTTON)){
    gamestate = 0;
    reset();
  }
  break;

  case 4:
  arduboy.setCursor(41, 30);
  arduboy.print(F("You lose"));
  arduboy.setCursor(35, 50);
  arduboy.print(F("A-Continue"));
  arduboy.setCursor(0, 50);
  arduboy.drawRoundRect(37, 27, 53, 13, 3);

  if (arduboy.justPressed(A_BUTTON)) {
  reset();
  gamestate = 1; 
  }

  break;
  }
  arduboy.display();

}


void YorPlayer(){
    if(markerPlayer == 0){
    selectedPlayer = ninga;
    selectedPlayer2 = ninga2;
  }
  if(markerPlayer == 1){
    selectedPlayer = girl;
    selectedPlayer2 = girl2;
  }
  if(markerPlayer == 2){
    selectedPlayer = mush;
    selectedPlayer2 = mush2;
  }
  if(markerPlayer == 3){
    selectedPlayer = sansay;
    selectedPlayer2 = sansay2;
  }
  if(markerPlayer == 4){
    selectedPlayer = panda;
    selectedPlayer2 = panda2;
  }
  if(markerPlayer == 5){
    selectedPlayer = filmote;
    selectedPlayer2 = filmote2;  
  }
  if(markerPlayer == 6){
    selectedPlayer = MrBlinky;
    selectedPlayer2 = MrBlinky2;  
  }
  if(markerPlayer == 7){
    selectedPlayer = Pharap;
    selectedPlayer2 = Pharap2;  
  }
  if(markerPlayer == 8){
    selectedPlayer = drummyfish;
    selectedPlayer2 = drummyfish2;  
  }
  if(markerPlayer == 9){
    selectedPlayer = Vampirics;
    selectedPlayer2 = Vampirics2;  
  } 
  if(markerPlayer == 10){
    selectedPlayer = mlxxxp;
    selectedPlayer2 = mlxxxp2;  
  } 
  if(markerPlayer == 11){
    selectedPlayer = ESPboy;
    selectedPlayer2 = ESPboy2;  
  } 
}

void reset(){
bridgeIsDown = 0;
bridgeOnPlatform = 0;
buttOn = 0;
collFirst = 0;
collSecond = 0;
playerOnPlatform = 0;
allowDrawLine = 1;
spriteAnim = 0;
frames = 0;
randFirstWidth = 30;
randFirstPos = 0;
randSecondWidth = 20;
randSecondPos = 0;
lineOnX = 29;
lineOnY = 54;
platformFirstMove = 0;
platformSecondMove = 2;
lengthBridge = 0;
player.x = 15;
player.y = 41;
rectFirst.x = 0;
rectFirst.y = 54;
rectFirst.width = 30;
rectFirst.height = 10;
rectSecond.x = 65;
rectSecond.y = 54;
rectSecond.width = 20;
rectSecond.height = 10; 
countPlatform = 0;
flipPlayer = 0;
coinRandF = - 10;
coinRandS = -10;
coinsCount = 0;
perfect = 0;
perfectCount = 0;
spriteAnim = 0;
endLine.x = -100;
}


void DrawPlayer(){
  
  if(chosenPlayer[0] == 1){
    selectedPlayer = ninga;
    selectedPlayer2 = ninga2;
  }
  if(chosenPlayer[1] == 1){
    selectedPlayer = girl;
    selectedPlayer2 = girl2;
  }
  if(chosenPlayer[2] == 1){
    selectedPlayer = mush;
    selectedPlayer2 = mush2;
  }
  if(chosenPlayer[3] == 1){
    selectedPlayer = sansay;
    selectedPlayer2 = sansay2;
  }
  if(chosenPlayer[4] == 1){
    selectedPlayer = panda;
    selectedPlayer2 = panda2;
  }
  if(chosenPlayer[5] == 1){
  selectedPlayer = filmote;
  selectedPlayer2 = filmote2;
  }
  if(chosenPlayer[6] == 1){
  selectedPlayer = MrBlinky;
  selectedPlayer2 = MrBlinky2;
  }
  if(chosenPlayer[7] == 1){
  selectedPlayer = Pharap;
  selectedPlayer2 = Pharap2;
  }
  if(chosenPlayer[8] == 1){
  selectedPlayer = drummyfish;
  selectedPlayer2 = drummyfish2;
  }
  if(chosenPlayer[9] == 1){
  selectedPlayer = Vampirics;
  selectedPlayer2 = Vampirics2;
  }
  if(chosenPlayer[10] == 1){
  selectedPlayer = mlxxxp;
  selectedPlayer2 = mlxxxp2;
  }
  if(chosenPlayer[11] == 1){
  selectedPlayer = ESPboy;
  selectedPlayer2 = ESPboy2;
  }
  if (arduboy.justPressed(B_BUTTON) && flipPlayer == 1 && Timer > 5){
    if(soundEnable == 0) beep.tone(beep.freq(200), 3);
    flipPlayer = 0;
    Timer = 0;
  }
  if (spriteAnim == 0) frames = 0; 
  else{
  if (arduboy.everyXFrames(8)) frames++;
  if (frames > 1) frames = 0;  
  }
  if (flipPlayer == 0){
    Sprites::drawPlusMask (player.x, player.y + 1, selectedPlayer, frames);
    Timer++;
  }
  if (flipPlayer == 1){
    Sprites::drawPlusMask (player.x, player.y + 12, selectedPlayer2, frames);
    Timer++;
  }
  
  if (platformFirstMove == 0 && platformSecondMove == 2 && arduboy.justPressed(B_BUTTON) && flipPlayer == 0){
  if (player.x > rectFirst.x + randFirstWidth && player.x < rectSecond.x && Timer > 5){
    if(soundEnable == 0) beep.tone(beep.freq(200), 3);
    flipPlayer = 1;
    Timer = 0;
  } 
  }
  if (platformFirstMove == 2 && platformSecondMove == 0 && arduboy.justPressed(B_BUTTON) && flipPlayer == 0){
  if (player.x > rectSecond.x + randSecondWidth && player.x < rectFirst.x && Timer > 5){
    flipPlayer = 1;
    Timer = 0;
  }
  }
  
}


void MovePlayer(){  
  
  if (arduboy.collide(player, rectFirst) && player.x > rectFirst.x) collFirst = 1;
  else collFirst = 0;
  if (arduboy.collide(player, rectSecond) && player.x > rectSecond.x) collSecond = 1;
  else collSecond = 0;
  
  if (platformFirstMove == 0 && platformSecondMove == 2){
  if (flipPlayer == 1 && player.x + 8 > rectSecond.x) player.y = 65;
  if (bridgeIsDown == 1 && player.x < lengthBridge + randFirstWidth + 1 && bridgeOnPlatform == 0){
    player.x++;
    spriteAnim = 1;
  }
  if(player.x < rectSecond.x + rectSecond.width - 12 && bridgeOnPlatform == 1){
  player.x++;
  spriteAnim = 1; 
  }

  if (player.x > lengthBridge + randFirstWidth && collSecond == 0 && bridgeOnPlatform == 0) player.y++;
  }


  
  if (platformSecondMove == 0 && platformFirstMove == 2){
  if (flipPlayer == 1 && player.x + 8 > rectFirst.x) player.y = 65; 
  if (bridgeIsDown == 1 && player.x < lengthBridge + randSecondWidth + 1 && bridgeOnPlatform == 0){
    player.x++;
    spriteAnim = 1;
  }

  if(player.x < rectFirst.x + rectFirst.width - 12 && bridgeOnPlatform == 1){
  player.x++;
  spriteAnim = 1; 
  }

  if (player.x > lengthBridge + randSecondWidth && collFirst == 0 && bridgeOnPlatform == 0) player.y++;
  }
  if (player.x == rectFirst.x + rectFirst.width - 12 && platformSecondMove == 0 && platformFirstMove == 2 && bridgeOnPlatform == 1|| player.x  == rectSecond.x + rectSecond.width - 12 && platformSecondMove == 2 && platformFirstMove == 0  && bridgeOnPlatform == 1){
    playerOnPlatform = 1;
    bridgeIsDown = 0;
  
  }
  else playerOnPlatform = 0;
  if (platformFirstMove == 3 && bridgeOnPlatform == 1) player.x--;
  if (platformSecondMove == 3 && bridgeOnPlatform == 1) player.x--;

  
 

}

void DrawLine(){
if (arduboy.pressed(B_BUTTON) && allowDrawLine == 1){
    if(platformFirstMove == 0 && platformSecondMove == 2 || platformSecondMove == 0 && platformFirstMove == 2 ){
      buttOn = 1;
      lengthBridge++;
    }
  }
  else buttOn = 0;
  if (lengthBridge > 0){
  if (platformFirstMove == 0 && platformSecondMove == 2) drawBridge(rectFirst.x + randFirstWidth - 1,53, lengthBridge, arduboy.frameCount);
  if (platformSecondMove == 0 && platformFirstMove == 2) drawBridge(rectSecond.x + randSecondWidth - 1,53, lengthBridge,arduboy.frameCount);
  }
  if (arduboy.collide(endLine, rectFirst) || arduboy.collide(endLine, rectSecond)) bridgeOnPlatform = 1;
  if (buttOn == 0 && lengthBridge > 1) allowDrawLine = 0;

  if  (playerOnPlatform == 1) endLine.x = -100;
 }


void drawBridge(int x, int y, int length, int frame)
{  

  if (buttOn == 1){ // rising the bridge: draw growing vertical line
    arduboy.drawLine(x,y,x,y - lengthBridge);
    arduboy.frameCount = 20;
    bridgeIsDown = 0;
    soundOn = 2;
  }
  else if (frame < ANIMATION_FRAMES) // bridge falling: draw rotating line
  {
    float phase = ((frame - ANIMATION_FRAMES / 2) * PI_HALF) / ((float) ANIMATION_FRAMES / 2); // by reordering the operations here we avoid using float :)
    arduboy.drawLine(x,y,x + sin(phase) * length,y - cos(phase) * length);
  }
  else{ // bridge on the ground: just draw a horizontal line
    arduboy.drawLine(x,y,x + length,y);
    if (lengthBridge > 1){
      endLine.x = x + length;
      endLine.y = y + 1;
    }
    

    if (lengthBridge > 0) bridgeIsDown = 1;
  }
    
}

void Platform(){

// First

if (rectFirst.x < 126 && platformFirstMove == 0 && playerOnPlatform == 1 && buttOn == 0 && platformSecondMove == 2){
  platformFirstMove = 4;
  spriteAnim = 0;
}
if (rectFirst.x == - 1){
  countPlatform++; 
  lengthBridge = 0;
}
if (platformFirstMove == 4) rectFirst.x--;
if (rectFirst.x <= 0 - randFirstWidth) rectFirst.x = 128;
if (rectFirst.x == 128){
    if(level == 0){
    randFirstWidth = random(15,40);
    randFirstPos = random(randSecondWidth + 16,90);
    randCoin = random(0,4);
    }

    if(level == 1){
    randFirstWidth = random(5,20);
    randFirstPos = random(randSecondWidth + 16,90);
    randCoin = random(0,3);
    }
    platformFirstMove = 1; 
    allowDrawLine = 1;
    
    
  }

  if (platformFirstMove == 1){
    rectFirst.width = randFirstWidth;
    if (rectFirst.x > randFirstPos) rectFirst.x --;
  }
  if (rectFirst.x == randFirstPos){
    platformFirstMove = 2;
  }
  if (platformSecondMove == 0 && buttOn == 0 && platformFirstMove == 2 && playerOnPlatform == 1) platformFirstMove = 3;
  if (platformFirstMove == 3 && rectFirst.x > 0 - randFirstWidth) rectFirst.x--;
  if (rectFirst.x == 0){
    platformFirstMove = 0;
    bridgeOnPlatform = 0;
  }

  
//Second

if (rectSecond.x < 126 && platformSecondMove == 0 && playerOnPlatform == 1 && buttOn == 0 && platformFirstMove >= 2){
  platformSecondMove = 4;
  spriteAnim = 0;
}
if (rectSecond.x == - 1){ 
lengthBridge = 0;
countPlatform++; 
}
if (platformSecondMove == 4) rectSecond.x--;
if (rectSecond.x <= 0 - randSecondWidth) rectSecond.x = 128;
if (rectSecond.x == 128){
    if(level == 0){
    randSecondWidth = random(15,40);
    randSecondPos = random(randFirstWidth + 10,90);
    randCoin = random(0,4);
    }
    if(level == 1){
    randSecondWidth = random(5,20);
    randSecondPos = random(randFirstWidth + 10,90);
    randCoin = random(0,3);
    }
    platformSecondMove = 1; 
    allowDrawLine = 1;
    
    
  }

  if (platformSecondMove == 1){
    rectSecond.width = randSecondWidth;
    if (rectSecond.x > randSecondPos) rectSecond.x --;
  }
  if (rectSecond.x == randSecondPos){
    platformSecondMove = 2;
  }
  if (platformFirstMove == 4 && buttOn == 0 && platformSecondMove == 2  && playerOnPlatform == 1) platformSecondMove = 3;
  if (platformSecondMove == 3 && rectSecond.x > 0 - randSecondWidth) rectSecond.x--;
  if (rectSecond.x == 0){
    platformSecondMove = 0;
  }
  if (platformSecondMove == 2 && platformFirstMove == 0 || platformFirstMove == 2 && platformSecondMove == 0) bridgeOnPlatform = 0;


  
  arduboy.fillRect(rectFirst.x, rectFirst.y, rectFirst.width, rectFirst.height);
  arduboy.fillRect(rectSecond.x, rectSecond.y, rectSecond.width, rectSecond.height);
}

void Bonus(){
  rectFirstMiddle.x = rectFirst.x + (rectFirst.width/2 - 2);
  rectSecondMiddle.x = rectSecond.x + (rectSecond.width/2 - 2);
  
  arduboy.fillRect(rectFirstMiddle.x, rectFirstMiddle.y, rectFirstMiddle.width, rectFirstMiddle.height, BLACK);
  arduboy.fillRect(rectSecondMiddle.x, rectSecondMiddle.y, rectSecondMiddle.width, rectSecondMiddle.height, BLACK);

  if (arduboy.collide(endLine, rectFirstMiddle) && middleOn == 0 || arduboy.collide(endLine, rectSecondMiddle) && middleOn == 0){
    perfect++;
    coinsCount++;
    allMoney++;
    middleOn = 1;
    soundOn = 1;
    perfectCount++;
    if(level == 1){
      coinsCount++;
      allMoney++;
    }
  }

  if(middleOn == 0 && bridgeIsDown == 1) perfectCount = 0;
  
  if(middleOn == 1 && bridgeIsDown == 0) middleOn = 0;

  //coin
  if (randCoin == 2){
  if (platformSecondMove == 1){
  if (rectSecond.x == randSecondPos + 1) coinRandF = random(rectFirst.x + randFirstWidth, rectSecond.x - 6);
  }
  if (platformFirstMove == 1){
  if (rectFirst.x == randFirstPos + 1) coinRandS = random(rectSecond.x + randSecondWidth, rectFirst.x - 6);
  }
  }
  
  if (platformFirstMove == 0 && platformSecondMove == 2) {
    rectCoin.x = coinRandF;
    Sprites::drawPlusMask (rectCoin.x, rectCoin.y + 12, coin, frameCoin);
  }
  if (platformFirstMove == 2 && platformSecondMove == 0){
    rectCoin.x = coinRandS;
    Sprites::drawPlusMask (rectCoin.x, rectCoin.y + 12, coin, frameCoin);
  }
  Timer2++;
  if (Timer2 < 10) frameCoin = 0;
  if (Timer2 > 9) frameCoin = 1;
  if (Timer2 == 20) Timer2 = 0;
  
    if (arduboy.collide(player, rectCoin) && flipPlayer == 1){ 

    soundOn = 1;
    coinsCount++;
    allMoney++;
    coinRandF = - 10;
    coinRandS = - 10;

    if(level = 2) {
    coinsCount++;
    allMoney++;  
    }
  }

  if(perfectCount == 5){
  soundOn = 3;
  allMoney = allMoney + 5; 
  coinsCount = coinsCount + 5;
  perfectCount = 0;
  if(level == 1){
  allMoney = allMoney + 5; 
  coinsCount = coinsCount + 5;
  }
  }

  if(soundOn == 3){
    if(level == 1){
    arduboy.setCursor(105,12);
    arduboy.print(F("+10"));  
    }
    else{
    arduboy.setCursor(110,12);
    arduboy.print(F("+5"));
    }
  }
  
    
}

void Menu(){  

 
  if (arduboy.justPressed(DOWN_BUTTON) && markerPos < 3){
    if(soundEnable == 0) beep.tone(beep.freq(300), 1);
    markerPos++;
  }
  if (arduboy.justPressed(UP_BUTTON) && markerPos > 0){
    if(soundEnable == 0) beep.tone(beep.freq(300), 1);
    markerPos--;
  }
  
  if(markerPos == 0){
  lineMarkerX = 47;
  lineMarkerY = 33;
  lineMarkerEndX = 81;
  }

  if(markerPos == 1){
  lineMarkerX = 53;
  lineMarkerY = 40;
  lineMarkerEndX = 74; 
  }

  if(markerPos == 2){
  lineMarkerX = 56;
  lineMarkerY = 47;
  lineMarkerEndX = 71; 
  }

  if(markerPos == 3){
  lineMarkerX = 53;
  lineMarkerY = 54;
  lineMarkerEndX = 73; 
  }
  if (arduboy.justPressed(LEFT_BUTTON) && markerPos == 2){
    if(soundEnable == 0) beep.tone(beep.freq(300), 1);
    level = 0;
  }
  if (arduboy.justPressed(RIGHT_BUTTON) && markerPos == 2){
    if(soundEnable == 0) beep.tone(beep.freq(300), 1);
    level = 1;
  }
  if (level == 1) Sprites::drawPlusMask (57, 42, hard, 0);
  
  
  arduboy.drawLine(lineMarkerX,lineMarkerY,lineMarkerEndX,lineMarkerY);
  
  if (arduboy.justPressed(B_BUTTON) && markerPos == 3) soundEnable = 1;
  if (arduboy.justPressed(A_BUTTON) && markerPos == 3) soundEnable = 0;

  if(soundEnable == 0) Sprites::drawOverwrite (76, 49, on1, 0);
}

void Players(){
  uint8_t i;
  Sprites::drawPlusMask (5, 57, coin, 0);
  arduboy.setCursor(15, 57);
  arduboy.print(allMoney);
  arduboy.drawLine(6, 14, 120, 14);
  arduboy.setCursor(10, 5);
  arduboy.print(F("Choose your runner"));

  if (arduboy.everyXFrames(10)) frames++;
  if (frames > 1) frames = 0;  

  if(arduboy.justPressed(RIGHT_BUTTON) &&  markerPlayer < 11){
    if(soundEnable == 0) beep.tone(beep.freq(100), 2);
    markerPlayer++;
    
  }
  if(arduboy.justPressed(LEFT_BUTTON) &&  markerPlayer > 0){
    if(soundEnable == 0) beep.tone(beep.freq(100), 2);
    markerPlayer--;
    
  }
  
  Sprites::drawPlusMask (60, 35, selectedPlayer, frames);
  if(markerPlayer < 11) Sprites::drawOverwrite (75, 38, MPR, 0);
  if(markerPlayer > 0) Sprites::drawOverwrite (50, 38, MPL, 0);

  if(markerPlayer > 1) Sprites::drawPlusMask (35, 85, coin, 0);
  if(markerPlayer == 0){
  arduboy.setCursor(50, 53);
  arduboy.print(F("NINJA"));  
  }

    if(markerPlayer == 1){       
  arduboy.setCursor(42, 53);
  arduboy.print(F("VICTORIA")); 
   
  }

    if(markerPlayer == 2){
  arduboy.setCursor(44, 53);
  arduboy.print(F("MUSHBOY"));  
  }

    if(markerPlayer == 3){
  arduboy.setCursor(46, 53);
  arduboy.print(F("SENSEI"));  
  }

    if(markerPlayer == 4){
  arduboy.setCursor(50, 53);
  arduboy.print(F("PANDA"));  
  }

    if(markerPlayer == 5){
  arduboy.setCursor(45, 53);
  arduboy.print(F("FILMOTE"));  
  }
  
    if(markerPlayer == 6){
  arduboy.setCursor(38, 53);
  arduboy.print(F("MR.BLINKY"));  
  }  

    if(markerPlayer == 7){
  arduboy.setCursor(48, 53);
  arduboy.print(F("PHARAP"));  
  }

    if(markerPlayer == 8){
  arduboy.setCursor(35, 53);
  arduboy.print(F("DRUMMYFISH"));  
  }

    if(markerPlayer == 9){
  arduboy.setCursor(35, 53);
  arduboy.print(F("VAMPIRICS"));  
  }

    if(markerPlayer == 10){
  arduboy.setCursor(48, 53);
  arduboy.print(F("MLXXXp"));  
  }

    if(markerPlayer == 11){
  arduboy.setCursor(47, 53);
  arduboy.print(F("ESPboy"));  
  }
  
    for (i = 0; i < 12; i++){
    if(costPlayer[i] <= allMoney && arduboy.justPressed(B_BUTTON) && buyPlayer[i] == 0 && markerPlayer == i ){
      buyPlayer[i] = 1;     
      allMoney = allMoney - costPlayer[i];
      soundOn = 3;
    }
    if(buyPlayer[i] == 0 && markerPlayer == i){
      Sprites::drawOverwrite (62, 25, LOCK, 0);
      Sprites::drawPlusMask (25, 41, coin, 0);
      arduboy.drawRoundRect(0, 25, 42, 27, 5);
      arduboy.setCursor(5, 30);
      arduboy.print(F("Price:"));
      if(costPlayer[i] < 100)arduboy.setCursor(13, 41);
      else arduboy.setCursor(7, 41);
      arduboy.println(costPlayer[i]);
    }
    if(buyPlayer[i] == 1 && markerPlayer == i && arduboy.justPressed(B_BUTTON)){
      chosenPlayer[0] = 0;
      chosenPlayer[1] = 0;
      chosenPlayer[2] = 0;
      chosenPlayer[3] = 0;
      chosenPlayer[4] = 0;
      chosenPlayer[5] = 0;
      chosenPlayer[6] = 0;
      chosenPlayer[7] = 0;
      chosenPlayer[8] = 0;
      chosenPlayer[9] = 0;
      chosenPlayer[10] = 0;
      chosenPlayer[11] = 0;
      chosenPlayer[i] = 1;
      if(soundEnable == 0) beep.tone(beep.freq(800), 3);
    } 
 
    
    if(chosenPlayer[i] == 1 && markerPlayer == i){
      
      arduboy.setCursor(41, 23);
      arduboy.print(F("SELECTED"));
      arduboy.drawRoundRect(39, 21, 51, 11, 3);
    }


    }
    
}

void gameBar(){

  if (arduboy.everyXFrames(80)) cloudXOne--;
  if (arduboy.everyXFrames(150)) cloudXTwo--; 
  
  
  if(cloudXOne < -20) cloudXOne = 128;
  if(cloudXTwo < -20) cloudXTwo = 128;
  
  Sprites::drawOverwrite (cloudXOne, 20, cloud, 0);
  Sprites::drawOverwrite (cloudXTwo, 25, cloud, 0);
  arduboy.print(countPlatform);
  arduboy.fillCircle (62, 20, 9, WHITE);
  Sprites::drawPlusMask (102, 0, coin, 0);
  arduboy.setCursor(112, 0);
  arduboy.print(coinsCount);
}

void Sound(){
    if(soundEnable == 0){
  //coin
  
    if (soundOn == 1 && soundOn != 3) soundTimer++;
    if (soundTimer < 3 && soundTimer > 0) beep.tone(beep.freq(900), 3);
    if (soundTimer > 3) beep.tone(beep.freq(1500), 3);
    if (soundTimer == 6){
      soundOn = 0;
      soundTimer = 0;
    }
    
    //platform move up
    if (soundOn == 2) soundTimer2++;
    if (soundTimer2 < 8 && soundTimer2 > 0) beep.tone(beep.freq(50), 3);
    if (soundTimer2 > 8) beep.tone(beep.freq(100), 3);
    if (soundTimer2 == 13){
      soundOn = 0;
      soundTimer2 = 0;
    }
    
  //perfectCount
    if (soundOn == 3 && soundOn != 1) soundTimer3++;
    if (soundTimer3 < 5 && soundTimer3 > 0) beep.tone(beep.freq(300), 3);
    if (soundTimer3 >= 5 && soundTimer3 < 10) beep.tone(beep.freq(600), 3);
    if (soundTimer3 > 15) beep.tone(beep.freq(900), 3);
    if (soundTimer3 == 20){
      soundOn = 0;
      soundTimer3 = 0;
    }
    
    }


    

}
