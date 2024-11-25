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

void sort(std::string fileName)
{
    std::list<Run>* runs = new std::list<Run>;
    BlockFileReader reader(fileName);
    sortFileBlocks(fileName);
    uint8_t buffer[BLOCK_SIZE];
    reader.readBlock(0, buffer);
    uint64_t totalCount = *((uint64_t*)buffer);
    for(int i=1;i<reader.size();i++)
    {
        int size = RECORDS_IN_BLOCK;
        if(i+1 == reader.size())
        {
            size = totalCount%RECORDS_IN_BLOCK;
            if(size == 0)
            {
                size = RECORDS_IN_BLOCK;
            }
        }
        runs->emplace_back(i, size);
    }

    Tape tape1(reader, "tape1.tape");
    Tape tape2(reader, "tape2.tape");

    OutputTape outputTape(reader);

    while(true)
    {
        auto* tempRuns = new std::list<Run>;
        while(runs->size()>=2)
        {
            Run a = runs->front();
            runs->pop_front();
            Run b = runs->front();
            runs->pop_front();
            Run ab = a+b;
            tape1.loadRun(&a);
            tape2.loadRun(&b);
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
            tempRuns->emplace_back(ab.getStartingBlock(), ab.getSize());
        }
        if(runs->size()==1)
        {
            Run c = runs->front();
            tempRuns->emplace_back(c.getStartingBlock(), c.getSize());
        }
        delete runs;
        runs = tempRuns;
        if(runs->size()==1)
        {
            break;
        }
    }
    delete runs;
}

#endif //P1_SORTING_H
