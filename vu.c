#define F_CPU 1000000

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	unsigned int adc_value;
	unsigned int average_value;
	unsigned int moving_sum;
	unsigned char leds;

	// PD0-4 as output
	DDRD = 0x1f;
	PORTD = 0x00;
	
	//enable ADC
	ADCSRA = (1<<ADEN); //enable ADC

	while (1)
	{
		ADCSRA |= (1<<ADSC);
		while (ADCSRA & (1<<ADSC));
		adc_value = ADCL;
		adc_value += ADCH << 8;
		moving_sum = moving_sum - moving_sum / 10;
		moving_sum += adc_value;
		average_value = moving_sum / 10;
		leds = 0;
		if (average_value > 3) leds |= (1<<0);
		if (average_value > 6) leds |= (1<<1);
		if (average_value > 16) leds |= (1<<2);
		if (average_value > 40) leds |= (1<<3);
		if (average_value > 101) leds |= (1<<4);
		PORTD = leds;
		_delay_ms(10);
	}
}
