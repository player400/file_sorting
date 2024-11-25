//
// Created by player402 on 24.11.24.
//

#include "OutputTape.h"

OutputTape::OutputTape(BlockFileReader &sourceFile) : sourceFile(sourceFile), manager(buffer) {}

void OutputTape::loadRun(Run *run) {
    this->run = run;
    index = 0;
    blockNumber=run->getStartingBlock();
    totalRecords=0;
}

void OutputTape::save(uint64_t record) {
    manager.writeRecord(record, index);
    index++;
    totalRecords++;
    if(index>=RECORDS_IN_BLOCK)
    {
        sourceFile.writeBlock( blockNumber, buffer);
        blockNumber++;
        index=0;
    }
    else if(totalRecords==run->getSize())
    {
        sourceFile.writeBlock( blockNumber, buffer);
    }
}
