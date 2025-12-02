#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>
#include <graphics.h>
using namespace std;

#define CELL_SIZE 30
#define H 20
#define W 15

const int SCREEN_WIDTH  = W * CELL_SIZE; 
const int SCREEN_HEIGHT = H * CELL_SIZE;

#define COLOR_EMPTY  BLACK
#define COLOR_BORDER DARKGRAY

char board[H][W] = {};
char blocks[][4][4] = {
        {{' ','I',' ',' '},
         {' ','I',' ',' '},
         {' ','I',' ',' '},
         {' ','I',' ',' '}},
        {{' ','I',' ',' '},
         {' ','I',' ',' '},
         {' ','I',' ',' '},
         {' ','I',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','O','O',' '},
         {' ','O','O',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','O','O',' '},
         {' ','O','O',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','O','O',' '},
         {' ','O','O',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','O','O',' '},
         {' ','O','O',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','O','O',' '},
         {' ','O','O',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','O','O',' '},
         {' ','O','O',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','O','O',' '},
         {' ','O','O',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {'I','I','I','I'},
         {' ',' ',' ',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','O','O',' '},
         {' ','O','O',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','T',' ',' '},
         {'T','T','T',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','S','S',' '},
         {'S','S',' ',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {'Z','Z',' ',' '},
         {' ','Z','Z',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {'J',' ',' ',' '},
         {'J','J','J',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ',' ','L',' '},
         {'L','L','L',' '},
         {' ',' ',' ',' '}}
};

int x = 4, y = 0, b = 1;

void gotoxy(int x, int y) {
    COORD c = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void boardDelBlock() {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (blocks[b][i][j] != ' ' && y + j < H)
                board[y + i][x + j] = ' ';
}
void block2Board() {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (blocks[b][i][j] != ' ')
                board[y + i][x + j] = blocks[b][i][j];
}
void initBoard() {
    for (int i = 0; i < H; i++)
        for (int j = 0; j < W; j++)
            if ((i == H - 1) || (j == 0) || (j == W - 1)) board[i][j] = '#';
            else board[i][j] = ' ';
}

void draw() {
    cleardevice(); 

    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (board[i][j] == ' ') continue;

            int x_pixel = j * CELL_SIZE;
            int y_pixel = i * CELL_SIZE;

            int color = WHITE; 
            switch (board[i][j]) {
                case '#': color = LIGHTGRAY; break;
                case 'I': color = CYAN; break;
                case 'O': color = YELLOW; break;
                case 'T': color = MAGENTA; break;
                case 'S': color = GREEN; break;
                case 'Z': color = RED; break;
                case 'J': color = BLUE; break;
                case 'L': color = BROWN; break;
            }

            setfillstyle(SOLID_FILL, color);
            bar(x_pixel, y_pixel, x_pixel + CELL_SIZE, y_pixel + CELL_SIZE); 

            setcolor(BLACK);
            rectangle(x_pixel, y_pixel, x_pixel + CELL_SIZE, y_pixel + CELL_SIZE);
        }
    }
}

bool canMove(int dx, int dy) {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (blocks[b][i][j] != ' ') {
                int tx = x + j + dx;
                int ty = y + i + dy;
                if (tx < 1 || tx >= W - 1 || ty >= H - 1) return false;
                if (board[ty][tx] != ' ') return false;
            }
    return true;
}

void removeLine() {
    int j;
    for (int i = H - 2; i > 0; i--) {
        for (j = 0; j < W - 1; j++)
            if (board[i][j] == ' ') break;
        if (j == W - 1) {
            for (int ii = i; ii > 0; ii--)
                for (int j = 0; j < W - 1; j++) board[ii][j] = board[ii - 1][j];
            i++;
            draw();
            delay(200);
        }
    }
}

int main()
{
    srand(time(0));
    b = rand() % 7;
    
    initwindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Tetris Game - SV3 Graphics");
    
    initBoard();
    while (1) {
        boardDelBlock();
        if (kbhit()) {
            char c = getch();
            if (c == 'a' && canMove(-1, 0)) x--;
            if (c == 'd' && canMove(1, 0)) x++;
            if (c == 'x' && canMove(0, 1))  y++;
            if (c == 'q') break;
        }
        
        if (canMove(0, 1)) {
            y++;
        } else {
            block2Board();
            removeLine();
            x = 5; y = 0; b = rand() % 7;
            
            if (!canMove(0, 0)) {
                settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
                outtextxy(W * CELL_SIZE / 2 - 100, H * CELL_SIZE / 2 - 20, "GAME OVER");
                getch();
                break;
            }
        }
        
        block2Board();
        draw();
        delay(200);
    }
    
    closegraph();
    return 0;
}
