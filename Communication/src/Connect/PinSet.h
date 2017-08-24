#include "Pin.h"
#include <map>
#include <initializer_list>

class PinSet
{
	public:
		std::map<int,Pin*> pins;
		PinSet(std::initializer_list<std::initializer_list<int>> l)
		{
			setup(l);
		}
		void setup(std::initializer_list<std::initializer_list<int>> l)
		{
			add(l);
		}
		void loop()
		{
			for (auto it = pins.begin(); it != pins.end(); ++it)
			{
				it->second->loop();
			}
		}
		void add(int pin, int type)
		{
			pins[pin] = new Pin(pin);
			pins[pin]->setType(type);
		}
		void add(Pin* pin)
		{
			pins[pin->pin] = pin;
		}
		void add(std::initializer_list<std::initializer_list<int>> l)
		{
			for (auto sl = l.begin(); sl != l.end(); ++sl)
			{
				int pair[2] = {0, Pin::DIGITAL}, i = 0;
				for (auto it = sl->begin(); it != sl->end(); ++it)
					pair[(i++)%2] = *it;
				add(pair[0], pair[1]);
			}
		}
		Pin* operator[](int pin)
		{
			return pins[pin];
		}
};

PinSet* pins;