#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>

using namespace std;

const int H = 20;
const int W = 12;
int speed = 200;
char board[H][W] = {};

class Piece {
protected:
    char shape[4][4];
public:
    virtual void rotate() = 0; 
    char get(int i, int j) const { return shape[i][j]; }
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

class LPiece : public Piece {
public:
    LPiece() {
        char tmp[4][4] = {
            {' ',' ','L',' '},
            {'L','L','L',' '},
            {' ',' ',' ',' '},
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

class JPiece : public Piece {
public:
    JPiece() {
        char tmp[4][4] = {
            {'J',' ',' ',' '},
            {'J','J','J',' '},
            {' ',' ',' ',' '},
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

class SPiece : public Piece {
public:
    SPiece() {
        char tmp[4][4] = {
            {' ','S','S',' '},
            {'S','S',' ',' '},
            {' ',' ',' ',' '},
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

class ZPiece : public Piece {
public:
    ZPiece() {
        char tmp[4][4] = {
            {'Z','Z',' ',' '},
            {' ','Z','Z',' '},
            {' ',' ',' ',' '},
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

int x = 5, y = 0;
Piece* currentPiece = nullptr;

void gotoxy(int x, int y) {
    COORD c = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void initBoard() {
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (j == 0 || j == W - 1 || i == H - 1) board[i][j] = '#';
            else board[i][j] = ' ';
        }
    }
}

void boardDelBlock() {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (currentPiece->get(i, j) != ' ' && y + i < H)
                board[y + i][x + j] = ' ';
}

void block2Board() {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (currentPiece->get(i, j) != ' ')
                board[y + i][x + j] = currentPiece->get(i, j);
}

void draw() {
    gotoxy(0, 0);
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (board[i][j] == ' ') cout << "  ";
            else if (board[i][j] == '#') cout << "##";
            else cout << "[]";
        }
        cout << endl;
    }
}

bool canMove(int dx, int dy) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (currentPiece->get(i, j) != ' ') {
                int tx = x + j + dx;
                int ty = y + i + dy;
                if (tx < 1 || tx >= W - 1 || ty >= H - 1) return false;
                if (board[ty][tx] != ' ') return false;
            }
        }
    }
    return true;
}

void removeLine() {
    for (int i = H - 2; i > 0; i--) {
        bool full = true;
        for (int j = 1; j < W - 1; j++) if (board[i][j] == ' ') full = false;
        if (full) {
            for (int k = i; k > 1; k--)
                for (int j = 1; j < W - 1; j++) board[k][j] = board[k - 1][j];
            i++; 
            if (speed > 30) speed -= 20;
        }
    }
}

int main() {
    srand((unsigned int)time(0));
    initBoard();
    currentPiece = new TPiece(); 
    system("cls");
    while (true) {
        boardDelBlock();
        if (_kbhit()) {
            char c = _getch();
            if (c == 'a' && canMove(-1, 0)) x--;
            if (c == 'd' && canMove(1, 0)) x++;
            if (c == 'w') {
                currentPiece->rotate();
                if (!canMove(0, 0)) { 
                    currentPiece->rotate();
                    currentPiece->rotate();
                    currentPiece->rotate();
                }
            }
        }
        if (canMove(0, 1)) {
            y++;
        } else {
            block2Board();
            removeLine();
            x = 5; y = 0;
            delete currentPiece;
            currentPiece = new IPiece(); 
            if (!canMove(0, 0)) break; 
        }
        block2Board();
        draw();
        Sleep(speed);
    }
    delete currentPiece;
    return 0;
}
