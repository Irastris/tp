cmake_minimum_required(VERSION 3.16)
project(tp VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(extern/aurora EXCLUDE_FROM_ALL)

# I don't care about fixing these issues for now, so I'm suppressing the warnings
add_compile_options(
    -Wno-multichar
    -Wno-int-to-pointer-cast
    -Wno-conversion-null
    -Wno-delete-incomplete # IMPORTANT TO RESOLVE
)

set(GAME_FILES
    src/main.cpp
    src/game/ext.cpp
    src/game/machine.cpp
    src/game/save.cpp
    src/game/stage.cpp
    src/game/com/inf/game.cpp
)

set(JSYS_FILES
    src/jsystem/jframework/jfwsystem.cpp
    src/jsystem/jkernel/jkrexpheap.cpp
    src/jsystem/jkernel/jkrheap.cpp
    src/jsystem/jkernel/jkrdisposer.cpp
    src/jsystem/jsupport/jsulist.cpp
)

set(SSYS_FILES
    src/ssystem/scomponent/c_lib.cpp
    src/ssystem/scomponent/c_m3d_g_aab.cpp
    src/ssystem/scomponent/c_m3d_g_cps.cpp
    src/ssystem/scomponent/c_m3d_g_cyl.cpp
    src/ssystem/scomponent/c_m3d_g_lin.cpp
    src/ssystem/scomponent/c_m3d_g_pla.cpp
    src/ssystem/scomponent/c_m3d_g_sph.cpp
    src/ssystem/scomponent/c_m3d_g_tri.cpp
    src/ssystem/scomponent/c_m3d_g_vtx.cpp
    src/ssystem/scomponent/c_m3d.cpp
    src/ssystem/scomponent/c_math.cpp
    src/ssystem/scomponent/c_phase.cpp
    src/ssystem/scomponent/c_sxyz.cpp
    src/ssystem/scomponent/c_xyz.cpp
)

add_executable(tp src/main.cpp ${GAME_FILES} ${JSYS_FILES} ${SSYS_FILES} ${DOLPHIN_FILES})
target_include_directories(tp PUBLIC include)
target_link_libraries(tp PUBLIC aurora::core aurora::gx aurora::mtx aurora::main)