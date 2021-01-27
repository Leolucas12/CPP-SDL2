# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.5)

# Set the project name
project (game)

# Create a sources variable with a link to all cpp files to compile
file(GLOB SOURCES src/*.cpp)

# Add an executable with the above sources
add_executable(game ${SOURCES})

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES})

# Set the directories that should be included in the build command for this target
# when running g++ these will be included as -I/directory/path/
target_include_directories(game
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/include
)
