#include "APIList.h"

void* Serial_println(JsonArray& args) {
	switch(args.size()) {
		case 1: auto r = Serial.println(args[0].as<String>()); return (void*)&r; break;
	}
}



void APIList::setup()
{
	add("Serial.println", Serial_println);
}


HandlerMap __handlerMap;
void* APIList::run(std::string name, JsonArray& args)
{
	return __handlerMap[name](args);
}
void APIList::add(std::string name, Handler handler)
{
	__handlerMap[name] = handler;
}