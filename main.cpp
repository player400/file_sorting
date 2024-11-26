#include <iostream>

#include "BlockFileReader.h"
#include "BufferRecordManager.h"
#include "RecordGenerator.h"
#include "PrintRecords.h"
#include "BlockSorter.h"
#include "Run.h"
#include "Sorting.h"
#include "GeneralLogger.h"

#define EXPERIMENTS 5

void generateAndSort(int recordCount, bool doPrintRecords = true)
{

    std::string fileName = "original.nur";
    generateRecords(fileName, recordCount, false);
    std::cout<<std::endl;
    std::cout<<"===== SORTING "<<recordCount<<" RECORDS ====="<<std::endl;
    if(doPrintRecords)
    {
        std::cout<<"Unsorted:"<<std::endl;
        printRecords(fileName);
    }
    GeneralLogger::reset();
    sort(fileName);
    long long int pageReads = GeneralLogger::getPageReads();
    long long int pageWrites = GeneralLogger::getPageWrites();
    long long int sortingPhases = GeneralLogger::getSortingPhases();
    if(doPrintRecords)
    {
        std::cout<<"Sorted:"<<std::endl;
        printRecords(fileName);
    }
    std::cout<<"Finished!"<<std::endl;
    std::cout<<"Page reads conducted: "<<pageReads<<std::endl;
    std::cout<<"Page writes conducted: "<<pageWrites<<std::endl;
    std::cout<<"Sorting phases: "<<sortingPhases<<std::endl;
}


int main() {
    int recordCount [EXPERIMENTS] ={100, 1000, 10000, 100000, 1000000};
    for(int i=0;i<EXPERIMENTS;i++)
    {
        generateAndSort(recordCount[i], false);
    }
    return 0;
}
