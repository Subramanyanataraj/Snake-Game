// #include <iostream>
// #include <memory>
// #include <string>

// // Your existing headers
// #include "controller.h"
// #include "game.h"
// #include "renderer.h"
// #include "player.h"

// // Qt headers (only used in the two short phases)
// #include <QApplication>
// #include "StartDialog.h"
// #include "ResultsDialog.h"

// struct StartConfig {
//   std::string name;
//   int difficulty = 1;
//   bool accepted = false;
// };

// static StartConfig run_qt_start_phase(int argc, char** argv) {
//   StartConfig cfg;
//   QApplication app(argc, argv);
//   StartDialog dlg;
//   if (dlg.exec() == QDialog::Accepted) {
//     cfg.name = dlg.playerName().toStdString();
//     cfg.difficulty = dlg.difficulty();
//     cfg.accepted = true;
//   }
//   // app quits when going out of scope
//   return cfg;
// }

// static void run_qt_results_phase(int argc, char** argv, int score, int size) {
//   QApplication app(argc, argv);
//   ResultsDialog dlg(score, size);
//   dlg.exec();
// }

// int main(int argc, char** argv) {
//   // ── Phase 1: Qt launcher ─────────────────────────────────────────────
//   auto cfg = run_qt_start_phase(argc, argv);
//   if (!cfg.accepted) return 0;  // user cancelled

//   // ── Phase 2: SDL game (your existing code) ───────────────────────────
//   // constants from your current main
//   constexpr std::size_t kFramesPerSecond{60};
//   constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
//   constexpr std::size_t kScreenWidth{640};
//   constexpr std::size_t kScreenHeight{640};
//   constexpr std::size_t kGridWidth{32};
//   constexpr std::size_t kGridHeight{32};

//   // NOTE: no Qt alive here — safe to run SDL
//   Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
//   Controller controller;
//   Game game(kGridWidth, kGridHeight, cfg.difficulty);
//   if (cfg.difficulty == 2) {
//     game.SetupObstacles(cfg.difficulty, kGridWidth, kGridHeight);
//   }

//   game.Run(controller, renderer, kMsPerFrame);

//   std::cout << "Game has terminated successfully!\n";
//   std::cout << "Score: " << game.GetScore() << "\n";
//   std::cout << "Size: " << game.GetSize() << "\n";

//   int score = game.GetScore();
//   int size  = game.GetSize();

//   // save results
//   Player player;
//   // set name captured in Qt phase:
//   // quick setter (add one in Player or just reuse EnterName if needed)
//   // Here we hack via SaveToFile (it uses Player::name field), so set it:
//   // -> add a setter in Player: void SetName(const std::string& n) { name = n; }
//   // For now assume you've added SetName:
//   player.SetName(cfg.name);
//   std::string path = std::string(SOURCE_DIR) + "/data/GameHistory.txt";
//   player.SaveToFile(path, score, size);

//   // ── Phase 3: Qt epilogue (results) ───────────────────────────────────
//   run_qt_results_phase(argc, argv, score, size);

//   return 0;
// }
#include <QApplication>
#include "MainMenuDialog.h"
#include "StartDialog.h"
#include "HistoryDialog.h"
#include "ResultsDialog.h"

// Your SDL game headers
#include "renderer.h"
#include "controller.h"
#include "game.h"
#include "player.h"

static int show_menu_and_get_choice(int argc,char** argv){
  QApplication app(argc, argv);
  MainMenuDialog dlg;
  dlg.exec();
  return (int)dlg.choice();
}

static bool get_start_config(int argc,char** argv,std::string& name,int& difficulty){
  QApplication app(argc, argv);
  StartDialog dlg;
  if (dlg.exec()!=QDialog::Accepted) return false;
  name = dlg.playerName().toStdString();
  difficulty = dlg.difficulty();
  return true;
}

static void show_history(int argc,char** argv,bool top){
  QApplication app(argc, argv);
  QString path = QString::fromStdString(std::string(SOURCE_DIR)+"/data/GameHistory.txt");
  HistoryDialog dlg(path, top);
  dlg.exec();
}

static void show_results(int argc,char** argv,int score,int size){
  QApplication app(argc, argv);
  ResultsDialog dlg(score, size);
  dlg.exec();
}

int main(int argc, char** argv){
  while (true) {
    int choice = show_menu_and_get_choice(argc, argv);
    if (choice == MainMenuDialog::Exit) return 0;
    if (choice == MainMenuDialog::History)   { show_history(argc, argv, /*topOnly=*/false); continue; }
    if (choice == MainMenuDialog::HighScores){ show_history(argc, argv, /*topOnly=*/true);  continue; }

    // Start New Game
    std::string name; int difficulty = 1;
    if (!get_start_config(argc, argv, name, difficulty)) continue;

    // --- SDL game runs here (Qt is destroyed) ---
    constexpr std::size_t kFPS = 60;
    constexpr std::size_t kMsPerFrame = 1000 / kFPS;
    constexpr std::size_t W = 640, H = 640, GW = 32, GH = 32;

    Renderer  renderer(W, H, GW, GH);
    Controller controller;
    Game       game(GW, GH, difficulty);
    if (difficulty == 2) game.SetupObstacles(difficulty, GW, GH);
    game.Run(controller, renderer, kMsPerFrame);

    // Save results
    Player player; player.SetName(name);
    std::string path = std::string(SOURCE_DIR) + "/data/GameHistory.txt";
    int score = game.GetScore();
    int size  = game.GetSize();
    player.SaveToFile(path, score, size);

    // Post-game Qt dialog
    show_results(argc, argv, score, size);
  }
}
