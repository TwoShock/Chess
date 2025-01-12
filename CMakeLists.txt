cmake_minimum_required(VERSION 3.10)
project(Chess)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
file(GLOB SOURCES "src/*.cpp")
list(FILTER SOURCES EXCLUDE REGEX "src/main.cpp")
file(GLOB HEADERS "include/*.hpp")
add_library(Chess STATIC ${SOURCES} ${HEADERS})

target_include_directories(Chess PUBLIC include)
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
file(GLOB TESTS "test/*.cpp")
add_executable(ChessTest ${TESTS})
target_link_libraries(ChessTest PRIVATE Chess gtest gtest_main)

# Copy resource files from the "test" folder to the build output directory
file(GLOB RESOURCE_FILES "test/resources/*")

# Create the 'resources' directory in the build output
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/resources)

# Copy resource files from the 'test/resources' directory to the 'resources' directory in the build output
add_custom_command(TARGET ChessTest POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/test/resources
        ${CMAKE_BINARY_DIR}/resources
)

# Add a separate executable for running the game
file(GLOB MAIN_CPP "src/main.cpp")
add_executable(ChessGame ${MAIN_CPP})
target_link_libraries(ChessGame PRIVATE Chess)
