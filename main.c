#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <string.h>
#include <math.h>

#define MAX_ROWS 22
#define MAX_COLS 121
#define MIN_Px1 0
#define MAX_Px1 24
#define MIN_Px2 85
#define MAX_Px2 111
#define TRUE 1
#define FALSE 0
#define UNAVAILABLE -1
#define MIN_POWERINPUT 1
#define MAX_POWERINPUT 100
#define MIN_ANGLE 0
#define MAX_ANGLE 180
#define THREE_SECONDS 3000
#define PI 3.14159265358
#define g 0.4
#define DELTA_t 0.1
#define DECREASED_HEALTH 20
#define PI_DEGREE 180.0
#define THREE_QUARTERS_OF_A_SECONDS 750

int randomPx(int min, int max);
void resetPlayground(char playground[MAX_ROWS][MAX_COLS]);
void Tank1InPlayground(int Px, char playground[MAX_ROWS][MAX_COLS]);
void Tank2InPlayground(int Px, char playground[MAX_ROWS][MAX_COLS]);
void statusBar(int health1, int health2);
void printPlaygroundWithFrame(char playground[MAX_ROWS][MAX_COLS]);
int firstPxOfBullet1(int Px1);
int firstPxOfBullet2(int Px2);
int getAngle(char playground[MAX_ROWS][MAX_COLS], int *health1, int *health2);
int getPower(char playground[MAX_ROWS][MAX_COLS], int *health1, int *health2);
void skipPlayer(int health1, int health2, char playground[MAX_ROWS][MAX_COLS], int *round);
void newgame(int *health1, int *health2, int *round, int *Px1, int *Px2, char playground[MAX_ROWS][MAX_COLS]);
int moveRight(int *Px,int *Px1, int *Px2, int number_of_move, int minPx, int maxPx, int *round, int *health1, int *health2, char playground[MAX_ROWS][MAX_COLS]);
int moveLeft(int *Px,int *Px1, int *Px2, int number_of_move, int minPx, int maxPx, int *round, int *health1, int *health2, char playground[MAX_ROWS][MAX_COLS]);
int Back(int *counter_back, char playground[MAX_ROWS][MAX_COLS], int *round, int Px1, int Px2, int *health1, int *health2, int last_Px1, int last_Px2, int last_health1, int last_health2, int shooter);
int changePositionOfTank(int *Px1,int *Px2, int *health1, int *health2, char playground[MAX_ROWS][MAX_COLS], char move, int number_of_move, int *round, int minPx, int maxPx, int shooter, int *counter_back, int last_health1, int last_health2, int last_Px1, int last_Px2);
void showTheBulletBeforeHit(double t, double vx, double vy, int X0, int Y0_in_the_playground, double x, double y, int col, int row, int Px1, int Px2, char playground[MAX_ROWS][MAX_COLS]);
int bulletHitToRockOrWallOrGround(int health1, int health2, double t, double vx, double vy, int X0, int Y0_in_the_playground, double x, double y, int col, int row, int Px1, int Px2, char playground[MAX_ROWS][MAX_COLS], int *last_health1, int *last_health2);
int hitTank1(int shooter, int *health1, int *health2, double t, double vx, double vy, int X0, int Y0_in_the_playground, double x, double y, int col, int row, int Px1, int Px2, char playground[MAX_ROWS][MAX_COLS], int *last_health1, int *last_health2);
int hitTank2(int shooter, int *health1, int *health2, double t, double vx, double vy, int X0, int Y0_in_the_playground, double x, double y, int col, int row, int Px1, int Px2, char playground[MAX_ROWS][MAX_COLS], int *last_health2, int *last_health1);
void printPlaygroundEverySixHousesMove(char playground[MAX_ROWS][MAX_COLS], int *stage, int *first_time, int Px1, int Px2, int row, int col);
void positionOfBullet(int shooter, int X0, int Y0, int power_input, int angle, char playground[MAX_ROWS][MAX_COLS], int Px1, int Px2, int *health1, int *health2, int *last_health1, int *last_health2);

