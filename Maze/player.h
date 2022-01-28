#include "maze-gen.cpp"

/*
Player class contains:
coordinates of player
reference to maze object
char to represent player in maze
*/
class Player {
    private:
    std::pair<int,int> coords;
    char rep = 'U';
    Maze* maze;
    int moves = 0;
    
    public:
    Player(int, int, char, Maze*);
    void UpdatePlayer(int);
    bool ValidMove(int, int);
    bool WinState();
};