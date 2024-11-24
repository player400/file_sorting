cmake_minimum_required(VERSION 3.27)
project(p1)

set(CMAKE_CXX_STANDARD 23)

add_executable(p1 main.cpp
        BlockFileReader.cpp
        BlockFileReader.h
        BufferRecordManager.cpp
        BufferRecordManager.h
        RecordGenerator.h
        BlockSorter.h
        PrintRecords.h
        Run.cpp
        Run.h)
