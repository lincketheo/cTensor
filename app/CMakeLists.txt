
add_executable(matrix_demo matrix_demo.c)
target_link_libraries(matrix_demo PUBLIC linalg)
target_include_directories(matrix_demo PUBLIC ${INCLUDE_DIR})
