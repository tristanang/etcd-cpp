file(GLOB TESTS "*UnitTest.cpp")

#include_directories(/usr/local/include)
find_library(GRPC++_LIBRARY grpc++)
find_library(GRPC_LIBRARY grpc)

add_executable(unit_tests ${TESTS})

add_dependencies(unit_tests etcd_cpp)

target_link_libraries(
    unit_tests
    gtest_main
    etcd_cpp
    ${GRPC++_LIBRARY}
    ${GRPC_LIBRARY}
    )

add_test(
  NAME
    unit
  COMMAND
    ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/unit_tests
  )
