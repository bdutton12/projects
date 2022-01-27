#include <iostream>
#include <vector>
#include <utility>
#include <conio.h>

class Maze {
    private:
    //Initialize directions
    int N = 0;
    int E = 1;
    int S = 2;
    int W = 3;

    //Initialize height,width and maze_arr to default size
    int height = 10;
    int width = 10;
    std::vector<std::vector<char>> maze_arr;

    bool InBounds(int,int);

    friend class Player;

    public:
    Maze(int, int);
    friend std::ostream& operator<<(std::ostream&, Maze&);
    void GenerateMaze(int, int);
};