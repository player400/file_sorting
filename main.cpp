#include <iostream>

#include "BlockFileReader.h"
#include "BufferRecordManager.h"
#include "RecordGenerator.h"
#include "PrintRecords.h"
#include "BlockSorter.h"
#include "Run.h"
#include "Sorting.h"
#include "GeneralLogger.h"

void generateAndSort(int recordCount, bool doPrintRecords = true)
{

    std::string fileName = "original.nur";
    generateRecords(fileName, recordCount);
    if(doPrintRecords)
    {
        printRecords(fileName);
    }
    GeneralLogger::reset();
    sort(fileName);
    long long int pageReads = GeneralLogger::getPageReads();
    long long int pageWrites = GeneralLogger::getPageWrites();
    long long int sortingPhases = GeneralLogger::getSortingPhases();
    if(doPrintRecords)
    {
        printRecords(fileName);
    }
    std::cout<<std::endl;
    std::cout<<"===== SORTING "<<recordCount<<" RECORDS ====="<<std::endl;
    std::cout<<"Page reads conducted: "<<pageReads<<std::endl;
    std::cout<<"Page writes conducted: "<<pageWrites<<std::endl;
    std::cout<<"Sorting phases: "<<sortingPhases<<std::endl;
}


int main() {
    generateAndSort(1000);
    return 0;
}
