#include <iostream>

#include "BlockFileReader.h"
#include "BufferRecordManager.h"
#include "RecordGenerator.h"
#include "PrintRecords.h"
#include "BlockSorter.h"

int main() {

    generateRecords("test.nur", 1000);
    printRecords("test.nur");
    sortFileBlocks("test.nur");
    printRecords("test.nur");
    return 0;
}
