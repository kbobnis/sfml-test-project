cmake_minimum_required(VERSION 3.21)
project(HelloSFML)

set(CMAKE_CXX_STANDARD 14)

add_executable(HelloSFML src/main.cpp src/Board.cpp src/FillType.cpp)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/envs/cpp/SFML-2.5.1/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(C:/envs/cpp/SFML-2.5.1/include)
target_link_libraries(HelloSFML sfml-system sfml-window sfml-graphics sfml-audio)
