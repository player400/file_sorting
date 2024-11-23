//
// Created by player402 on 23.11.24.
//

#include "BlockFileReader.h"

const std::string& BlockFileReader::getFileName() const {
    return fileName;
}

BlockFileReader::BlockFileReader(const std::string &fileName) : fileName(fileName) {
    fileHandle = std::fopen(fileName.c_str(), "r+");
    if(fileHandle==NULL)
    {
        fileHandle = std::fopen(fileName.c_str(), "w+");
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
    return fread((void*)outputArray, 1, BLOCK_SIZE, fileHandle);
}

bool BlockFileReader::writeBlock(int blockNumber, uint8_t *inputArray) const {
    if(!moveFileCursor(blockNumber))
    {
        return false;
    }
    fwrite(inputArray, 1, BLOCK_SIZE, fileHandle);
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
