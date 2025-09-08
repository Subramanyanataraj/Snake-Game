#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <string>
#include <cstdlib> 
struct GameRecord {
    std::string name;
    int score;
    int size;
    std::string datetime;
};
class Player {
 public:
  Player();
  void EnterName();
  void SaveToFile(const std::string& filename,int &score, int &size) const;
  std::string GetName() const;
  void PrintGameHistory(const std::string& filename, bool topScoresOnly) const;
  void SetName(const std::string& n) { name = n; }

 private:
   std::string name;
};

#endif // PLAYER_HPP
