#include "player.h"
#include "maze-gen.h"
#include <cctype>

// Define ASCII values for each key press needed
#define KEY_UP    72
#define KEY_LEFT  75
#define KEY_RIGHT 77
#define KEY_DOWN  80
#define ESC 27

// Global variables for whether first game and player char
char player_char = 'A';
bool first_game = true;

int main() {
    // Initialize maze
    system("color 08");
    Maze m = Maze(30,30);
    srand(time(0));

    m.GenerateMaze(1,1);

    // Initialize game if first game
    if (first_game) {
        std::string welcome_msg = "-------------------------\n"
                                "WELCOME TO MAZE GENERATOR\n"
                                "PLEASE ENTER A CHARACTER\n"
                                "TO REPRESENT YOUR PLAYER\n"
                                "-------------------------\n";
        std::cout << welcome_msg << std::endl;
        std::cout << "Character: ";
        std::cin >> player_char;
        first_game = false;
    }

    // Initialize player and place on maze
    Player p = Player(1, 1, player_char, &m);

    p.UpdatePlayer(-1);


    // While 'ESC' key not pressed, take in arrow key inputs
    // Also allow wasd
    // Update player accordingly
    bool not_quit = true;
    int c;
    while(not_quit)
    {
        switch(c = getch())
        {
            case 'W':
            case 'w':
            case KEY_UP:
                p.UpdatePlayer(0);
                break;
            case 'S':
            case 's':
            case KEY_DOWN:
                p.UpdatePlayer(2);
                break;
            case 'A':
            case 'a':
            case KEY_LEFT:
                p.UpdatePlayer(3);
                break;
            case 'D':
            case 'd':
            case KEY_RIGHT:
                p.UpdatePlayer(1);
                break;
            case ESC:
                not_quit = false;
            default:  // not arrow or esc
                break;
        }

        // If player won, end game and display message
        if (p.WinState()) {
            std::cout << std::endl << std::endl << std::endl;
            std::cout << "-----------------------------------" << std::endl;
            std::cout << "YOU WON | CONGRATULATIONS | YOU WON" << std::endl;
            std::cout << "-----------------------------------" << std::endl;
            not_quit = false;
            char p_again = 'N';

            // Ask to play again
            std::cout << std::endl << "Play again? (Y/N): ";
            std::cin >> p_again;
            if (std::tolower(p_again) == 'y') {
                system("cls");
                main();
            }
        }
    }

    return 0;
}