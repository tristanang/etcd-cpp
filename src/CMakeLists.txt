cmake_minimum_required (VERSION 3.15.2)
project (etcd-cpp)

set(CMAKE_CXX_FLAGS "-Wall -std=c++11")
include_directories(${CMAKE_CURRENT_LIST_DIR}/../include/etcd-cpp/)

find_library(GRPC++_LIBRARY grpc++)
find_library(GRPC_LIBRARY grpc)

file(GLOB SRCS "*.cpp")
# file(GLOB HEADERS "${CMAKE_CURRENT_LIST_DIR}/../include/etcd-cpp/*.h")

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../serialize ${CMAKE_CURRENT_BINARY_DIR}/lib)

add_library(etcd_cpp SHARED ${SRCS})
add_dependencies(etcd_cpp serialize)

target_include_directories(etcd_cpp PUBLIC /usr/local/include)
target_link_libraries(etcd_cpp serialize ${GRPC++_LIBRARY} ${GRPC_LIBRARY})
