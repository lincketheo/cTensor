add_library(cTensor SHARED
        UI.cpp
        Matrix.cpp
        Network.cpp
        training.cpp
)
target_include_directories(cTensor PUBLIC ${INCLUDE_DIR})
