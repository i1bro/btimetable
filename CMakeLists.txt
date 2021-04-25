cmake_minimum_required(VERSION 3.10)
project(btimetable)

set(CMAKE_CXX_STANDARD 20)

add_library(hiredis STATIC IMPORTED)
set_target_properties(hiredis PROPERTIES IMPORTED_LOCATION ../lib/libhiredis.a)
add_library(redis++ STATIC IMPORTED)
set_target_properties(redis++ PROPERTIES IMPORTED_LOCATION ../lib/libredis++.a)

add_executable(btimetable main.cpp
        #src/ModuleSelector.cpp
        src/dataBase/ClientAPI.h
        src/dataBase/CompanyAPI.h
        src/dataBase/EntryPoint.cpp
        #src/AddingEvents.cpp
        #src/booking/BookingModule.cpp
        src/dataBase/Entities.h
        #src/dataBase/TestDataBase.cpp
        src/dataBase/Storage.cpp
        src/dataBase/Service.cpp)

add_library(backend STATIC
        src/dataBase/ClientAPI.h
        src/dataBase/CompanyAPI.h
        src/dataBase/Entities.h
        src/dataBase/Service.cpp)

target_link_libraries(btimetable PRIVATE hiredis)
target_link_libraries(btimetable PRIVATE redis++)
target_include_directories(btimetable PRIVATE include)
target_link_libraries(backend PRIVATE hiredis)
target_link_libraries(backend PRIVATE redis++)
target_include_directories(backend PRIVATE include)