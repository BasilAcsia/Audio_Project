cmake_minimum_required(VERSION 3.1)

project(Audio2 VERSION 1.0
              LANGUAGES CXX)
              
add_executable(audio main.cpp)
 
# Find the ALSA library
find_package(ALSA REQUIRED)
 
# Link against ALSA and the math library
target_link_libraries(audio PRIVATE ${ALSA_LIBRARIES})
 
# Include ALSA headers
target_include_directories(audio PRIVATE ${ALSA_INCLUDE_DIRS})
