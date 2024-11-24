//
// Created by player402 on 23.11.24.
//

#ifndef P1_BUFFERRECORDMANAGER_H
#define P1_BUFFERRECORDMANAGER_H


#include <cstdint>
#include <functional>

#include "BlockFileReader.h"

#define RECORD_SIZE 7
#define RECORDS_IN_BLOCK (BLOCK_SIZE/RECORD_SIZE)

class BufferRecordManager {
    uint8_t* recordBuffer;
public:

    uint64_t operator[](int index) const;

    void writeRecord(uint64_t record, int index) const;

    BufferRecordManager(uint8_t* buffer, const std::function<void(uint8_t*)>& buffer_reading_function = [](uint8_t*){});
};


#endif //P1_BUFFERRECORDMANAGER_H
