cmake_minimum_required(VERSION 3.0.2)

project(SDL_exploration)

set(CMAKE_CXX_STANDARD 11) # enable C++11 standard

find_package(SDL2 REQUIRED)

add_executable(sdl1 src/sdl1.cpp)
target_link_libraries(sdl1 ${SDL2_LIBRARIES})


add_executable(sdl2 src/sdl2.cpp)
target_link_libraries(sdl2 ${SDL2_LIBRARIES})


add_executable(sdl_grid src/sdl_grid.cpp)
target_link_libraries(sdl_grid ${SDL2_LIBRARIES})

add_executable(sdl_maze src/sdl_maze.cpp src/sdl_maze_main.cpp)
target_link_libraries(sdl_maze ${SDL2_LIBRARIES})
target_include_directories(sdl_maze
	PUBLIC	
	${PROJECT_SOURCE_DIR}/include
)
