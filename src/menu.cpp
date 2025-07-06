#include "menu.h"
#include <cstdlib>     
#include <limits>      
#include <memory>


// Constructor: Displays the main menu options to the user.

Menu::Menu() {  
  std::cout << "======= SNAKE GAME MENU =======\n";
  std::cout << "1. Start New Game\n";
  std::cout << "2. Show Game History\n";
  std::cout << "3. View Top 10 High Scores\n";
  std::cout << "4. Exit\n";
  std::cout << "Choose an option: ";  
}


// Displays the difficulty selection menu and validates user input.

void Menu::NewGame(){

  std::cout << "======= CHOOSE DIFFICULTY LEVEL =======\n";
  std::cout << "1. Easy\n";
  std::cout << "2. Difficult\n";

  std::cout << "Choose an option: "; 

    while (true) {
        try {
            // Try to read input
            if (!(std::cin >> m_diffculty_level)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw std::runtime_error("Invalid input (not a number)");
            }
            if (m_diffculty_level < 1 || m_diffculty_level >2) {
                throw std::runtime_error("Invalid option (out of range)");
            }
            break;
        }
        catch (const std::exception& e) {
            std::cout << e.what() << ". Please try again: ";
        }
    }
}
// Handles menu options: shows game history, high scores, or exits the game.
void Menu::GameOptions(Entry entry) {
               std::unique_ptr<Player> player = std::make_unique<Player>();
                           std::string path = std::string(SOURCE_DIR) + "/data/GameHistory.txt";


    switch (entry) {
        case Entry::kHighScores: 
            system("clear");

            std::cout << "======= GAME HISTORY =======\n";

            player->PrintGameHistory(path, false);
            break;
        case Entry::kHistory: 
            system("clear");  
            std::cout << "======= TOP 10 HIGH SCORES =======\n";
            player->PrintGameHistory(path, true);
            break;
        case Entry::kQuit:
            system("clear");
            std::cout << "Exiting the game. Goodbye!\n";
            std::exit(0); 

            break;
        default:
            
            system("clear");
            std::cout << "Invalid option selected.\n";
            break;
    }
}

// Returns the selected difficulty level.

int Menu::GetDifficultyLevel() const {
    return m_diffculty_level;
}
// Prompts the user for a menu choice and validates the input.

Menu::Entry Menu::ChoiceEntered() {
    while (true) {
        try {
            if (!(std::cin >> m_choice)) {
                throw std::runtime_error("Invalid input (not a number)");
            }
            if (m_choice < 1 || m_choice > 4) {
                throw std::runtime_error("Invalid option (out of range)");
            }
            return static_cast<Entry>(m_choice);
        }
        catch (const std::exception& e) {
            std::cout << e.what() << ". Please try again: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}
// Destructor: Cleans up any resources.
Menu::~Menu() {}
