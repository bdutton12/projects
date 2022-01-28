#ifndef MAZEGEN
#define MAZEGEN

#include <iostream>
#include <vector>
#include <utility>
#include <conio.h>
#include <time.h>
#include <windows.h>

/*
Maze class contains:
4 Directions set to their numerical representation
Height of maze
Width of maze
Vector<Vector<Char>> containing each character of maze
*/
class Maze {
    private:
    //Initialize directions
    int N = 0;
    int E = 1;
    int S = 2;
    int W = 3;

    bool InBounds(int,int);

    friend class Player;

    public:
    //Initialize maze_arr to default size
    std::vector<std::vector<char>> maze_arr;
    
    //  Initialize height, width
    int height = 10;
    int width = 10;

    Maze(int, int);
    friend std::ostream& operator<<(std::ostream&, Maze&);
    void GenerateMaze(int, int);
};

#endif