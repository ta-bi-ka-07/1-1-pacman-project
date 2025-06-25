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
void generateMaze();
// void pauseGame();
// void resumeGame();
 //void drawMaze();
 //
// void drawBalls();



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
int isPixelPositionValid(int pixelX, int pixelY);
int canStartMoving(int direction);


#define MAX_GHOSTS 4
#define GHOST_SPEED 2

typedef struct {
    int row, col;           // Grid position
    int pixelX, pixelY;     // Pixel position
    int targetX, targetY;   // Target pixel position
    int direction;          // Current direction
    int isMoving;           // Movement state
    int color;              // Ghost color (0=red, 1=pink, 2=cyan, 3=orange)
    int moveCounter;        // Counter for movement timing
} Ghost;

Ghost ghosts[MAX_GHOSTS];
int numGhosts = 0;

void InitializeGhosts();
int canGhostMoveInDirection(Ghost* ghost, int direction);
int getValidDirections(Ghost* ghost, int validDirs[4]);
int chooseRandomDirection(Ghost* ghost);
void startGhostMoving(Ghost* ghost, int direction);
void updateGhostMovement();
int checkGhostCollision();
void drawGhosts();


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
#define pacmanSpeed 2

int pacmanDirection = Right;
int pacmanRow, pacmanCol;
int pacmanPixelX, pacmanPixelY;     
int targetPixelX, targetPixelY; 
int isMoving = 0;
int pendingDirection = -1;
int movementflag = 1;



