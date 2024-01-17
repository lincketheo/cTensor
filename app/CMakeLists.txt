
add_executable(matrix_example examples/linalg/matrix_example.cpp)
target_link_libraries(matrix_example PUBLIC cTensor)
target_include_directories(matrix_example PUBLIC ${INCLUDE_DIR})

add_executable(network_example examples/linalg/network_example.cpp)
target_link_libraries(network_example PUBLIC cTensor)
target_include_directories(network_example PUBLIC ${INCLUDE_DIR})

add_executable(npz_example examples/linalg/npz_example.cpp)
target_link_libraries(npz_example PUBLIC cTensor)
target_include_directories(npz_example PUBLIC ${INCLUDE_DIR})


add_executable(mnist_example examples/linalg/mnist_example.cpp)
target_link_libraries(mnist_example PUBLIC cTensor)
target_include_directories(mnist_example PUBLIC ${INCLUDE_DIR})

add_executable(main examples/main.cpp)
target_link_libraries(main PUBLIC cTensor)
target_include_directories(main PUBLIC ${INCLUDE_DIR})
