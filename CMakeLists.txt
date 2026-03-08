cmake_minimum_required(VERSION 3.10)

set(GAME_NAME GridDungeonEscape)
set(GAME_VERSION 1.0)
project(${GAME_NAME} VERSION ${GAME_VERSION})


include_directories(
	${PROJECT_SOURCE_DIR}/Game/Core/Inc
	${PROJECT_SOURCE_DIR}/Game/Utils/Inc
	${PROJECT_SOURCE_DIR}/Game/Menu/Inc
	${PROJECT_SOURCE_DIR}/Game/Engine/Core/Inc
	${PROJECT_SOURCE_DIR}/Game/Engine/World/Inc
)

file(GLOB SOURCES
	${PROJECT_SOURCE_DIR}/Game/Core/Src/*.cpp
	${PROJECT_SOURCE_DIR}/Game/Utils/Src/*.cpp
	${PROJECT_SOURCE_DIR}/Game/Menu/Src/*.cpp
	${PROJECT_SOURCE_DIR}/Game/Engine/Core/Src/*.cpp
	${PROJECT_SOURCE_DIR}/Game/Engine/World/Src/*.cpp
)

add_executable(${GAME_NAME} ${SOURCES})

# Base runtime data directory (default for local builds, overridable via -DGAME_DATA_DIR=... in RPM spec)
set(GAME_DATA_DIR "${PROJECT_SOURCE_DIR}/Game/Res" CACHE PATH "Runtime game data directory")
set(IMAGE_FOLDER "${GAME_DATA_DIR}/Images")
set(MAP_FOLDER "${GAME_DATA_DIR}/Maps")

target_compile_definitions(${GAME_NAME} PRIVATE
	GAME_DATA_DIR="${GAME_DATA_DIR}"
	IMAGE_FOLDER="${IMAGE_FOLDER}"
	MAP_FOLDER="${MAP_FOLDER}"
)

find_package(raylib REQUIRED)
target_link_libraries(${GAME_NAME} PRIVATE raylib)
