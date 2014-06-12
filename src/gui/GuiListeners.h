#ifndef LISTENERS_H
#define LISTENERS_H

#include <functional>
#include <map>

namespace boxModel {

namespace gui {

class GuiListeners {
private:

	class ListenerEntryBase {
	public:
	};

	template <typename Type>
	class ListenerEntry: public ListenerEntryBase {
		public:
		typedef std::function<void(Type*)> Listener;
		
		ListenerEntry(Listener l){
			listener = l;
		}
		
		Listener listener;
	};

	GuiListeners();
	~GuiListeners();

public:

	template <typename GuiType, typename T, void(T::*membr)(GuiType*)>
	static void add(std::string name, T* instance) {
		listeners[name] = new ListenerEntry<GuiType>(std::bind<T, membr>(instance, std::placeholders::_1));
	}
	
	static std::map<std::string, ListenerEntryBase*> listeners;

};

}

}

#endif // LISTENERS_H
