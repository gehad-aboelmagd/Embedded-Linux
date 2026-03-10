#include "BCM2837_GPIO.h"

#define LED_PIN             17
#define GPFSEL1             (*(uint32_t *)BCM2837_GPFSEL1)
#define GPCLR0              (*(uint32_t *)BCM2837_GPCLR0)
#define GPSET0              (*(uint32_t *)BCM2837_GPSET0)

typedef unsigned int uint32_t;

void wait(uint32_t cycles)
{
    volatile uint32_t i;
    for(i=0; i<cycles; i++)
    {
        __asm__ __volatile__ ("nop");
    }
}


void main(void)
{
    uint32_t fsel1 = GPFSEL1;
    fsel1 &= ~(0b111 << ((LED_PIN % 10) * 3));
    fsel1 |= 0b001 << ((LED_PIN % 10) * 3);
    GPFSEL1 = fsel1;

    while(1)
    {
        GPSET0 |= 1 << LED_PIN;
        wait(50000000);

        GPCLR0 |= 1 << LED_PIN;
        wait(50000000);
    }
}