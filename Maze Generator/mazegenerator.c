#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Width and height of the maze as macro definitions
// Note that these must be odd numbers to ensure a consistent structure where walls and paths alternate
#define W 21
#define H 21

// 2D array to store the maze as characters.
char maze[H][W];

// Direction vectors
// 2 in order to leave walls between paths
int dx[] = { 0, 0, -2, 2 }; // left/right 
int dy[] = { -2, 2, 0, 0 }; // up/down

// Function to shuffle the array
// Uses the Fisher-Yates shuffle
void shuffle(int* a, int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1); // random index
        int t = a[i]; a[i] = a[j]; a[j] = t; // swap elements
    }
}
// Function that recursively 'carves' paths in the maze
// Terminates when no path can be made from any direction at any position
void carve(int x, int y) {
    int dirs[4] = { 0,1,2,3 }; // Array of directions (0,1,2,3 represent the 4 possible directions)
    shuffle(dirs, 4); // Shuffle the directions each time this function is called so the generation is random

	// Try each direction
    for (int i = 0; i < 4; i++) {
        int d = dirs[i];
        int nx = x + dx[d], ny = y + dy[d]; // Calculate new position 2 steps away
		// Check bounds of new position
        if (nx > 0 && nx < W - 1 && ny > 0 && ny < H - 1 && maze[ny][nx] == '#') {
            maze[y + dy[d] / 2][x + dx[d] / 2] = ' '; // Remove wall between the current and new position
            maze[ny][nx] = ' '; // Mark new position as a path
            carve(nx, ny); // Recursively carve from new position
        }
    }
}

int main() {
    srand(time(NULL)); // Set random seed based on system time

	// Set up maze with walls
    for (int y = 0; y < H; y++)
        for (int x = 0; x < W; x++)
            maze[y][x] = '#';
	// Set starting point and begin carving
    maze[1][1] = ' ';
    carve(1, 1);

	// Output final maze.
    for (int y = 0; y < H; y++) {
        for (int x = 0; x < W; x++)
            putchar(maze[y][x]);
        putchar('\n');
    }

    return 0;
}