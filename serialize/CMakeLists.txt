set(CMAKE_CXX_FLAGS "-Wall -Werror -std=c++11")

set(GRPC_DIR ${CMAKE_CURRENT_LIST_DIR})

find_package(GRPC REQUIRED)

include_directories(${PROTOBUF_INCLUDE_DIR})

file(GLOB PROTOS "*.proto")

grpc_generate_cpp(GRPC_SRC GRPC_HEADER ${PROTOS})

#Generate the static library from the sources
add_library(serialize STATIC ${GRPC_SRC})

target_link_libraries(serialize ${GRPC++_LIBRARIES})

file(MAKE_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/../include/etcd-cpp/protos)

#Custom command needs work
add_custom_command(TARGET serialize PRE_LINK
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/*.h ${CMAKE_CURRENT_LIST_DIR}/../include/etcd-cpp/protos)
