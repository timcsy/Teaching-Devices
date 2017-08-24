#include "PinSet.h"
#include "API.h"

class Button: public Dispatcher
{
	public:
		Button(int pin)
		{
			setup((*pins)[pin]);
		}
		Button(Pin* pin)
		{
			setup(pin);
		}
		void setup(Pin* pin)
		{
			this->pin = pin;
			this->pin->setMode(INPUT);
			state = -1;
			lastState = -1;
			lastDebounceTime = 0;
			delay = 50;
			onChangeListener = new OnChangeListener(this);
			this->pin->addListener(onChangeListener);
		}
		void onPress()
		{
			dispatch();
		}
		
		Pin* pin;
		int state;
		int lastState;
		unsigned long lastDebounceTime; // the last time the output pin was toggled
		unsigned long delay; // the debounce time; increase if the output flickers
		class OnChangeListener : public Listener {
			public:
				Button* btn;
				OnChangeListener(Button* btn): btn(btn){}
				void onEvent(Dispatcher* sender)
				{
					Pin* pin = reinterpret_cast<Pin*>(sender);
					int reading = pin->value;
					if ((millis() - btn->lastDebounceTime) > btn->delay)
					{
						if (reading != btn->state)
						{
						  btn->state = reading;
						  if (btn->state == HIGH) btn->onPress();
						}
					}
					btn->lastState = reading;
					btn->lastDebounceTime = millis();
				}
		};
		OnChangeListener* onChangeListener;
};

class CallAPIListener: public APIListener {
	public:
		void onReturn(JsonVariant& value) {
			Serial.println("value is");
			Serial.println(value.as<String>());
		}
};

class OnPressListener : public Listener {
	public:
		int i;
		CallAPIListener* callAPIListener;
		OnPressListener(): i(0){tmpListener = new CallAPIListener();}
		void onEvent(Dispatcher* sender) {
			Button* button = reinterpret_cast<Button*>(sender);
			auto state = button->state;
			Serial.println("pressed");
			
			// send message to server
			DynamicJsonBuffer jsonBuffer;
			//send("{\"1\":{\"api\":\"Web.Page:::view()\",\"args\":{}},\"cookies\":{\"current_timestamp\":\"1501349471\"}}");
			String api = "Device.Device::send(Hello";
			JsonObject& args = jsonBuffer.createObject();
			API::send(api + (++i) + ")", args, callAPIListener);
		}
};