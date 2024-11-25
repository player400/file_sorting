//
// Created by player402 on 24.11.24.
//

#ifndef P1_BLOCKSORTER_H
#define P1_BLOCKSORTER_H

#include "BufferRecordManager.h"
#include "BlockFileReader.h"

void sortFileBlocks(std::string fileName)
{
    BlockFileReader reader(fileName);
    uint8_t buffer[BLOCK_SIZE];
    reader.readBlock(0, buffer);
    uint64_t totalRecords = *((uint64_t*)buffer);
    for(int i=1;i<reader.size();i++)
    {
        int records = RECORDS_IN_BLOCK;
        if(i+1 == reader.size())
        {
            records = totalRecords%RECORDS_IN_BLOCK;
            if(records==0)
            {
                records = RECORDS_IN_BLOCK;
            }
        }
        BufferRecordManager block(buffer, [i, &reader](uint8_t* buff) {reader.readBlock(i, buff);});
        for(int j=0;j<records;j++)
        {
            for(int k=0; k<records-1; k++)
            {
                if(block[k]>block[k+1])
                {
                    uint64_t temp = block[k];
                    block.writeRecord(block[k+1], k);
                    block.writeRecord(temp, k+1);
                }
            }
        }
        reader.writeBlock(i, buffer);
    }
}

#endif //P1_BLOCKSORTER_H
