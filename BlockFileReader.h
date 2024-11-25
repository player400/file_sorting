//
// Created by player402 on 23.11.24.
//

#ifndef P1_BLOCKFILEREADER_H
#define P1_BLOCKFILEREADER_H


#include <string>
#include <cstdio>
#include <unistd.h>

#define BLOCK_SIZE 512

class BlockFileReader {
private:
    std::string fileName;
    FILE* fileHandle;

    bool moveFileCursor(int blockNumber) const;
public:
    const std::string& getFileName() const;

    int size() const;

    unsigned int readBlock(int blockNumber, uint8_t* outputArray) const;

    bool writeBlock(int blockNumber, uint8_t* inputArray) const;

    virtual ~BlockFileReader();

    explicit BlockFileReader(const std::string &fileName, bool createNew=false);
};


#endif //P1_BLOCKFILEREADER_H
