cmake_minimum_required(VERSION 3.10)

project(Localized)

add_custom_target(allclean COMMAND rm -rf CMakeCache.txt CMakeFiles cmake_install.cmake Makefile Localized ru)

add_custom_target(
        new.pot
        ALL
        DEPENDS main.c
        COMMAND xgettext main.c -k_ -o main.pot
)
add_custom_target(
        ru.po
        ALL
        DEPENDS main.pot main.c
        COMMAND msgmerge -U ru.po main.pot
)
add_custom_target(
        prog.mo
        ALL
        DEPENDS ru.po
        COMMAND mkdir -p ru/LC_MESSAGES/
        COMMAND msgfmt ru.po -o ru/LC_MESSAGES/this.mo
)

add_executable(Localized main.c)