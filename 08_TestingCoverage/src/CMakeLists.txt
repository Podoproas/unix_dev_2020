cmake_minimum_required(VERSION 3.10)

project(Buf)
add_library(buf SHARED buf.c)

add_custom_target(clean_src COMMAND rm -rf
        cmake-build-debug
        CMakeFiles
        Buf.cbp
        cmake_install.cmake
        CMakeCache.txt
        CTestTestfile.cmake
        libbuf.so
        Makefile
        )
