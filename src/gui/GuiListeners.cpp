#include "GuiListeners.h"

namespace boxModel {

namespace gui {

std::map<std::string, GuiListeners::ListenerEntryBase*> GuiListeners::listeners;

GuiListeners::GuiListeners() {
}

GuiListeners::~GuiListeners() {
}


}

}
