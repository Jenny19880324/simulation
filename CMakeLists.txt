cmake_minimum_required (VERSION 2.8.11)
project(Deformable)

add_library(simulation-obj OBJECT 
src/simulation/integrator.h src/simulation/integrator.cpp
src/simulation/minimizationMethod.h src/simulation/minimizationMethod.cpp)

add_library(deformable 
$<TARGET_OBJECTS:simulation-obj>)

add_executable(main src/main.cpp)
target_link_libraries(main deformable)

set(MAIN_INCLUDE_DIRECTORIES "")
list(APPEND MAIN_INCLUDE_DIRECTORIES 
src/simulation)
target_include_directories(main PUBLIC ${MAIN_INCLUDE_DIRECTORIES})