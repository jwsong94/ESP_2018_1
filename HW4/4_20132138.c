#include <stdio.h>
#include <pigpiod_if2.h>
#include "74hc595_functions.h"

// HW4 : 
// 20132138
// Jungwoo Song
// Usage : gcc -Wall -W 74hc595_functions.c 4_20132138.c -o 4_20132138.out -pthread -lpigpiod_if2 -lrt

int main(void)
{
    int i;
    uint8_t arr[] = {   0b00000000,
                        0b00011000,
                        0b00111100,
                        0b01111110,
                        0b11111111,
                        0b01111110,
                        0b00111100,
                        0b00011000,
                        0b00000000};

    int ret;
    
    ret = init();
    if(ret == 0)
        return 0;

    while(1){
        for(int i = 0 ; i < sizeof(arr) ; i++){
            set8(arr[i]);
            time_sleep(0.1);
        }
    }

    release();
    return 0;
}
