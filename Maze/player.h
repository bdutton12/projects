#include "maze-gen.cpp"

class Player {
    private:
    std::pair<int,int> coords;
    char rep = 'U';
    Maze* maze;
    
    public:
    Player(int, int, Maze*);
    void UpdatePlayer(int);
    bool ValidMove(int, int);
};