cmake_minimum_required(VERSION 3.10)
project(StockProgram)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(StockProgram
        nbproject/private/c_standard_headers_indexer.c
        nbproject/private/cpp_standard_headers_indexer.cpp
        Inventory.cpp
        Inventory.h
        StockItem.cpp
        StockItem.h
        StockProgram.cpp)
