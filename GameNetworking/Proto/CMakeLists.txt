find_package(protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)


file(GLOB_RECURSE PROTO_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.proto)


add_library(GameNetworkingProto ${PROTO_FILES})
target_link_libraries(GameNetworkingProto PUBLIC
    protobuf::libprotobuf
    gRPC::grpc
    gRPC::grpc++
)
target_include_directories(GameNetworkingProto PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

#
# Compile protobuf and grpc files in myproto target to cpp
#
get_target_property(grpc_cpp_plugin_location gRPC::grpc_cpp_plugin LOCATION)
protobuf_generate(TARGET GameNetworkingProto LANGUAGE cpp)
protobuf_generate(TARGET GameNetworkingProto
    LANGUAGE grpc
    GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc
    PLUGIN "protoc-gen-grpc=${grpc_cpp_plugin_location}")