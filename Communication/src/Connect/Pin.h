#include "Event.h"
#include <Arduino.h>

class Pin: public Dispatcher
{
	public:
		enum {DIGITAL, ANALOG};
		int pin;
		int mode;
		int type;
		int value;
		
		Pin(int pin)
		{
			setup(pin);
		}
		Pin(int pin, int mode, int type, int value)
		{
			setup(pin);
			setMode(mode);
			setType(type);
			this->value = value;
		}
		void setup(int pin)
		{
			this->pin = pin;
			setMode(OUTPUT);
			setType(ANALOG);
			value = 0;
		}
		void loop()
		{
			if(mode == INPUT)
			{
				int newValue = read();
				if(value != newValue)
				{
					value = newValue;
					dispatch();
				}
			}
		}
		void setMode(int mode)
		{
			pinMode(pin, mode);
		}
		void setType(int type)
		{
			this->type = type;
		}
		void write(int value)
		{
			switch(type)
			{
				case DIGITAL:
					digitalWrite(pin, value);
					break;
				case ANALOG:
					analogWrite(pin, value);
					break;
			}
		}
		int read()
		{
			switch(type)
			{
				case DIGITAL:
					return digitalRead(pin);
					break;
				case ANALOG:
					return analogRead(pin);
					break;
			}
		}
};