int main() {
    srand(time(NULL));
    char grid[MAX_ROWS][MAX_COLS] = {
        "                  ^                                                                                                     ",
        "                 ^^^                                                                            ^                       ",
        "                ^^^^^                                                                          ^^^                      ",
        "                                                                                              ^^^^^                     ",
        "                                                                                                                        ",
        "                                                                                                                        ",
        "                      ^^                                                                                                ",
        "                     ^^^^                                                                                               ",
        "                    ^^^^^^                                                                                    ^         ",
        "                                                                                                             ^^^        ",
        "                                                                                                                        ",
        "                                                                                                                        ",
        "                                                          ^                                                             ",
        "                                                         ^^^         ^^                                                 ", 
        "                                                        ^^^^^       ^^^^                                                ", 
        "                                               ^       ^^^^^^^^    ^^^^^^                                               ",
        "                                              ^^^     ^^^^^^^^^^  ^^^^^^^^     ^                                        ",
        "                                   ^^        ^^^^^  ^^^^^^^^^^^^^^^^^^^^^^^^  ^^^                                       ", 
        "                                  ^^^^     ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^                                      ",
        "                                 ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^                                    ",
        "########################################################################################################################", 
        "########################################################################################################################"
    };
    int result;
    int Px1 = randomPx(MIN_Px1, MAX_Px1); /*Px1 shows the leftmost and lowest tank1 house and make it with random*/
    int Px2 = randomPx(MIN_Px2, MAX_Px2); /*Px2 shows the leftmost and lowest tank2 house and make it with random*/
    int round = 1;
    int health1 = 100, health2 = 100;
    int X0_1 = 0, Y0_1 = 17; /*X0_1 and Y0_1 shows the first position of bullet1*/
    int X0_2 = 0, Y0_2 = 17; /*X0_2 and Y0_2 shows the first position of bullet2*/
    char move1, move2;
    int number_of_move1 = 0, number_of_move2 = 0;
    int angle1 = 0, angle2 = 0;
    int power_input1 = 0, power_input2 = 0;
    int counter_back1 = 0, counter_back2 = 0;
    int last_health1 = 0, last_health2 = 0;
    int last_Px1 = Px1, last_Px2 = Px2; 
    Tank1InPlayground(Px1, grid);
    Tank2InPlayground(Px2, grid);
    statusBar(health1, health2);
    printPlaygroundWithFrame(grid);
    /*this loop shows the flow of the game*/
    while (TRUE) {
        if (round % 2 != 0) {
            last_Px1 = Px1;
            printf("\n(Player 1) Enter Command - L=Left, R=Right, S=Skip, Q=Quit, N=New Game, B=Back: ");
            scanf(" %c", &move1);
            if (move1 == 'R' || move1 == 'L') {
                scanf(" %d", &number_of_move1);
            }
            result = changePositionOfTank(&Px1, &Px2, &health1, &health2, grid, move1, number_of_move1, &round, MIN_Px1, MAX_Px1, 1, &counter_back1, last_health1, last_health2, last_Px1, last_Px2);
            if (result == TRUE && (move1 == 'R' || move1 == 'L' || move1 == 'B')) {
                printf("\n(Player 1) Enter Firing Angle [0-180]: ");
                angle1 = getAngle(grid, &health1, &health2);
                if (angle1 != UNAVAILABLE) {
                    printf("(Player 1) Enter Shot Power [1-100]: ");
                    power_input1 = getPower(grid, &health1, &health2);
                    if (power_input1 != UNAVAILABLE) {
                        X0_1 = firstPxOfBullet1(Px1);
                        positionOfBullet(1, X0_1, Y0_1, power_input1, angle1, grid, Px1, Px2, &health1, &health2, &last_health1, &last_health2);
                    }
                }
            }
            /*when health of one of tank runs out the game is over*/
            if (health1 == 0 || health2 == 0) {
                break;
            }
        }
        else {
            last_Px2 = Px2;
            printf("\n(Player 2) Enter Command - L=Left, R=Right, S=Skip, Q=Quit, N=New Game, B=Back: ");
            scanf(" %c", &move2);
            if (move2 == 'R' || move2 == 'L') {
                scanf(" %d", &number_of_move2);
            }
            result = changePositionOfTank(&Px1, &Px2, &health1, &health2, grid, move2, number_of_move2, &round, MIN_Px2, MAX_Px2, 2, &counter_back2, last_health1, last_health2, last_Px1, last_Px2);
            if (result == TRUE && ( move2 == 'R' || move2 == 'L' || move2 == 'B')) {
                printf("\n(Player 2) Enter Firing Angle [0-180]: ");
                angle2 = getAngle(grid, &health1, &health2);
                if (angle2 != UNAVAILABLE) {
                    printf("(Player 2) Enter Shot Power [1-100]: ");
                    power_input2 = getPower(grid, &health1, &health2);
                    if (power_input2 != UNAVAILABLE) {
                        X0_2 = firstPxOfBullet2(Px2);
                        positionOfBullet(2, X0_2, Y0_2, power_input2, angle2, grid, Px1, Px2, &health1, &health2, &last_health1, &last_health2);
                    }
                }
            }
            /*when health of one of the tank runs out the game is over*/
            if (health1 == 0 || health2 == 0) {
                break;
            }
        }
    }
    if (health1 == 0) {
        printf("--------------------------------------------------------PLAYER 2 WINS-----------------------------------------------------");
    }
    else {
        printf("--------------------------------------------------------PLAYER 1 WINS-----------------------------------------------------");
    }
}

