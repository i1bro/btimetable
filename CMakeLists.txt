cmake_minimum_required(VERSION 3.10)
project(btimetable)

set(CMAKE_CXX_STANDARD 20)

add_library(hiredis STATIC IMPORTED)
set_target_properties(hiredis PROPERTIES IMPORTED_LOCATION ../lib/libhiredis.a)
add_library(redis++ STATIC IMPORTED)
set_target_properties(redis++ PROPERTIES IMPORTED_LOCATION ../lib/libredis++.a)

add_executable(btimetable main.cpp
        include/ClientAPI.h
        include/CompanyAPI.h
        include/Entities.h
        src/Storage.cpp
        src/Service.cpp)

add_library(btt STATIC
        include/ClientAPI.h
        include/CompanyAPI.h
        include/Entities.h
        src/Service.cpp)

target_link_libraries(btimetable PRIVATE hiredis)
target_link_libraries(btimetable PRIVATE redis++)
target_include_directories(btimetable PRIVATE include)
target_link_libraries(btt PRIVATE hiredis)
target_link_libraries(btt PRIVATE redis++)
target_include_directories(btt PRIVATE include)