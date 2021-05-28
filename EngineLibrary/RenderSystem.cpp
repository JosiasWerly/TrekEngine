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
	renderWindow.create(sf::VideoMode(200, 200), "Trekk Demo");
	renderWindow.setFramerateLimit(24);
}
void RenderSystem::tick() {
	if (++i % 24 == 0) {
		String st = "Trekk Demo | ";
		st += std::to_string(i);
		renderWindow.setTitle(st);
	}
	renderWindow.clear();
	for (auto &o : drawcalls)
		o->draw(renderWindow);
	renderWindow.display();
}