const int refMaze1[15][25] = 
{
    {0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 2, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 2, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
    {0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0},
    {0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0},
    {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1},
    {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 5, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0},
    {0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 5, 0, 0, 0, 5, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0},
    {0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 2, 0, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 2, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

const int refMaze2[20][33]
{
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
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

const int refMaze3[30][50] =
{
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1},
    {1, 2, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 2, 1},
    {1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1},
    {1, 4, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
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


int maze1[15][25];
int maze2[20][33];
int maze3[30][50];


void generateMaze(){
    if (level1page){
        for (int i = 0; i < row1; i++){
            for (int j = 0; j < col1; j++)
                maze1[i][j] = refMaze1[i][j];
            
        }
    }
    else if (level2page){
        for (int i = 0; i < row2; i++){
            for (int j = 0; j < col2; j++)
                maze2[i][j] = refMaze2[i][j];
        }
    }
    else if (level3page){
        for (int i = 0; i < row3; i++){
            for (int j = 0; j < col3; j++)
                maze3[i][j] = refMaze3[i][j];
        }
    }
}



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
            if (mx>=410 && mx<=635 && my>=325 && my<=385 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            homepage = 0; 
            menuPage = 1; 
        }
        else if (mx>=410 && mx<=635 && my>=250 && my<=315 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            homepage = 0; 
            instructionsPage = 1; 
        }
        else if (mx>=410 && mx<=635 && my>=170 && my<=240 &&   button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            homepage = 0; 
            highScorePage = 1; 
        }
        else if (mx>=410 && mx<=635 && my>=95 && my<=165 &&   button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            homepage = 0; 
            aboutPage= 1; 
        }
        else if (mx>=410 && mx<=635 && my>=20 && my<=85 &&   button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            homepage = 0; 
            exitPage = 1; 
        }
    }
    else if (menuPage == 1){
            if (mx>=92 && mx<=345 && my>=445 && my<=500 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            menuPage = 0;
            EnterNamePage = 1;
            TextInputActive = true;
            
            
        }
        else if (mx>=92 && mx<=345 && my>=345 && my<=400 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            menuPage=0;
            gamePage = 1; 
            gameState(); 
            
        }
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
            generateMaze();
            InitializePacman();
            InitializeGhosts();
            switchMusic();
        }
        else if (mx >= 98 && mx <= 282 && my >= 295 && my <= 355 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
            levelSelectionPage = 0;
            level2page = 1;
            generateMaze();
            InitializePacman();
            InitializeGhosts();
            switchMusic();
        }
        else if (mx >= 98 && mx <= 282 && my >= 197 && my <= 255 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
            levelSelectionPage = 0;
            level3page = 1;
            generateMaze();
            InitializePacman();
            InitializeGhosts();
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
                    gameState(); // Draw the game page
                }
                else if (gamestate == menu)
                {
                    gamestate = running; // Resume the game from menu
                    gamePage = 1; // Set game page to active
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
                PlaySound("music\\menuMusic.wav", NULL, SND_LOOP | SND_ASYNC);
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
            
            // If Pacman is currently moving, store as pending direction
            if (isMoving) {
                pendingDirection = newDirection;
            }
            // If Pacman is not moving, try to start moving immediately
            else if (canMoveInDirection(newDirection)) {
                pacmanDirection = newDirection;
                startMoving(pacmanDirection);
            }
            // If can't move in new direction, store as pending
            else {
                pendingDirection = newDirection;
            }
        }
        break;
    }
    default:
        break;
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
                iFilledCircle(x + cellwidth / 2, y + cellheight / 2, 4, 100); // small white dots
                // iShowImage(x + cellwidth/2, y + cellheight/2, "Sprites\\other\\dot.png");
            }
            
            else if(maze1[i][j] == 1)
            {
                iSetColor(0,0,139);//blue color
                iFilledRectangle(x, y, cellwidth, cellheight); // draw the wall


            }
            else if(maze1[i][j] == 2)
            {
                iSetColor(255, 255, 0); // yellow color
                // iFilledCircle(x + cellwidth / 2, y + cellheight / 2, cellwidth / 3, 100); // larger yellow circles
                iShowImage(x+cellwidth/3.5, y + cellheight/3.5, "Sprites\\other\\strawberry.png");
            }
     
        }
    }
    drawPacman();
    drawGhosts();
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
                iShowImage(x + 2 , y + 2, "Sprites\\other\\dot.png");
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
    PlaySound(0, 0, 0);
    
    menuMusicON = false;
    level12MusicON = false;
    level3MusicON = false;
    
    // Determine which music to play based on current page
    if (menuPage || homepage || levelSelectionPage){
        menuMusicON = true;
        PlaySound("music\\menuMusic.wav", NULL, SND_LOOP | SND_ASYNC);
    }
    else if (level1page || level2page){
        level12MusicON = true;
        PlaySound("music\\level12music.wav", NULL, SND_LOOP | SND_ASYNC);
    }
    else if (level3page){
        level3MusicON = true;
        PlaySound("music\\level3music.wav", NULL, SND_LOOP | SND_ASYNC);
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

//Aligns Pacman to the Grid Coordinates, helps with changing directions
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
    
    if (level1page || level2page){
        pacmanPixelX = pacmanCol*cellwidth + 8;
        pacmanPixelY = screenHeight-(pacmanRow+1)*cellheight + 8;
    }
    else{
        pacmanPixelX = pacmanCol*cellwidth + 5;
        pacmanPixelY = screenHeight-(pacmanRow+1)*cellheight + 5;
    }

}

// Give Pixel Coordinates to turn into Grid Position (Row and Column)
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
                    pacmanPixelX = j * cellwidth + 8;
                    pacmanPixelY = screenHeight - (i + 1) * cellheight + 8;

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
                    cellwidth = screenWidth / col2;
                    cellheight = screenHeight / row2;
                    pacmanPixelX = j * cellwidth + 5;
                    pacmanPixelY = screenHeight - (i + 1) * cellheight + 5;

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
                    pacmanPixelX = j * cellwidth + 5;
                    pacmanPixelY = screenHeight - (i + 1) * cellheight + 5;

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
   if (level1page){
        if (row < 0 || row >= row1 || col < 0 || col >= col1){
            return 0;
        }
        return maze1[row][col] != 1;
   }
   if (level2page){
        if (row < 0 || row >= row2 || col < 0 || col >= col2){
            return 0;
        }
        return maze2[row][col] != 1;
   }
   if (level3page){
        if (row < 0 || row >= row3 || col < 0 || col >= col3){
            return 0;
        }
        return maze3[row][col] != 1;
   }
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


