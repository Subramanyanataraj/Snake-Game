#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <vector>
#include "SDL.h"
#include "snake.h"
#include <vector>
#include <thread>
#include <mutex>
struct Obstacle {
    std::vector<SDL_Point> cells;

    bool IsCellOccupied(int x, int y, const SDL_Point& food, const SDL_Point& unknown_food, const SDL_Point& medicinal_food, const Snake& snake) const;
    void GenerateRandom(int grid_width, int grid_height, const SDL_Point& food, const SDL_Point& unknown_food, const SDL_Point& medicinal_food, const Snake& snake);
    bool Contains(int x, int y) const;
};
#endif
