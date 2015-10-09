#include "CoreGraphicsHelpers.hpp"


int main(int argc, char *argv[])
{
    for(auto i = 0; i< 1000; i++ ) {
        deallocateImageBuffer(getImageAsBuffer(149).mutableDataRef);
    }
    return 0;
}
