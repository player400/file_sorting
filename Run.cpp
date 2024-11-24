//
// Created by player402 on 24.11.24.
//

#include <array>
#include "Run.h"

Run::Run(int startingBlock, int size) : startingBlock(startingBlock), size(size) {}

Run operator+(Run &left, Run &right) {
    return {std::min(left.startingBlock, right.startingBlock), left.size+right.size};
}

Run::Run(Run &old) {
    startingBlock = old.startingBlock;
    size = old.size;
}

Run::Run(Run &&old){
    startingBlock = old.startingBlock;
    size = old.size;
}

Run Run::operator=(Run &right) {
    return Run(right);
}

int Run::getStartingBlock() const {
    return startingBlock;
}

int Run::getSize() const {
    return size;
}
