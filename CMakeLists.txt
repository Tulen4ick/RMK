cmake_minimum_required(VERSION 3.10.0)
project(rmk_project VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES "src/*.cpp")

add_definitions(
    -DINPUT_FILE_PATH="${CMAKE_SOURCE_DIR}/Products.csv"
)

add_executable(rmk ${SOURCES})

target_include_directories(rmk PUBLIC "${CMAKE_SOURCE_DIR}/include")

