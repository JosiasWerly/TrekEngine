#include "RenderSystem.hpp"
//#include "Engine.hpp"

Drawcall::~Drawcall() {}
void Drawcall::draw(sf::RenderWindow &w) {
}
bool Drawcall::operator==(const Drawcall &other) const {
	return this == &other;
}

void RenderSystem::setup() {
	renderWindow.create(sf::VideoMode(200, 200), "engine demo");
	renderWindow.setFramerateLimit(2);
}
void RenderSystem::tick() {
	renderWindow.clear();
	for (auto &o : drawcalls)
		o->draw(renderWindow);
	renderWindow.display();
}
