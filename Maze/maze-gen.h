#include <iostream>
#include <array>

class Maze {
    private:
    int height = 10;
    int width = 10;
    std::array<std::array<int, 10>, 10> maze_arr;

    public:
    Maze(int, int);
    friend std::ostream& operator<<(std::ostream&, Maze&);
};