/*this function calculate a random Px for tanks with minimum position and maximum position*/
int randomPx(int min, int max) {
    int Px = min + (rand() % (max - min + 1));
    return Px;
}

/*this function make a new playground without tanks and bullet*/
void resetPlayground(char playground[MAX_ROWS][MAX_COLS]) {
    strcpy(playground[0], "                  ^                                                                                                     ");
    strcpy(playground[1], "                 ^^^                                                                            ^                       ");
    strcpy(playground[2], "                ^^^^^                                                                          ^^^                      ");
    strcpy(playground[3], "                                                                                              ^^^^^                     ");
    strcpy(playground[4], "                                                                                                                        ");
    strcpy(playground[5], "                                                                                                                        ");
    strcpy(playground[6], "                      ^^                                                                                                ");
    strcpy(playground[7], "                     ^^^^                                                                                               ");
    strcpy(playground[8], "                    ^^^^^^                                                                                    ^         ");
    strcpy(playground[9], "                                                                                                             ^^^        ");
    strcpy(playground[10], "                                                                                                                        ");
    strcpy(playground[11], "                                                                                                                        ");
    strcpy(playground[12], "                                                          ^                                                             ");
    strcpy(playground[13], "                                                         ^^^         ^^                                                 ");
    strcpy(playground[14], "                                                        ^^^^^       ^^^^                                                ");
    strcpy(playground[15], "                                               ^       ^^^^^^^^    ^^^^^^                                               ");
    strcpy(playground[16], "                                              ^^^     ^^^^^^^^^^  ^^^^^^^^     ^                                        ");
    strcpy(playground[17], "                                   ^^        ^^^^^  ^^^^^^^^^^^^^^^^^^^^^^^^  ^^^                                       ");
    strcpy(playground[18], "                                  ^^^^     ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^                                      ");
    strcpy(playground[19], "                                 ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^                                    ");
    strcpy(playground[20], "########################################################################################################################");
    strcpy(playground[21], "########################################################################################################################");
}

/*this function draws the tank1 in the playground*/
void Tank1InPlayground(int Px, char playground[MAX_ROWS][MAX_COLS]) {
    playground[17][Px+3] = '_';
    playground[17][Px+4] = '_';
    playground[18][Px+1] = '_';
    playground[18][Px+2] = '|';
    playground[18][Px+3] = '_';
    playground[18][Px+4] = '_';
    playground[18][Px+5] = '|';
    playground[18][Px+6] = '_';
    playground[18][Px+7] = '/';
    playground[18][Px+8] = '/';
    playground[19][Px] = '|';
    playground[19][Px+1] = '_';
    playground[19][Px+2] = '_';
    playground[19][Px+3] = '_';
    playground[19][Px+4] = '_';
    playground[19][Px+5] = '_';
    playground[19][Px+6] = '_';
    playground[19][Px+7] = '_';
    playground[19][Px+8] = '|';
}

