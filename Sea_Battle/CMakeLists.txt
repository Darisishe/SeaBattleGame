cmake_minimum_required(VERSION 2.8)
project(Sea_Battle)

add_executable(Sea_Battle main.cpp)
add_library(detail Game/Game.cpp Player/Player.cpp IO/IO.cpp Field/Field.cpp Command/Command.cpp)
target_include_directories(detail PUBLIC Game Player IO Field Command)
target_link_libraries(Sea_Battle detail)
