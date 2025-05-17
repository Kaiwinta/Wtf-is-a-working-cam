cmake_minimum_required(VERSION 3.10)

project(CamShit)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native -DNDEBUG")
set(CMAKE_BUILD_TYPE Release)

# Find SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})


# Source files
set(SOURCES
    src/Main.cpp
    src/Camera/Camera.cpp
    src/Display/Sdl2.cpp
)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -rdynamic")

add_executable(CamShit ${SOURCES})

# Include directories
target_include_directories(CamShit PRIVATE
    ${PROJECT_SOURCE_DIR}/src/
    ${PROJECT_SOURCE_DIR}/src/Camera
    ${PROJECT_SOURCE_DIR}/src/Display
)

# Link libraries
target_link_libraries(CamShit
    ${SDL2_LIBRARIES}
)