/*this function draws the tank2 in the playground*/
void Tank2InPlayground(int Px, char playground[MAX_ROWS][MAX_COLS]) {
    playground[17][Px+4] = '_';
    playground[17][Px+5] = '_';
    playground[18][Px] = '\\';
    playground[18][Px+1] = '\\';
    playground[18][Px+2] = '_';
    playground[18][Px+3] = '|';
    playground[18][Px+4] = '_';
    playground[18][Px+5] = '_';
    playground[18][Px+6] = '|';
    playground[18][Px+7] = '_';
    playground[19][Px] = '|';
    playground[19][Px+1] = '_';
    playground[19][Px+2] = '_';
    playground[19][Px+3] = '_';
    playground[19][Px+4] = '_';
    playground[19][Px+5] = '_';
    playground[19][Px+6] = '_';
    playground[19][Px+7] = '_';
    playground[19][Px+8] = '|';
}

/*this function draws the status bar of tanks*/
void statusBar(int health1, int health2) {
    for (int i=0; i<(MAX_COLS+1); i++) {
        printf("=");
    }
    printf("\n");
    printf("|                         [P1] TANK ALPHA  | HEALTH: %3d%%   ||   [P2] TANK BETA  | HEALTH: %3d%%                          |\n", health1, health2);
    for (int i=0; i<(MAX_COLS+1); i++) {
        printf("=");
    }
    printf("\n");
}

/*this function draws the frame of playground*/
void printPlaygroundWithFrame(char playground[MAX_ROWS][MAX_COLS]) {
    printf("|");
    for (int i=0; i<(MAX_COLS-1); i++) {
        printf("-");
    }
    printf("|\n");
    for (int i=0; i<(MAX_ROWS); i++) {
        printf("|");
        printf("%s", playground[i]);
        printf("|\n");
    }
    printf("|");
    for (int i=0; i<(MAX_COLS-1); i++) {
        printf("-");
    }
    printf("|\n");
}

/*this function calculates the first postion of bullet1*/
int firstPxOfBullet1(int Px1) {
    return (Px1 + 9);
}

/*this function calculates the first postion of bullet2*/
int firstPxOfBullet2(int Px2) {
    return (Px2 - 1);
}

/*this function get a number between 0 to 180 for angle for bullet from user*/
int getAngle(char playground[MAX_ROWS][MAX_COLS], int *health1, int *health2) {
    int angle;
    scanf("%d", &angle);
    if ((angle >= MIN_ANGLE) && (angle <= MAX_ANGLE)) {
        return angle;
    }
    else {
        printf("Angle Out Of Range - Your Turn Is Lost!\n");
        Sleep(THREE_SECONDS);
        system("cls");
        statusBar(*health1, *health2);
        printPlaygroundWithFrame(playground);
        return UNAVAILABLE;
    }
}

/*this function get a number between 1 to 100 for power input for bullet from user*/
int getPower(char playground[MAX_ROWS][MAX_COLS], int *health1, int *health2) {
    int power_input;
    scanf("%d", &power_input);
    if ((power_input >= MIN_POWERINPUT) && (power_input <= MAX_POWERINPUT)) {
        return power_input;
    }
    else {
        printf("Power Out Of Range - Your Turn Is Lost!\n");
        Sleep(THREE_SECONDS);
        system("cls");
        statusBar(*health1, *health2);
        printPlaygroundWithFrame(playground);
        return UNAVAILABLE;
    }
}

/*this function skips the turn of player*/
void skipPlayer(int health1, int health2, char playground[MAX_ROWS][MAX_COLS], int *round) {
    system("cls");
    statusBar(health1, health2);
    printPlaygroundWithFrame(playground);
    (*round)++;
} 

/*this function make a new game with random Px for each tank*/
void newgame(int *health1, int *health2, int *round, int *Px1, int *Px2, char playground[MAX_ROWS][MAX_COLS]) {
    system("cls");
    *health1 = 100;
    *health2 = 100;
    *round = 1;
    *Px1 = randomPx(MIN_Px1, MAX_Px1);
    *Px2 = randomPx(MIN_Px2, MAX_Px2);
    resetPlayground(playground);
    Tank1InPlayground(*Px1, playground);
    Tank2InPlayground(*Px2, playground);
    statusBar(*health1, *health2);
    printPlaygroundWithFrame(playground);
}

