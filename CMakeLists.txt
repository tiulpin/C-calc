cmake_minimum_required(VERSION 3.7)
project(calc)
set(CMAKE_C_STANDARD 90)
include_directories(${SOURCE_FILES}sources)
include_directories(${SOURCE_FILES}headers)
set(SOURCE_FILES
        sources/Calculate.c
        sources/Main.c
        sources/ProcessLine.c
        sources/SortStation.c
        sources/Stack.c
        headers/Calculate.h
        headers/Operations.h
        headers/ProcessLine.h
        headers/SortStation.h
        headers/SortStationOther.h
        headers/Stack.h
        )
add_executable(calc ${SOURCE_FILES})
target_link_libraries(calc m)
include(PVS-Studio.cmake)
pvs_studio_add_target(calc analyze ALL
        OUTPUT FORMAT errorfile
        ANALYZE calc
        LOG calc-tiulpin.plog
        LICENSE "/home/tv/Documents/PVS-Studio/PVS-Studio.lic")
