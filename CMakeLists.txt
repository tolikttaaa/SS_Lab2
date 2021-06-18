cmake_minimum_required(VERSION 3.19)
project(System_Software_Lab2 C)

set(CMAKE_C_STANDARD 11)

add_library(
        ListModeLib
        SHARED
        utils.c list_mode.c fat32_lib.c ListModeLib.c
)

add_library(
        ScriptModeLib
        SHARED
        utils.c script_mode.c fat32_lib.c ScriptModeLib.c
)