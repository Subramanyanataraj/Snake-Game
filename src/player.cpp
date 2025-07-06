#include "player.h"
#include <iostream>
#include <fstream>
#include <sstream>    

#include <experimental/filesystem>
#include <chrono>
#include <iomanip>
#include <algorithm>
namespace fs = std::experimental::filesystem;

// Constructor: Initializes a Player object.

Player::Player() = default;

void Player::EnterName() {
  std::cout << "======= Enter Player's Name =======\n";
  std::cin>> name;
  system("clear");
}

// Prompts the user to enter their name.
void Player::SaveToFile(const std::string& filename, int &score, int &size) const {
  fs::path file_path = filename;
  auto parent = file_path.parent_path();
  if (!parent.empty()) {
    fs::create_directories(parent);
  }

  std::ofstream ofs(file_path, std::ios::app);
  if (!ofs) {
    std::cerr << "Error: Could not open file for writing.\n";
    return;
  }

 

  // Get current date and time as string
  auto now = std::chrono::system_clock::now();
  std::time_t now_c = std::chrono::system_clock::to_time_t(now);
  ofs << name << ',' << score << ',' << size << ','
      << std::put_time(std::localtime(&now_c), "%Y-%m-%d %H:%M:%S")
      << '\n';
  ofs.close();
}




// Reads and prints the game history from a file; shows all records or top 10 high scores based on the flag.
void Player::PrintGameHistory(const std::string& filename, bool topScoresOnly) const {
    fs::path file_path = filename;
    std::ifstream ifs(file_path);
    if (!ifs) {
        std::cerr << "Error: Could not open file for reading: " << file_path << "\n";
        return;
    }

    // Read and parse all records
    std::vector<GameRecord> records;
    std::string line;
    while (std::getline(ifs, line)) {
        std::istringstream iss(line);
        std::string name, score_str, size_str, datetime;
        if (std::getline(iss, name, ',') &&
            std::getline(iss, score_str, ',') &&
            std::getline(iss, size_str, ',') &&
            std::getline(iss, datetime)) {
            try {
                int score = std::stoi(score_str);
                int size = std::stoi(size_str);
                records.push_back({name, score, size, datetime});
            } catch (...) {
                // Ignore malformed lines
            }
        }
    }
    ifs.close();

    // Sort by score (highest first) if topScoresOnly is true
    if (topScoresOnly) {
        std::sort(records.begin(), records.end(),
            [](const GameRecord& a, const GameRecord& b) {
                return a.score > b.score; // Highest first
            });
    }

    // Print table header
    std::cout << std::left;
    if (topScoresOnly) {
        std::cout << std::setw(6) << "Rank";
    }
    std::cout << std::setw(15) << "Name"
              << std::setw(10) << "Score"
              << std::setw(10) << "Size"
              << std::setw(25) << "Date & Time"
              << "\n";
    std::cout << std::string(topScoresOnly ? 66 : 60, '=') << "\n";

    // Print all records, or only top 10 if topScoresOnly is true
    int count = topScoresOnly ? std::min(10, static_cast<int>(records.size())) : records.size();
    for (int i = 0; i < count; ++i) {
        const auto& r = records[i];
        if (topScoresOnly) {
            std::cout << std::setw(6) << (i + 1);
        }
        std::cout << std::setw(15) << r.name
                  << std::setw(10) << r.score
                  << std::setw(10) << r.size
                  << std::setw(25) << r.datetime
                  << "\n";
    }
}

// Returns the player's name.
std::string Player::GetName() const {
  return name;
}