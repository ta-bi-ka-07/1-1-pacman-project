//this is a level-1 term-1 project of CSE,BUET on  making pac-man game using iGraphics library
//bismillahir rahmanir rahim
//gamepage diye gamestate page open hobe,pause

#include "iGraphics.h"
#include <string.h>
#include <windows.h>


#define screenWidth 1000
#define screenHeight 600
#define paused 0
#define running 1
#define menu 2

int gamestate = menu; // Initial game state is menu
int previousState = paused; // Variable to hold the previous state when paused


void drawHomepage();
void drawGamePage();
void buttons();
void drawExit();
void drawLevelSelectionPage();
void drawEnterNamePage();

void drawInstructions();
void drawAbout();
void drawMenuPage();
void gameState();

bool menuMusicON = true;
bool level12MusicON = false;
bool level3MusicON = false;

 //void drawHighScore();
void drawLevel1();
 void drawLevel2();
 void drawLevel3();
void switchMusic();
// void pauseGame();
// void resumeGame();
 //void drawMaze();
 //
// void drawBalls();
void pacmanMoveRight();
void pacmanMoveLeft();
void pacmanMoveUp();
void pacmanMoveDown();

void ghostMoveRight();
void ghostMoveLeft();
void ghostMoveUp();
void ghostMoveDown();


void pacmanMove();
void ghostMove();
void collisionDetection();



int homepageImage; // Variable to hold the homepage image
int homepage = 1; // 1 for homepage, 0 for game
int gamePage ;
int aboutPage;
int instructionsPage;
int exitPage;
int highScorePage;
int menuPage;
int EnterNamePage;
int levelSelectionPage;
int level1page;
int level2page;
int level3page;
int row1=15;
int col1=25;
int row2=20;
int col2=33;
int row3=30;
int col3=50;
int cellwidth;
int cellheight;
int pacmanX = screenWidth / 2; // Initial X position of Pacman
int pacmanY = cellheight + cellheight/2; // Initial Y position of Pacman
//int pacmanradius = 15; // Radius of Pacman

 // 1 for game over, 0 for not game over

/*
function iDraw() is called again and again by the system.
*/
char playerName[25] = "";
int namelength = 0;
bool TextInputActive = true;
int inputBoxX = 373;
int inputBoxY = 221;
int inputBoxWidth = 337;
int inputBoxHeight = 30;



int mouthOpen;
int mouthClose;


int maze1[15][25]=

