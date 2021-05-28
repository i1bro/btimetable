cmake_minimum_required(VERSION 3.10)
project(btimetable)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenSSL REQUIRED)

set(SOURCE
        src/ClientAPI.cpp
        src/CompanyAPI.cpp
        src/Storage.cpp
        src/Service.cpp)

set(HEADERS
        include/ClientAPI.h
        include/CompanyAPI.h
        include/Entities.h
        include/btt/Service.h
        include/btt/Storage.h)

set(INCLUDE_DIRS
        include include/postgresql)

IF (WIN32)
    find_package(PostgreSQL REQUIRED)
    add_library(pqxx STATIC IMPORTED)
    set_target_properties(pqxx PROPERTIES IMPORTED_LOCATION ../../../lib/pqxx.lib)
    set(PQXX_LIB pqxx)
    set(PQ_LIB PostgreSQL::PostgreSQL)
    set(LIBS ws2_32.lib)
ELSE ()
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpqxx -lpq -lcrypto -lssl")
    find_library(PQXX_LIB pqxx)
    find_library(PQ_LIB pq)
ENDIF ()

set(LIBS
        ${PQXX_LIB} ${PQ_LIB} OpenSSL::SSL OpenSSL::Crypto ${LIBS})

add_executable(init-db initDB.cpp)
target_link_libraries(init-db ${LIBS})
target_include_directories(init-db PRIVATE ${INCLUDE_DIRS})

add_executable(data-base-test
        testing/doctestMain.cpp
        testing/dataBaseTest.cpp
        ${SOURCE} ${HEADERS})
target_link_libraries(data-base-test ${LIBS})
target_include_directories(data-base-test PRIVATE ${INCLUDE_DIRS})

add_library(btt STATIC
        ${SOURCE} ${HEADERS})
target_link_libraries(btt ${LIBS})
target_include_directories(btt PRIVATE ${INCLUDE_DIRS})