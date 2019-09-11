cmake_minimum_required (VERSION 3.15.2)
project (etcd-cpp)

set(CMAKE_CXX_FLAGS "-Wall -std=c++11")

find_library(GRPC++_LIBRARY grpc++)
find_library(GRPC_LIBRARY grpc)
find_library(PROTOBUF_LIBRARY protobuf)

file(GLOB_RECURSE SRCS "*.cpp")
file(GLOB_RECURSE HEADERS "${CMAKE_CURRENT_LIST_DIR}/../include/etcd-cpp/*.h")

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../serialize ${CMAKE_BINARY_DIR}/lib)

add_library(etcd_cpp SHARED)
add_dependencies(etcd_cpp serialize)

target_sources(
    etcd_cpp
        PRIVATE
            ${SRCS}
        PUBLIC
            ${HEADERS})

target_include_directories(
    etcd_cpp
	   PUBLIC
	      $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../include/etcd-cpp>
          $<INSTALL_INTERFACE:include/etcd-cpp>
          /usr/local/include)

target_link_libraries(etcd_cpp serialize ${GRPC++_LIBRARY} ${GRPC_LIBRARY} ${PROTOBUF_LIBRARY})
