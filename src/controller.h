#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"

class Controller {
 public:
  // Processes user input and window events, updating the running state and snake direction.
  void HandleInput(bool &running, Snake &snake) const;

 private:
 // Updates the snake's direction if the new direction is valid (not directly opposite).
  void ChangeDirection(Snake &snake, Snake::Direction input,
                       Snake::Direction opposite) const;
};

#endif