cmake_minimum_required(VERSION 3.6)

project(yaht)

add_subdirectory(magidoor)

add_executable(yaht Program.cpp Yaht.cpp Dice.cpp)
if (WIN32)
	TARGET_LINK_LIBRARIES(yaht mdoor Ws2_32)
Else()
	TARGET_LINK_LIBRARIES(yaht mdoor)
endif()