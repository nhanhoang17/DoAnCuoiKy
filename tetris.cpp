#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>

using namespace std;

#define H 20
#define W 15

int speed = 200;
char board[H][W];

class Piece {
protected:
    char shape[4][4];
public:
    virtual void rotate() = 0;
    char get(int i, int j) const { return shape[i][j]; }

    void rotateBack() {
        char tmp[4][4];
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                tmp[3 - j][i] = shape[i][j];
        memcpy(shape, tmp, sizeof(shape));
    }

    virtual ~Piece() {}
};

class IPiece : public Piece {
public:
    IPiece() {
        char tmp[4][4] = {
            {' ','I',' ',' '},
            {' ','I',' ',' '},
            {' ','I',' ',' '},
            {' ','I',' ',' '}
        };
        memcpy(shape, tmp, sizeof(shape));
    }
    void rotate() override {
        char tmp[4][4];
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                tmp[j][3 - i] = shape[i][j];
        memcpy(shape, tmp, sizeof(shape));
    }
};

class OPiece : public Piece {
public:
    OPiece() {
        char tmp[4][4] = {
            {' ',' ',' ',' '},
            {' ','O','O',' '},
            {' ','O','O',' '},
            {' ',' ',' ',' '}
        };
        memcpy(shape, tmp, sizeof(shape));
    }
    void rotate() override {}
};

class TPiece : public Piece {
public:
    TPiece() {
        char tmp[4][4] = {
            {' ',' ',' ',' '},
            {' ','T','T','T'},
            {' ',' ','T',' '},
            {' ',' ',' ',' '}
        };
        memcpy(shape, tmp, sizeof(shape));
    }
    void rotate() override {
        char tmp[4][4];
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                tmp[j][3 - i] = shape[i][j];
        memcpy(shape, tmp, sizeof(shape));
    }
};

Piece* currentPiece = NULL;
int x = 5, y = 0;

void gotoxy(int x, int y) {
    COORD c;
    c.X = (SHORT)x;
    c.Y = (SHORT)y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void initBoard() {
    for (int i = 0; i < H; i++)
        for (int j = 0; j < W; j++)
            if (i == H - 1 || j == 0 || j == W - 1)
                board[i][j] = '#';
            else
                board[i][j] = ' ';
}

void draw() {
    gotoxy(0, 0);
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (board[i][j] == '#') cout << (char)178 << (char)178;
            else if (board[i][j] == ' ') cout << "  ";
            else cout << "[]";
        }
        cout << endl;
    }
}

void boardDelBlock() {
    if (!currentPiece) return;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (currentPiece->get(i, j) != ' ')
                board[y + i][x + j] = ' ';
}

void block2Board() {
    if (!currentPiece) return;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (currentPiece->get(i, j) != ' ')
                board[y + i][x + j] = currentPiece->get(i, j);
}

bool canMove(int dx, int dy) {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (currentPiece->get(i, j) != ' ') {
                int tx = x + j + dx;
                int ty = y + i + dy;
                if (tx < 1 || tx >= W - 1 || ty >= H - 1) return false;
                if (board[ty][tx] != ' ') return false;
            }
    return true;
}

bool canRotate() {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (currentPiece->get(i, j) != ' ') {
                int tx = x + j;
                int ty = y + i;
                if (tx < 1 || tx >= W - 1 || ty >= H - 1) return false;
                if (board[ty][tx] != ' ') return false;
            }
    return true;
}

void removeLine() {
    for (int i = H - 2; i > 0; i--) {
        bool full = true;
        for (int j = 1; j < W - 1; j++)
            if (board[i][j] == ' ') { full = false; break; }

        if (full) {
            for (int ii = i; ii > 0; ii--)
                for (int j = 1; j < W - 1; j++)
                    board[ii][j] = board[ii - 1][j];
            i++;
        }
    }
}

int main() {
    srand(time(0));
    system("cls");
    initBoard();

    currentPiece = new TPiece();

    while (true) {
        boardDelBlock();

        if (kbhit()) {
            char c = getch();
            if (c == 'a' && canMove(-1, 0)) x--;
            if (c == 'd' && canMove(1, 0)) x++;
            if (c == 's' && canMove(0, 1)) y++;

            if (c == 'w') {
                currentPiece->rotate();
                if (!canRotate())
                    currentPiece->rotateBack();
            }

            if (c == 'q') break;
        }

        if (canMove(0, 1))
            y++;
        else {
            block2Board();
            removeLine();
            delete currentPiece;
            currentPiece = new TPiece();
            x = 5; y = 0;
        }

        block2Board();
        draw();
        Sleep(speed);
    }

    delete currentPiece;
    return 0;
}
