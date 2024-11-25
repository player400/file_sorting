//
// Created by player402 on 25.11.24.
//
#include "GeneralLogger.h"

long long int GeneralLogger::getPageWrites()
{
    return diskPageWrites;
}

long long int GeneralLogger::getPageReads()
{
    return diskPageReads;
}

long long int GeneralLogger::getSortingPhases()
{
    return sortingPhases;
}

void GeneralLogger::writeDiskPage()
{
    diskPageWrites++;
}

void GeneralLogger::readDiskPage()
{
    diskPageReads++;
}

void GeneralLogger::sortingPhaseDone()
{
    sortingPhases++;
}

void GeneralLogger::reset()
{
    sortingPhases = 0;
    diskPageReads = 0;
    diskPageWrites = 0;
}

long long int GeneralLogger::diskPageWrites = 0;
long long int GeneralLogger::diskPageReads = 0;
long long int GeneralLogger::sortingPhases = 0;