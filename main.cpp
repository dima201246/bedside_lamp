#define SET_DAY_LIGHT_ON(v)	TCCR0B |= (1 << CS01);\
							TCCR0A |= (1 << WGM01) | (1 << WGM00) | (1 << COM0A1);\
							OCR0A = v

#define SET_DAY_LIGHT_OFF	OCR0A = 0;\
							TCCR0B &= ~(1 << CS01);\
							TCCR0A &= ~((1 << WGM01) | (1 << WGM00) | (1 << COM0A1))

uint8_t test = 0;

/*enum lightMode {
	mode_none
}

lightMode mode = mode_none;
*/
int main(int argc, char const *argv[]) {
	uint8_t i = 0;
	// Инициализация выхода на транзистор
	DDRB |= 0b00000001;

	// Инициализация входа на кнопку
	DDRB &= ~0b00000100;
	PORTB |= 0b00000100;

	for (;;)
	{
		if (!(PINB & 0b00000100))
		{
			delay(100);

			if (test)
			{
				for (i = OCR0A; ((i != 0) && (!(PINB & 0b00000100))); --i)
				{
					SET_DAY_LIGHT_ON(i);
					delay(5);
				}

				delay(50);

				if (OCR0A == 1)
				{
					while (!(PINB & 0b00000100))
					{
						for (i = 0; i <= 75; i += 5)
						{
							SET_DAY_LIGHT_ON(i);
							delay(13);
						}

						for (i = 75; i != 0; i -= 5)
						{
							SET_DAY_LIGHT_ON(i);
							delay(13);
						}
					}

					SET_DAY_LIGHT_OFF;
				}


				test = false;
			}
			else
			{
				for (i = OCR0A; ((i < 255) && (!(PINB & 0b00000100))); ++i)
				{
					SET_DAY_LIGHT_ON(i);
					delay(5);
				}

				delay(50);

				if (OCR0A == 254)
				{
					while (!(PINB & 0b00000100))
					{
						for (i = 255; i > 155; i -= 5)
						{
							SET_DAY_LIGHT_ON(i);
							delay(10);
						}

						for (i = 155; i <= 254; i += 5)
						{
							SET_DAY_LIGHT_ON(i);
							delay(10);
						}
					}

					OCR0A = 255;
				}

				test = true;
			}

			delay(100);
		}

/*		switch (mode) {
			case mode_none:
		}*/

	}

	return 0;
}