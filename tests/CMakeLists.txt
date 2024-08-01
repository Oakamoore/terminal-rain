FetchContent_Declare(Catch2
	GIT_REPOSITORY https://github.com/catchorg/Catch2.git
	GIT_TAG v3.6.0
	GIT_PROGRESS ON
)

FetchContent_MakeAvailable(Catch2)
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)

add_executable(terminal-rain-tests
	drop_tests.cpp
	rain_tests.cpp
)

target_link_libraries(terminal-rain-tests
	PRIVATE Catch2::Catch2WithMain
	PRIVATE terminal-rain-lib
)

catch_discover_tests(terminal-rain-tests)