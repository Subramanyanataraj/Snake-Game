#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "menu.h"
#include "player.h"
#include <memory>



int main() {
  // Display the main menu and get the user's choice.
  Menu menu{};

  Menu::Entry entry = menu.ChoiceEntered();

  // Create a Player object using smart pointer for automatic memory management.

  std::unique_ptr<Player> player = std::make_unique<Player>();
  
  if(entry == Menu::Entry::kNewGame){
    system("clear");
    player->EnterName();
    // Start a new game: clear screen, get player name, and display new game menu.

    menu.NewGame();

    // Game configuration constants.
    int difficulty_level = menu.GetDifficultyLevel(); 
    constexpr std::size_t kFramesPerSecond{60};
    constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
    constexpr std::size_t kScreenWidth{640};
    constexpr std::size_t kScreenHeight{640};
    constexpr std::size_t kGridWidth{32};
    constexpr std::size_t kGridHeight{32};
   
  // Initialize renderer, controller, and game objects.
    Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
    Controller controller;
    Game game(kGridWidth, kGridHeight, difficulty_level);

  // Setup obstacles if hard difficulty is selected.
 
    if (difficulty_level == 2) { 
    game.SetupObstacles(difficulty_level, kGridWidth, kGridHeight);
    }
    game.Run(controller, renderer, kMsPerFrame);
    
  // Display final results after the game ends.

    std::cout << "Game has terminated successfully!\n";
    std::cout << "Score: " << game.GetScore() << "\n";
    std::cout << "Size: " << game.GetSize() << "\n";

    int score = game.GetScore();
    int size = game.GetSize();

    // Save game results to file.

    std::string path = std::string(SOURCE_DIR) + "/data/GameHistory.txt";
    player->SaveToFile(path, score, size);
    }else{
      // Handle other menu options (e.g., view history, exit).

      menu.GameOptions(entry);
    }

  return 0;
}