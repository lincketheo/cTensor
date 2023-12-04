add_subdirectory(Matrix Networks)

add_library(cTensor SHARED
        UI/driver.cpp
        Matrix/kernel.cpp
        Matrix/operations.cpp
        Networks/Network.cpp
        Data/dataHandler.cpp
)
target_include_directories(cTensor PUBLIC ${INCLUDE_DIR})

add_executable(runTheDamnNetwork runTheDamnNetwork.cpp)
target_link_libraries(runTheDamnNetwork PUBLIC cTensor)
target_include_directories(runTheDamnNetwork PUBLIC ${INCLUDE_DIR})

add_executable(run main.cpp)
target_link_libraries(run PUBLIC cTensor)
target_include_directories(run PUBLIC ${INCLUDE_DIR})

