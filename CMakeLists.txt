cmake_minimum_required(VERSION 3.7)
project(calc-tiulpin)
set(CMAKE_C_STANDARD 90)
include_directories(${SOURCE_FILES}sources)
include_directories(${SOURCE_FILES}headers)
set(SOURCE_FILES
        sources/ProcessLine.c
        sources/SortStation.c
        sources/Calculate.c
        sources/Stack.c
        sources/Main.c
        headers/SortStationOther.h
        headers/ProcessLine.h
        headers/SortStation.h
        headers/Operations.h
        headers/Calculate.h
        headers/Stack.h
        )
add_executable(calc-tiulpin ${SOURCE_FILES})
target_link_libraries(calc-tiulpin m)
include(PVS-Studio.cmake)
pvs_studio_add_target(calc-tiulpin analyze ALL
        OUTPUT FORMAT errorfile
        ANALYZE calc-tiulpin
        LOG calc-tiulpin.plog
        LICENSE "/home/tv/Documents/PVS-Studio/PVS-Studio.lic")
