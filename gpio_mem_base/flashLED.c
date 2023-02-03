#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<errno.h>
#include<sys/mman.h>
#include<stdint.h>
#include <unistd.h>

//GPIO_BASE is 0xfe200000
#define GPIO_BASE 0xfe200000
#define GPSET0    0x1c
#define GPCLR0    0X28
#define GPLEV0    0x34
#define _GNU_SOURCE
static volatile uint32_t *gpio;

int main() {
    int fd, x;
    printf("Start of GPIO memory-manipulation test program. \n");
    if(getuid() != 0){
        printf("You must run this program as root. Exiting. \n");
        return -EPERM;
    }
    if ((fd = open("/dev/mem", O_RDWR | O_SYNC)) < 0)
    {
        printf("Unable to open /dev/mem\n");
        return -EBUSY;
    }

    gpio = (uint32_t *) mmap(0, getpagesize(), PROT_READ | PROT_WRITE, MAP_SHARED, fd, GPIO_BASE);
    if (MAP_FAILED == gpio){
        printf("Memory mapping error \n");
        return -EBUSY;
    }

    //GPIO Register Assignment in Page 91 (bcm2835-peripherals.pdf)
    //set FESL17 mode = 001 (output) in GPFSEL1
    *(gpio + 1) = *(gpio + 1) & ~(7 << 21) | (1 << 21);
    //set FESL17 mode = 000 (input) in GPFSEL2
    *(gpio + 2) = *(gpio + 2) & ~(7 << 21);

    do{
        // GPSET/4 -> byte
        *(gpio + GPSET0/4) = 1 << 17;
        printf("GPIO17 is SET\n");
        for (int i = 0; i < 50; i++){
            *(gpio + (GPCLR0/4)) = 1 << 17;
            printf("GPIO17 is CLR\n");
        }
        for (int j = 0; j < 40; j++) {}
    } while ((*gpio + GPLEV0/4) & (1 << 27) == 0);
    
    printf("Button was pressed - end of example program.\n");
    close(fd);
    return 0;
}