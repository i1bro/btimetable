cmake_minimum_required(VERSION 3.10)
project(btimetable)

set(CMAKE_CXX_STANDARD 20)

IF (WIN32)
    find_package(PostgreSQL REQUIRED)
    add_library(pqxx STATIC IMPORTED)
    set_target_properties(pqxx PROPERTIES IMPORTED_LOCATION ../../../lib/pqxx.lib)
    set(PQXX_LIB pqxx)
    set(PQ_LIB PostgreSQL::PostgreSQL)
ELSE()
    find_package(OpenSSL 1.0.2 REQUIRED)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpqxx -lpq -lcrypto -lssl")
    set(PQXX /usr/local/include/pqxx)
    find_library(PQXX_LIB pqxx)
    find_library(PQ_LIB pq)
ENDIF()

add_executable(init-db initDB.cpp)

target_link_libraries(init-db ${PQXX_LIB} ${PQ_LIB} OpenSSL::SSL OpenSSL::Crypto)
IF (WIN32)
    target_link_libraries(init-db ws2_32.lib)
ENDIF()
target_include_directories(init-db PRIVATE include include/postgresql)

add_executable(data-base-test
        testing/doctestMain.cpp
        testing/dataBaseTest.cpp
        src/ClientAPI.cpp
        src/CompanyAPI.cpp
        src/Storage.cpp
        src/Service.cpp)

target_link_libraries(data-base-test ${PQXX_LIB} ${PQ_LIB} OpenSSL::SSL OpenSSL::Crypto)
IF (WIN32)
    target_link_libraries(init-db ws2_32.lib)
ENDIF()
target_include_directories(data-base-test PRIVATE include include/postgresql)

add_library(btt STATIC
        src/ClientAPI.cpp
        src/CompanyAPI.cpp
        src/Service.cpp
        src/Storage.cpp)

target_link_libraries(btt ${PQXX_LIB} ${PQ_LIB} OpenSSL::SSL OpenSSL::Crypto)
IF (WIN32)
    target_link_libraries(init-db ws2_32.lib)
ENDIF()
target_include_directories(btt PRIVATE include include/postgresql)