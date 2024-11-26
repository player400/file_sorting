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

void generateAndSort(int recordCount, bool doPrintRecords = true, bool manualRecords=false)
{
    std::string fileName = "original.nur";
    generateRecords(fileName, recordCount, manualRecords);
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
    while(true)
    {
        std::cout<<std::endl;
        std::cout<<"===== RUNNING EXPERIMENTS ====="<<std::endl;
        std::cout<<"Type 1 to do manual testing. 2 to run tests on randomly generated records. 3 to terminate."<<std::endl;
        int n;
        std::cin>>n;
        if(n==3)
        {
            break;
        }
        if(n==2)
        {
            std::cout<<"Type 1 to do the default range (100, 1000, 10000, 100000, 1000000). Or insert the number of records manually (has to be greater than 1)."<<std::endl;
            int m;
            std::cin >> m;
            if(m==1)
            {
                int recordCount [EXPERIMENTS] ={100, 1000, 10000, 100000, 1000000};
                system("clear");
                for(int i=0;i<EXPERIMENTS;i++)
                {
                    generateAndSort(recordCount[i], false, false);
                }
            }
            else
            {
                std::cout<<"Type 1 to print the results, 0 to not print the results."<<std::endl;
                int o;
                std::cin >> o;
                system("clear");
                generateAndSort(m, o, false);
            }

        }
        else
        {
            std::cout<<"How many records do you want?"<<std::endl;
            int m;
            std::cin >> m;
            system("clear");
            generateAndSort(m, true, true);
        }

    }
}
