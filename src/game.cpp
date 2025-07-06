#include "game.h"
#include <iostream>
#include "SDL.h"
#include "menu.h"
#include <mutex>

// Game constructor: Initializes the snake, random number generators, food, and special food items.

Game::Game(std::size_t grid_width, std::size_t grid_height, int difficulty_level)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)),
      is_poisoned(false),
      unknown_food_timer(SDL_GetTicks()), 
      unknown_food_active(true) {         
    PlaceFood();
    PlaceSpecialFood(unknown_food);
    PlaceSpecialFood(medicinal_food);
}
// Generates a new obstacle and adds it to the obstacles vector in a thread-safe manner.
void GenerateObstacle(
    std::vector<Obstacle>& obstacles,
    std::mutex& mutex,
    int grid_width, int grid_height,
    const SDL_Point& food, const SDL_Point& unknown_food, const SDL_Point& medicinal_food,
    const Snake& snake
) {
    Obstacle o;
    o.GenerateRandom(grid_width, grid_height, food, unknown_food, medicinal_food, snake);
    std::lock_guard<std::mutex> lock(mutex);
    obstacles.push_back(o);
}

// Sets up obstacles based on difficulty level, using multithreading for concurrent generation.
void Game::SetupObstacles(int difficulty_level, int grid_width, int grid_height) {
    obstacles.clear();
    if (difficulty_level != 2) return; 

    std::vector<std::thread> threads;
    std::mutex obstacles_mutex;

    for (int i = 0; i < 2; ++i) { 
        threads.emplace_back(
            GenerateObstacle,
            std::ref(obstacles),
            std::ref(obstacles_mutex),
            grid_width, grid_height,
            std::ref(food),
            std::ref(unknown_food),
            std::ref(medicinal_food),
            std::ref(snake)
        );
    }

    for (auto& t : threads) {
        t.join();
    }
}

// Checks whether the given (x, y) cell contains an obstacle.
bool Game::IsObstacleCell(int x, int y) const {
    for (const auto& obstacle : obstacles) {
        if (obstacle.Contains(x, y)) {
            return true;
        }
    }
    return false;
}



// Main game loop: Handles input, updates game state, manages special food timing, and renders the scene.
void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    controller.HandleInput(running, snake);
    Update();
    Uint32 current_ticks = SDL_GetTicks();
    if (current_ticks - unknown_food_timer >= 5000) { 
    unknown_food_timer = current_ticks;
    unknown_food_active = !unknown_food_active;
    if (unknown_food_active) {
        PlaceSpecialFood(unknown_food); 
      }
    }
    renderer.Render(snake, food, unknown_food, 
                is_poisoned, medicinal_food, 
                unknown_food_active, obstacles);
    frame_end = SDL_GetTicks();

    frame_count++;
    frame_duration = frame_end - frame_start;

    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}
// Places regular food at a random, unoccupied cell on the grid.

void Game::PlaceFood() {
    int x, y;
    while (true) {
        x = random_w(engine);
        y = random_h(engine);
        if (!snake.SnakeCell(x, y) && !IsObstacleCell(x, y)) {
            food.x = x;
            food.y = y;
            return;
        }
    }
}

// Places a special food item at a random, valid cell, avoiding overlap with other items or obstacles.

void Game::PlaceSpecialFood(SDL_Point &food) {
    int x, y;
    while (true) {
        x = random_w(engine);
        y = random_h(engine);
        if (!snake.SnakeCell(x, y) &&
            (x != this->food.x || y != this->food.y) &&
            (x != unknown_food.x || y != unknown_food.y) &&
            (x != medicinal_food.x || y != medicinal_food.y) &&
            !IsObstacleCell(x, y)) {
            food.x = x;
            food.y = y;
            return;
        }
    }
}


// Updates the game state: moves the snake, checks for food/special food/obstacle collisions, and handles poisoning logic.
void Game::Update() {
  if (!snake.alive) return;

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  if (food.x == new_x && food.y == new_y) {
    score++;
    PlaceFood();
    snake.GrowBody();
    snake.speed += 0.02;
  }

  

  if (unknown_food_active) {
    if (unknown_food.x == new_x && unknown_food.y == new_y) {
        if (std::rand() % 2 == 0) { 
            is_poisoned = true;
            poison_start_time = SDL_GetTicks(); 

            unknown_food_active = false; 
            unknown_food_timer = SDL_GetTicks(); 
        } else {
            score += 2;
            snake.GrowBody(2);
            unknown_food_active = false; 
            unknown_food_timer = SDL_GetTicks(); 
        }
    }


  }
  if (is_poisoned) {
    Uint32 current_time = SDL_GetTicks();
    if (current_time - poison_start_time >= 10000) { // 10000 ms = 10 seconds
        snake.alive = false;
        
    }
}


    if (is_poisoned && medicinal_food.x == new_x && medicinal_food.y == new_y) {
        is_poisoned = false;
        PlaceSpecialFood(medicinal_food);
    }

    if (!snake.alive) return;



for (const auto& obstacle : obstacles)
    if (obstacle.Contains(new_x, new_y))
        snake.alive = false;


}
// Returns the current score.
int Game::GetScore() const { return score; }

// Returns the current size of the snake.
int Game::GetSize() const { return snake.size; }