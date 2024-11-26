//
// Created by player402 on 24.11.24.
//

#include "Tape.h"




int Tape::loadRun(int startingBlock, int totalSize, uint8_t* blockCache, bool useCache, bool firstPhase) {

    this->startingBlock = startingBlock;
    this->size = 0;
    uint8_t transitionalBuffer[BLOCK_SIZE];
    if(useCache)
    {
        for(int i=0;i<BLOCK_SIZE;i++)
        {
            buffer[i] = blockCache[i];
        }
    }
    else
    {
        sourceReader.readBlock(startingBlock, buffer);
    }
    uint64_t greatestLast = 0;
    int firstBlockSize = RECORDS_IN_BLOCK;
    if(startingBlock+1==sourceReader.size())
    {
        firstBlockSize = totalSize % RECORDS_IN_BLOCK;
        if(firstBlockSize == 0)
        {
            firstBlockSize = RECORDS_IN_BLOCK;
        }
    }
    this->size += firstBlockSize;
    if(firstPhase)
    {
        sortBlock(firstBlockSize, buffer);
    }
    greatestLast = manager[firstBlockSize - 1];
    myFile.writeBlock(0, buffer);
    int pagesCopied = 1;
    BufferRecordManager transManager(transitionalBuffer);
    for(int i=startingBlock+1;i<sourceReader.size();i++)
    {
        sourceReader.readBlock(i, transitionalBuffer);
        int blockSize = RECORDS_IN_BLOCK;
        if(i+1==sourceReader.size())
        {
            blockSize = totalSize % RECORDS_IN_BLOCK;
            if(blockSize == 0)
            {
                blockSize = RECORDS_IN_BLOCK;
            }
        }
        if(firstPhase)
        {
            sortBlock(blockSize, transitionalBuffer);
        }
        if(transManager[0]<greatestLast)
        {
            for(int j=0;j<BLOCK_SIZE;j++)
            {
                blockCache[j] = transitionalBuffer[j];
            }
            break;
        }
        myFile.writeBlock(pagesCopied, transitionalBuffer);
        greatestLast = transManager[blockSize-1];
        this->size += blockSize;
        pagesCopied++;
    }
    totalRecordsLeft = this->size;
    index = 0;
    currentBuffer = 0;
    return startingBlock+pagesCopied;
}

Tape::Tape(BlockFileReader &sourceReader, std::string operatingFile) : sourceReader(sourceReader), myFile(operatingFile, true), manager(buffer) {}

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

void Tape::sortBlock(int records, uint8_t* buffer) {
    BufferRecordManager manager(buffer);
    for(int j=0;j<records;j++)
    {
        for(int k=0; k<records-1; k++)
        {
            if(manager[k]>manager[k+1])
            {
                uint64_t temp = manager[k];
                manager.writeRecord(manager[k+1], k);
                manager.writeRecord(temp, k+1);
            }
        }
    }
}

int Tape::getSize() const {
    return size;
}
