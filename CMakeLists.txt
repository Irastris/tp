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
    -Wno-return-type
)

set(GAME_FILES
    src/d/d_com_inf_game.cpp
    src/d/d_save.cpp
    src/d/d_stage.cpp
    src/f_pc/f_pc_node.cpp
    src/m_Do/m_Do_controller_pad.cpp
    src/m_Do/m_Do_dvd_thread.cpp
    src/m_Do/m_Do_ext.cpp
    src/m_Do/m_Do_graphic.cpp
    src/m_Do/m_Do_machine.cpp
    src/m_Do/m_Do_main.cpp
)

set(JSYS_FILES
    src/JSystem/JFramework/JFWSystem.cpp
    src/JSystem/JKernel/JKRDisposer.cpp
    src/JSystem/JKernel/JKRExpHeap.cpp
    src/JSystem/JKernel/JKRHeap.cpp
    src/JSystem/JSupport/JSUList.cpp
)

set(SSYS_FILES
    src/SSystem/SComponent/c_lib.cpp
    src/SSystem/SComponent/c_list.cpp
    src/SSystem/SComponent/c_m3d_g_aab.cpp
    src/SSystem/SComponent/c_m3d_g_cps.cpp
    src/SSystem/SComponent/c_m3d_g_cyl.cpp
    src/SSystem/SComponent/c_m3d_g_lin.cpp
    src/SSystem/SComponent/c_m3d_g_pla.cpp
    src/SSystem/SComponent/c_m3d_g_sph.cpp
    src/SSystem/SComponent/c_m3d_g_tri.cpp
    src/SSystem/SComponent/c_m3d_g_vtx.cpp
    src/SSystem/SComponent/c_m3d.cpp
    src/SSystem/SComponent/c_math.cpp
    src/SSystem/SComponent/c_node.cpp
    src/SSystem/SComponent/c_phase.cpp
    src/SSystem/SComponent/c_sxyz.cpp
    src/SSystem/SComponent/c_xyz.cpp
)

set(DOLPHIN_FILES
    src/dolphin/mtx/vec.c
)

add_executable(tp ${GAME_FILES} ${JSYS_FILES} ${SSYS_FILES} ${DOLPHIN_FILES})
target_include_directories(tp PUBLIC include)
target_link_libraries(tp PUBLIC aurora::core aurora::gx aurora::mtx aurora::main)