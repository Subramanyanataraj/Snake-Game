#include "obstacle.h"
#include <cstdlib>
#include <ctime>
#include "snake.h"

// Checks if the specified cell (x, y) is occupied by food, special food, or the snake.
bool Obstacle::IsCellOccupied(int x, int y, const SDL_Point& food, const SDL_Point& unknown_food, const SDL_Point& medicinal_food, const Snake& snake) const {
    if ((x == food.x && y == food.y) ||
        (x == unknown_food.x && y == unknown_food.y) ||
        (x == medicinal_food.x && y == medicinal_food.y))
        return true;
    if (snake.SnakeCell(x, y))
        return true;
    return false;
}

// Generates a random 4x4 obstacle block at a valid position, avoiding food and the snake.
void Obstacle::GenerateRandom(int grid_width, int grid_height, const SDL_Point& food, const SDL_Point& unknown_food, const SDL_Point& medicinal_food, const Snake& snake) {
    cells.clear();
    int x, y;
    bool valid;
    do {
        valid = true;
        x = std::rand() % (grid_width - 3); // -3 to fit 4x4 block
        y = std::rand() % (grid_height - 3);
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                if (IsCellOccupied(x + i, y + j, food, unknown_food, medicinal_food, snake)) {
                    valid = false;
                    break;
                }
            }
            if (!valid) break;
        }
    } while (!valid);
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            cells.push_back({x + i, y + j});
}
// Checks if the obstacle contains the specified cell (x, y).

bool Obstacle::Contains(int x, int y) const {
    for (const auto& cell : cells)
        if (cell.x == x && cell.y == y)
            return true;
    return false;
}
