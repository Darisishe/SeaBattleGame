cmake_minimum_required(VERSION 2.8)
project(Sea_Battle)

add_executable(Sea_Battle main.cpp)
add_subdirectory(detail)
target_link_libraries(Sea_Battle detail)
