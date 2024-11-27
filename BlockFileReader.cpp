//
// Created by player402 on 23.11.24.
//

#include <iostream>
#include "BlockFileReader.h"
#include "GeneralLogger.h"

const std::string& BlockFileReader::getFileName() const {
    return fileName;
}

BlockFileReader::BlockFileReader(const std::string &fileName, bool createNew) : fileName(fileName) {
    if(createNew)
    {
        fileHandle = std::fopen(fileName.c_str(), "w+");
    }
    else
    {
        fileHandle = std::fopen(fileName.c_str(), "r+");
        if(fileHandle==NULL)
        {
            fileHandle = std::fopen(fileName.c_str(), "w+");
        }
    }
}

BlockFileReader::~BlockFileReader() {
    if(fileHandle==NULL)
    {
        return;
    }
    std::fclose(fileHandle);
}

unsigned int BlockFileReader::readBlock(int blockNumber, uint8_t *outputArray) const {
    if(!moveFileCursor(blockNumber))
    {
        return 0;
    }
    GeneralLogger::readDiskPage();
    //std::cout<<fileName<<" reading"<<std::endl;
    return fread((void*)outputArray, 1, BLOCK_SIZE, fileHandle);
}

bool BlockFileReader::writeBlock(int blockNumber, uint8_t *inputArray) const {
    if(!moveFileCursor(blockNumber))
    {
        return false;
    }
    fwrite(inputArray, 1, BLOCK_SIZE, fileHandle);
    fflush(fileHandle);
    GeneralLogger::writeDiskPage();
    //std::cout<<fileName<<" writing"<<std::endl;
    return true;
}

bool BlockFileReader::moveFileCursor(int blockNumber) const {
    size_t minumumSizeIntended = (blockNumber+1)*BLOCK_SIZE;
    if(fseek(fileHandle, 0L, SEEK_END))
    {
        return false;
    }
    if(ftell(fileHandle)<minumumSizeIntended)
    {
        ftruncate((long int)fileHandle, minumumSizeIntended);
    }
    if(fseek(fileHandle, blockNumber*BLOCK_SIZE, SEEK_SET))
    {
        return false;
    }
    return true;
}

int BlockFileReader::size() const {
    fseek(fileHandle, 0L, SEEK_END);
    int size = ftell(fileHandle);
    return (size-1)/BLOCK_SIZE + 1;
}
