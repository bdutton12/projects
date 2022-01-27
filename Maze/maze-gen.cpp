#include "maze-gen.h"

// Define maze constructor taking in height,width, and
// filling array with 1s
Maze::Maze(int x, int y) {
    width = x;
    height = y;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            maze_arr[i][j] = 1;
        }
    }
}

// Define output as outputting each cell separated by " "
// New rows on new lines
std::ostream& operator<<(std::ostream& os, Maze& m) {
    for (int i = 0; i < m.height; i++) {
        for (int j = 0; j < m.width; j++) {
            os << m.maze_arr[i][j] << " ";
        }
        os << std::endl;
    }

    return os;
}

int main() {
    Maze m = Maze(20,20);

    std::cout << m;
    return 0;
}