void startMoving(int direction) {
    if (canStartMoving(direction)) {
        pacmanDirection = direction;
        isMoving = 1;

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
        
        int newTargetX = pacmanPixelX;
        int newTargetY = pacmanPixelY;
        
        switch (direction) {
            case Left:
                newTargetX -= cellwidth;
                break;
            case Right:
                newTargetX += cellwidth;
                break;
            case Up:
                newTargetY += cellheight;
                break;
            case Down:
                newTargetY -= cellheight;
                break;
        }
        
        if (isPixelPositionValid(newTargetX, newTargetY)) {
            targetPixelX = newTargetX;
            targetPixelY = newTargetY;
        } else {
            isMoving = 0;
        }
    }

}

//Turns Pixel Coordinates into Grid Coordinates and checks if they're valid
int isPixelPositionValid(int pixelX, int pixelY) {
    int row, col;
    getGridPosition(pixelX, pixelY, &row, &col);
    return isValidPosition(row, col);
}

int canStartMoving(int direction) {
    if (!isPacmanAlignedWithGrid()) {
        alignPacmanToGrid();
    }
    
    return canMoveInDirection(direction);
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
        // Before snapping, verify the target position is still valid
        if (isPixelPositionValid(targetPixelX, targetPixelY)) {
            pacmanPixelX = targetPixelX;
            pacmanPixelY = targetPixelY;
            isMoving = 0; //Keeps moving in that direction until change
            
            // Update grid position
            getGridPosition(pacmanPixelX, pacmanPixelY, &pacmanRow, &pacmanCol);
            
            // Eat food/pellets at new position
            if (level1page) {
                if (maze1[pacmanRow][pacmanCol] == 2) {
                    maze1[pacmanRow][pacmanCol] = -1;  // Remove power pellet
                } else if (maze1[pacmanRow][pacmanCol] == 0) {
                    maze1[pacmanRow][pacmanCol] = -1;  // Remove dot
                }
            }
            else if (level2page) {
                if (maze2[pacmanRow][pacmanCol] == 2) {
                    maze2[pacmanRow][pacmanCol] = -1;  // Remove power pellet
                } else if (maze2[pacmanRow][pacmanCol] == 0) {
                    maze2[pacmanRow][pacmanCol] = -1;  // Remove dot
                }
            }
            else if (level3page) {
                if (maze3[pacmanRow][pacmanCol] == 2) {
                    maze3[pacmanRow][pacmanCol] = -1;  // Remove power pellet
                } else if (maze3[pacmanRow][pacmanCol] == 0) {
                    maze3[pacmanRow][pacmanCol] = -1;  // Remove dot
                }
            }
            // Check for pending direction changes
            if (pendingDirection != -1 && canMoveInDirection(pendingDirection)) {
                pacmanDirection = pendingDirection;
                startMoving(pendingDirection);
                pendingDirection = -1;
            }
            // Otherwise continue in current direction if possible
            else if (canMoveInDirection(pacmanDirection)) {
                startMoving(pacmanDirection);
            }
            else {
            // Target position became invalid, stop and align
            isMoving = 0;
            alignPacmanToGrid();
            }
            }
        }    
        else {
        // Calculate next position with smaller steps for better collision detection
        int stepSize = min(pacmanSpeed, distance);
        int nextX = pacmanPixelX;
        int nextY = pacmanPixelY;
        
        // Move in smaller increments to avoid skipping through walls
        if (distanceX > 0) nextX += min(stepSize, distanceX);
        else if (distanceX < 0) nextX += max(-stepSize, distanceX);
        
        if (distanceY > 0) nextY += min(stepSize, distanceY);
        else if (distanceY < 0) nextY += max(-stepSize, distanceY);
        
        // Validate the next position before moving
        if (isPixelPositionValid(nextX, nextY)) {
            pacmanPixelX = nextX;
            pacmanPixelY = nextY;
        } else {
            // Hit a wall, stop moving and align to grid
            isMoving = 0;
            alignPacmanToGrid();
            }
        }
}




