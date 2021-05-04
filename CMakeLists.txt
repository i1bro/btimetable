cmake_minimum_required(VERSION 3.10)
project(btimetable)

set(CMAKE_CXX_STANDARD 20)

add_library(hiredis STATIC IMPORTED)
add_library(redis++ STATIC IMPORTED)

IF (WIN32)
    set_target_properties(hiredis PROPERTIES IMPORTED_LOCATION ../../../lib/hiredis_static.lib)
    set_target_properties(redis++ PROPERTIES IMPORTED_LOCATION ../../../lib/redis++_static.lib)
ELSE()
    set_target_properties(redis++ PROPERTIES IMPORTED_LOCATION ../lib/libredis++.a)
    set_target_properties(hiredis PROPERTIES IMPORTED_LOCATION ../lib/libhiredis.a)
ENDIF()

add_executable(data-base-test
        testing/doctestMain.cpp
        testing/dataBaseTest.cpp
        src/ClientAPI.cpp
        src/CompanyAPI.cpp
        src/Storage.cpp
        src/Service.cpp)

target_link_libraries(data-base-test PRIVATE hiredis)
target_link_libraries(data-base-test PRIVATE redis++)
target_include_directories(data-base-test PRIVATE include)

add_library(btt STATIC
        src/ClientAPI.cpp
        src/CompanyAPI.cpp
        src/Service.cpp
        src/Storage.cpp)

target_link_libraries(btt PRIVATE hiredis)
target_link_libraries(btt PRIVATE redis++)
target_include_directories(btt PRIVATE include)