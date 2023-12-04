
add_executable(runTheDamnNetwork runTheDamnNetwork.cpp)
target_link_libraries(runTheDamnNetwork PUBLIC cTensor)
target_include_directories(runTheDamnNetwork PUBLIC ${INCLUDE_DIR})

add_executable(run main.cpp)
target_link_libraries(run PUBLIC cTensor)
target_include_directories(run PUBLIC ${INCLUDE_DIR})
