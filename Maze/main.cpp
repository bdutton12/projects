#include "player.h"
#include "maze-gen.h"
#include <cctype>
#include <chrono>
#include <thread>
#include <cmath>

// Define ASCII values for each key press needed
#define KEY_UP    72
#define KEY_LEFT  75
#define KEY_RIGHT 77
#define KEY_DOWN  80
#define ESC 27

// Global variables for whether first game and player char
char player_char = 'A';
bool first_game = true;

// Initialize FPS and frame values
const int FPS = 30;
std::vector<char> frame;
short cursor = 0;

// Get first buffer
auto buffer_one = GetStdHandle(STD_OUTPUT_HANDLE);

// Initialize second buffer
auto buffer_two = CreateConsoleScreenBuffer(
                GENERIC_READ | GENERIC_WRITE,
                FILE_SHARE_WRITE | FILE_SHARE_READ,
                nullptr,
                CONSOLE_TEXTMODE_BUFFER,
                nullptr);

// Initialize switchable buffer
HANDLE back_buffer = buffer_two;
bool buffer_switch = true;

// Get size of current screen
COORD GetScreenSize()
{
    CONSOLE_SCREEN_BUFFER_INFO buffer_info;
    GetConsoleScreenBufferInfo(buffer_one, &buffer_info);
    const auto new_screen_width = buffer_info.srWindow.Right - buffer_info.srWindow.Left + 1;
    const auto new_screen_height = buffer_info.srWindow.Bottom - buffer_info.srWindow.Top + 1;

    return COORD{static_cast<short>(new_screen_width), static_cast<short>(new_screen_height)};
}

// Sets current background buffer as active
void SwapBuffers()
{
    WriteConsole(back_buffer, &frame.front(), static_cast<short>(frame.size()), nullptr, nullptr);
    SetConsoleActiveScreenBuffer(back_buffer);
    back_buffer = buffer_switch ? buffer_one : buffer_two;
    buffer_switch = !buffer_switch;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000 / FPS));
}

// Draw the next frame before displaying
void DrawFrame(COORD screen_size, Maze* maze)
{
    // Iterate through screen
    for (auto i = 0; i < screen_size.Y; i++)
    {
        int characters = 0;
        for (auto j = 0; j < screen_size.X; j++) {
            // Write character to frame data
            if (i < maze->width && j < maze->height) {
                frame[i * screen_size.X + j+characters] = maze->maze_arr[i][j];
                frame[i * screen_size.X + j + characters+1] = ' ';
                characters++;
            }
            else {
                frame[i * screen_size.X + j + characters] = ' ';
            }
        }
    }

    cursor++;
    if (cursor >= screen_size.Y)
        cursor = 0;
}

int main() {
    // Initialize maze
    system("color 08");
    Maze m = Maze(30,30);
    srand(time(0));

    m.GenerateMaze(1,1);

    /*
    // Initialize screen data
    const auto screen_size = GetScreenSize();
    SetConsoleScreenBufferSize(buffer_one, screen_size);
    SetConsoleScreenBufferSize(buffer_two, screen_size);
    frame.resize(screen_size.X * screen_size.Y); // Doubled to make place for spaces

    // Initialize console text colors
    SetConsoleTextAttribute(buffer_one, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    SetConsoleTextAttribute(buffer_two, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

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

    // Color coded maze before any player input
    std::cout << m;

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
                DrawFrame(screen_size, &m);
                SwapBuffers();
                break;
            case 'S':
            case 's':
            case KEY_DOWN:
                p.UpdatePlayer(2);
                DrawFrame(screen_size, &m);
                SwapBuffers();
                break;
            case 'A':
            case 'a':
            case KEY_LEFT:
                p.UpdatePlayer(3);
                DrawFrame(screen_size, &m);
                SwapBuffers();
                break;
            case 'D':
            case 'd':
            case KEY_RIGHT:
                p.UpdatePlayer(1);
                DrawFrame(screen_size, &m);
                SwapBuffers();
                break;
            case ESC:
                not_quit = false;
            default:  // not arrow or esc
                DrawFrame(screen_size, &m);
                SwapBuffers();
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
    */
    return 0;
}