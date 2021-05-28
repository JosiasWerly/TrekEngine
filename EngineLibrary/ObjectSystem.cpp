#include "ObjectSystem.hpp"

Object::Object() {
}
Object::~Object() {
}
void Object::tick() {
}



void UObjectSystem::registerObject(TPointer<Object> newInstace) {
	objs.push_back(newInstace);
}
void UObjectSystem::unloadMemory() {
	for (auto &o : objs)
		o.free();
	objs.clear();
}
void UObjectSystem::tick() {
	list<TPointer<Object> *> toRemove;
	for (auto &o : objs) {
		if (o.isValid())
			o()->tick();
		else
			toRemove.push_back(&o);
	}
	for (auto &rem : toRemove)
		objs.remove(*rem);
}
TPointer<Object> UObjectSystem::getObject(string name) {
	for (auto o : objs) {
		if (o.isValid() && o()->name == name)
			return o;
	}
	return nullptr;
}