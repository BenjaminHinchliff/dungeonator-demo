cmake_minimum_required(VERSION 3.11)

include(FetchContent)
FetchContent_Declare(
	dungeonator
	GIT_REPOSITORY https://github.com/BenjaminHinchliff/dungeonator.git
	GIT_TAG 1.0.0
)

set(FETCHCONTENT_QUIET OFF)
FetchContent_MakeAvailable(dungeonator)

add_executable(${PROJECT_NAME} "main.c")

target_link_libraries(${PROJECT_NAME} PUBLIC dungeonator)

if(NOT EMSCRIPTEN)
	find_package(SDL2 CONFIG REQUIRED)
	find_package(sdl2-image CONFIG REQUIRED)
	target_link_libraries(${PROJECT_NAME} PUBLIC SDL2::SDL2 SDL2::SDL2_image SDL2::SDL2main)
endif()
