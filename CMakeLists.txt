cmake_minimum_required(VERSION 3.10)
project(btimetable)

set(CMAKE_CXX_STANDARD 20)

add_executable(btimetable main.cpp src/ModuleSelector.cpp src/ModuleSelector.h src/dataBase/EntryPoint.cpp src/dataBase/EntryPoint.h src/booking/BookingModule.cpp src/booking/BookingModule.h src/dataBase/Entities.h src/dataBase/Entities.cpp src/dataBase/TestDataBase.cpp src/dataBase/TestDataBase.h)
