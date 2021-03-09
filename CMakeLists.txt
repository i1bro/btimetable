cmake_minimum_required(VERSION 3.10)
project(btimetable)

set(CMAKE_CXX_STANDARD 20)

find_library(HIREDIS hiredis lib)
find_library(REDIS++ redis++ lib)

add_executable(btimetable main.cpp
        src/ModuleSelector.cpp
        src/dataBase/EntryPoint.cpp
        src/AddingEvents.cpp
        src/booking/BookingModule.cpp
        src/dataBase/Entities.cpp
        src/dataBase/TestDataBase.cpp
        src/dataBase/Storage.cpp
        src/dataBase/Service.cpp)

target_link_libraries(btimetable PUBLIC ${HIREDIS})
target_link_libraries(btimetable PUBLIC ${REDIS++})
target_include_directories(btimetable PUBLIC include)