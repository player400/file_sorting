//
// Created by player402 on 23.11.24.
//

#include <bit>
#include "BufferRecordManager.h"
#include "stdlib.h"

BufferRecordManager::BufferRecordManager(uint8_t* buffer, const std::function<void(uint8_t*)>& buffer_reading_function) {
    this->recordBuffer = buffer;
    buffer_reading_function(recordBuffer);
}

uint64_t BufferRecordManager::operator[](int index) const {
    uint8_t* record = recordBuffer + index*RECORD_SIZE;
    uint64_t extractedRecord = *((uint64_t*)record);
    extractedRecord = std::byteswap(extractedRecord);
    extractedRecord = extractedRecord >> ((8 - RECORD_SIZE)*8);
    return extractedRecord;
}

void BufferRecordManager::writeRecord(uint64_t record, int index) const {
    record = record << ((8-RECORD_SIZE)*8);
    record = std::byteswap(record);
    uint64_t* recordSpot = (uint64_t*)(recordBuffer + index*RECORD_SIZE);
    *recordSpot = *recordSpot & 0xFF00000000000000;
    *recordSpot = *recordSpot | record;

}
