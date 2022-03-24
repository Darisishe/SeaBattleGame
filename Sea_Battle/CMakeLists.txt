cmake_minimum_required(VERSION 2.8)
project(Sea_Battle)

add_executable(Sea_Battle main.cpp IO/IO.cpp Game/Game.cpp Player/Player.cpp Command/Command.cpp Ship/Ship.cpp)
target_include_directories(Sea_Battle PUBLIC Game Player Ship Command IO)

