# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/coiland/Documents/Emulator/chip8/Chip-8-Emu/Core

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/coiland/Documents/Emulator/chip8/Chip-8-Emu/Build

# Include any dependencies generated for this target.
include CMakeFiles/Chip8.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Chip8.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Chip8.dir/flags.make

CMakeFiles/Chip8.dir/Src/main.cpp.o: CMakeFiles/Chip8.dir/flags.make
CMakeFiles/Chip8.dir/Src/main.cpp.o: /home/coiland/Documents/Emulator/chip8/Chip-8-Emu/Core/Src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/coiland/Documents/Emulator/chip8/Chip-8-Emu/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Chip8.dir/Src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Chip8.dir/Src/main.cpp.o -c /home/coiland/Documents/Emulator/chip8/Chip-8-Emu/Core/Src/main.cpp

CMakeFiles/Chip8.dir/Src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Chip8.dir/Src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/coiland/Documents/Emulator/chip8/Chip-8-Emu/Core/Src/main.cpp > CMakeFiles/Chip8.dir/Src/main.cpp.i

CMakeFiles/Chip8.dir/Src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Chip8.dir/Src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/coiland/Documents/Emulator/chip8/Chip-8-Emu/Core/Src/main.cpp -o CMakeFiles/Chip8.dir/Src/main.cpp.s

CMakeFiles/Chip8.dir/Src/chip8.cpp.o: CMakeFiles/Chip8.dir/flags.make
CMakeFiles/Chip8.dir/Src/chip8.cpp.o: /home/coiland/Documents/Emulator/chip8/Chip-8-Emu/Core/Src/chip8.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/coiland/Documents/Emulator/chip8/Chip-8-Emu/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Chip8.dir/Src/chip8.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Chip8.dir/Src/chip8.cpp.o -c /home/coiland/Documents/Emulator/chip8/Chip-8-Emu/Core/Src/chip8.cpp

CMakeFiles/Chip8.dir/Src/chip8.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Chip8.dir/Src/chip8.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/coiland/Documents/Emulator/chip8/Chip-8-Emu/Core/Src/chip8.cpp > CMakeFiles/Chip8.dir/Src/chip8.cpp.i

CMakeFiles/Chip8.dir/Src/chip8.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Chip8.dir/Src/chip8.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/coiland/Documents/Emulator/chip8/Chip-8-Emu/Core/Src/chip8.cpp -o CMakeFiles/Chip8.dir/Src/chip8.cpp.s

# Object files for target Chip8
Chip8_OBJECTS = \
"CMakeFiles/Chip8.dir/Src/main.cpp.o" \
"CMakeFiles/Chip8.dir/Src/chip8.cpp.o"

# External object files for target Chip8
Chip8_EXTERNAL_OBJECTS =

Chip8: CMakeFiles/Chip8.dir/Src/main.cpp.o
Chip8: CMakeFiles/Chip8.dir/Src/chip8.cpp.o
Chip8: CMakeFiles/Chip8.dir/build.make
Chip8: CMakeFiles/Chip8.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/coiland/Documents/Emulator/chip8/Chip-8-Emu/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable Chip8"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Chip8.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Chip8.dir/build: Chip8

.PHONY : CMakeFiles/Chip8.dir/build

CMakeFiles/Chip8.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Chip8.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Chip8.dir/clean

CMakeFiles/Chip8.dir/depend:
	cd /home/coiland/Documents/Emulator/chip8/Chip-8-Emu/Build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/coiland/Documents/Emulator/chip8/Chip-8-Emu/Core /home/coiland/Documents/Emulator/chip8/Chip-8-Emu/Core /home/coiland/Documents/Emulator/chip8/Chip-8-Emu/Build /home/coiland/Documents/Emulator/chip8/Chip-8-Emu/Build /home/coiland/Documents/Emulator/chip8/Chip-8-Emu/Build/CMakeFiles/Chip8.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Chip8.dir/depend

