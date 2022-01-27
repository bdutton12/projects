#include "player.h"

//Initialize player
Player::Player(int x, int y, Maze* m) {
    coords = std::make_pair(x,y);
    UpdatePlayer(-1);
    maze = m;
}

bool Player::ValidMove(int x, int y) {
    if (maze->maze_arr[y][x] != '#') {
        return true;
    }

    return false;
}

// Reset past pos to empty and update new pos to player character
// Do nothing if move would hit wall or out of bounds
void Player::UpdatePlayer(int dir) {
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
}