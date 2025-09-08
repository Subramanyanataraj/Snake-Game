# cmake_minimum_required(VERSION 3.7)
# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# add_definitions(-std=c++17)
# add_definitions(-DSOURCE_DIR="${CMAKE_SOURCE_DIR}")

# set(CXX_FLAGS "-Wall")
# set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

# project(SDL2Test)

# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# find_package(SDL2 REQUIRED)
# include_directories(${SDL2_INCLUDE_DIRS} src)

# add_executable(SnakeGame src/main.cpp src/game.cpp src/controller.cpp src/renderer.cpp src/snake.cpp src/menu.cpp src/player.cpp src/obstacle.cpp)
# string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
# target_link_libraries(SnakeGame ${SDL2_LIBRARIES} stdc++fs pthread)

cmake_minimum_required(VERSION 3.16)   # Qt6 finder works reliably from 3.16+
project(SnakeGame LANGUAGES CXX)
# Enable Qt's automatic MOC/UIC/RCC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
# ---- C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---- Project options
option(USE_QT_LAUNCHER "Enable Qt6 launcher (pre/post UI) around SDL game" ON)

# ---- Common compile warnings
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# ---- Define SOURCE_DIR macro for your code that writes GameHistory.txt
add_definitions(-DSOURCE_DIR="${CMAKE_SOURCE_DIR}")

# ---- SDL2 (keep your current game as-is)
find_package(SDL2 REQUIRED)
# Prefer modern include usage, but keep compatibility with your variable
include_directories(${SDL2_INCLUDE_DIRS} src)

# ---- Game sources (unchanged SDL game)
set(GAME_SOURCES
    src/main.cpp
    src/game.cpp
    src/controller.cpp
    src/renderer.cpp
    src/snake.cpp
    src/menu.cpp
    src/player.cpp
    src/obstacle.cpp
    src/StartDialog.cpp
    src/StartDialog.h       # <- include headers too
    src/ResultsDialog.cpp
    src/ResultsDialog.h     # <- include headers too
    src/MainMenuDialog.cpp 
    src/MainMenuDialog.h
    src/HistoryDialog.cpp
    src/HistoryDialog.h
)

add_executable(SnakeGame ${GAME_SOURCES})

# Some older toolchains needed stdc++fs; with C++17 it’s usually not required.
# If your linker complains about filesystem, uncomment the next line:
# target_link_libraries(SnakeGame stdc++fs)

# pthread for your obstacle threads
find_package(Threads REQUIRED)
# target_link_libraries(SnakeGame ${SDL2_LIBRARIES} Threads::Threads)
target_link_libraries(SnakeGame ${SDL2_LIBRARIES} Threads::Threads stdc++fs)

# ---------------------------
# Optional: Qt6 launcher flow
# ---------------------------
if (USE_QT_LAUNCHER)
  # Expect these files in a 'qt' subfolder:
  #   qt/StartDialog.h  qt/StartDialog.cpp
  #   qt/ResultsDialog.h qt/ResultsDialog.cpp
  #
  # And your main.cpp updated to:
  #   - run a small Qt dialog first (collect name/difficulty)
  #   - run the SDL game (same as before)
  #   - re-open a Qt dialog to show results
  #
  # (I already provided these files in the previous message—use those.)

  find_package(Qt6 6.2 REQUIRED COMPONENTS Widgets)

  # Add the Qt sources to the same executable so you don’t need two binaries.
  # target_sources(SnakeGame PRIVATE
  #     qt/StartDialog.cpp
  #     qt/ResultsDialog.cpp
  # )
  target_sources(SnakeGame PRIVATE
  src/StartDialog.cpp
  src/ResultsDialog.cpp
)
  target_include_directories(SnakeGame PRIVATE qt)
  target_link_libraries(SnakeGame Qt6::Widgets)
  
  # On Windows: make sure we still have a console for your std::cout end-screen prints.
  # If you prefer hiding the console, you can set WIN32 on the target, but then
  # you won't see terminal prints:
  # set_target_properties(SnakeGame PROPERTIES WIN32_EXECUTABLE FALSE)
endif()