void InitializeGhosts(){
    numGhosts = 0;
    
    if (level1page) {
        // Find ghost spawn positions (value 5 in maze1)
        for(int i = 0; i < row1; i++) {
            for(int j = 0; j < col1; j++) {
                if(maze1[i][j] == 5 && numGhosts < MAX_GHOSTS) {
                    ghosts[numGhosts].row = i;
                    ghosts[numGhosts].col = j;
                    
                    // Convert to pixel coordinates
                    int cellwidth = screenWidth / col1;
                    int cellheight = screenHeight / row1;
                    ghosts[numGhosts].pixelX = j * cellwidth + 8;
                    ghosts[numGhosts].pixelY = screenHeight - (i + 1) * cellheight + 8;
                    
                    // Set initial target to current position
                    ghosts[numGhosts].targetX = ghosts[numGhosts].pixelX;
                    ghosts[numGhosts].targetY = ghosts[numGhosts].pixelY;
                    
                    // Initialize other properties
                    ghosts[numGhosts].direction = Right; // Start moving right
                    ghosts[numGhosts].isMoving = 0;
                    ghosts[numGhosts].color = numGhosts; // Different color for each ghost
                    ghosts[numGhosts].moveCounter = 0;
                    
                    // Remove spawn marker from maze
                    maze1[i][j] = -1;
                    numGhosts++;
                }
            }
        }
    }
    else if (level2page) {
        // Similar logic for level2
        for(int i = 0; i < row2; i++) {
            for(int j = 0; j < col2; j++) {
                if(maze2[i][j] == 5 && numGhosts < MAX_GHOSTS) {
                    ghosts[numGhosts].row = i;
                    ghosts[numGhosts].col = j;
                    
                    int cellwidth = screenWidth / col2;
                    int cellheight = screenHeight / row2;
                    ghosts[numGhosts].pixelX = j * cellwidth + 5;
                    ghosts[numGhosts].pixelY = screenHeight - (i + 1) * cellheight + 5;
                    
                    ghosts[numGhosts].targetX = ghosts[numGhosts].pixelX;
                    ghosts[numGhosts].targetY = ghosts[numGhosts].pixelY;
                    ghosts[numGhosts].direction = Right;
                    ghosts[numGhosts].isMoving = 0;
                    ghosts[numGhosts].color = numGhosts;
                    ghosts[numGhosts].moveCounter = 0;
                    
                    maze2[i][j] = -1;
                    numGhosts++;
                }
            }
        }
    }
    else if (level3page) {
        // Similar logic for level3
        for(int i = 0; i < row3; i++) {
            for(int j = 0; j < col3; j++) {
                if(maze3[i][j] == 5 && numGhosts < MAX_GHOSTS) {
                    ghosts[numGhosts].row = i;
                    ghosts[numGhosts].col = j;
                    
                    int cellwidth = screenWidth / col3;
                    int cellheight = screenHeight / row3;
                    ghosts[numGhosts].pixelX = j * cellwidth + 5;
                    ghosts[numGhosts].pixelY = screenHeight - (i + 1) * cellheight + 5;
                    
                    ghosts[numGhosts].targetX = ghosts[numGhosts].pixelX;
                    ghosts[numGhosts].targetY = ghosts[numGhosts].pixelY;
                    ghosts[numGhosts].direction = Right;
                    ghosts[numGhosts].isMoving = 0;
                    ghosts[numGhosts].color = numGhosts;
                    ghosts[numGhosts].moveCounter = 0;
                    
                    maze3[i][j] = -1;
                    numGhosts++;
                }
            }
        }
    }
}

int canGhostMoveInDirection(Ghost* ghost, int direction){
    int newRow = ghost -> row;
    int newCol = ghost -> col;

    switch(direction){
        case Left   : newCol--; break;
        case Right  : newCol++; break;
        case Up     : newRow++; break;
        case Down   : newRow--; break;
    }

    return isValidPosition(newRow, newCol);
}

int getValidDirections(Ghost* ghost, int validDirs[4]){
    int count = 0;
    int directions[] = {Left, Right, Up, Down};
    
    for (int i = 0; i < 4; i++){
        if (canGhostMoveInDirection(ghost ,directions[i])){
            validDirs[count] = directions[i];
            count++;
        }
    }

    return count;
}

