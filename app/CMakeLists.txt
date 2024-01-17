
add_executable(matrix_example examples/linalg/matrix_example.cpp)
target_link_libraries(matrix_example PUBLIC cTensor)
target_include_directories(matrix_example PUBLIC ${INCLUDE_DIR})

add_executable(network_example examples/linalg/network_example.cpp)
target_link_libraries(network_example PUBLIC cTensor)
target_include_directories(network_example PUBLIC ${INCLUDE_DIR})

