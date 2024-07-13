cmake_minimum_required(VERSION 3.29)

include(FetchContent)
set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
FetchContent_Declare(ftxui
	GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
	GIT_TAG v5.0.0
	GIT_PROGRESS ON
)

FetchContent_MakeAvailable(ftxui)

project(terminal-rain
	VERSION 1.0
	DESCRIPTION "A terminal based rain visualisation"
	HOMEPAGE_URL "https://github.com/Oakamoore/terminal-rain"
	LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(terminal-rain-lib 
	src/drop.cpp
	src/rain.cpp
	src/terminal.cpp
)

target_include_directories(terminal-rain-lib
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(terminal-rain-lib
	PUBLIC ftxui::screen
	PUBLIC ftxui::component
)

option(ENABLE_TESTING "Enable tests" ON)

if(ENABLE_TESTING)
	enable_testing()
	add_subdirectory(test)
endif()

add_executable(terminal-rain
	src/main.cpp
)

target_link_libraries(terminal-rain
	PRIVATE terminal-rain-lib
)
