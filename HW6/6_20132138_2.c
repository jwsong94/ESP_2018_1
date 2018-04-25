#include <stdio.h>
#include <pigpiod_if2.h> 
#include <unistd.h>

#define DUTYCYCLE(x,range) x/(float)range*100

// HW6 : 
// 20132138
// Jungwoo Song
// Usage : gcc -Wall -W -pthread -lpigpiod_if2 -lrt 6_20132138_2.c -o 6_20132138_2.out 

int pi;
int range;
//int gpios[] = {22, 23, 24, 5, 6, 13, 19, 16, 26, 20};
int gpios[] = {6, 13, 5, 19, 24, 16, 23, 26, 22, 20};
int default_range = 200;
void* dimming_thread(void* arg)
{
    int gpio = (int)arg;
    //printf("dimming_thread start gpio:%d\n", gpio);
    for(int i = 0 ; i <= range ; i++){
        set_PWM_dutycycle(pi, gpio, i);
        time_sleep(0.007);
    }

    set_PWM_dutycycle(pi, gpio, 0);
    time_sleep(0.1);
    /*
    for(int i = range ; i >= 0 ; i-=2){
        set_PWM_dutycycle(pi, gpio, i);
        time_sleep(0.007);
    }
    */
    //printf("dimming_thread exit gpio:%d\n", gpio);
    return NULL;
}

int main()
{
    if((pi = pigpio_start(NULL, NULL)) < 0){
        fprintf(stderr, "%s\n", pigpio_error(pi));
        return 1;
    }
    for(int i = 0 ; i < 10 ; i++){
        set_PWM_range(pi, gpios[i], default_range);
        range = get_PWM_range(pi, gpios[i]);
    }
    printf("range:%d\n", range);

    for(int i = 0 ; ; i++){
        start_thread(dimming_thread, (void*)gpios[2*(i%5)]);
        start_thread(dimming_thread, (void*)gpios[2*(i%5) + 1]);

        time_sleep(0.3);
    }

    pigpio_stop(pi);
    return 0;
}
