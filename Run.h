//
// Created by player402 on 24.11.24.
//

#ifndef P1_RUN_H
#define P1_RUN_H


class Run {
    int startingBlock;
public:
    int getStartingBlock() const;

    int getSize() const;

private:
    int size;

public:
    friend Run operator+(Run& left, Run& right);

    Run operator=(Run& right);

    Run(Run& old);

    Run(Run&& old);

    Run(int startingBlock, int size);
};


#endif //P1_RUN_H
