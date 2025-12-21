#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>

using namespace std;

#define H 20
#define W 15
int speed = 200;
char board[H][W] = {};


class Piece {
protected:
    char shape[4][4];
public:
    virtual void rotate() = 0;   
    char get(int i, int j) const {
        return shape[i][j];
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
    void rotate() override { 
    }
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
            {'L',' ',' ',' '},
            {'L',' ',' ',' '},
            {'L','L',' ',' '},
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
            {' ',' ','J',' '},
            {' ',' ','J',' '},
            {' ','J','J',' '},
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


Piece* currentPiece = NULL;
int x = 5, y = 0;

void gotoxy(int x, int y) {
    COORD c;
    c.X = (SHORT)x;
    c.Y = (SHORT)y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void boardDelBlock() {
    if (currentPiece == NULL) return;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (currentPiece->get(i, j) != ' ')
                board[y + i][x + j] = ' ';
}

void block2Board() {
    if (currentPiece == NULL) return;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (currentPiece->get(i, j) != ' ')
                board[y + i][x + j] = currentPiece->get(i, j);
}

void initBoard() {
    for (int i = 0; i < H; i++)
        for (int j = 0; j < W; j++)
            if ((i == H - 1) || (j == 0) || (j == W - 1)) 
                board[i][j] = '#';
            else 
                board[i][j] = ' ';
}

void draw() {
    gotoxy(0, 0);
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (board[i][j] == '#') 
                cout << (char)178 << (char)178;
            else if (board[i][j] == ' ') 
                cout << "  ";
            else 
                cout << "[]";
        }
        cout << endl;
    }
}

bool canMove(int dx, int dy) {
    if (currentPiece == NULL) return false;
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

void removeLine() {
    int j;
    bool removed = false;
    for (int i = H - 2; i > 0; i--) {
        for (j = 1; j < W - 1; j++)
            if (board[i][j] == ' ') break;
        if (j == W - 1) {
            removed = true;
            for (int ii = i; ii > 0; ii--)
                for (int k = 1; k < W - 1; k++)
                    board[ii][k] = board[ii - 1][k];
            i++;
        }
    }
    if (removed && speed > 30) speed -= 10;
}

int main() {
    srand(time(0));
    system("cls");
    initBoard();

    // Khởi tạo quân cờ đầu tiên bằng Class con cụ thể
    currentPiece = new IPiece(); 

    while (true) {
        boardDelBlock();
        if (kbhit()) {
            char c = getch();
            if (c == 'a' && canMove(-1, 0)) x--;
            if (c == 'd' && canMove(1, 0)) x++;
            if (c == 's' && canMove(0, 1)) y++;
            if (c == 'w') {
                currentPiece->rotate();
                if (!canMove(0, 0))
            }
            if (c == 'q') break;
        }
        if (canMove(0, 1)) {
            y++;
        } else {
            block2Board();
            removeLine();
            delete currentPiece;
            currentPiece = new TPiece(); 
            x = 5; 
            y = 0;
            if (!canMove(0, 0)) break;
        }
        block2Board();
        draw();
        Sleep(speed);
    }
    delete currentPiece;
    return 0;
}
