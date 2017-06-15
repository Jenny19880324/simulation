cmake_minimum_required (VERSION 2.8.11)
project(Deformable)

###############################################################################
#external library
###############################################################################

#nanogui and its dependencies

set(DEBUG_NANOGUI_LIB "${CMAKE_CURRENT_SOURCE_DIR}/extern/lib/debug/nanogui.lib")
set(RELEASE_NANOGUI_LIB "${CMAKE_CURRENT_SOURCE_DIR}/extern/lib/release/nanogui.lib")
set(NANOGUI_EXTRA_LIBS "")
list(APPEND NANOGUI_EXTRA_LIBS opengl32)

###############################################################################
#deformable library
###############################################################################
set(DEFORMABLE_SRC_DIR src/deformable)
set(DEFORMABLE_BIN_DIR deformable)
add_subdirectory(${DEFORMABLE_SRC_DIR} ${DEFORMABLE_BIN_DIR})

###############################################################################
#the application
###############################################################################
add_executable(main src/main.cpp)
target_link_libraries(main debug deformable debug ${DEBUG_NANOGUI_LIB} ${NANOGUI_EXTRA_LIBS})
target_link_libraries(main optimized deformable optimized ${RELEASE_NANOGUI_LIB} ${NANOGUI_EXTRA_LIBS})

set(MAIN_INCLUDE_DIRECTORIES "")
list(APPEND MAIN_INCLUDE_DIRECTORIES 
src/deformable)
target_include_directories(main PUBLIC ${MAIN_INCLUDE_DIRECTORIES})


###############################################################################
#copy dlls to the exe folder
###############################################################################

#COPY external library DLL to exe folder

add_custom_command(TARGET main POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy_directory
"${CMAKE_CURRENT_SOURCE_DIR}/extern/dll/$<CONFIGURATION>"
$<TARGET_FILE_DIR:main>)

#COPY deformable library DLL to exe folder

add_custom_command(TARGET main POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy_if_different
"${DEFORMABLE_BIN_DIR}/$<CONFIGURATION>/deformable.dll"
$<TARGET_FILE_DIR:main>)
