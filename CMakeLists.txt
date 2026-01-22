cmake_minimum_required(VERSION 3.26.0)

project(tp VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 23)

set(SOURCE_FILES
    src/main.cpp
    src/game/machine.cpp
)

add_executable(tp src/main.cpp ${SOURCE_FILES})

target_include_directories(tp PUBLIC include)