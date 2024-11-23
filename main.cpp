#include <iostream>

#include "BlockFileReader.h"

int main() {
    uint8_t test1[512];
    uint8_t test2[512] = {0};

    for(int i=0;i<512;i++)
    {
        test1[i]=i;
    }
    test2[0]=232;
    test2[1]=233;
    test2[2]=234;
    test2[3]=235;
    uint8_t output[512];
    BlockFileReader reader("test.nur");
    /*reader.writeBlock(0, test1);
    reader.writeBlock(1, test1);
    reader.writeBlock(2, test1);*/
    reader.writeBlock(1, test2);

    std::cout<<"Start!"<<std::endl;
    for(int i=0;i<3;i++)
    {
        reader.readBlock(i, output);
        for(int j=0;j<512;j++)
        {
            std::cout<<(int)output[j]<<std::endl;
        }
    }
    return 0;
}
