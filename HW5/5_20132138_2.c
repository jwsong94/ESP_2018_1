#include <stdio.h>
#include <string.h>
#include <pigpio.h>
#include "74hc595_functions.h"

// HW5 : 
// 20132138
// Jungwoo Song
// Usage : gcc -Wall -W -Wno-overflow -pthread -lpigpio -lrt 5_20132138_2.c 74hc595_functions_pigpio.c -o 5_20132138_2.out 

void dot(int row, int col)
{
    uint8_t row8, col8;
    uint16_t tmp;
    row8 = ~(1 << (8-row));
    col8 = 1 << (8-col);
    tmp = (row8<<8) | col8;
    set16(tmp);
}

int cnt;
void callback(void)
{
	printf("500 milliseconds have elapsed\n");
	cnt++;	
}
 
int main(void)
{
    int i,j;
    int total_col;

    uint8_t mat[8][1000] = {0};
    char str[1000] = {'\0'};
    int length = -1;

    for(int i = 0; i < 8; i++){
        gets(str);
        length = strlen(str);
        for(int j = 0; j < length; j++){
            if(str[j] == 'o')
                mat[i][j] = 1;
            else
                mat[i][j] = 0;
        }
    }

    total_col = length;

    int ret;
    ret = init();
    if(ret == 0)
        return 0;

    gpioSetTimerFunc(0, 50, callback);

    while(1)
        for(i = 0 ; i < 8 ; i++)
            for(j = 0 ; j < 8 ; j++)
                if(mat[i][(j+cnt)%total_col] == 1)
                    dot(i+1,j+1);


    release();
    return 0;
}

