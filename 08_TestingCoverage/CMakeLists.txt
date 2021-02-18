cmake_minimum_required(VERSION 3.10)

project(UnitTests)
include(CTest)

set(CMAKE_C_FLAGS "-O0 -fprofile-arcs -ftest-coverage")
set(MAIN_GENERATES
        "CMakeFiles"
        "Testing"
        "cmake_install.cmake"
        "CMakeCache.txt"
        "CTestTestfile.cmake"
        "DartConfiguration.tcl"
        "Makefile"
        )
set(SRC_GENERATES
        "src/cmake-build-debug"
        "src/CMakeFiles"
        "src/Buf.cbp"
        "src/cmake_install.cmake"
        "src/CMakeCache.txt"
        "src/CTestTestfile.cmake"
        "src/libbuf.so"
        "src/Makefile"
        )
set(TEST_GENERATES
        "test/cmake-build-debug"
        "test/CMakeFiles"
        "test/Buf.cbp"
        "test/cmake_install.cmake"
        "test/CMakeCache.txt"
        "test/CTestTestfile.cmake"
        "test/tests"
        "test/Makefile"
        )

add_custom_target(
        allclean
        COMMAND rm -rf ${MAIN_GENERATES} ${SRC_GENERATES} ${TEST_GENERATES}
)

enable_testing()

add_subdirectory(src src)
add_subdirectory(test test)
