#include "player.h"

// Initialize player with coords, char, and maze
Player::Player(int x, int y, char c, Maze* m) {
    coords = std::make_pair(x,y);
    rep = c;
    maze = m;
}

// Check if attempted move will hit wall
bool Player::ValidMove(int x, int y) {
    if (maze->maze_arr[y][x] != '#') {
        return true;
    }

    return false;
}

// Update player coords and re-display maze
void Player::UpdatePlayer(int dir) {
    // Reset past pos to empty and update new pos to player character
    // Do nothing if move would hit wall or out of bounds
    switch(dir) {
        case 0: // North
            if (ValidMove(coords.first, coords.second-1)) {
                maze->maze_arr[coords.second][coords.first] = ' ';

                coords.second -= 1;
                maze->maze_arr[coords.second][coords.first] = rep;
            }
            break;

        case 1: // East
            if (ValidMove(coords.first+1, coords.second)) {
                maze->maze_arr[coords.second][coords.first] = ' ';

                coords.first += 1;                
                maze->maze_arr[coords.second][coords.first] = rep;
            }
            break;

        case 2: // South
            if (ValidMove(coords.first, coords.second+1)) {
                maze->maze_arr[coords.second][coords.first] = ' ';

                coords.second += 1;
                maze->maze_arr[coords.second][coords.first] = rep;
            }
            break;

        case 3: // West
            if (ValidMove(coords.first-1, coords.second)) {
                maze->maze_arr[coords.second][coords.first] = ' ';

                coords.first -= 1;
                maze->maze_arr[coords.second][coords.first] = rep;
            }
            break;

        default: // Stay in same place if not a valid dir
            maze->maze_arr[coords.second][coords.first] = rep;
            break;
    }

    // Ensure start and finish labels exist and clear screen then display maze
    if (maze->maze_arr[1][1] != 'S' && (coords.first != 1 || coords.second != 1)) {
        maze->maze_arr[1][1] = 'S';
    }
    if (maze->maze_arr[maze->height-3][maze->width-3] != 'F' && (coords.first != maze->width-3 || coords.second != maze->height-3)) {
        maze->maze_arr[maze->height-3][maze->width-3] = 'F';
    }

    system("cls");
    std::cout << *maze;
}

// Check if player is at finish point
bool Player::WinState() {
    if (coords.first == maze->height - 3) {
        if (coords.second == maze->width - 3) {
            return true;
        }
    }

    return false;
}