int chooseRandomDirection(Ghost* ghost) {
    int validDirs[4];
    int numValidDirs = getValidDirections(ghost, validDirs);
    
    if(numValidDirs == 0) {
        return ghost->direction; // No valid moves, keep current direction
    }
    
    // Prefer not to reverse direction (makes movement more natural)
    int oppositeDir = -1;
    switch(ghost->direction) {
        case Left: oppositeDir = Right; break;
        case Right: oppositeDir = Left; break;
        case Up: oppositeDir = Down; break;
        case Down: oppositeDir = Up; break;
    }
    
    // Try to find directions that aren't opposite
    int preferredDirs[4];
    int numPreferred = 0;
    
    for (int i = 0; i < numValidDirs; i++){
        if (validDirs[i] != oppositeDir){
            preferredDirs[numPreferred] = validDirs[i];
            numPreferred++;
        }
    }
    
    // If we have preferred directions, use them
    if(numPreferred > 0) {
        return preferredDirs[rand() % numPreferred];
    }
    
    // Otherwise, use any valid direction
    return validDirs[rand() % numValidDirs];
}

void startGhostMoving(Ghost* ghost, int direction) {
    if(!canGhostMoveInDirection(ghost, direction)) {
        return;
    }
    
    ghost->direction = direction;
    ghost->isMoving = 1;
    
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
    
    int newTargetX = ghost->pixelX;
    int newTargetY = ghost->pixelY;
    
    switch (direction) {
        case Left:
            newTargetX -= cellwidth;
            break;
        case Right:
            newTargetX += cellwidth;
            break;
        case Up:
            newTargetY += cellheight;
            break;
        case Down:
            newTargetY -= cellheight;
            break;
    }
    
    ghost->targetX = newTargetX;
    ghost->targetY = newTargetY;
}

void updateGhostMovement(){
    for(int i = 0; i < numGhosts; i++) {
        Ghost* ghost = &ghosts[i];
        
        // If not moving, try to start moving
        if(!ghost->isMoving) {
            // Add some randomness to movement timing
            ghost->moveCounter++;
            if(ghost->moveCounter >= 10) { // Wait 10 frames before moving
                int newDirection = chooseRandomDirection(ghost);
                startGhostMoving(ghost, newDirection);
                ghost->moveCounter = 0;
            }
            continue;
        }
        
        // Calculate distance to target
        int distanceX = ghost->targetX - ghost->pixelX;
        int distanceY = ghost->targetY - ghost->pixelY;
        int distance = abs(distanceX) + abs(distanceY);
        
        // If close enough to target, snap to it
        if(distance <= GHOST_SPEED) {
            ghost->pixelX = ghost->targetX;
            ghost->pixelY = ghost->targetY;
            ghost->isMoving = 0;
            
            // Update grid position
            getGridPosition(ghost->pixelX, ghost->pixelY, &ghost->row, &ghost->col);
            
            // Immediately choose next direction for continuous movement
            int newDirection = chooseRandomDirection(ghost);
            if (canGhostMoveInDirection(ghost, newDirection))
                startGhostMoving(ghost, newDirection);
        }
        else {
            // Move towards target
            int nextX = ghost->pixelX;
            int nextY = ghost->pixelY;
            
            if(distanceX > 0) nextX += min(GHOST_SPEED, distanceX);
            else if(distanceX < 0) nextX += max(-GHOST_SPEED, distanceX);
            
            if(distanceY > 0) nextY += min(GHOST_SPEED, distanceY);
            else if(distanceY < 0) nextY += max(-GHOST_SPEED, distanceY);
            
            ghost->pixelX = nextX;
            ghost->pixelY = nextY;
        }
    }
}

int checkGhostCollision() {
    for(int i = 0; i < numGhosts; i++) {
        Ghost* ghost = &ghosts[i];
        
        // Check if ghost and pacman are in same grid cell or very close
        int distance = abs(ghost->pixelX - pacmanPixelX) + abs(ghost->pixelY - pacmanPixelY);
        
        if (level1page){
            if(distance < 20) { // Collision threshold
                return 1; // Collision detected
            }
        }
        else if (level2page){
            if (distance < 16)
                return 1;
        }
        else{
            if (distance < 12)
                return 1;
        }
    }
    return 0; // No collision
}

void drawGhosts() {
    for(int i = 0; i < numGhosts; i++) {
        Ghost* ghost = &ghosts[i];
        iShowImage(ghost -> pixelX, ghost -> pixelY,  "Sprites\\ghosts\\blinky.png");
    }
}


