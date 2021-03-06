#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/mman.h>

#define MMAP_SIZE 4096
#define GPIO_PHY_BASE_ADDRESS 0x3F200000

#define INPUT   0b000
#define OUTPUT  0b001
#define HIGH    1
#define LOW 0

// HW1 : GPIO direct register access
// 20132138
// Jungwoo Song

void open_devmem();
void gpio_pinMode(int pin, int mode);
void gpio_digitalWrite(int pin, int value);
int gpio_getPinMode(int pin); // HW1 : GPFSELn
int gpio_digitalRead(int pin); // HW1 : GPLEVn
void close_devmem();

int fd;

// GPIO registers
typedef struct TAG_GPIO_REGS{
    uint32_t GPFSEL[6];
    uint32_t reserved1;
    uint32_t GPSET[2];
    uint32_t reserved2;
    uint32_t GPCLR[2];
    uint32_t reserved3;
    uint32_t GPLEV[2];
}GPIO_REGS, *pGPIO_REGS;

pGPIO_REGS pGpio;

int main()
{
    int i;
    int gpio = 13;
    open_devmem();

    // Test Code
    printf("GPFSELn Test\n");
    printf("Set gpio %d OUTPUT\n", gpio);
    gpio_pinMode(gpio, OUTPUT);
    printf("gpio %d : %d\n", gpio, gpio_getPinMode(gpio));
    
    printf("Set gpio %d INPUT\n", gpio);
    gpio_pinMode(gpio, INPUT);
    printf("gpio %d : %d\n", gpio, gpio_getPinMode(gpio));

    printf("\nGPLEVn Test\n");
    printf("gpio %d level : %d\n", gpio, gpio_digitalRead(gpio));

    close_devmem();
    return 0;
}

void open_devmem()
{
    fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (fd<0){
        printf("can not open /dev/mem\n");
        perror("");
        exit(-1);
    }

    void *mmaped = mmap(NULL,
            MMAP_SIZE,
            PROT_READ | PROT_WRITE,
            MAP_SHARED,
            fd,
            GPIO_PHY_BASE_ADDRESS);

    if (mmaped == MAP_FAILED) {
        printf("mmap failed\n");
        perror("");
        exit(-1);
    }
    pGpio = mmaped;
}

void gpio_pinMode(int pin, int mode)
{
    int registerIdx = pin / 10;
    int bitOffset = (pin % 10) * 3;

    uint32_t oldGpfsel = pGpio->GPFSEL[registerIdx];
    uint32_t mask = 0b111 << bitOffset;

    pGpio->GPFSEL[registerIdx] = (oldGpfsel & ~mask) | ((mode << bitOffset) & mask);
}

int gpio_getPinMode(int pin)
{
    int registerInx = pin / 10;
    int bitOffset = (pin % 10) * 3;

    uint32_t mask = 0b111 << bitOffset;
    uint32_t mode = (pGpio->GPFSEL[registerInx] & mask) >> bitOffset;

    return mode;
}

void gpio_digitalWrite(int pin, int value)
{
    if(value)
        pGpio->GPSET[pin / 32] = (1 << (pin % 32));
    else
        pGpio->GPCLR[pin / 32] = (1 << (pin % 32));
}

int gpio_digitalRead(int pin)
{
    int registerInx = pin / 32;
    int bitOffset = pin % 32;

    uint32_t mask = 0b1 << bitOffset;
    uint32_t level = (pGpio->GPLEV[registerInx] & mask) >> bitOffset;

    return level;
}

void close_devmem()
{
    //munmap()
    close(fd);
}


