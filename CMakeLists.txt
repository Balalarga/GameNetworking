cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(GameNetworking LANGUAGES CXX)

set(IS_MAIN_MODULE ${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
set(MAIN_SOURCE_DIR GameNetworking)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake)

find_package(fmt CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)
find_package(protobuf CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
add_subdirectory(GameNetworking/Proto)

# Source files
file(GLOB_RECURSE PROJECT_SOURCES
    ${MAIN_SOURCE_DIR}/*.cpp
    ${MAIN_SOURCE_DIR}/*.h
    ${MAIN_SOURCE_DIR}/*.hpp)

add_library(${PROJECT_NAME} STATIC
    ${PROJECT_SOURCES}
)
target_include_directories(${PROJECT_NAME} PRIVATE
    ${MAIN_SOURCE_DIR}
)
target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    GameNetworkingProto
    nlohmann_json::nlohmann_json
    gRPC::gpr
    gRPC::grpc
    gRPC::grpc++
    protobuf::libprotobuf
    gRPC::grpc++_alts
    fmt::fmt
)

if (${IS_MAIN_MODULE})
    add_subdirectory(Tests)
endif()

