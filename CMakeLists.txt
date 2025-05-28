cmake_minimum_required(VERSION 3.10)

project(camShit)

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
    src/CamShit/CamShit.cpp
    src/Camera/Camera.cpp

    src/Parser/Parser.cpp
    src/Parser/Utils/ParamUtils.cpp

    src/VirtualCamera/VirtualCamera.cpp
    src/Display/Sdl2.cpp

    src/Effects/ColorScales/ColorScales.cpp

    src/Effects/Random/MiddleDuplication/MiddleDuplication.cpp
    src/Effects/Random/SquareSplit/SquareSplit.cpp
    src/Effects/Random/FlyEffect/FlyEffect.cpp
    src/Effects/Random/Tests/Test.cpp

    src/Effects/Reverse/Reverse.cpp
    src/Effects/Reverse/Vertical/Vertical.cpp
    src/Effects/Reverse/Horizontal/Horizontal.cpp

    src/Effects/Texture/Image/Image.cpp
)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -rdynamic")

add_executable(camShit ${SOURCES})

# Include directories
target_include_directories(camShit PRIVATE
    ${PROJECT_SOURCE_DIR}/src/
    ${PROJECT_SOURCE_DIR}/src/Camera
    ${PROJECT_SOURCE_DIR}/src/Parser
    ${PROJECT_SOURCE_DIR}/src/Parser/Utils
    ${PROJECT_SOURCE_DIR}/src/CamShit
    ${PROJECT_SOURCE_DIR}/src/VirtualCamera
    ${PROJECT_SOURCE_DIR}/src/Display
    ${PROJECT_SOURCE_DIR}/src/Enum
    ${PROJECT_SOURCE_DIR}/src/Effects
    ${PROJECT_SOURCE_DIR}/src/Effects/Reverse
    ${PROJECT_SOURCE_DIR}/src/Effects/Random
    ${PROJECT_SOURCE_DIR}/src/Effects/Random/MiddleDuplication
    ${PROJECT_SOURCE_DIR}/src/Effects/Random/SquareSplit
    ${PROJECT_SOURCE_DIR}/src/Effects/Random/FlyEffect
    ${PROJECT_SOURCE_DIR}/src/Effects/Random/Tests
    ${PROJECT_SOURCE_DIR}/src/Effects/ColorScales
    ${PROJECT_SOURCE_DIR}/src/Effects/Reverse/Vertical
    ${PROJECT_SOURCE_DIR}/src/Effects/Reverse/Horizontal
    ${PROJECT_SOURCE_DIR}/src/Effects/Texture/Image

    $(PROJECT_SOURCE_DIR)/stb/stb_image

)

# Link libraries
target_link_libraries(camShit
    ${SDL2_LIBRARIES}
)