#include <vector>

class Dispatcher;
class Listener
{
	public:
		virtual ~Listener(){}
		virtual void onEvent(Dispatcher* sender){}
};

class Dispatcher
{
	public:
		virtual ~Dispatcher(){}
		std::vector<Listener*> listeners;
		void addListener(Listener* listener)
		{
			listeners.push_back(listener);
		}
		void dispatch()
		{
			for (auto listener = listeners.begin(); listener != listeners.end(); ++listener) {
				(*listener)->onEvent(this);
			}
		}
};