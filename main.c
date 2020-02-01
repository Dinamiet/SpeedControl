#include <xc.h>
#include <stdint.h>

#define _XTAL_FREQ  8000000

#define refreshTime 15000 //us
#define minPulse 1000 //us
#define maxPulse 2000 //us

#define prescaler 0b100;

void delay(uint16_t us)
{
    TMR0= 255 -(us>>4);
    while (TMR0);
}

void main(void)
{
    uint8_t value= 0;
    //Setup GPIO
    TRISGPIO= 0b11110001;
    //Setup ADC
    ADCON0bits.ANS0= 1; //GP0 to analog mode
    ADCON0bits.ANS1= 0; //GP1 to digital mode
    ADCON0bits.CHS= 0; // Set analog channel to use AN0
    ADCON0bits.ADON= 1; // Turn ADC on
    
    // Set timer0 to use internal clock
    // Set Prescaler to be used for Timer0
    OPTION= prescaler; // Set Prescaler value
    
    while (1)
    {
//        if (!ADCON0bits.GO)
//        {
//            value= ADRES;
//            ADCON0bits.GO= 1; // Start next conversion
//        }
        GPIObits.GP1= 1;
        delay(1000);
        GPIObits.GP1= 0;
        delay(1000);
    }
}
