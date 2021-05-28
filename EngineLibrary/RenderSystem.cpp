#include "RenderSystem.hpp"
//#include "Engine.hpp"
void Drawcall::setDraw() {
}
bool Drawcall::getDraw() {
	return enableDraw; 
}
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
	for (auto &d : drawcalls) {
		if (d.isValid())
			d()->draw(renderWindow);
		else
			toDelete.push_back(&d);
	}
	for (auto &d : toDelete)
		drawcalls.remove(*d);
	toDelete.clear();
	renderWindow.display();
}
void RenderSystem::popDrawcall(Drawcall &ref) {
	for (auto &d : drawcalls) {

	}

}
