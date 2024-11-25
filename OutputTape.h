//
// Created by player402 on 24.11.24.
//

#ifndef P1_OUTPUTTAPE_H
#define P1_OUTPUTTAPE_H


#include "BlockFileReader.h"
#include "Run.h"
#include "BufferRecordManager.h"

class OutputTape {
    BlockFileReader& sourceFile;
    BufferRecordManager manager;
    Run* run;
    uint8_t buffer[BLOCK_SIZE];
    int index = 0;
    int blockNumber=0;
    int totalRecords = 0;
public:
    void save(uint64_t record);

    void loadRun(Run* run);

    OutputTape(BlockFileReader &sourceFile);
};


#endif //P1_OUTPUTTAPE_H