/*this function move the tank to right and if the tank can not move skips the turn of player*/
int moveRight(int *Px,int *Px1, int *Px2, int number_of_move, int minPx, int maxPx, int *round, int *health1, int *health2, char playground[MAX_ROWS][MAX_COLS]) {
    *Px = *Px + number_of_move;
    if ((*Px < minPx) || (*Px > maxPx)) {
        *Px = *Px - number_of_move;
        printf("Illegal Move - Your Turn Is Lost!\n");
        Sleep(THREE_SECONDS);
        (*round)++;
        system("cls");
        resetPlayground(playground);
        Tank1InPlayground(*Px1, playground);
        Tank2InPlayground(*Px2, playground);
        statusBar(*health1, *health2);
        printPlaygroundWithFrame(playground);
        return FALSE;
    }
    else {
        system("cls");
        resetPlayground(playground);
        Tank1InPlayground(*Px1, playground);
        Tank2InPlayground(*Px2, playground);
        statusBar(*health1, *health2);
        printPlaygroundWithFrame(playground);
        (*round)++;
        return TRUE;
    }
}

/*this function move the tank to left and if the tank can not move skips the turn of player*/
int moveLeft(int *Px,int *Px1, int *Px2, int number_of_move, int minPx, int maxPx, int *round, int *health1, int *health2, char playground[MAX_ROWS][MAX_COLS]) {
    *Px = *Px - number_of_move;
    if ((*Px < minPx) || (*Px > maxPx)) {
        *Px = *Px + number_of_move;
        printf("Illegal Move - Your Turn Is Lost!\n");
        Sleep(THREE_SECONDS);
        (*round)++;
        system("cls");
        resetPlayground(playground);
        Tank1InPlayground(*Px1, playground);
        Tank2InPlayground(*Px2, playground);
        statusBar(*health1, *health2);
        printPlaygroundWithFrame(playground);
        return FALSE;
    }
    else {
        system("cls");
        resetPlayground(playground);
        Tank1InPlayground(*Px1, playground);
        Tank2InPlayground(*Px2, playground);
        statusBar(*health1, *health2);
        printPlaygroundWithFrame(playground);
        (*round)++;
        return TRUE;
    }
}

/*this function rewinds the game one turn*/
int Back(int *counter_back, char playground[MAX_ROWS][MAX_COLS], int *round, int Px1, int Px2, int *health1, int *health2, int last_Px1, int last_Px2, int last_health1, int last_health2, int shooter) {
    if (*counter_back >= 1) {
        printf("Ability Is Already Used - Your Turn Is Lost!");
        Sleep(THREE_SECONDS);
        (*round)++;
        system("cls");
        resetPlayground(playground);
        Tank1InPlayground(Px1, playground);
        Tank2InPlayground(Px2, playground);
        statusBar(*health1, *health2);
        printPlaygroundWithFrame(playground);
        return FALSE;
    }
    else {
        (*counter_back)++;
        (*round)++;
        *health1 = last_health1;
        *health2 = last_health2;
        system("cls");
        resetPlayground(playground);
        if (shooter == 1) {
            Tank1InPlayground(Px1, playground);
            Tank2InPlayground(last_Px2, playground);
        }
        else {
            Tank1InPlayground(last_Px1, playground);
            Tank2InPlayground(Px2, playground);
        }
        statusBar(last_health1, last_health2);
        printPlaygroundWithFrame(playground);
        return TRUE;
    }
}

