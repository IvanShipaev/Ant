cmake_minimum_required(VERSION 3.14)

# Set the project name
project (ant_step)

include_directories( 
    .
)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME})


