#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define W 21
#define H 21

char maze[H][W];

int dx[] = { 0, 0, -2, 2 };
int dy[] = { -2, 2, 0, 0 };

void shuffle(int* a, int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int t = a[i]; a[i] = a[j]; a[j] = t;
    }
}

void carve(int x, int y) {
    int dirs[4] = { 0,1,2,3 };
    shuffle(dirs, 4);

    for (int i = 0; i < 4; i++) {
        int d = dirs[i];
        int nx = x + dx[d], ny = y + dy[d];

        if (nx > 0 && nx < W - 1 && ny > 0 && ny < H - 1 && maze[ny][nx] == '#') {
            maze[y + dy[d] / 2][x + dx[d] / 2] = ' ';
            maze[ny][nx] = ' ';
            carve(nx, ny);
        }
    }
}

int main() {
    srand(time(NULL));

    for (int y = 0; y < H; y++)
        for (int x = 0; x < W; x++)
            maze[y][x] = '#';

    maze[1][1] = ' ';
    carve(1, 1);

    for (int y = 0; y < H; y++) {
        for (int x = 0; x < W; x++)
            putchar(maze[y][x]);
        putchar('\n');
    }

    return 0;
}