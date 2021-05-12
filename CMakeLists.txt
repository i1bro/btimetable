cmake_minimum_required(VERSION 3.10)
project(btimetable)

set(CMAKE_CXX_STANDARD 20)

add_library(hiredis STATIC IMPORTED)
add_library(redis++ STATIC IMPORTED)
#find_package(PostgreSQL REQUIRED)
#find_package(libpqxx REQUIRED)
#add_library(pqxx STATIC IMPORTED)
#add_library(pq STATIC IMPORTED)

IF (WIN32)
    set_target_properties(hiredis PROPERTIES IMPORTED_LOCATION ../../../lib/hiredis_static.lib)
    set_target_properties(redis++ PROPERTIES IMPORTED_LOCATION ../../../lib/redis++_static.lib)
    #set_target_properties(pqxx PROPERTIES IMPORTED_LOCATION ../../../lib/pqxx.lib)
ELSE()
    set_target_properties(redis++ PROPERTIES IMPORTED_LOCATION ../lib/libredis++.a)
    set_target_properties(hiredis PROPERTIES IMPORTED_LOCATION ../lib/libhiredis.a)
    #set_target_properties(pqxx PROPERTIES IMPORTED_LOCATION ../lib/libpqxx-7.5.a)
    #set_target_properties(pq PROPERTIES IMPORTED_LOCATION ../lib/libpq.a)
ENDIF()

add_executable(init-db initDB.cpp)

target_link_libraries(init-db pqxx pq)
target_include_directories(init-db PRIVATE include include/postgresql)

add_executable(data-base-test
        testing/doctestMain.cpp
        testing/dataBaseTest.cpp
        src/ClientAPI.cpp
        src/CompanyAPI.cpp
        src/Storage.cpp
        src/Service.cpp)

target_link_libraries(data-base-test hiredis redis++)
target_include_directories(data-base-test PRIVATE include)

add_library(btt STATIC
        src/ClientAPI.cpp
        src/CompanyAPI.cpp
        src/Service.cpp
        src/Storage.cpp)

target_link_libraries(btt hiredis redis++)
target_include_directories(btt PRIVATE include)