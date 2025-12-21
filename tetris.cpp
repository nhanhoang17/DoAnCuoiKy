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

Piece* currentPiece;
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
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (currentPiece->get(i, j) != ' ')
                board[y + i][x + j] = ' ';
}

void block2Board() {
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

void newPiece() {
    int r = rand() % 7;
    if (r == 0) currentPiece = new IPiece();
    if (r == 1) currentPiece = new OPiece();
    if (r == 2) currentPiece = new TPiece();
    if (r == 3) currentPiece = new LPiece();
    if (r == 4) currentPiece = new JPiece();
    if (r == 5) currentPiece = new SPiece();
    if (r == 6) currentPiece = new ZPiece();
    x = 5; y = 0;
}

int main() {
    srand(time(0));
    system("cls");
    initBoard();
    newPiece();

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
            delete currentPiece;
            newPiece();
        }

        block2Board();
        draw();
        Sleep(speed);
    }

    delete currentPiece;
    return 0;
}
