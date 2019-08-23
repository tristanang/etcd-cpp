set(CMAKE_CXX_FLAGS "-Wall -std=c++11")

set(GRPC_DIR ${CMAKE_CURRENT_LIST_DIR})

#find_package(Protobuf REQUIRED)
find_package(GRPC REQUIRED)

include_directories(${PROTOBUF_INCLUDE_DIR})

file(GLOB PROTOS "*.proto")

#protobuf_generate_cpp(PROTO_SRC PROTO_HEADER ${PROTOS})
grpc_generate_cpp(GRPC_SRC GRPC_HEADER ${PROTOS})

#Generate the static library from the sources
add_library(serialize STATIC ${PROTO_HEADER} ${PROTO_SRC} ${GRPC_HEADER} ${GRPC_SRC})

target_link_libraries(serialize ${GRPC++_LIBRARY})
