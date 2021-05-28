#include "RenderSystem.hpp"
//#include "Engine.hpp"

Drawcall::~Drawcall() {}
void Drawcall::draw(sf::RenderWindow &w) {
}
bool Drawcall::operator==(const Drawcall &other) const {
	return 0;
}

void RenderSystem::setup() {
	renderWindow.create(sf::VideoMode(200, 200), "engine demo");
	renderWindow.setFramerateLimit(2);
}
void RenderSystem::tick() {
	renderWindow.clear();
	list<TPointer<Drawcall> *> toRemove;
	for (auto &o : drawcalls) {
		if (o.isValid())
			o()->draw(renderWindow);
		else
			toRemove.push_back(&o);
	}
	for (auto &rem : toRemove)
		drawcalls.remove(*rem);
	renderWindow.display();
}
void RenderSystem::popDrawcall(Drawcall &ref) {
	for (auto &d : drawcalls) {

	}

}
