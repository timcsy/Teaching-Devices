#include "APIList.h"
#include "Communication.h"
#include <map>

/*class Parser {
	public:
		char* str;
		enum {}
		struct Identifier {
			int type;
			int val;
		};
		Identifier* cid;
		static void parse(char* str) {
			this->str = str;
			next();
		}
		static void next() {
			char* p = str;
			while(tk = *p) {
				++p;
				switch(tk) {
					case ':':
						
						break;
					case '@':
						
						break;
					case '\0':
						return;
					default:
						
				}
			}
		}
};*/

class APIListener {
	public:
		virtual ~APIListener() {}
		virtual void onReturn(JsonObject& value) {}
};

std::map<int, APIListener*>* APIlisteners;
APIListener* tmpListener;
class API
{
	public:
		static void setup(String host, uint16_t port)
		{
			APIlisteners = new std::map<int, APIListener*>();
			Communication::setup(host, port);
			APIList::setup();
		}
		static void loop()
		{
			Communication::loop();
		}
		static void send(String api, JsonObject& args, APIListener* listener = nullptr)
		{
			String output;
			DynamicJsonBuffer jsonBuffer;
			
			JsonObject& request = jsonBuffer.createObject();
			request.createNestedObject("1");
			request["1"]["api"] = api;
			request["1"]["args"] = args;
			
			request.printTo(output);
			//if(listener != nullptr) setListener(listener, 1);
			Communication::send(output);
		}
		static void onReceive(char* str)
		{
			DynamicJsonBuffer jsonBuffer;
			JsonVariant variant = jsonBuffer.parse(str);
			if (variant.is<JsonObject>())
			{
				JsonObject& json = variant.as<JsonObject>();
				/*for (auto req : json) {
					Serial.println(req.key);
					Serial.println(req.value.as<char*>());
				}*/
				/*if(APIlisteners->find(1) != APIlisteners->end())
				{
					(*APIlisteners)[1]->onReturn(json["1"]["value"]);
				}*/
				Serial.println(json["1"]["value"].as<String>());
				tmpListener->onReturn(json["1"]["value"]);
			}
		}
		static void setListener(APIListener* listener, int id)
		{
			(*APIlisteners)[id] = listener;
		}
		static void parse(char* str)
		{
			
		}
};

class APIReceiver : public Receiver {
	public:
		void onReceive(uint8_t * payload, size_t length)
		{
			API::onReceive((char*)payload);
		}
};