{
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 2, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 2, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
    {0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0},
    {0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0},
    {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1},
    {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0},
    {0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0},
    {0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 2, 0, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 2, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};


int maze2[20][33]=
 {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
    {1, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 1},
    {1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
    {1, 2, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 2, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};


int maze3[30][50]=
{
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1},
    {1, 2, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 2, 1},
    {1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
    {1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1},
    {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 2, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 2, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};




void iDraw()
{
    // place your drawing codes here
    iClear();
    // iText(140, 180, "Hello World");
    // iLine(100, 100, 200, 200);
    // iEllipse(200, 200, 50, 50);
    // iRectangle(100, 100, 50, 50);

    // iCircle(300, 300, 50);

    // iSetColor(255, 0, 0);

    // iFilledCircle(300, 300, 50);
    
    // iSetColor(0, 255, 0);
if (homepage)
    {
        drawHomepage();
    }
    else if(menuPage)
    {
        drawMenuPage();
    }
    else if (gamePage)
    
    {
      drawGamePage();
    }
    else if (aboutPage)
    {
        drawAbout();
    }
    else if (instructionsPage)
    {
        drawInstructions();
    }
    else if (exitPage)
    {
        drawExit();
    }
    else if (EnterNamePage){
        drawEnterNamePage();
    }
    else if (levelSelectionPage){
        drawLevelSelectionPage();
    }
     else if(level1page)

     {
        drawLevel1();
        pacmanMove();
     }
     else if(level2page)
     {
        drawLevel2();
        pacmanMove();
     }
     else if(level3page)
     {
        drawLevel3();
        pacmanMove();
     }

    // {
    //     // Draw the game elements
    //     drawMaze();
    //     drawPacman();
    //     drawGhosts();
    //     drawBalls();
        // Add other game elements as needed
}

    // Add any other drawing functions here



/*
function iMouseMove() is called when the user moves the mouse.
(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
 printf("Mouse moved to (%d, %d)\n", mx, my);
   
//    if(homepage==1 && mx>=370 && mx<=608 && my>=355 && my<=400)
//     {
//         homepage = 0; 
//         gamePage = 1; 
//         buttons(); // Draw buttons on the homepage
//          // Draw the game page
//          // Set game page to active
//         // You can add code here to initialize the game state if needed
//     }
//       if(homepage==1 && mx>=370 && mx<=608 && my>=355 && my<=400)
//     {
//         homepage = 0; 
//         gamePage = 1; 
//         buttons(); // Draw buttons on the homepage
//          // Draw the game page
//          // Set game page to active
//         // You can add code here to initialize the game state if needed
//     }
//       if(homepage==1 && mx>=370 && mx<=608 && my>=355 && my<=400)
//     {
//         homepage = 0; 
//         gamePage = 1; 
//         buttons(); // Draw buttons on the homepage
//          // Draw the game page
//          // Set game page to active
//         // You can add code here to initialize the game state if needed
//     }
//       if(homepage==1 && mx>=370 && mx<=608 && my>=355 && my<=400)
//     {
//         homepage = 0; 
//         gamePage = 1; 
//         buttons(); // Draw buttons on the homepage
//          // Draw the game page
//          // Set game page to active
//         // You can add code here to initialize the game state if needed
//     }
//       if(homepage==1 && mx>=370 && mx<=608 && my>=355 && my<=400)
//     {
//         homepage = 0; 
//         gamePage = 1; 
//         buttons(); // Draw buttons on the homepage
//          // Draw the game page
//          // Set game page to active
//         // You can add code here to initialize the game state if needed
//     }
   
//     // place your codes here
}

// /*
// function iMouseDrag() is called when the user presses and drags the mouse.
// (mx, my) is the position where the mouse pointer is.
// */
void iMouseDrag(int mx, int my)
{
    
    // place your codes here
}

/*
function iMouse() is called when the user presses/releases the mouse.
(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
    if (homepage == 1){
            if (mx>=370 && mx<=608 && my>=355 && my<=400 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            homepage = 0; 
            menuPage = 1; 
            buttons(); 
        }
        else if (mx>=367 && mx<=605 && my>=291 && my<=333 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            homepage = 0; 
            instructionsPage = 1; 
            buttons(); 
        }
        else if (mx>=369 && mx<=605 && my>=231 && my<=275 &&   button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            homepage = 0; 
            highScorePage = 1; 
            buttons(); 
        }
        else if (mx>=367 && mx<=605 && my>=164 && my<=211 &&   button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            homepage = 0; 
            aboutPage= 1; 
            buttons(); 
        }
        else if (mx>=368 && mx<=605 && my>=100 && my<=146 &&   button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            homepage = 0; 
            exitPage = 1; 
            buttons(); 
        }
    }
    else if (menuPage == 1){
            if (mx>=92 && mx<=345 && my>=445 && my<=500 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            menuPage = 0;
            EnterNamePage = 1;
            TextInputActive = true;
            buttons();
            // menuPage=0;
            // gamePage = 1; 
            // gameState(); // Set game state to running
            // buttons(); // Draw buttons on the homepage
            // Draw the game page
            // Set game page to active
            
        }
        else if (mx>=92 && mx<=345 && my>=345 && my<=400 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            menuPage=0;
            gamePage = 1; 
            gameState(); // Set game state to running
            buttons(); // Draw buttons on the homepage
            // Draw the game page
            // Set game page to active
            
        }
        // else if (menuPage==1 && mx>=92 && mx<=345 && my>=245 && my<=300 && button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
        // {
        //     menuPage=0;
        //     gamePage = 1; 
        //     gameState(); // Set game state to running
        //     buttons(); 
        // }
        else if (mx>=92 && mx<=345 && my>=145 && my<=200 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            menuPage=0;
            homepage = 1; //Returns to home page from menu page when pressing exit
        }
        else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
        {
            menuPage = 0;
            homepage = 1;
        }
    }

    else if (levelSelectionPage){
        if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
        {
            levelSelectionPage = 0;
            menuPage = 1;
        }
        else if (mx >= 98 && mx <= 282 && my >= 396 && my <= 454 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
            levelSelectionPage = 0;
            level1page = 1;
            switchMusic();
        }
        else if (mx >= 98 && mx <= 282 && my >= 295 && my <= 355 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
            levelSelectionPage = 0;
            level2page = 1;
            switchMusic();
        }
        else if (mx >= 98 && mx <= 282 && my >= 197 && my <= 255 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
            levelSelectionPage = 0;
            level3page = 1;
            switchMusic();
        }
    }
       


}

/*
function iMouseWheel() is called when the user scrolls the mouse wheel.
dir = 1 for up, -1 for down.
*/
void iMouseWheel(int dir, int mx, int my)
{
    // place your code here
}

/*
function iKeyboard() is called whenever the user hits a key in keyboard.
key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{
    int gamestate=menu;
    int previousState = paused; // Assuming paused is a global variable indicating the game state
    
    switch (key)
    {
    case 27:
    {
        if (homepage == 1){
            gamestate = menu;
            exit(0);
        }
        else if (menuPage == 1 || aboutPage == 1 || highScorePage == 1 || instructionsPage == 1){
            gamestate = menu;
            aboutPage = 0;
            highScorePage = 0;
            instructionsPage = 0;
            menuPage = 0;
            homepage = 1;
        }
        else if (EnterNamePage){
            EnterNamePage = 0;
            menuPage = 1;
        }
        else if (levelSelectionPage == 1){
            menuPage = 1;
            levelSelectionPage = 0;
        }
        else if (gamePage == 1){
            gamePage = 0;
            menuPage = 1;
        }
        else if (level1page || level2page ||level3page){
            level1page = 0;
            level2page = 0;
            level3page = 0;
            levelSelectionPage = 1;
        }
        if (!(menuMusicON) && (menuPage || homepage || levelSelectionPage))
            switchMusic();
        

     
        break;
    }

        case 'm':
        case 'M':
        {   
            if (EnterNamePage == 0){
                gamestate = menu;
                previousState = paused; // Save the previous state
                menuPage = 1; // Set homepage to active
                gamePage = 0;
                if (!(menuMusicON))
                    switchMusic();
                    
                buttons(); 
                gameState(); // Draw the menu page
                break;
            }
            else 
                break;
        }
        case 'h':
        case 'H':
        {
            if (EnterNamePage == 0){
                gamestate = menu;
                previousState = paused; // Save the previous state
                menuPage = 0; // Set homepage to active
                gamePage = 0; // Set game page to inactive
                homepage = 1;
                if (!(menuMusicON))
                    switchMusic(); // Set homepage to active
                buttons();
                break;
            }
            else
                break;     
        }

        case 'p':
        case 'P':
        {   
            if (level1page || level2page || level3page){
            if (gamestate == running)
            {
                gamestate = paused; 
                previousState=running;// Pause the game
                gameState(); // Draw the paused state
                
            }
            break;
            }  
        }
        case 'r':
        case 'R':
        {   
            if (menuPage){
                if (gamestate == paused)
                {
                    gamestate = previousState; // Resume the game from the previous state
                    gamePage = 1; // Set game page to active
                    buttons(); // Draw buttons on the homepage
                    gameState(); // Draw the game page
                }
                else if (gamestate == menu)
                {
                    gamestate = running; // Resume the game from menu
                    gamePage = 1; // Set game page to active
                    buttons(); // Draw buttons on the homepage
                    gameState(); // Draw the game page
                }
            }
        
            break;
        }
    
    // place your codes for other keys here
        default:
            break;
    }
    if (EnterNamePage){
        if (TextInputActive){
            if (key == '\r' || key == '\n'){ //Enter key
                if (namelength > 0){
                    TextInputActive = false;
                    printf("Player Name %s", playerName);
                    EnterNamePage = 0;
                    levelSelectionPage = 1;
                }
            }
            else if (key == '\b' && namelength > 0){ //backspace
                namelength--;
                playerName[namelength] = '\0';
            }
            else if (key >= 32 && key <= 126 && namelength < 15) {  // Printable characters
            // Only allow letters, numbers, and some symbols
                if ((key >= 'A' && key <= 'Z') || 
                    (key >= 'a' && key <= 'z') || 
                    (key >= '0' && key <= '9') || 
                    key == ' ' || key == '_' || key == '-'){
                        playerName[namelength] = key;
                        namelength++;
                        playerName[namelength] = '\0';
                }
                
            }
        }
    }
        
}

/*
function iSpecialKeyboard() is called whenver user hits special keys likefunction
keys, home, end, pg up, pg down, arraows etc. you have to use
appropriate constants to detect them. A list is:
GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11,
GLUT_KEY_F12, GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN,
GLUT_KEY_PAGE_UP, GLUT_KEY_PAGE_DOWN, GLUT_KEY_HOME, GLUT_KEY_END,
GLUT_KEY_INSERT */
void iSpecialKeyboard(unsigned char key)
{
    switch (key)
    {
    case GLUT_KEY_F1:
    {
        if (homepage == 1 || menuPage == 1 || levelSelectionPage == 1){
            if (menuMusicON){
                menuMusicON = false;
                PlaySound(0, 0, 0);
            }
            else{
                menuMusicON = true;
                PlaySound("E:\\1-1-pacman-project\\music\\menuMusic.wav", NULL, SND_LOOP | SND_ASYNC);
            }
        }
        break;
    }
    // place your codes for other keys here
    // case GLUT_KEY_RIGHT:
    //  if(level1page==1|level2page==1|level3page==1)
    //  {
    //     pacmanMoveRight();
    //     break;
        
    //  }
     
    // case GLUT_KEY_LEFT:
    //  if(level1page==1|level2page==1|level3page==1)
    //  {
    //     pacmanMoveLeft();
    //     break;
    //  }
    //  case GLUT_KEY_UP:
    //  if(level1page==1|level2page==1|level3page==1)
    //  {
    //     pacmanMoveUp();
    //     break;
    //  }
    //  case GLUT_KEY_DOWN:
    //  if(level1page==1|level2page==1|level3page==1)
    //  {
    //     pacmanMoveDown();
    //     break;
    //  }
    
    // default:
    //     break;
    }
}


void iLoadImages()
{
    // Load images here if needed
// homepageImage = iLoadImage("C:\\Users\\User\\Downloads\\Modern-iGraphics-main\\images\\frontpage.jpg","frontpage");
// Example: iLoadImage("", "myImage");
// If you want to use iShowBMP, you don't need to load the image beforehand.
}


void gameState()
{
if (gamestate == menu)
{
    drawMenuPage();
}
else if (gamestate == running)
{
    drawGamePage();
    // Add code to update game elements like Pacman, ghosts, etc.
}
else if (gamestate == paused)
{
    // Draw the paused state
    iSetColor(255, 0, 0); // Red color for paused state
    iText(screenWidth / 2 - 50, screenHeight / 2, "Game Paused", GLUT_BITMAP_TIMES_ROMAN_24);
    //  

}
}

void buttons()
{
    // Draw buttons here if needed
    // For example, you can draw a button for starting the game or exiting
    if(homepage)
    {
        
        gamePage = 0;
        aboutPage=0;
        menuPage=0;
        instructionsPage=0;
        exitPage=0;
        highScorePage=0;
        levelSelectionPage = 0;
        level1page = 0;
        level2page = 0;
        level3page = 0;
         
        iDraw();

         // Reset game page when on homepage
    }
       else if(menuPage)
    {
        
        gamePage = 0;
        aboutPage=0;
        homepage=0;
        instructionsPage=0;
        levelSelectionPage = 0;
        level1page = 0;
        level2page = 0;
        level3page = 0;

        exitPage=0;
        highScorePage=0;
        iDraw();

         // Reset game page when on homepage
    }



    else if(gamePage)
    {
       
        homepage = 0;
        aboutPage=0;
        menuPage=0;
        instructionsPage=0;
        levelSelectionPage = 0;
        level1page = 0;
        level2page = 0;
        level3page = 0;
        exitPage=0;
        highScorePage=0;
         iDraw();
        
        // Draw game page buttons
 
    }
    else if(aboutPage)
    {
        homepage = 0;
        gamePage=0;
        menuPage=0;
        levelSelectionPage = 0;
        level1page = 0;
        level2page = 0;
        level3page = 0;

        instructionsPage=0;
        exitPage=0;
        highScorePage=0;


        iDraw();
    }
    else if(instructionsPage)
    {

        homepage = 0;
        menuPage=0;
        aboutPage=0;
        levelSelectionPage = 0;
        level1page = 0;
        level2page = 0;
        level3page = 0;
        gamePage=0;
        exitPage=0;
        highScorePage=0;
        iDraw();
    }
    else if(exitPage)
    
    {
        homepage = 0;
        menuPage=0;
        aboutPage=0;
        instructionsPage=0;
        levelSelectionPage = 0;
        level1page = 0;
        level2page = 0;
        level3page = 0;

        gamePage=0;
        highScorePage=0;
        iDraw();
    }
    else if (EnterNamePage){
        homepage = 0;
        levelSelectionPage = 0;
        menuPage=0;
        aboutPage=0;
        instructionsPage=0;
        level1page = 0;
        level2page = 0;
        level3page = 0;
        gamePage=0;
        highScorePage=0;
        exitPage = 0;
        
        iDraw();
    }
    else if (levelSelectionPage){
        homepage = 0;
        menuPage=0;
        aboutPage=0;
        instructionsPage=0;
        level1page = 0;
        level2page = 0;
        level3page = 0;
        gamePage=0;
        highScorePage=0;
        exitPage = 0;
        iDraw();
    }
    else if(level1page)
    {
        homepage = 0;
        menuPage=0;
        aboutPage=0;
        instructionsPage=0;
        levelSelectionPage = 0;
        level2page = 0;
        level3page = 0;
        gamePage=0;
        exitPage=0;
        highScorePage=0;

        iDraw();
    }
    else if(level2page)
    {
        homepage = 0;
        menuPage=0;
        aboutPage=0;
        instructionsPage=0;
        levelSelectionPage = 0;
        level1page = 0;
        level3page = 0;
        gamePage=0;
        exitPage=0;
        highScorePage=0;

        iDraw();
    }
    else if(level3page)
    {
         homepage = 0;
         menuPage=0;
         aboutPage=0;
         instructionsPage=0;
         levelSelectionPage = 0;
         level1page = 0;
         level2page = 0;

         gamePage=0;
         exitPage=0;
         highScorePage=0;

         iDraw();
    
    
    
    }
}


void drawLevel1()
{
    iSetColor(0, 0, 0); // black colour
    iFilledRectangle(0, 0, screenWidth, screenHeight); // fill the background
    iShowImage(pacmanX, pacmanY, "E:\\1-1-pacman-project\\images\\sprites\\base.png"); // Draw Pacman at the current position
    
    cellwidth = screenWidth/col1;
    cellheight = screenHeight/row1;
    int i, j;
    for(i=0;i<row1;i++)
    {
        for(j=0;j<col1;j++)
        {
            int x=j*cellwidth;
            int y=screenHeight-(i+1)*cellheight;
            if (maze1[i][j] == 0) {
                iSetColor(255, 255, 255); // white color
                iFilledCircle(x + cellwidth / 2, y + cellheight / 2, 4, 100); // small white dots
            }
            
            if(maze1[i][j] == 1)
            {
                iSetColor(0,0,139);//blue color
                iFilledRectangle(x, y, cellwidth, cellheight); // draw the wall


            }
            if(maze1[i][j] == 2)
            {
                iSetColor(255, 255, 0); // yellow color
                iFilledCircle(x + cellwidth / 2, y + cellheight / 2, cellwidth / 3, 100); // larger yellow circles
            }


     }




}
}



void drawLevel2()
{
    
    iSetColor(0, 0, 0); // black colour
    iFilledRectangle(0, 0, screenWidth, screenHeight); // fill the background
    cellwidth = screenWidth/col2;
    cellheight = screenHeight/row2;
    int i, j;
    for(i=0;i<row2;i++)
    {
        for(j=0;j<col2;j++)
        {
            int x=j*cellwidth;
            int y=screenHeight-(i+1)*cellheight;

            if (maze2[i][j] == 0) {
                iSetColor(255, 255, 255); // white color
                iFilledCircle(x + cellwidth / 2, y + cellheight / 2, 3, 100); // small white dots
            }
            
            if(maze2[i][j] == 1)
            {
                iSetColor(0,0,139);//blue color
                iFilledRectangle(x, y, cellwidth, cellheight); // draw the wall

            }
            if(maze2[i][j] == 2)
            {
                iSetColor(255, 255, 0); // yellow color
                iFilledCircle(x + cellwidth / 2, y + cellheight / 2, cellwidth / 3, 100); // larger yellow circles
            }
        }
    }
}

void drawLevel3()
{

    iSetColor(0, 0, 0); // black colour
    iFilledRectangle(0, 0, screenWidth, screenHeight); // fill the background
    cellwidth = screenWidth / col3;
     cellheight = screenHeight / row3;
    int i, j;
    for(i = 0; i < row3; i++)
    {
        for(j = 0; j < col3; j++)
        {
            int x = j * cellwidth;
            int y = screenHeight - (i + 1) * cellheight;
            if (maze3[i][j] == 0) {
                iSetColor(255, 255, 255); // white color
                iFilledCircle(x + cellwidth / 2, y + cellheight / 2, 2, 100); // small white dots
            }

            if(maze3[i][j] == 1)
            {
                iSetColor(0, 0, 139); // blue color
                iFilledRectangle(x, y, cellwidth, cellheight); // draw the wall
            }
            if(maze3[i][j] == 2)
            {
                iSetColor(255, 255, 0); // yellow color
                iFilledCircle(x + cellwidth / 2, y + cellheight / 2, cellwidth / 3, 100); // larger yellow circles
            }
        }
    }
}

void switchMusic(){
    // Always stop current music first
    PlaySound(0, 0, 0);
    
    // Reset all music flags
    menuMusicON = false;
    level12MusicON = false;
    level3MusicON = false;
    
    // Determine which music to play based on current page
    if (menuPage || homepage || levelSelectionPage){
        menuMusicON = true;
        PlaySound("E:\\1-1-pacman-project\\music\\menuMusic.wav", NULL, SND_LOOP | SND_ASYNC);
    }
    else if (level1page || level2page){
        level12MusicON = true;
        PlaySound("E:\\1-1-pacman-project\\music\\level12music.wav", NULL, SND_LOOP | SND_ASYNC);
    }
    else if (level3page){
        level3MusicON = true;
        PlaySound("E:\\1-1-pacman-project\\music\\level3music.wav", NULL, SND_LOOP | SND_ASYNC);
    }
}

void pacmanMoveRight()
{
    mouthOpen=1;
    float dx=2.5;
    //pacmanX += dx;
     // Adjust the speed as needed
    if (pacmanX + dx < screenWidth - screenHeight/2) // Check boundaries
    {
        pacmanX += dx; // Move Pacman to the right
    }
    // Check for wall collision
   if(maze1[screenHeight-(pacmanY/cellheight+1)][pacmanX/cellwidth] == 1) // Check for wall collision
   {
       pacmanX -= dx; // Move Pacman back
   }
 if(mouthOpen==1)
 {
  iShowImage(pacmanX, pacmanY, "E:\\1-1-pacman-project\\images\\sprites\\right1.png");
  mouthOpen=0;
  mouthClose=1;

}
    else if(mouthClose==1)
    {
        iShowImage(pacmanX, pacmanY, "E:\\1-1-pacman-project\\images\\sprites\\right2.png");
        mouthClose=0;
        mouthOpen=1;
    }
 
}
void pacmanMoveLeft()
{
    float dx=2.5;
    //pacmanX -= dx;
     // Adjust the speed as needed
    if (pacmanX - dx > 0) // Check boundaries
    {
        pacmanX -= dx; // Move Pacman to the left
    }
   if(maze1[screenHeight-(pacmanY/cellheight+1)][pacmanX/cellwidth] == 1) // Check for wall collision
   {
       pacmanX += dx; // Move Pacman back
   }
}

void pacmanMoveUp()
{
    float dy=2.5;
    //pacmanY += dy;
     // Adjust the speed as needed
    if (pacmanY + dy < screenHeight - screenWidth/2) // Check boundaries
    {
        pacmanY += dy; // Move Pacman up
    }
   if(maze1[screenHeight-(pacmanY/cellheight+1)][pacmanX/cellwidth] == 1) // Check for wall collision
   {
       pacmanY -= dy; // Move Pacman back
   }
}

void pacmanMoveDown()
{
    float dy=2.5;
    //pacmanY -= dy;
     // Adjust the speed as needed
    if (pacmanY - dy > 0) // Check boundaries
    {
        pacmanY -= dy; // Move Pacman down
    }
   if(maze1[screenHeight-(pacmanY/cellheight+1)][pacmanX/cellwidth] == 1) // Check for wall collision
   {
       pacmanY += dy; // Move Pacman back
   }

}
void pacmanMove()
{

pacmanMoveDown();
pacmanMoveUp();
pacmanMoveLeft();
pacmanMoveRight();



}

void drawHomepage()
{

    iSetColor(0, 0, 255); // blue color
    iFilledRectangle(0, 0, screenWidth, screenHeight); // fill the background
    iShowImage(0, 0, "E:\\1-1-pacman-project\\images\\front page.jpg");
    iSetColor (255, 255, 255);
    iText(92, 52, "Press F1 to stop/start Music", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(655, 52, "PRESS Esc to go back", GLUT_BITMAP_TIMES_ROMAN_24);


}

void drawEnterNamePage(){
    iSetColor(255, 255, 255);
    iFilledRectangle(0, 0, screenWidth, screenHeight);
    iShowImage(0, 0, "E:\\1-1-pacman-project\\images\\EnterNamePage.jpeg");
    iText(inputBoxX, inputBoxY - 10, playerName, GLUT_BITMAP_TIMES_ROMAN_24);


}

void drawLevelSelectionPage(){
    iSetColor(0, 255, 0);
    iFilledRectangle(0, 0, screenWidth, screenHeight);
    iShowImage(0, 0, "E:\\1-1-pacman-project\\images\\LevelSelectionPage.jpg");
    iShowImage(90, 380, "E:\\1-1-pacman-project\\images\\ButtonEasy.png");
    iShowImage(90, 280, "E:\\1-1-pacman-project\\images\\ButtonMedium.png");
    iShowImage(90, 180, "E:\\1-1-pacman-project\\images\\ButtonHard.png");
    iSetColor(255, 255, 255);
    iText(75, 490, "SELECT DIFFICULTY:", GLUT_BITMAP_TIMES_ROMAN_24);
}

void drawInstructions()
{
    iSetColor(0, 0, 255); // blue color
    iFilledRectangle(0, 0, screenWidth, screenHeight); // fill the background
    // Add instructions drawing code here
    // For example, draw the instructions text or images
    iSetColor(255, 255, 255); // white color for text
    iText(100, 500, "Instructions:", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(100, 450, "1. Use arrow keys to move Pacman.", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(100, 400, "2. Eat all the dots to win.Collect power pellets to temporarily turn the ghosts blue and vulnearable-you can eat them for bonus point", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(100, 350, "3. Avoid ghosts!Touching one will make you lose  a life.", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(100, 300, "4. Press 'p' to pause the game.", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(100, 250, "5. Press 'r' to resume the game.", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(100, 200, "6. Press 'q' to quit the game.", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(100, 150, "7. Press 'h' to go back to the homepage.", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(100, 100, "8. The game is over when you lose all your lives.", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(100, 50, "9. Good luck!", GLUT_BITMAP_TIMES_ROMAN_24);
}
void drawAbout()
{
    iSetColor(0, 0, 255); // blue color
    iFilledRectangle(0, 0, screenWidth, screenHeight); // fill the background
    // Add about page drawing code here
    // For example, draw the about text or images
    iSetColor(255, 255, 255); // white color for text
   // iText(100, 500, "About Pacman Game:", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(100, 500, "This is a simple Pacman game created using the iGraphics library.", GLUT_BITMAP_TIMES_ROMAN_24);
   // iText(100, 400, "The objective of the game is to eat all the dots while avoiding ghosts.", GLUT_BITMAP_TIMES_ROMAN_24);
   // iText(100, 350, "The game features multiple levels and increasing difficulty.", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(100, 400, "Developed by :", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(100, 350, "Tabassum Binte Kamal(2405117) & Tahmid Bin Rouf(2405109)", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(100, 300, "Under the supervision of:", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(100, 250, "ASA", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(100, 200, "Department of Computer Science and Engineering", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(100, 150, "BUET", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(100, 100, "Version: 1.0", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(100, 50, "Thank you for playing!", GLUT_BITMAP_TIMES_ROMAN_24);
    

}
void drawMenuPage()
{
   // iSetColor(0, 0, 255); // blue color
    iShowImage(0, 0, "E:\\1-1-pacman-project\\images\\menupage.jpg");
    iSetColor(255, 255, 255);
    iText(92, 52, "Press F1 to stop/start Music", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(655, 52, "Press Esc to go back", GLUT_BITMAP_TIMES_ROMAN_24);

}
 void drawGamePage()
{
    iSetColor(0, 0, 255); // green color
    iFilledRectangle(0, 0, screenWidth, screenHeight); // fill the background
    // Add game page drawing code here
    // For example, draw the game elements like maze, pacman, ghosts, etc.
}
void drawExit()
{
    exit(0);
}

int main(int argc, char *argv[])
{
    PlaySound("E:\\1-1-pacman-project\\music\\menuMusic.wav", NULL, SND_LOOP | SND_ASYNC);
    glutInit(&argc, argv);
    // place your own initialization codes here.
    iInitialize(screenWidth, screenHeight, "pacman");
    return 0;
}
