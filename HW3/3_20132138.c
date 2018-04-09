#include <stdio.h>
#include <pigpiod_if2.h> 
#define PINNO 23  // BUTTONA
#define PINNO2 24 // BUTTONB
#define PINNO3 17 // LED

// HW3 : switch button debouncing
// 20132138
// Jungwoo Song

int count;
uint32_t falling_tickA, rising_tickA;
uint32_t falling_tickB, rising_tickB;

void cb_falling_funcA(int pi, unsigned user_gpio, unsigned level, uint32_t tick)
{
    falling_tickA = tick;
}

void cb_rising_funcA(int pi, unsigned user_gpio, unsigned level, uint32_t tick)
{
    rising_tickA = tick;
    if(rising_tickA-falling_tickA > 10000){
        printf("ButtonA Clicked\n");
        count++;
    }
}

void cb_falling_funcB(int pi, unsigned user_gpio, unsigned level, uint32_t tick)
{
    falling_tickB = tick;
}

void cb_rising_funcB(int pi, unsigned user_gpio, unsigned level, uint32_t tick)
{
    rising_tickB = tick;
    if(rising_tickB-falling_tickB > 10000)
    {
        printf("ButtonB Clicked\n");
        printf("count:%d\n", count);
        for(int i=0; i<count; i++){
            // printf("*\n");
            gpio_write(pi, PINNO3, 1);
            time_sleep(0.5);
            gpio_write(pi, PINNO3, 0);
            time_sleep(0.5);
        }
    }
}

int main()
{
    int pi;
    if((pi = pigpio_start(NULL, NULL)) < 0){
        fprintf(stderr, "%s\n", pigpio_error(pi));
        return 1;
    }

    set_mode(pi, PINNO, PI_INPUT);
    set_pull_up_down(pi, PINNO, PI_PUD_UP);
    set_mode(pi, PINNO2, PI_INPUT);
    set_pull_up_down(pi, PINNO2, PI_PUD_UP);
    set_mode(pi, PINNO3, PI_OUTPUT);

    callback(pi, PINNO, FALLING_EDGE, cb_falling_funcA);
    callback(pi, PINNO, RISING_EDGE, cb_rising_funcA);
    callback(pi, PINNO2, FALLING_EDGE, cb_falling_funcB);
    callback(pi, PINNO2, RISING_EDGE, cb_rising_funcB);

    getchar();
    // printf("버튼 누른 총 횟수:%d\n", count);

    pigpio_stop(pi);
    return 0;
}
