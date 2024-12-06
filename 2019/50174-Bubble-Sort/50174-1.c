#include "BubbleSort.h"
#include <stdint.h>

void BubbleSort(uint64_t input, uint64_t output[63]){
    for(int i = 63; i > 0; i--){
        for(int j = 0; j < i; j++){
            if((input >> (63 - j)) & 1ULL){
                //swap
                uint64_t next = (input >> (62 - j)) & 1ULL;
                input &= ~(1ULL << (63 - j));
                input |= (next << (63 - j));
                input |= 1ULL << (62 - j);
            }
        }

        output[63 - i] = input;
    }

    return;
}