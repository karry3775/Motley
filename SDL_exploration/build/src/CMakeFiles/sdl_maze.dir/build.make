# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/kartik/Documents/Motley/SDL_exploration

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kartik/Documents/Motley/SDL_exploration/build

# Include any dependencies generated for this target.
include src/CMakeFiles/sdl_maze.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/sdl_maze.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/sdl_maze.dir/flags.make

src/CMakeFiles/sdl_maze.dir/sdl_maze_main.cpp.o: src/CMakeFiles/sdl_maze.dir/flags.make
src/CMakeFiles/sdl_maze.dir/sdl_maze_main.cpp.o: ../src/sdl_maze_main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kartik/Documents/Motley/SDL_exploration/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/sdl_maze.dir/sdl_maze_main.cpp.o"
	cd /home/kartik/Documents/Motley/SDL_exploration/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sdl_maze.dir/sdl_maze_main.cpp.o -c /home/kartik/Documents/Motley/SDL_exploration/src/sdl_maze_main.cpp

src/CMakeFiles/sdl_maze.dir/sdl_maze_main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sdl_maze.dir/sdl_maze_main.cpp.i"
	cd /home/kartik/Documents/Motley/SDL_exploration/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kartik/Documents/Motley/SDL_exploration/src/sdl_maze_main.cpp > CMakeFiles/sdl_maze.dir/sdl_maze_main.cpp.i

src/CMakeFiles/sdl_maze.dir/sdl_maze_main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sdl_maze.dir/sdl_maze_main.cpp.s"
	cd /home/kartik/Documents/Motley/SDL_exploration/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kartik/Documents/Motley/SDL_exploration/src/sdl_maze_main.cpp -o CMakeFiles/sdl_maze.dir/sdl_maze_main.cpp.s

src/CMakeFiles/sdl_maze.dir/sdl_maze_main.cpp.o.requires:

.PHONY : src/CMakeFiles/sdl_maze.dir/sdl_maze_main.cpp.o.requires

src/CMakeFiles/sdl_maze.dir/sdl_maze_main.cpp.o.provides: src/CMakeFiles/sdl_maze.dir/sdl_maze_main.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/sdl_maze.dir/build.make src/CMakeFiles/sdl_maze.dir/sdl_maze_main.cpp.o.provides.build
.PHONY : src/CMakeFiles/sdl_maze.dir/sdl_maze_main.cpp.o.provides

src/CMakeFiles/sdl_maze.dir/sdl_maze_main.cpp.o.provides.build: src/CMakeFiles/sdl_maze.dir/sdl_maze_main.cpp.o


src/CMakeFiles/sdl_maze.dir/sdl_maze.cpp.o: src/CMakeFiles/sdl_maze.dir/flags.make
src/CMakeFiles/sdl_maze.dir/sdl_maze.cpp.o: ../src/sdl_maze.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kartik/Documents/Motley/SDL_exploration/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/sdl_maze.dir/sdl_maze.cpp.o"
	cd /home/kartik/Documents/Motley/SDL_exploration/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sdl_maze.dir/sdl_maze.cpp.o -c /home/kartik/Documents/Motley/SDL_exploration/src/sdl_maze.cpp

src/CMakeFiles/sdl_maze.dir/sdl_maze.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sdl_maze.dir/sdl_maze.cpp.i"
	cd /home/kartik/Documents/Motley/SDL_exploration/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kartik/Documents/Motley/SDL_exploration/src/sdl_maze.cpp > CMakeFiles/sdl_maze.dir/sdl_maze.cpp.i

src/CMakeFiles/sdl_maze.dir/sdl_maze.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sdl_maze.dir/sdl_maze.cpp.s"
	cd /home/kartik/Documents/Motley/SDL_exploration/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kartik/Documents/Motley/SDL_exploration/src/sdl_maze.cpp -o CMakeFiles/sdl_maze.dir/sdl_maze.cpp.s

src/CMakeFiles/sdl_maze.dir/sdl_maze.cpp.o.requires:

.PHONY : src/CMakeFiles/sdl_maze.dir/sdl_maze.cpp.o.requires

src/CMakeFiles/sdl_maze.dir/sdl_maze.cpp.o.provides: src/CMakeFiles/sdl_maze.dir/sdl_maze.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/sdl_maze.dir/build.make src/CMakeFiles/sdl_maze.dir/sdl_maze.cpp.o.provides.build
.PHONY : src/CMakeFiles/sdl_maze.dir/sdl_maze.cpp.o.provides

src/CMakeFiles/sdl_maze.dir/sdl_maze.cpp.o.provides.build: src/CMakeFiles/sdl_maze.dir/sdl_maze.cpp.o


# Object files for target sdl_maze
sdl_maze_OBJECTS = \
"CMakeFiles/sdl_maze.dir/sdl_maze_main.cpp.o" \
"CMakeFiles/sdl_maze.dir/sdl_maze.cpp.o"

# External object files for target sdl_maze
sdl_maze_EXTERNAL_OBJECTS =

src/sdl_maze: src/CMakeFiles/sdl_maze.dir/sdl_maze_main.cpp.o
src/sdl_maze: src/CMakeFiles/sdl_maze.dir/sdl_maze.cpp.o
src/sdl_maze: src/CMakeFiles/sdl_maze.dir/build.make
src/sdl_maze: src/CMakeFiles/sdl_maze.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kartik/Documents/Motley/SDL_exploration/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable sdl_maze"
	cd /home/kartik/Documents/Motley/SDL_exploration/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sdl_maze.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/sdl_maze.dir/build: src/sdl_maze

.PHONY : src/CMakeFiles/sdl_maze.dir/build

src/CMakeFiles/sdl_maze.dir/requires: src/CMakeFiles/sdl_maze.dir/sdl_maze_main.cpp.o.requires
src/CMakeFiles/sdl_maze.dir/requires: src/CMakeFiles/sdl_maze.dir/sdl_maze.cpp.o.requires

.PHONY : src/CMakeFiles/sdl_maze.dir/requires

src/CMakeFiles/sdl_maze.dir/clean:
	cd /home/kartik/Documents/Motley/SDL_exploration/build/src && $(CMAKE_COMMAND) -P CMakeFiles/sdl_maze.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/sdl_maze.dir/clean

src/CMakeFiles/sdl_maze.dir/depend:
	cd /home/kartik/Documents/Motley/SDL_exploration/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kartik/Documents/Motley/SDL_exploration /home/kartik/Documents/Motley/SDL_exploration/src /home/kartik/Documents/Motley/SDL_exploration/build /home/kartik/Documents/Motley/SDL_exploration/build/src /home/kartik/Documents/Motley/SDL_exploration/build/src/CMakeFiles/sdl_maze.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/sdl_maze.dir/depend
