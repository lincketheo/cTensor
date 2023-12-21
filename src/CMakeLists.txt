add_library(linalg SHARED
        matrix.c
        basic_math/add.c
)
target_include_directories(linalg PUBLIC ${INCLUDE_DIR})
