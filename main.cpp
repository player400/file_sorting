#include <iostream>

#include "BlockFileReader.h"
#include "BufferRecordManager.h"
#include "RecordGenerator.h"
#include "PrintRecords.h"
#include "BlockSorter.h"
#include "Run.h"

int main() {

    generateRecords("test.nur", 1000);
    printRecords("test.nur");
    sortFileBlocks("test.nur");
    printRecords("test.nur");

    

    Run a(1, 2);
    Run b(3, 4);

    Run c = a+b;

    return 0;

}
