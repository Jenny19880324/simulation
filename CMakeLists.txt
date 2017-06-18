cmake_minimum_required (VERSION 2.8.11)
project(application)

###############################################################################
#external library
###############################################################################

#nanogui and its dependencies

set(DEBUG_NANOGUI_LIB "${CMAKE_CURRENT_SOURCE_DIR}/extern/lib/debug/nanogui.lib")
set(RELEASE_NANOGUI_LIB "${CMAKE_CURRENT_SOURCE_DIR}/extern/lib/release/nanogui.lib")
set(NANOGUI_EXTRA_LIBS "")
list(APPEND NANOGUI_EXTRA_LIBS opengl32)

###############################################################################
#include directory
###############################################################################

# set the MAIN_INCLUDE_DIRECTORIES before add_subdirectory so that the 
# CHILD SCOPE can see it as well

set(MAIN_INCLUDE_DIRECTORIES "")
list(APPEND MAIN_INCLUDE_DIRECTORIES 
"${CMAKE_CURRENT_SOURCE_DIR}/include"
"${CMAKE_CURRENT_SOURCE_DIR}/include/eigen"
"${CMAKE_CURRENT_SOURCE_DIR}/include/solver")


###############################################################################
#solver library
###############################################################################
set(SOLVER_SRC_DIR src/solver)
set(SOLVER_BIN_DIR solver)
add_subdirectory(${SOLVER_SRC_DIR} ${SOLVER_BIN_DIR})


###############################################################################
#the application
###############################################################################
add_executable(main src/main.cpp)
target_link_libraries(main debug solver debug ${DEBUG_NANOGUI_LIB} ${NANOGUI_EXTRA_LIBS})
target_link_libraries(main optimized solver optimized ${RELEASE_NANOGUI_LIB} ${NANOGUI_EXTRA_LIBS})

target_include_directories(main PUBLIC "${MAIN_INCLUDE_DIRECTORIES}")


###############################################################################
#copy dlls to the exe folder
###############################################################################

#COPY external library DLL to exe folder

add_custom_command(TARGET main POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy_directory
"${CMAKE_CURRENT_SOURCE_DIR}/extern/dll/$<CONFIGURATION>"
$<TARGET_FILE_DIR:main>)

#COPY solver library DLL to exe folder

add_custom_command(TARGET main POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy_if_different
"${SOLVER_BIN_DIR}/$<CONFIGURATION>/solver.dll"
$<TARGET_FILE_DIR:main>)
