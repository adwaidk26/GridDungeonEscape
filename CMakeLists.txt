cmake_minimum_required(VERSION 3.10)

set(GAME_NAME GridDungeonEscape)
set(GAME_VERSION 1.0)
project(${GAME_NAME} VERSION ${GAME_VERSION})


include_directories(
	${PROJECT_SOURCE_DIR}/Game/Core/Inc
	${PROJECT_SOURCE_DIR}/Game/Utils/Inc
)

file(GLOB SOURCES
	${PROJECT_SOURCE_DIR}/Game/Core/Src/*.cpp
	${PROJECT_SOURCE_DIR}/Game/Utils/Src/*.cpp
)

add_executable(${GAME_NAME} ${SOURCES})

find_package(raylib REQUIRED)
target_link_libraries(${GAME_NAME} PRIVATE raylib)
