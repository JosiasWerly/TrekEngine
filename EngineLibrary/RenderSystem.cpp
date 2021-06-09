#include "RenderSystem.hpp"

#include <sstream>
#include <string>

Drawcall::~Drawcall() {}
void Drawcall::draw(sf::RenderWindow &w) {
}
bool Drawcall::operator==(const Drawcall &other) const {
	return this == &other;
}

void RenderSystem::setup() {
	renderWindow.create(sf::VideoMode(800, 600), "Trekk Demo");
	renderWindow.setFramerateLimit(24);
}
void RenderSystem::tick() {
	renderWindow.clear();
	for (auto &o : drawcalls)
		o->draw(renderWindow);
	linesQuerry.draw(renderWindow);
	renderWindow.display();
}
