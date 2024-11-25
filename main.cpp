#include <iostream>

#include "BlockFileReader.h"
#include "BufferRecordManager.h"
#include "RecordGenerator.h"
#include "PrintRecords.h"
#include "BlockSorter.h"
#include "Run.h"
#include "Sorting.h"

int main() {

    generateRecords("test.nur", 1000);
    printRecords("test.nur");
    sort("test.nur");
    printRecords("test.nur");


    return 0;

}
