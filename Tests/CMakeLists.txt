cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(GameNetworkingTests LANGUAGES CXX)

add_executable(TestClient TestClient.cpp)
add_executable(TestServer TestServer.cpp)
target_link_libraries(TestClient PRIVATE GameNetworking)
target_link_libraries(TestServer PRIVATE GameNetworking)

target_link_libraries(TestClient PUBLIC
    nlohmann_json::nlohmann_json
    gRPC::gpr
    gRPC::grpc
    gRPC::grpc++
    protobuf::libprotobuf
    gRPC::grpc++_alts
    fmt::fmt
)
target_link_libraries(TestServer PUBLIC
    nlohmann_json::nlohmann_json
    gRPC::gpr
    gRPC::grpc
    gRPC::grpc++
    protobuf::libprotobuf
    gRPC::grpc++_alts
    fmt::fmt
)