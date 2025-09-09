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


cmake_minimum_required(VERSION 3.16)
project(SnakeGame LANGUAGES CXX)

# Qt automagic
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# Options
option(USE_QT_LAUNCHER "Enable Qt6 launcher (pre/post UI) around SDL game" ON)

# Macro used by your code
add_definitions(-DSOURCE_DIR="${CMAKE_SOURCE_DIR}")

# SDL2
find_package(SDL2 REQUIRED)

# Threads
find_package(Threads REQUIRED)

# Sources
set(GAME_SOURCES
    src/main.cpp
    src/game.cpp
    src/controller.cpp
    src/renderer.cpp
    src/snake.cpp
    src/menu.cpp
    src/player.cpp
    src/obstacle.cpp
    # Qt dialogs (compiled always; linked to Qt only when option ON)
    src/StartDialog.cpp
    src/StartDialog.h
    src/ResultsDialog.cpp
    src/ResultsDialog.h
    src/MainMenuDialog.cpp 
    src/MainMenuDialog.h
    src/HistoryDialog.cpp
    src/HistoryDialog.h
)

add_executable(SnakeGame ${GAME_SOURCES})

# Include dirs (target-scoped)
target_include_directories(SnakeGame PRIVATE
    ${SDL2_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/src
)

# Link SDL2, threads, and (for now) experimental filesystem
target_link_libraries(SnakeGame PRIVATE
    ${SDL2_LIBRARIES}
    Threads::Threads
    stdc++fs
)

# Qt (only when launcher enabled)
if (USE_QT_LAUNCHER)
  find_package(Qt6 6.2 REQUIRED COMPONENTS Widgets)
  target_link_libraries(SnakeGame PRIVATE Qt6::Widgets)
endif()
