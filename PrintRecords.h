//
// Created by player402 on 24.11.24.
//

#ifndef P1_PRINTRECORDS_H
#define P1_PRINTRECORDS_H


#include <iostream>
#include "BufferRecordManager.h"
#include "BlockFileReader.h"

void printRecords(std::string fileName)
{
    BlockFileReader reader(fileName);
    uint8_t buffer[BLOCK_SIZE];
    reader.readBlock(0, buffer);
    uint64_t totalRecords = *((uint64_t*)buffer);
    int recordNumber = 0;
    for(int g=1;g<reader.size();g++)
    {
        int records = RECORDS_IN_BLOCK;
        if(g+1 == reader.size())
        {
            records = totalRecords%RECORDS_IN_BLOCK;
            if(records==0)
            {
                records = RECORDS_IN_BLOCK;
            }
        }
        reader.readBlock(g, buffer);
        int characterCount = 0;
        for(int i=0;i<records;i++) {
            std::cout<<recordNumber<<". ";
            for (int j = 0; j < RECORD_SIZE; j++)
            {
                std::cout<<buffer[characterCount];
                characterCount++;
            }
            std::cout<<std::endl;
            recordNumber++;
        }
    }
}

#endif //P1_PRINTRECORDS_H
