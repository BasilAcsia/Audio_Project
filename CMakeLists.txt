cmake_minimum_required(VERSION 3.1)

project(AudioTest VERSION 1.0
              LANGUAGES C)
              
add_executable(test main.c)
 
# Find the ALSA library
find_package(ALSA REQUIRED)
 
# Link against ALSA and the math library
target_link_libraries(test PRIVATE ${ALSA_LIBRARIES})
 
# Include ALSA headers
target_include_directories(test PRIVATE ${ALSA_INCLUDE_DIRS})
