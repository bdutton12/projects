#include "maze-gen.h"
#include <time.h>
#include <windows.h>

// Initialize output console
HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);

// Define maze constructor taking in height,width, and
// filling array with 1s
Maze::Maze(int x, int y) {
    width = x;
    height = y;
    maze_arr.resize(width, std::vector<char>(height, '#'));
}

// Define output as outputting each cell separated by " "
// New rows on new lines
// Start and finish and player given special color
std::ostream& operator<<(std::ostream& os, Maze& m) {
    for (int i = 0; i < m.width; i++) {
        for (int j = 0; j < m.height; j++) {
            switch(m.maze_arr[i][j]) {
                case '#':
                case ' ':
                    SetConsoleTextAttribute(hcon, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // dark gray
                    os << m.maze_arr[i][j] << " ";
                    break;
                case 'S':
                case 'F':
                    SetConsoleTextAttribute(hcon, FOREGROUND_GREEN); // green
                    os << m.maze_arr[i][j] << " ";
                    break;
                default:
                    SetConsoleTextAttribute(hcon, FOREGROUND_BLUE); // dark blue
                    os << m.maze_arr[i][j] << " ";
                    break;
            }
        }
        os << std::endl;
    }

    return os;
}

// Check if next coords to visit are in bounds
bool Maze::InBounds(int x, int y) {
    if (x > 0 && x < width-1) {
        if (y > 0 && y < height-1) {
            return true;
        }
    }
    return false;
}

// Recursively generate maze
void Maze::GenerateMaze(int x, int y) {
    //Set point currently at to empty
    maze_arr[y][x] = ' ';

    //Create array of 4 dir and shuffle
    int dirs[4];
    dirs[0] = N;
    dirs[1] = E;
    dirs[2] = S;
    dirs[3] = W;

    for (int i = 0; i < 4; i++) {
        int seed = rand() % 4;

        int temp = dirs[seed];
        dirs[seed] = dirs[i];
        dirs[i] = temp;
    }

    //For each direction, recursively travel until impossible
    int travelX, travelY = 0;
    for (int i : dirs) {
        switch(i) {
            case 0:
                if (InBounds(x,y-2)) {
                    if (maze_arr[y-2][x] != ' '  && maze_arr[y-1][x] != ' ') {
                        maze_arr[y-1][x] = ' ';
                        GenerateMaze(x,y-2);
                    }
                }
                break;
            case 1:
                if (InBounds(x+2,y)) {
                    if (maze_arr[y][x+2] != ' ' && maze_arr[y][x+1] != ' ') {
                        maze_arr[y][x+1] = ' ';
                        GenerateMaze(x+2,y);
                    }
                }
                break;
            case 2:
                if (InBounds(x,y+2)) {
                    if (maze_arr[y+2][x] != ' ' && maze_arr[y+1][x] != ' ') {
                        maze_arr[y+1][x] = ' ';
                        GenerateMaze(x,y+2);
                    }
                }
                break;
            case 3:
                if (InBounds(x-2,y)) {
                    if (maze_arr[y][x-2] != ' ' && maze_arr[y][x-1] != ' ') {
                        maze_arr[y][x-1] = ' ';
                        GenerateMaze(x-2,y);
                    }
                }
                break;
        }
    }
}