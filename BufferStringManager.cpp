//
// Created by player402 on 23.11.24.
//

#include <bit>
#include "BufferStringManager.h"
#include "stdlib.h"

BufferStringManager::BufferStringManager(uint8_t* buffer, std::function<void(uint8_t*)> buffer_reading_function) {
    this->recordBuffer = buffer;
    buffer_reading_function(recordBuffer);
}

uint64_t BufferStringManager::operator[](int index) const {
    uint8_t* record = recordBuffer + index*RECORD_SIZE;
    uint64_t extractedRecord = *((uint64_t*)record);
    extractedRecord = std::byteswap(extractedRecord);
    extractedRecord = extractedRecord >> ((8 - RECORD_SIZE)*8);
    return extractedRecord;
}
