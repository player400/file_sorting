//
// Created by player402 on 24.11.24.
//

#include "Tape.h"




void Tape::loadRun(Run *run) {

    this->run = run;
    totalRecordsLeft = run->getSize();
    index = 0;
    currentBuffer = 0;
    for(int i=(run->getSize()-1)/RECORDS_IN_BLOCK; i>=0;i--)
    {
        sourceReader.readBlock(i+run->getStartingBlock(), buffer);
        myFile.writeBlock(i, buffer);
    }
}

Tape::Tape(BlockFileReader &sourceReader, std::string operatingFile) : sourceReader(sourceReader), myFile(operatingFile), manager(buffer) {}

uint64_t Tape::next() {
    return manager[index];
}

uint64_t Tape::popNext() {
    uint64_t result = manager[index];
    index++;
    if(index==RECORDS_IN_BLOCK)
    {
        currentBuffer++;
        myFile.readBlock(currentBuffer, buffer);
        index = 0;
    }
    totalRecordsLeft--;
    return result;
}

bool Tape::isEmpty() {
    if(totalRecordsLeft==0)
    {
        return true;
    }
    return false;
}
