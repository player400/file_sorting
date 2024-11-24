//
// Created by player402 on 23.11.24.
//

#ifndef P1_BUFFERSTRINGMANAGER_H
#define P1_BUFFERSTRINGMANAGER_H


#include <cstdint>
#include <functional>

#include "BlockFileReader.h"

#define RECORD_SIZE 7
#define RECORDS_IN_BLOCK (BLOCK_SIZE/RECORD_SIZE)

class BufferStringManager {
    uint8_t* recordBuffer;
public:

    uint64_t operator[](int index) const;

    BufferStringManager(uint8_t* buffer, std::function<void(uint8_t*)> buffer_reading_function);
};


#endif //P1_BUFFERSTRINGMANAGER_H
