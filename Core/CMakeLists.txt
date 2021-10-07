cmake_minimum_required(VERSION 3.10)

Project(Chip8)

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(Inc)



add_executable (Chip8 Src/main.cpp Src/chip8.cpp Inc/chip8.h)

target_link_libraries(Chip8 ${SDL2_LIBRARIES})

# End of CMakeLists.Txt file. Save it as a plain text file and the name should be exactly CMakeLists.Txt