#ifndef _MENU_H_
#define _MENU_H_

#include <iostream>   // For std::cout, std::cin, etc.
#include <string>     // For std::string
#include "player.h"   // For Player class

class Menu {
public:
    Menu();        
    ~Menu();        

  
    void NewGame(); 
    
    Player player;

    enum Entry {
        kNewGame = 1,     
        kHighScores = 2, 
        kHistory = 3,  
        kQuit = 4         
    };

    enum Difficulty {
        kLevelOne = 1,    
        kLevelTwo = 2,    
        kLevelThree = 3  
    };

    Entry ChoiceEntered();

    void GameOptions(Entry entry);

    int GetDifficultyLevel() const;

private:
    int m_choice;           
    int m_diffculty_level;  
};

#endif // _MENU_H_
