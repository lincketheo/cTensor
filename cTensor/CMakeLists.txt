add_library(cTensor SHARED
        src/Matrix.cpp
        src/Network.cpp
        src/Matlib.cpp
        src/NPZReader.cpp
        src/MNistLoader.cpp
)

find_package(ZLIB REQUIRED)
include_directories(${ZLIB_INCLUDE_DIRS})
target_link_libraries(cTensor ${ZLIB_LIBRARIES})

include_directories(include)
target_include_directories(cTensor PUBLIC include)