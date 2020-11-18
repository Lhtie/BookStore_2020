cmake_minimum_required(VERSION 3.17)
project(BookStore_2020)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast")

add_executable(code main.cpp IO_UnrolledLinkedList.cpp Command_User.cpp Command_Book.cpp IO_Data.cpp BasicFunc.cpp)
