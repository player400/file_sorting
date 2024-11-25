//
// Created by player402 on 24.11.24.
//

#ifndef P1_RECORDGENERATOR_H
#define P1_RECORDGENERATOR_H


#include "BlockFileReader.h"
#include "BufferRecordManager.h"

char randomLetter()
{
    int letterSpace = ('Z'-'A')+1;
    return rand()%letterSpace + 'A';
}

char randomCharacter()
{
    int letterSpace = ('Z'-'A')+1;
    int numberSpace = 1+('9'-'0');
    int space = letterSpace + numberSpace;
    char result = rand()%space;
    if(result>=letterSpace)
    {
        result-=letterSpace;
        result+='0';
    }
    else
    {
        result+='A';
    }
    return result;
}

void generateRecords(std::string fileName, int recordCount, bool manualInsert=false)
{
    srand(0);
    BlockFileReader writer(fileName, true);
    uint8_t buffer[BLOCK_SIZE];
    int recordsGenerated;
    int blockNumber =1;
    while(true)
    {
        BufferRecordManager bufferManager(buffer);
        for(int i=0;i<RECORDS_IN_BLOCK;i++)
        {
            char manualRecord[RECORD_SIZE+1];
            if(manualInsert)
            {
                std::cout<<"Please Insert record "<<recordsGenerated<<": ";
                std::cin>>manualRecord;
            }
            uint64_t newRecord = 0;
            for(int j=0;j<RECORD_SIZE;j++)
            {
                newRecord = newRecord << 8;
                if(manualInsert)
                {
                    newRecord = newRecord | manualRecord[j];
                }
                else
                {
                    if(j<3)
                    {
                        newRecord = newRecord | randomLetter();
                    }
                    else
                    {
                        newRecord = newRecord | randomCharacter();
                    }
                }
            }
            bufferManager.writeRecord(newRecord, i);
            recordsGenerated++;
            if(recordsGenerated==recordCount)
            {
                break;
            }
        }
        writer.writeBlock(blockNumber, buffer);
        if(recordsGenerated==recordCount)
        {
            break;
        }
        blockNumber++;
    }
    *((uint64_t*)buffer) = recordCount;
    writer.writeBlock(0, buffer);

}


#endif //P1_RECORDGENERATOR_H
