//
// Created by player402 on 24.11.24.
//

#ifndef P1_SORTING_H
#define P1_SORTING_H

#include <string>
#include <algorithm>
#include <list>
#include "Run.h"
#include "BlockFileReader.h"
#include "BlockSorter.h"
#include "PrintRecords.h"
#include "Tape.h"
#include "OutputTape.h"
#include "GeneralLogger.h"

void sort(std::string fileName)
{
    BlockFileReader reader(fileName);
    uint8_t buffer[BLOCK_SIZE];
    reader.readBlock(0, buffer);
    uint64_t totalCount = *((uint64_t*)buffer);

    if(reader.size()<=2)
    {
        sortFileBlocks(fileName, 1, totalCount);
        return;
    }

    Tape tape1(reader, "tape1.tape");
    Tape tape2(reader, "tape2.tape");

    OutputTape outputTape(reader);
    uint8_t blockCache[BLOCK_SIZE];
    int phases = 1;
    while(true)
    {
        bool sortingDone = false;
        int nextRun=1;
        do
        {
            int outputRun = nextRun;
            bool wasOne = nextRun==1;
            nextRun = tape1.loadRun(nextRun, totalCount, blockCache, nextRun!=1,phases == 1);
            if(nextRun == reader.size())
            {

                break;
            }
            nextRun = tape2.loadRun(nextRun, totalCount, blockCache, nextRun!=1, phases == 1);
            if(nextRun==reader.size())
            {
                if(wasOne)
                {
                    sortingDone= true;
                }
            }
            Run ab(outputRun, tape1.getSize()+tape2.getSize());
            outputTape.loadRun(&ab);
            while(!tape1.isEmpty() || !tape2.isEmpty())
            {
                if(tape1.isEmpty())
                {
                    outputTape.save(tape2.popNext());
                }
                else if(tape2.isEmpty())
                {
                    outputTape.save(tape1.popNext());
                }
                else
                {
                    if(tape1.next() < tape2.next())
                    {
                        outputTape.save(tape1.popNext());
                    }
                    else
                    {
                        outputTape.save(tape2.popNext());
                    }
                }
            }
        } while(nextRun+1<reader.size());
        if(phases==1 && nextRun+1 == reader.size())
        {
            sortFileBlocks(fileName, nextRun, totalCount);
        }
        phases++;
        GeneralLogger::sortingPhaseDone();
        if(sortingDone)
        {
            break;
        }

    }
}

#endif //P1_SORTING_H