/*this function shows the position of tank and whose turn it is with another function*/
int changePositionOfTank(int *Px1,int *Px2, int *health1, int *health2, char playground[MAX_ROWS][MAX_COLS], char move, int number_of_move, int *round, int minPx, int maxPx, int shooter, int *counter_back, int last_health1, int last_health2, int last_Px1, int last_Px2) {
    int *Px;
    if (shooter == 1) {
        Px = Px1;
    }
    else {
        Px = Px2;
    }
    if (move == 'S') {
        skipPlayer(*health1, *health2, playground, round);
        return FALSE;
    }
    else if (move == 'N') {
        newgame(health1, health2, round, Px1, Px2, playground);
        return TRUE;
    }
    else if (move == 'Q') {
        exit(TRUE);
    }
    else if(move == 'R') {
        int result = moveRight(Px, Px1, Px2, number_of_move, minPx, maxPx, round, health1, health2, playground);
        return result;
    }
    else if(move == 'L') {
        int result = moveLeft(Px, Px1, Px2, number_of_move, minPx, maxPx, round, health1, health2, playground);
        return result;
    }
    else if(move == 'B') {
        int result = Back(counter_back, playground, round, *Px1, *Px2, health1, health2, last_Px1, last_Px2, last_health1, last_health2, shooter);
        return result;
    }
    else {
        printf("Invalid Input - Your Turn Is Lost!\n");
        Sleep(THREE_SECONDS);
        (*round)++;
        system("cls");
        statusBar(*health1, *health2);
        printPlaygroundWithFrame(playground);
        return FALSE;
    }
}

/*this function prints the bullet 0.1 second before hit*/
void showTheBulletBeforeHit(double t, double vx, double vy, int X0, int Y0_in_the_playground, double x, double y, int col, int row, int Px1, int Px2, char playground[MAX_ROWS][MAX_COLS]) {
    t -= DELTA_t;
    x = vx * t + X0;
    y = -0.5 * g * pow(t, 2) + vy * t + Y0_in_the_playground;
    col = (int)round(x);
    row = (MAX_ROWS - 1) - (int)round(y);
    system("cls");
    resetPlayground(playground);
    Tank1InPlayground(Px1, playground);
    Tank2InPlayground(Px2, playground);
    playground[row][col] = '*';
    printPlaygroundWithFrame(playground);
}

/*this function shows the bullet when the bullet hit to the rock or wall or ground*/
int bulletHitToRockOrWallOrGround(int health1, int health2, double t, double vx, double vy, int X0, int Y0_in_the_playground, double x, double y, int col, int row, int Px1, int Px2, char playground[MAX_ROWS][MAX_COLS], int *last_health1, int *last_health2) {
    if (playground[row][col] == '#' || playground[row][col] == '^' || col < 0 || col >= (MAX_COLS-1) || row < 0 || row >= MAX_ROWS) {
        *last_health1 = health1;
        *last_health2 = health2;
        showTheBulletBeforeHit(t, vx, vy, X0, Y0_in_the_playground, x, y, col, row, Px1, Px2, playground);
        printf("Shot Terminated!");
        Sleep(THREE_SECONDS);
        system("cls");
        resetPlayground(playground);
        Tank1InPlayground(Px1, playground);
        Tank2InPlayground(Px2, playground);
        statusBar(health1, health2);
        printPlaygroundWithFrame(playground);
        return TRUE;
    }
    return FALSE;
}

/*this function shows the bullet when the bullet hit to the tank1*/
int hitTank1(int shooter, int *health1, int *health2, double t, double vx, double vy, int X0, int Y0_in_the_playground, double x, double y, int col, int row, int Px1, int Px2, char playground[MAX_ROWS][MAX_COLS], int *last_health1, int *last_health2) {
    if (col >= Px1 && col <= Px1 + 8 && row <= (MAX_ROWS-3) && row >= (MAX_ROWS-5)) {
        showTheBulletBeforeHit(t, vx, vy, X0, Y0_in_the_playground, x, y, col, row, Px1, Px2, playground);
        if (shooter == 1) {
            printf("Boom!!! Friendly Fire");
        }
        else {
            printf("Boom!!! Clean Hit On The Enemy");
        }
        *last_health1 = *health1;
        *last_health2 = *health2;
        *health1 -= DECREASED_HEALTH;
        Sleep(THREE_SECONDS);
        system("cls");
        resetPlayground(playground);
        Tank1InPlayground(Px1, playground);
        Tank2InPlayground(Px2, playground);
        statusBar(*health1, *health2);
        printPlaygroundWithFrame(playground);
        return TRUE;
    }
    return FALSE;
}

