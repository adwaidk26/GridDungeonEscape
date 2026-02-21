cmake_minimum_required(VERSION 3.10)

set(GAME_NAME GridDungeonEscape)
set(GAME_VERSION 1.0)
project(${GAME_NAME} VERSION ${GAME_VERSION})


include_directories(
	${PROJECT_SOURCE_DIR}/Game/Core/Inc
	${PROJECT_SOURCE_DIR}/Game/Utils/Inc
	${PROJECT_SOURCE_DIR}/Game/Menu/Inc
	${PROJECT_SOURCE_DIR}/Game/Engine/Core/Inc
)

file(GLOB SOURCES
	${PROJECT_SOURCE_DIR}/Game/Core/Src/*.cpp
	${PROJECT_SOURCE_DIR}/Game/Utils/Src/*.cpp
	${PROJECT_SOURCE_DIR}/Game/Menu/Src/*.cpp
	${PROJECT_SOURCE_DIR}/Game/Engine/Core/Src/*.cpp
)

add_executable(${GAME_NAME} ${SOURCES})

# Define image folder path as preprocessor macro
set(IMAGE_FOLDER "${PROJECT_SOURCE_DIR}/Game/Res/Images")
add_definitions(-DIMAGE_FOLDER="${IMAGE_FOLDER}")

# Define map folder path as preprocessor macro
set(MAP_FOLDER "${PROJECT_SOURCE_DIR}/Game/Res/Maps")
add_definitions(-DMAP_FOLDER="${MAP_FOLDER}")

find_package(raylib REQUIRED)
target_link_libraries(${GAME_NAME} PRIVATE raylib)
