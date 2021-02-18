cmake_minimum_required(VERSION 3.10)

project(tests)

add_custom_target(clean_test COMMAND rm -rf
        cmake-build-debug
        CMakeFiles
        Buf.cbp
        cmake_install.cmake
        CMakeCache.txt
        CTestTestfile.cmake
        tests
        Makefile
        )


include_directories("../src")
link_directories("../src")

add_executable(tests main.c)
target_link_libraries(tests PUBLIC buf)

add_test(capacity_init tests 1)
add_test(size_init tests 2)
add_test(size_1 tests 3)
add_test(value tests 4)
add_test(clear tests 5)
add_test(clear_not-free tests 6)
add_test(free tests 7)
add_test(clear_empty tests 8)
add_test(clear_no-op tests 9)
add_test(size_10000 tests 10)
add_test(match_10000 tests 11)
add_test(grow_1000 tests 12)
add_test(size_0_grow tests 13)
add_test(trunc_100 tests 14)
add_test(size_4 tests 15)
add_test(pop_3 tests 16)
add_test(size_3 tests 17)
add_test(pop_2 tests 18)
add_test(pop_1 tests 19)
add_test(pop_0 tests 20)
add_test(size_0_pop tests 21)
