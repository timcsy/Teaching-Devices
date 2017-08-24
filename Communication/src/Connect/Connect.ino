#include "Button.h"

void setup()
{
	Serial.begin(115200);
	pins = new PinSet({
		{D0, Pin::DIGITAL},
		{D1, Pin::DIGITAL},
		{D2, Pin::DIGITAL},
		{D3, Pin::DIGITAL},
		{D4, Pin::DIGITAL},
		{D5, Pin::DIGITAL},
		{D6, Pin::DIGITAL},
		{D7, Pin::DIGITAL},
		{D8, Pin::DIGITAL},
		{A0, Pin::ANALOG}
	});
	Button* btn = new Button(D4);
	OnPressListener* onPressListener = new OnPressListener();
	btn->addListener(onPressListener);
	
	receiver = new APIReceiver();
	API::setup("140.116.102.78", 8080);
	
	//API::parse();
}

//int i = 0;
void loop()
{
	pins->loop();
	
	API::loop();
	/*
	// send message to server
	DynamicJsonBuffer jsonBuffer;
	//send("{\"1\":{\"api\":\"Web.Page:::view()\",\"args\":{}},\"cookies\":{\"current_timestamp\":\"1501349471\"}}");
	String api = "Device.Device::send(Hello";
	JsonObject& args = jsonBuffer.createObject();
	API::send(api + (++i) + ")", args);
	*/
	/*
	DynamicJsonBuffer jsonBuffer;
	JsonArray& args = jsonBuffer.createArray();
	args.add("This is APIList Test!");
	APIList::run("Serial.println", args);
	*/
}
