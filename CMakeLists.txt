cmake_minimum_required(VERSION 3.10)

project(TemplateMaker VERSION 1.0 LANGUAGES CXX)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(TemplateMaker
    src/main.cpp
)
target_include_directories(TemplateMaker PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

list(APPEND CMAKE_PREFIX_PATH "/opt/homebrew/opt/cli11")
find_package(CLI11 CONFIG REQUIRED)
target_link_libraries(TemplateMaker PRIVATE CLI11::CLI11)


message(STATUS "The project has been configured")
