//this is a level-1 term-1 project of CSE,BUET on  making pac-man game using iGraphics library
//bismillahir rahmanir rahim
//gamepage diye gamestate page open hobe,pause

#include "iGraphics.h"
#include <string.h>
#include <windows.h>
#include <algorithm>


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

void ghostMoveRight();
void ghostMoveLeft();
void ghostMoveUp();
void ghostMoveDown();


void pacmanMove();
void ghostMove();
int isValidPosition(int row, int col);
void InitializePacman();
void drawPacman();
void getGridPosition(int pixelX, int pixelY, int* row, int* col);
int canMoveInDirection(int direction);
void startMoving(int direction);
void updatePacmanMovement();
int isPacmanAlignedWithGrid();
void alignPacmanToGrid();



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
int row1 = 15;
int col1 = 25;
int row2 = 20;
int col2 = 33;
int row3 = 30;
int col3 = 50;
int cellwidth;
int cellheight;
int pacmanX, pacmanY;
int levelWidth, levelHeight;
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

#define Right 0
#define Left 1
#define Up 2
#define Down 3
#define pacmanSpeed 4

int pacmanDirection = Right;
int pacmanRow, pacmanCol;
int pacmanPixelX, pacmanPixelY;     
int targetPixelX, targetPixelY; 
int isMoving = 0;
int pendingDirection = -1;
int mouthClose = 0, mouthOpen = 1;


int maze1[15][25]=

{
    {0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 2, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 2, 0},
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

    iClear();

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
        InitializePacman();
        drawLevel1();

     }
     else if(level2page)
     {
        drawLevel2();
        
     }
     else if(level3page)
     {
        drawLevel3();
     }

}




