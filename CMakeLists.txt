cmake_minimum_required(VERSION 3.8)

project("dungeonator-demo")

if(EMSCRIPTEN)
	set(EMSCRIPTEN_COMMON_FLAGS "-s WASM=1 -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS=\"[\"\"png\"\"]\" --preload-file assets/img")
	set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} ${EMSCRIPTEN_COMMON_FLAGS} -s ASSERTIONS=1")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${EMSCRIPTEN_COMMON_FLAGS}")
	set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif()

add_subdirectory("assets")
add_subdirectory("src")
