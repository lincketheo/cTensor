include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
        test
        Matrix.cpp
)
target_link_libraries(
        test
        GTest::gtest_main
        cTensor
)
target_include_directories(test PUBLIC include)

include(GoogleTest)
gtest_discover_tests(test)