/*this function shows the bullet when the bullet hit to the tank2*/
int hitTank2(int shooter, int *health1, int *health2, double t, double vx, double vy, int X0, int Y0_in_the_playground, double x, double y, int col, int row, int Px1, int Px2, char playground[MAX_ROWS][MAX_COLS], int *last_health2, int *last_health1) {
    if (col >= Px2 && col <= Px2 + 8 && row <= (MAX_ROWS-3) && row >= (MAX_ROWS-5)) {
        showTheBulletBeforeHit(t, vx, vy, X0, Y0_in_the_playground, x, y, col, row, Px1, Px2, playground);
        if (shooter == 1) {
            printf("Boom!!! Clean Hit On The Enemy");
        }
        else {
            printf("Boom!!! Friendly Fire");
        }
        *last_health2 = *health2;
        *last_health1 = *health1;
        *health2 -= DECREASED_HEALTH;
        Sleep(THREE_SECONDS);
        system("cls");
        resetPlayground(playground);
        Tank1InPlayground(Px1, playground);
        Tank2InPlayground(Px2, playground);
        statusBar(*health1, *health2);
        printPlaygroundWithFrame(playground);
        return TRUE;
    }
    return FALSE;
}

/*this function prints the playground with bullet and the tanks every six houses move*/
void printPlaygroundEverySixHousesMove(char playground[MAX_ROWS][MAX_COLS], int *stage, int *first_time, int Px1, int Px2, int row, int col) {
    if (*first_time || *stage == 6) {
        Sleep(THREE_QUARTERS_OF_A_SECONDS);
        system("cls");
        resetPlayground(playground);
        Tank1InPlayground(Px1, playground);
        Tank2InPlayground(Px2, playground);
        playground[row][col] = '*';
        printPlaygroundWithFrame(playground);
        *stage = 0;
        *first_time = FALSE;
    }
}

/*this function shows the position of bullet every six houses move*/
void positionOfBullet(int shooter, int X0, int Y0, int power_input, int angle, char playground[MAX_ROWS][MAX_COLS], int Px1, int Px2, int *health1, int *health2, int *last_health1, int *last_health2) {
    double power = 2.0 + 7.0 * pow((power_input/100.0), 1.5);
    double angle_radian;
    if (shooter == 1) {
        angle_radian = angle * PI / PI_DEGREE;
    }
    else {
        angle_radian = (PI_DEGREE - angle) * PI / PI_DEGREE;
    }
    double vx = power * cos(angle_radian);
    double vy = power * sin(angle_radian);
    double t = 0;
    int last_location_x = -1;
    int last_location_y = -1;
    int stage = 0;
    int first_time = TRUE;
    while (TRUE) {
        int Y0_in_the_playground = (MAX_ROWS - 1) - Y0;
        double x = vx * t + X0;
        double y = -0.5 * g * pow(t, 2) + vy * t + Y0_in_the_playground;
        int col = (int)round(x);
        int row = (MAX_ROWS - 1) - (int)round(y);
        if (bulletHitToRockOrWallOrGround(*health1, *health2, t, vx, vy, X0, Y0_in_the_playground, x, y, col, row, Px1, Px2, playground, last_health1, last_health2)) {
            break;
        }
        if (shooter == 1) {
            if (hitTank1(1, health1, health2, t, vx, vy, X0, Y0_in_the_playground, x, y, col, row, Px1, Px2, playground, last_health1, last_health2)) {
                break;
            }
            if (hitTank2(1, health1, health2, t, vx, vy, X0, Y0_in_the_playground, x, y, col, row, Px1, Px2, playground, last_health2, last_health1)) {
                break;
            }
        }
        else {
            if (hitTank1(2, health1, health2, t, vx, vy, X0, Y0_in_the_playground, x, y, col, row, Px1, Px2, playground, last_health1, last_health2)) {
                break;
            }
            if (hitTank2(2, health1, health2, t, vx, vy, X0, Y0_in_the_playground, x, y, col, row, Px1, Px2, playground, last_health2, last_health1)) {
                break;
            }
        }
        if (col != last_location_x || row != last_location_y) {
            stage++;
        }
        printPlaygroundEverySixHousesMove(playground, &stage, &first_time, Px1, Px2, row, col);
        last_location_x = col;
        last_location_y = row;
        t += DELTA_t;
    }
}