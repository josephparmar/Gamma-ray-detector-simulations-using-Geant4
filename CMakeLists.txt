cmake_minimum_required(VERSION 3.2 FATAL_ERROR) #checks correct version of cmake

project(Tutorial) #Name of the project

find_package(Geant4 REQUIRED ui_all vis_all) #checks geant4 package

include(${Geant4_USE_FILE}) #include header files

include_directories(${PROJECT_SOURCE_DIR}/include) #include our own files from include folder

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc) #glob for wildcard. include all .cc in src folder

file(GLOB MACRO_FILES "macros/*.mac")
file(COPY ${MACRO_FILES} DESTINATION ${CMAKE_BINARY_DIR})

add_executable(sim sim.cc ${sources}) #create the excecutable with all sources

target_link_libraries(sim ${Geant4_LIBRARIES}) # link geant4 libraries

add_custom_target(Tutorial DEPENDS sim) #project tutorial is related to executable  sim

#run following in /build
#cmake -DGeant4_DIR=/home/joepar/Geant4/geant4-v11.4.1-install/lib/cmake/Geant4 ..
#make
#./sim