//
// Created by player402 on 24.11.24.
//

#ifndef P1_TAPE_H
#define P1_TAPE_H

#include <cstdint>
#include "Run.h"
#include "BlockFileReader.h"
#include "BufferRecordManager.h"

class Tape {
private:
    int startingBlock;
    int size;
    uint8_t buffer[BLOCK_SIZE];
    int index = 0;
    int currentBuffer = 0;
public:
    int getSize() const;

private:
    int totalRecordsLeft = 0;
    BlockFileReader& sourceReader;
    BlockFileReader myFile;
    BufferRecordManager manager;
public:
    Tape(BlockFileReader &sourceReader, std::string operatingFile);

    void sortBlock(int records, uint8_t* buffer);

    bool isEmpty();

    uint64_t next();

    uint64_t popNext();

    int loadRun(int startingBlock, int totalSize, bool firstPhase = false);

};


#endif //P1_TAPE_H