void drawHomepage()
{

    iSetColor(0, 0, 0); // black color
    iFilledRectangle(0, 0, screenWidth, screenHeight); // fill the background
    iShowImage(0, 0, "images\\front page.png");
    iSetColor (255, 255, 0); // yellow color for text
    iText(92, 52, "Press F1 to stop/start Music", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(655, 52, "PRESS Esc to go back", GLUT_BITMAP_TIMES_ROMAN_24);


}

void drawEnterNamePage(){
    iSetColor(255, 255, 255);
    iFilledRectangle(0, 0, screenWidth, screenHeight);
    iShowImage(0, 0, "images\\EnterNamePage.jpeg");
    iText(inputBoxX, inputBoxY - 10, playerName, GLUT_BITMAP_TIMES_ROMAN_24);


}

void drawPacman() {
    if (level1page){
        switch(pacmanDirection){
            case Right:
                if (movementflag >= 1 && movementflag < 20){
                    iShowImage(pacmanPixelX, pacmanPixelY, "Sprites\\pacman-right\\Easy1.png");
                    movementflag++;
                }
                else if (movementflag >= 20 && movementflag < 40){
                    iShowImage(pacmanPixelX, pacmanPixelY, "Sprites\\pacman-right\\Easy2.png");
                    movementflag++;
                }
                else if (movementflag >= 40 && movementflag < 60){
                    iShowImage(pacmanPixelX, pacmanPixelY, "Sprites\\pacman-right\\Easy3.png");
                    movementflag++;
                }
                else if (movementflag >= 60){
                    movementflag = 1; // Reset animation cycle
                    iShowImage(pacmanPixelX, pacmanPixelY, "Sprites\\pacman-right\\Easy1.png");
                }
                break;
            
            case Left:
                if (movementflag >= 1 && movementflag < 20){
                    iShowImage(pacmanPixelX, pacmanPixelY, "Sprites\\pacman-left\\Easy1.png");
                    movementflag++;
                }
                else if (movementflag >= 20 && movementflag < 40){
                    iShowImage(pacmanPixelX, pacmanPixelY, "Sprites\\pacman-left\\Easy2.png");
                    movementflag++;
                }
                else if (movementflag >= 40 && movementflag < 60){
                    iShowImage(pacmanPixelX, pacmanPixelY, "Sprites\\pacman-left\\Easy3.png");
                    movementflag++;
                }
                else if (movementflag >= 60){
                    movementflag = 1; // Reset animation cycle
                    iShowImage(pacmanPixelX, pacmanPixelY, "Sprites\\pacman-left\\Easy1.png");
                }
                break;
            case Up:
                if (movementflag >= 1 && movementflag < 20){
                    iShowImage(pacmanPixelX, pacmanPixelY, "Sprites\\pacman-up\\Easy1.png");
                    movementflag++;
                }
                else if (movementflag >= 20 && movementflag < 40){
                    iShowImage(pacmanPixelX, pacmanPixelY, "Sprites\\pacman-up\\Easy2.png");
                    movementflag++;
                }
                else if (movementflag >= 40 && movementflag < 60){
                    iShowImage(pacmanPixelX, pacmanPixelY, "Sprites\\pacman-up\\Easy3.png");
                    movementflag++;
                }
                else if (movementflag >= 60){
                    movementflag = 1; // Reset animation cycle
                    iShowImage(pacmanPixelX, pacmanPixelY, "Sprites\\pacman-up\\Easy1.png");
                }
                break;
            case Down:
                if (movementflag >= 1 && movementflag < 20){
                    iShowImage(pacmanPixelX, pacmanPixelY, "Sprites\\pacman-down\\Easy1.png");
                    movementflag++;
                }
                else if (movementflag >= 20 && movementflag < 40){
                    iShowImage(pacmanPixelX, pacmanPixelY, "Sprites\\pacman-down\\Easy2.png");
                    movementflag++;
                }
                else if (movementflag >= 40 && movementflag < 60){
                    iShowImage(pacmanPixelX, pacmanPixelY, "Sprites\\pacman-down\\Easy3.png");
                    movementflag++;
                }
                else if (movementflag >= 60){
                    movementflag = 1; // Reset animation cycle
                    iShowImage(pacmanPixelX, pacmanPixelY, "Sprites\\pacman-down\\Easy1.png");
                }
                break;
        }
    }

    else if (level2page){
        switch(pacmanDirection){
            case Right:
                if (movementflag >= 1 && movementflag < 20){
                    iShowImage(pacmanPixelX, pacmanPixelY, "Sprites\\pacman-right\\1.png");
                    movementflag++;
                }
                else if (movementflag >= 20 && movementflag < 40){
                    iShowImage(pacmanPixelX, pacmanPixelY, "Sprites\\pacman-right\\2.png");
                    movementflag++;
                }
                else if (movementflag >= 40 && movementflag < 60){
                    iShowImage(pacmanPixelX, pacmanPixelY, "Sprites\\pacman-right\\3.png");
                    movementflag++;
                }
                else if (movementflag >= 60){
                    movementflag = 1; // Reset animation cycle
                    iShowImage(pacmanPixelX, pacmanPixelY, "Sprites\\pacman-right\\1.png");
                }
                break;
            
            case Left:
                if (movementflag >= 1 && movementflag < 20){
                    iShowImage(pacmanPixelX, pacmanPixelY, "Sprites\\pacman-left\\1.png");
                    movementflag++;
                }
                else if (movementflag >= 20 && movementflag < 40){
                    iShowImage(pacmanPixelX, pacmanPixelY, "Sprites\\pacman-left\\2.png");
                    movementflag++;
                }
                else if (movementflag >= 40 && movementflag < 60){
                    iShowImage(pacmanPixelX, pacmanPixelY, "Sprites\\pacman-left\\3.png");
                    movementflag++;
                }
                else if (movementflag >= 60){
                    movementflag = 1; // Reset animation cycle
                    iShowImage(pacmanPixelX, pacmanPixelY, "Sprites\\pacman-left\\1.png");
                }
                break;
            case Up:
                if (movementflag >= 1 && movementflag < 20){
                    iShowImage(pacmanPixelX, pacmanPixelY, "Sprites\\pacman-up\\1.png");
                    movementflag++;
                }
                else if (movementflag >= 20 && movementflag < 40){
                    iShowImage(pacmanPixelX, pacmanPixelY, "Sprites\\pacman-up\\2.png");
                    movementflag++;
                }
                else if (movementflag >= 40 && movementflag < 60){
                    iShowImage(pacmanPixelX, pacmanPixelY, "Sprites\\pacman-up\\3.png");
                    movementflag++;
                }
                else if (movementflag >= 60){
                    movementflag = 1; // Reset animation cycle
                    iShowImage(pacmanPixelX, pacmanPixelY, "Sprites\\pacman-up\\1.png");
                }
                break;
            case Down:
                if (movementflag >= 1 && movementflag < 20){
                    iShowImage(pacmanPixelX, pacmanPixelY, "Sprites\\pacman-down\\1.png");
                    movementflag++;
                }
                else if (movementflag >= 20 && movementflag < 40){
                    iShowImage(pacmanPixelX, pacmanPixelY, "Sprites\\pacman-down\\2.png");
                    movementflag++;
                }
                else if (movementflag >= 40 && movementflag < 60){
                    iShowImage(pacmanPixelX, pacmanPixelY, "Sprites\\pacman-down\\3.png");
                    movementflag++;
                }
                else if (movementflag >= 60){
                    movementflag = 1; // Reset animation cycle
                    iShowImage(pacmanPixelX, pacmanPixelY, "Sprites\\pacman-down\\1.png");
                }
                break;
        }
    }

    else if (level3page){
        switch(pacmanDirection){
            case Right:
                if (movementflag >= 1 && movementflag < 5){
                    iShowImage(pacmanPixelX, pacmanPixelY, "Sprites\\pacman-right\\Hard1.png");
                    movementflag++;
                }
                else if (movementflag >= 5 && movementflag < 10){
                    iShowImage(pacmanPixelX, pacmanPixelY, "Sprites\\pacman-right\\Hard2.png");
                    movementflag++;
                }
                else if (movementflag >= 10 && movementflag < 15){
                    iShowImage(pacmanPixelX, pacmanPixelY, "Sprites\\pacman-right\\Hard3.png");
                    movementflag++;
                }
                else if (movementflag >= 15){
                    movementflag = 1; // Reset animation cycle
                    iShowImage(pacmanPixelX, pacmanPixelY, "Sprites\\pacman-right\\Hard1.png");
                }
                break;
            
            case Left:
                if (movementflag >= 1 && movementflag < 5){
                    iShowImage(pacmanPixelX, pacmanPixelY, "Sprites\\pacman-left\\Hard1.png");
                    movementflag++;
                }
                else if (movementflag >= 5 && movementflag < 10){
                    iShowImage(pacmanPixelX, pacmanPixelY, "Sprites\\pacman-left\\Hard2.png");
                    movementflag++;
                }
                else if (movementflag >= 10 && movementflag < 15){
                    iShowImage(pacmanPixelX, pacmanPixelY, "Sprites\\pacman-left\\Hard3.png");
                    movementflag++;
                }
                else if (movementflag >= 15){
                    movementflag = 1; // Reset animation cycle
                    iShowImage(pacmanPixelX, pacmanPixelY, "Sprites\\pacman-left\\Hard1.png");
                }
                break;
            case Up:
                if (movementflag >= 1 && movementflag < 5){
                    iShowImage(pacmanPixelX, pacmanPixelY, "Sprites\\pacman-up\\Hard1.png");
                    movementflag++;
                }
                else if (movementflag >= 5 && movementflag < 10){
                    iShowImage(pacmanPixelX, pacmanPixelY, "Sprites\\pacman-up\\Hard2.png");
                    movementflag++;
                }
                else if (movementflag >= 10 && movementflag < 15){
                    iShowImage(pacmanPixelX, pacmanPixelY, "Sprites\\pacman-up\\Hard3.png");
                    movementflag++;
                }
                else if (movementflag >= 15){
                    movementflag = 1; // Reset animation cycle
                    iShowImage(pacmanPixelX, pacmanPixelY, "Sprites\\pacman-up\\Hard1.png");
                }
                break;
            case Down:
                if (movementflag >= 1 && movementflag < 5){
                    iShowImage(pacmanPixelX, pacmanPixelY, "Sprites\\pacman-down\\Hard1.png");
                    movementflag++;
                }
                else if (movementflag >= 5 && movementflag < 10){
                    iShowImage(pacmanPixelX, pacmanPixelY, "Sprites\\pacman-down\\Hard2.png");
                    movementflag++;
                }
                else if (movementflag >= 10 && movementflag < 15){
                    iShowImage(pacmanPixelX, pacmanPixelY, "Sprites\\pacman-down\\Hard3.png");
                    movementflag++;
                }
                else if (movementflag >= 15){
                    movementflag = 1; // Reset animation cycle
                    iShowImage(pacmanPixelX, pacmanPixelY, "Sprites\\pacman-down\\Hard1.png");
                }
                break;
        }
    } 
}


void drawLevelSelectionPage(){
    iSetColor(0, 255, 0);
    iFilledRectangle(0, 0, screenWidth, screenHeight);
    iShowImage(0, 0, "images\\LevelSelectionPage.jpg");
    iShowImage(90, 380, "images\\ButtonEasy.png");
    iShowImage(90, 280, "images\\ButtonMedium.png");
    iShowImage(90, 180, "images\\ButtonHard.png");
    iSetColor(255, 255, 255);
    iText(75, 490, "SELECT DIFFICULTY:", GLUT_BITMAP_TIMES_ROMAN_24);
}



void drawInstructions()
{
    iSetColor(0, 0, 0); // black color
    iFilledRectangle(0, 0, screenWidth, screenHeight); // fill the background
    iShowImage(0, 0, "images\\background.png");
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
    iSetColor(0, 0, 0); // black color
    iFilledRectangle(0, 0, screenWidth, screenHeight); // fill the background
    iShowImage(0, 0, "images\\background.png");
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
    iShowImage(0, 0, "images\\menupage.jpg");
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
    PlaySound("music\\menuMusic.wav", NULL, SND_LOOP | SND_ASYNC);
    glutInit(&argc, argv);
    iSetTimer(25, updatePacmanMovement);
    iSetTimer(60, drawPacman);
    iSetTimer(25, updateGhostMovement);
    // place your own initialization codes here.
    iInitialize(screenWidth, screenHeight, "pacman");
    return 0;
}
