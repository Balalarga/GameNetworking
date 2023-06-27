cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(GameNetworking LANGUAGES CXX)

set(IS_MAIN_MODULE ${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_SOURCE_DIR})


if (EXISTS ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json)
    add_custom_target(compile_commands_link ALL
        COMMAND ${CMAKE_COMMAND} -E create_hardlink ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
        ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json)
endif()

set(MAIN_SOURCE_DIR GameNetworking)

# Source files
file(GLOB_RECURSE PROJECT_SOURCES
    ${MAIN_SOURCE_DIR}/*.cpp
    ${MAIN_SOURCE_DIR}/*.h
    ${MAIN_SOURCE_DIR}/*.hpp)


add_library(${PROJECT_NAME} STATIC
    ${PROJECT_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE
    ${MAIN_SOURCE_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/asio/asio/include)


if (${IS_MAIN_MODULE})
    add_subdirectory(Tests)
endif()
