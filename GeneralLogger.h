//
// Created by player402 on 25.11.24.
//

#ifndef P1_GENERALLOGGER_H
#define P1_GENERALLOGGER_H


struct GeneralLogger {

    static long long int diskPageWrites;
    static long long int diskPageReads;
    static long long int sortingPhases;


    static long long int getPageWrites();

    static long long int getPageReads();

    static long long int getSortingPhases();

    static void writeDiskPage();

    static void readDiskPage();

    static void sortingPhaseDone();

    static void reset();

};




#endif //P1_GENERALLOGGER_H
