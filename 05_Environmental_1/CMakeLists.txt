cmake_minimum_required(VERSION 3.10)

project(Environmental)

find_library(NCURSES ncursesw REQUIRED)
find_library(PCRE2 pcre2-8 REQUIRED)

option(without_UTF "Without UTF usage" OFF)
if(without-UTF)
    add_definitions(-DWITHOUT_UTF=1)
else()
    add_definitions(-DWITHOUT_UTF=0)
endif()

add_executable(Environmental main.c)
target_link_libraries(Environmental PUBLIC ncursesw)
target_link_libraries(Environmental PUBLIC pcre2-8)

add_custom_target(allclean COMMAND rm -rf build CMakeFiles cmake_install.cmake CMakeCache.txt Environmental Makefile Enviromental.cbp)
