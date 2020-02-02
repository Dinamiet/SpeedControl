// CONFIG
#pragma config IOSCFS = 8MHZ    // Internal Oscillator Frequency Select bit (8 MHz)
#pragma config MCPU = OFF       // Master Clear Pull-up Enable bit (Pull-up disabled)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config CP = OFF         // Code protection bit (Code protection off)
#pragma config MCLRE = ON       // GP3/MCLR Pin Function Select bit (GP3/MCLR pin function is MCLR)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdint.h>

#define refreshTime 5000 // us
#define minPulse	700	 // us
#define maxPulse	1900 // us

#define LED_ON_POS  20

#define prescaler 0b101;

void delay(uint16_t us)
{
	TMR0 = ~(us >> 5);
	while (TMR0);
}

void main(void)
{
	uint16_t value		  = 0;
	uint8_t	 rawADC		  = 0;
	// Setup GPIO
	TRISGPIO = 0b11110001;
	// Setup ADC
	ADCON0bits.ANS0 = 1; // GP0 to analog mode
	ADCON0bits.ANS1 = 0; // GP1 to digital mode
	ADCON0bits.CHS	= 0; // Set analog channel to use AN0
	ADCON0bits.ADON = 1; // Turn ADC on

	// Set timer0 to use internal clock
	// Set Prescaler to be used for Timer0
	OPTION = prescaler; // Set Prescaler value
	while (1)
	{
		GPIObits.GP2 = 1;
		delay(value);
		GPIObits.GP2 = 0;
		delay(refreshTime);

		if (!ADCON0bits.GO)
		{
			rawADC		  = ADRES;
			value		  = ADRES * ((maxPulse - minPulse) / 255) + minPulse;
			ADCON0bits.GO = 1; // Start next conversion
		}
	}
}
