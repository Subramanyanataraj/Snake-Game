#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "snake.h"
#include "obstacle.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();
void Render(
    Snake const snake,
    SDL_Point const &food,
    SDL_Point const &unknown_food,
    bool is_poisoned,
    SDL_Point const &medicinal_food,
    bool unknown_food_active,
    const std::vector<Obstacle>& obstacles // <-- Add this
);
  void UpdateWindowTitle(int score, int fps);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif