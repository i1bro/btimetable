cmake_minimum_required(VERSION 3.10)
project(btimetable)

set(CMAKE_CXX_STANDARD 20)

add_executable(btimetable main.cpp)
add_executable(src/ModuleSelector.cpp src/ModuleSelector.h)
add_executable(src/dataBase/EntryPoint.cpp src/dataBase/EntryPoint.h)
add_executable(src/booking/BookingModule.cpp src/booking/BookingModule.h)
add_executable(src/dataBase/Entities.h src/dataBase/Entities.cpp)
add_executable(src/dataBase/TestDataBase.cpp src/dataBase/TestDataBase.h)
add_executable(src/AddingEvents.cpp src/AddingEvents.h)
