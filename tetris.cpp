#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>
using namespace std;
#define H 20
#define W 15
int speed = 200;
int score = 0;
int highScore = 0;
int lines = 0;
time_t startTime;


char board[H][W] = {};
class Piece {
protected:
    char shape[4][4];
public:
    virtual void rotate() = 0;   // đa hình
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
    void rotate() override { // O không xoay
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
void initBoard() {
    for (int i = 0; i < H; i++)
        for (int j = 0; j < W; j++)
            if ((i == H - 1) || (j == 0) || (j == W - 1)) board[i][j] = '#';
            else board[i][j] = ' ';
}
void draw() {
    gotoxy(0, 0);
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            gotoxy(j * 2, i);
                if (board[i][j] == '#') {
                cout << (char)178 << (char)178;
            }
            else if (board[i][j] == ' ') {
                cout << "  ";
            }
            else {
                cout << "[]";
            }
        }
    }
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

void removeLine()
{
    int j;
    bool removed = false;  // Kiểm tra có xóa dòng hay không

    for (int i = H-2; i > 0 ; i-- )
    {
        for (j = 0; j < W-1 ; j++)
            if (board[i][j] == ' ') break;
        if (j == W-1)
        {
            removed = true;

            for (int ii = i; ii >0 ; ii-- )
                for (int j = 0; j < W-1 ; j++ )
                    board[ii][j] = board[ii-1][j];

            i++;
            draw();
            Sleep(200);
        }
    }

    // Tăng tốc nếu có xóa dòng
    if (removed)
    {
        if (speed > 30) speed -= 20;
    }
}

Piece* randomPiece() {
    int r = rand() % 7;
    switch (r) {
    case 0: return new IPiece();
    case 1: return new OPiece();
    case 2: return new TPiece();
    case 3: return new LPiece();
    case 4: return new JPiece();
    case 5: return new SPiece();
    case 6: return new ZPiece();
    }
    return nullptr;
}

// Hàm drawInfo() để hiển thị bảng thông tin.
void drawInfo()
{
    int xInfo = W * 2 + 4;
    gotoxy(xInfo, 2);
    cout << "High Score: " << highScore;
    gotoxy(xInfo, 4);
    cout << "Score:      " << score;
    gotoxy(xInfo, 6);
    cout << "Lines:      " << lines;

     // Tính thời gian đã chơi
    int t = (int)difftime(time(0), startTime);
    int min = t / 60;
    int sec = t % 60;

    gotoxy(xInfo, 8);
    cout << "Time:       " << min << ":" << (sec < 10 ? "0" : "") << sec;

}

// Hàm vẽ khung bao quanh bảng thông tin
void drawInfoFrame()
{
    int x = W * 2 + 2;
    int y = 1;
    int width = 22;
    int height = 12;

    // góc
    gotoxy(x, y);               cout << (char)218;
    gotoxy(x + width, y);       cout << (char)191;
    gotoxy(x, y + height);      cout << (char)192;
    gotoxy(x + width, y + height); cout << (char)217;

    // ngang
    for (int i = 1; i < width; i++) {
        gotoxy(x + i, y);          cout << (char)196;
        gotoxy(x + i, y + height); cout << (char)196;
    }

}

int main()
{
    srand(time(0));
    system("cls");
    initBoard();
    startTime = time(0);

    currentPiece = randomPiece();

    while (1) {
        boardDelBlock();
        if (kbhit()) {
            char c = getch();
            if (c == 'a' && canMove(-1, 0)) x--;
            if (c == 'd' && canMove(1, 0)) x++;
            if (c == 'x')
            {
                while (canMove(0, 1)) y++;
            }
            if (c == 'w') currentPiece->rotate();
            if (c == 's')
            {
                if (canMove(0, 1)) y++;
            }
            if (c == 'q') break;
        }

        if (canMove(0, 1)) y++;
        else {
            block2Board();
            removeLine();

            delete currentPiece;
            currentPiece = randomPiece();

            x = 5; y = 0;

            if (!canMove(0,0)) break;
        }
        block2Board();
        draw();
        drawInfo();
        Sleep(speed);
    }

    delete currentPiece;
    return 0;
}
