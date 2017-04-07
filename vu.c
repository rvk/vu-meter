#define F_CPU 1000000

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	unsigned char adc_value;
	unsigned char leds;

	// PD0-4 as output
	DDRD = 0x1f;
	PORTD = 0x00;
	
	//enable ADC
	ADCSRA = (1<<ADEN); //enable ADC
	ADMUX |= (1<<ADLAR); //left adjusted, result in ADCH

	while (1)
	{
		ADCSRA |= (1<<ADSC);
		while (ADCSRA & (1<<ADSC));
		adc_value = ADCH;
		leds = 0;
		if (adc_value > 3) leds |= (1<<0);
		if (adc_value > 6) leds |= (1<<1);
		if (adc_value > 16) leds |= (1<<2);
		if (adc_value > 40) leds |= (1<<3);
		if (adc_value > 101) leds |= (1<<4);
		PORTD = leds;
	}
}