/*
function iMouseMove() is called when the user moves the mouse.
(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
 printf("Mouse moved to (%d, %d)\n", mx, my);

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
            InitializePacman();
            level1page = 1;
            switchMusic();
        }
        else if (mx >= 98 && mx <= 282 && my >= 295 && my <= 355 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
            levelSelectionPage = 0;
            InitializePacman();
            level2page = 1;
            switchMusic();
        }
        else if (mx >= 98 && mx <= 282 && my >= 197 && my <= 255 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
            levelSelectionPage = 0;
            InitializePacman();
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
        
    
    // Handle arrow keys for Pacman movement
    case GLUT_KEY_LEFT:
    case GLUT_KEY_RIGHT:
    case GLUT_KEY_UP:
    case GLUT_KEY_DOWN:
    {
        if (level1page || level2page || level3page){
            int newDirection = pacmanDirection;
            switch (key) {
            case GLUT_KEY_LEFT: newDirection = Left; break;
            case GLUT_KEY_RIGHT: newDirection = Right; break;
            case GLUT_KEY_UP: newDirection = Up; break;
            case GLUT_KEY_DOWN: newDirection = Down; break;
            }
            
            // If we can move in the new direction, change direction immediately
            if (level1page){
                cellwidth = screenWidth/col1;
                cellheight = screenHeight/row1;
                for(int i=0;i<row1;i++)
                {
                    for(int j=0;j<col1;j++)
                    {
                        int x=j*cellwidth;
                        int y=screenHeight-(i+1)*cellheight;
                        if (pacmanX == x && pacmanY == y){
                            if (canMoveInDirection(newDirection)) {
                            isMoving = 0; // Stop current movement
                            pacmanDirection = newDirection;
                            startMoving(newDirection); // Start moving in new direction
                            }
                            else {
                            // If we can't move in the new direction immediately, 
                            // store it as a pending direction to try later
                            pacmanDirection = newDirection;
                            }
                        }
                    }
                }
                break;    
            }  
        }
        default:
            break;
    }
}
}

void iLoadImages()
{   
    
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

    cellwidth = screenWidth/col1;
    cellheight = screenHeight/row1;
    for(int i=0;i<row1;i++)
    {
        for(int j=0;j<col1;j++)
        {
            int x=j*cellwidth;
            int y=screenHeight-(i+1)*cellheight;
            if (maze1[i][j] == 0) {
                iSetColor(255, 255, 255); // white color
                // iFilledCircle(x + cellwidth / 2, y + cellheight / 2, 4, 100); // small white dots
                iShowImage(x + cellwidth/2, y + cellheight/2, "E:\\1-1-pacman-project\\Sprites\\other\\dot.png");
            }
            
            else if(maze1[i][j] == 1)
            {
                iSetColor(0,0,139);//blue color
                iFilledRectangle(x, y, cellwidth, cellheight); // draw the wall


            }
            else if(maze1[i][j] == 2)
            {
                iSetColor(255, 255, 0); // yellow color
                iFilledCircle(x + cellwidth / 2, y + cellheight / 2, cellwidth / 3, 100); // larger yellow circles
            }
     
        }
    }

    drawPacman();

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
    drawPacman();
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
                // iFilledCircle(x + cellwidth / 2, y + cellheight / 2, 2, 100); // small white dots
                iShowImage(x + 4, y, "E:\\1-1-pacman-project\\Sprites\\other\\dot.png");
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
    drawPacman();
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

// Function to check if Pacman is aligned with the grid
int isPacmanAlignedWithGrid() {
    int cellwidth, cellheight;
    
    // Get cell dimensions based on current level
    if (level1page) {
        cellwidth = screenWidth / col1;
        cellheight = screenHeight / row1;
    } else if (level2page) {
        cellwidth = screenWidth / col2;
        cellheight = screenHeight / row2;
    } else if (level3page) {
        cellwidth = screenWidth / col3;
        cellheight = screenHeight / row3;
    } else {
        return 0; // Not in a valid level
    }
    
    // Calculate what the centered position should be for current grid cell
    int expectedX = pacmanCol * cellwidth + cellwidth/2;
    int expectedY = screenHeight - (pacmanRow + 1) * cellheight + cellheight/2;
    
    // Check if Pacman is close enough to the center (within a small tolerance)
    int tolerance = pacmanSpeed; // Allow some tolerance based on movement speed
    
    return (abs(pacmanPixelX - expectedX) <= tolerance && 
            abs(pacmanPixelY - expectedY) <= tolerance);
}

void alignPacmanToGrid() {
    int cellwidth, cellheight;
    
    if (level1page) {
        cellwidth = screenWidth / col1;
        cellheight = screenHeight / row1;
    } else if (level2page) {
        cellwidth = screenWidth / col2;
        cellheight = screenHeight / row2;
    } else if (level3page) {
        cellwidth = screenWidth / col3;
        cellheight = screenHeight / row3;
    }
    
    pacmanPixelX = pacmanCol * cellwidth + cellwidth/2;
    pacmanPixelY = screenHeight - (pacmanRow + 1) * cellheight + cellheight/2;
}

// Get grid position from pixel coordinates
void getGridPosition(int pixelX, int pixelY, int* row, int* col){
    if (level1page){
        cellwidth = screenWidth / col1;
        cellheight = screenHeight / row1;
        
        *col = pixelX / cellwidth;
        *row = (screenHeight - pixelY) / cellheight;
        
        // Clamp to valid range
        if (*row < 0) *row = 0;
        if (*row >= row1) *row = row1 - 1;
        if (*col < 0) *col = 0;
        if (*col >= col1) *col = col1 - 1;
    }
    else if (level2page){
        cellwidth = screenWidth / col2;
        cellheight = screenHeight / row2;
        
        *col = pixelX / cellwidth;
        *row = (screenHeight - pixelY) / cellheight;
        
        // Clamp to valid range
        if (*row < 0) *row = 0;
        if (*row >= row2) *row = row2 - 1;
        if (*col < 0) *col = 0;
        if (*col >= col2) *col = col2 - 1;
    }
    else if (level3page){
        cellwidth = screenWidth / col3;
        cellheight = screenHeight / row3;
        
        *col = pixelX / cellwidth;
        *row = (screenHeight - pixelY) / cellheight;
        
        // Clamp to valid range
        if (*row < 0) *row = 0;
        if (*row >= row3) *row = row3 - 1;
        if (*col < 0) *col = 0;
        if (*col >= col3) *col = col3 - 1;
    }
}

void InitializePacman(){
    // Find Pac-Man spawn position (value 4 in maze)
    if (level1page){
        for(int i = 0; i < row1; i++) {
            for(int j = 0; j < col1; j++) {
                if(maze1[i][j] == 4) {
                    pacmanRow = i;
                    pacmanCol = j;
                    
                    // Convert to pixel coordinates
                    cellwidth = screenWidth / col1;
                    cellheight = screenHeight / row1;
                    pacmanPixelX = j * cellwidth + cellwidth/2;
                    pacmanPixelY = screenHeight - (i + 1) * cellheight + cellheight/2;

                    // Set target to current position initially
                    targetPixelX = pacmanPixelX;
                    targetPixelY = pacmanPixelY;
                    
                    // Remove the spawn marker from maze
                    maze1[i][j] = -1;
                    return;
                }
            }
        }
    }
    else if (level2page){
        for(int i = 0; i < row2; i++) {
            for(int j = 0; j < col2; j++) {
                if(maze2[i][j] == 4) {
                    pacmanRow = i;
                    pacmanCol = j;
                    
                    // Convert to pixel coordinates
                    cellwidth = screenWidth / col3;
                    cellheight = screenHeight / row3;
                    pacmanPixelX = j * cellwidth + cellwidth / 2;
                    pacmanPixelY = screenHeight - (i + 1) * cellheight + cellheight / 2;

                    // Set target to current position initially
                    targetPixelX = pacmanPixelX;
                    targetPixelY = pacmanPixelY;
                    
                    // Remove the spawn marker from maze
                    maze2[i][j] = -1;
                    return;
                }
            }
        }
    }
    else if (level3page){
        for(int i = 0; i < row3; i++) {
            for(int j = 0; j < col3; j++) {
                if(maze3[i][j] == 4) {
                    pacmanRow = i;
                    pacmanCol = j;
                    
                    // Convert to pixel coordinates
                    cellwidth = screenWidth / col3;
                    cellheight = screenHeight / row3;
                    pacmanPixelX = j * cellwidth + cellwidth/2;
                    pacmanPixelY = screenHeight - (i + 1) * cellheight + cellheight/2;

                    // Set target to current position initially
                    targetPixelX = pacmanPixelX;
                    targetPixelY = pacmanPixelY;
                    
                    // Remove the spawn marker from maze
                    maze3[i][j] = -1;
                    return;
                }
            }
        }
    }
}

int isValidPosition(int row, int col){
    // Check bounds
    if (level1page){
        if (row < 0 || row >= row1 || col < 0 || col >= col1) {
            return 0;
        }
        
        // Check if cell is walkable (0 = food, 2 = power pellet)
        return (maze1[row][col] != 1);
    }
    else if (level2page){
        if (row < 0 || row >= row2 || col < 0 || col >= col2) {
            return 0;
        }
        
        // Check if cell is walkable (0 = food, 2 = power pellet)
        return (maze2[row][col] != 1);
    }
    else if (level3page){
        if (row < 0 || row >= row3 || col < 0 || col >= col3) {
            return 0;
        }
        
        // Check if cell is walkable (0 = food, 2 = power pellet)
        return (maze3[row][col] != 1);
    }
    return 0;
}

// Check if Pac-Man can move in a direction from current position
int canMoveInDirection(int direction) {
    int newRow = pacmanRow;
    int newCol = pacmanCol;
    
    switch (direction) {
        case Left:  newCol--; break;
        case Right: newCol++; break;
        case Up:    newRow--; break;
        case Down:  newRow++; break;
    }
    
    return isValidPosition(newRow, newCol);
}

// Start moving in a direction
void startMoving(int direction) {
    if (canMoveInDirection(direction)) {
        pacmanDirection = direction;
        isMoving = 1;
    
        // Calculate target position based on current level
        if (level1page) {
            cellwidth = screenWidth / col1;
            cellheight = screenHeight / row1;
        } else if (level2page) {
            cellwidth = screenWidth / col2;
            cellheight = screenHeight / row2;
        } else if (level3page) {
            cellwidth = screenWidth / col3;
            cellheight = screenHeight / row3;
        }
        
        switch (direction) {
            case Left:
                targetPixelX = pacmanPixelX - cellwidth;
                targetPixelY = pacmanPixelY;
                break;
            case Right:
                targetPixelX = pacmanPixelX + cellwidth;
                targetPixelY = pacmanPixelY;
                break;
            case Up:
                targetPixelX = pacmanPixelX;
                targetPixelY = pacmanPixelY + cellheight;
                break;
            case Down:
                targetPixelX = pacmanPixelX;
                targetPixelY = pacmanPixelY - cellheight;
                break;
        }
    }
}


void updatePacmanMovement() {
    if (!isMoving) {
        // Not moving, check if we should continue in current direction
        if (canMoveInDirection(pacmanDirection)) {
            startMoving(pacmanDirection);
        }
        return;
    }
    
    
    // Calculate distance to target
    int distanceX = targetPixelX - pacmanPixelX;
    int distanceY = targetPixelY - pacmanPixelY;
    int distance = abs(distanceX) + abs(distanceY);
    
    // If we're close enough to target, snap to it
    if (distance <= pacmanSpeed) {
        pacmanPixelX = targetPixelX;
        pacmanPixelY = targetPixelY;
        isMoving = 0;
        
        // Update grid position
        getGridPosition(pacmanPixelX, pacmanPixelY, &pacmanRow, &pacmanCol);
        
        // Eat food/pellets at new position
        if (level1page && pacmanRow >= 0 && pacmanRow < row1 && pacmanCol >= 0 && pacmanCol < col1) {
            if (maze1[pacmanRow][pacmanCol] == 2) {
                maze1[pacmanRow][pacmanCol] = -1;  // Remove power pellet
                // Add power-up logic here
            } else if (maze1[pacmanRow][pacmanCol] == 0) {
                maze1[pacmanRow][pacmanCol] = -1;  // Remove dot
            }
        }
        else if (level2page && pacmanRow >= 0 && pacmanRow < row2 && pacmanCol >= 0 && pacmanCol < col2) {
            if (maze2[pacmanRow][pacmanCol] == 2) {
                maze2[pacmanRow][pacmanCol] = -1;  // Remove power pellet
            } else if (maze2[pacmanRow][pacmanCol] == 0) {
                maze2[pacmanRow][pacmanCol] = -1;  // Remove dot
            }
        }
        else if (level3page && pacmanRow >= 0 && pacmanRow < row3 && pacmanCol >= 0 && pacmanCol < col3) {
            if (maze3[pacmanRow][pacmanCol] == 2) {
                maze3[pacmanRow][pacmanCol] = -1;  // Remove power pellet
            } else if (maze3[pacmanRow][pacmanCol] == 0) {
                maze3[pacmanRow][pacmanCol] = -1;  // Remove dot
            }
        }
        
        // Now that we're aligned, check for pending direction changes
        if (pendingDirection != -1 && canMoveInDirection(pendingDirection)) {
            pacmanDirection = pendingDirection;
            startMoving(pendingDirection);
            pendingDirection = -1; // Clear pending direction
        }
        // Otherwise continue in current direction if possible
        else if (canMoveInDirection(pacmanDirection)) {
            startMoving(pacmanDirection);
        }
    } 
        else {
        // Calculate next position
        int nextX = pacmanPixelX;
        int nextY = pacmanPixelY;
        
        if (distanceX > 0) nextX += min(pacmanSpeed, distanceX);
        else if (distanceX < 0) nextX += max(-pacmanSpeed, distanceX);
        
        if (distanceY > 0) nextY += min(pacmanSpeed, distanceY);
        else if (distanceY < 0) nextY += max(-pacmanSpeed, distanceY);
        
        // Check if the next position would be valid
        int nextRow, nextCol;
        getGridPosition(nextX, nextY, &nextRow, &nextCol);
        
        // Only move if the destination is valid
        if (isValidPosition(nextRow, nextCol)) {
            pacmanPixelX = nextX;
            pacmanPixelY = nextY;
        } else {
            // Hit a wall, stop moving and align to grid
            isMoving = 0;
            alignPacmanToGrid();
        }
    }
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

void drawPacman() {
    
    switch(pacmanDirection) {
        case Right:
            iShowImage(pacmanPixelX, pacmanPixelY, "E:\\1-1-pacman-project\\Sprites\\pacman-right\\1.png");
            break;
        case Left:
            iShowImage(pacmanPixelX, pacmanPixelY, "E:\\1-1-pacman-project\\Sprites\\pacman-left\\1.png");
            break;
        case Up:
            iShowImage(pacmanPixelX, pacmanPixelY, "E:\\1-1-pacman-project\\Sprites\\pacman-up\\1.png");
            break;
        case Down:
            iShowImage(pacmanPixelX, pacmanPixelY, "E:\\1-1-pacman-project\\Sprites\\pacman-down\\1.png");
            break;
    }
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
    iText(100, 200, "6. Press 'Esc' to quit the game.", GLUT_BITMAP_TIMES_ROMAN_24);
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
    iSetTimer(80, updatePacmanMovement);
    // place your own initialization codes here.
    iInitialize(screenWidth, screenHeight, "pacman");
    return 0;
}
