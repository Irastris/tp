cmake_minimum_required(VERSION 3.16)
project(tp VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

# I don't care about fixing these issues for now, so I'm suppressing the warnings
add_compile_options(
    -Wno-multichar
    -Wno-int-to-pointer-cast
    -Wno-conversion-null
    -Wno-delete-incomplete
    -Wno-return-type
    -Wno-pointer-arith
)

add_subdirectory(extern/aurora EXCLUDE_FROM_ALL)

include(tp.cmake)

add_executable(tp ${GAME_FILES} ${JSYS_FILES} ${SSYS_FILES} ${DOLPHIN_FILES})
target_include_directories(tp PUBLIC include)
target_link_libraries(tp PUBLIC aurora::core aurora::gx aurora::mtx aurora::pad aurora::main)