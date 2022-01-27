#include "player.cpp"

#define KEY_UP    72
#define KEY_LEFT  75
#define KEY_RIGHT 77
#define KEY_DOWN  80
#define ESC 27

int main() {
    Maze m = Maze(30,30);
    srand(time(0));

    m.GenerateMaze(1,1);

    std::cout << m;

    Player p = Player(1, 1, &m);

    std::cout << "Player made" << std::endl;

    bool not_quit = true;
    int c,ex;
    
    while(true)
    {
        c = getch();
        switch(ex = getch())
        {
            case KEY_UP     /* H */:
                p.UpdatePlayer(0);
                break;
            case KEY_DOWN   /* K */:
                p.UpdatePlayer(1);
                break;
            case KEY_LEFT   /* M */:
                p.UpdatePlayer(2);
                break;
            case KEY_RIGHT: /* P */
                p.UpdatePlayer(3);
                break;
            case ESC:
                not_quit = false;
            default:  // not arrow
                break;
        }
    }

    return 0;
}