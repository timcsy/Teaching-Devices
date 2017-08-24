#include <Arduino.h>
#include <ArduinoJson.h>

#include <unordered_map>
typedef void* (*Handler)(JsonArray&); // function pointer type
typedef std::unordered_map<std::string, Handler> HandlerMap;

class APIList
{
	public:
		static void setup();
		static void* run(std::string name, JsonArray& args);
		static void add(std::string name, Handler handler);
};