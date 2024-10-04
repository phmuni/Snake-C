#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define H 20
#define W 20
#define MS 16000
#define MLen 100

int out = 0;

struct Player {
    int x;
    int y;
    char dir;
} head;

struct Body {
    int x;
    int y;
} body[MLen];
int bodyLen = 0;

struct Item {
    int x;
    int y;
} apple;

void clearTerminal() { printf("\033[H"); }

void renderMap() {
    usleep(MS * 8);
    clearTerminal();

    char map[H][W];

    printf("Score: %d\n", bodyLen);
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            map[i][j] = '.';
        }
    }

    map[head.y][head.x] = 'O';
    map[apple.y][apple.x] = 'X';

    if (head.y == apple.y && head.x == apple.x) {
        bodyLen++;
        apple.x = rand() % W;
        apple.y = rand() % H;
    }

    for (int i = 0; i < bodyLen; i++) {
        map[body[i].y][body[i].x] = 'o';

        if (body[i].x == head.x && body[i].y == head.y) {
            out = 1;
        } else if (bodyLen == MLen) {
            out = 2;
        }
    }

    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            printf("%c ", map[i][j]);
        }
        printf("\n");
    }
}

void checkKey(char input) {
    switch (input) {
        case 'w':
            if (head.dir != 's') head.dir = 'w';
            break;
        case 's':
            if (head.dir != 'w') head.dir = 's';
            break;
        case 'a':
            if (head.dir != 'd') head.dir = 'a';
            break;
        case 'd':
            if (head.dir != 'a') head.dir = 'd';
            break;
    }
}

void updateMov() {
    for (int i = bodyLen; i >= 0; i--) {
        if (i == 0) {
            body[0].x = head.x;
            body[0].y = head.y;
        } else {
            body[i] = body[i - 1];
        }
    }

    switch (head.dir) {
        case 'w':
            head.y--;
            if (head.y < 0) head.y = H - 1;
            break;
        case 's':
            head.y++;
            if (head.y > H - 1) head.y = 0;
            break;
        case 'a':
            head.x--;
            if (head.x < 0) head.x = W - 1;
            break;
        case 'd':
            head.x++;
            if (head.x > W - 1) head.x = 0;
            break;
    }
}

int main() {
    system("cls");
    system("mode con: cols=40 lines=22");
    srand(time(NULL));

    apple.x = rand() % W;
    apple.y = rand() % H;

    head.x = 10;
    head.y = 10;
    head.dir = 'w';

    while (1) {
        if (_kbhit()) {
            char input = _getch();
            if (input == 27) break;
            checkKey(input);
        }

        updateMov();
        renderMap();

        if (out == 1) {
            system("cls");
            printf("You Lost!\n");
            system("pause");
            return 0;

        } else if (out == 2) {
            system("cls");
            printf("You Win!\n");
            system("pause");
            return 0;
        }
    }

    return 0;
}
