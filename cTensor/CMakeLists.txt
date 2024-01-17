add_library(cTensor SHARED
        src/Matrix.cpp
        include/Common.h
        src/Network.cpp
        include/Network.h
        include/Matlib.h
        src/Matlib.cpp
)

include_directories(include)
target_include_directories(cTensor PUBLIC include)