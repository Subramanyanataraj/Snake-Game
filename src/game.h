#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "obstacle.h"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height,int difficulty_level);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;
  void SetupObstacles(int difficulty_level, int grid_width, int grid_height);
  bool IsObstacleCell(int x, int y) const;

 private:
  Snake snake;
  SDL_Point food;
  SDL_Point unknown_food;
  SDL_Point medicinal_food;
  std::vector<Obstacle> obstacles;

  Uint32 unknown_food_timer;
  bool unknown_food_active;
  Uint32 poison_start_time;


  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;
  bool is_poisoned; 

  int score{0};

  void PlaceFood();
  void PlaceSpecialFood(SDL_Point &food);

  void Update();
};

#endif