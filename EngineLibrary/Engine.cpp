#include "Engine.hpp"



bool InputManager::isClick(TKey k) {
	return clickKeys.count(k);
}
bool InputManager::isPressed(TKey k) {
	return clickKeys.count(k) || pressedKeys.count(k);
}
void InputManager::processEvent(sf::Event &e) {
	TKey &key = e.key.code;
	if (e.type == sf::Event::EventType::KeyPressed) {
		if (!pressedKeys.count(key)) {
			pressedKeys.insert(key);
			clickKeys.insert(key);
		}
		else
			clickKeys.erase(key);
	}
	else if (e.type == sf::Event::EventType::KeyReleased) {
		clickKeys.erase(key);
		pressedKeys.erase(key);
	}
}


void EventSystem::tick() {
	sf::Event event;
	while (renderWindow->pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			renderWindow->close();
		else if (event.type & (sf::Event::KeyPressed | sf::Event::KeyReleased))
			inputManager.processEvent(event);
	}
}


Engine::Engine() {
	playing = true;
	eventSystem.renderWindow = &renderSystem.renderWindow;
}
void Engine::play() {	
	if (playing)
		endPlay();
	playing = true;
	projectSystem.attachedProject->beginPlay();
	cout << "playing" << endl;
	
}
void Engine::endPlay() {
	playing = false;
	projectSystem.attachedProject->endPlay();
	runTimeObjs.unloadMemory();
	transientObjs.unloadMemory();
	cout << "endPlay" << endl;
}
bool Engine::isPlaying() {
	return playing;
}
//renderWindow.setTitle(st); 
//clock_t curTick;
//String st = "Trekk Demo | ";
//st += std::to_string(i);
void Engine::tick() {
	curTick = clock();
	if (projectSystem.deprecatedProject()) {
		runTimeObjs.unloadMemory();
		projectSystem.detachProject();
		projectSystem.loadProject(this);
	}
	eventSystem.tick();
	renderSystem.tick();
	transientObjs.tick();
	if (playing)
		runTimeObjs.tick();
	renderSystem.renderWindow.setTitle(String(std::to_string(clock() - curTick)));
}


DrawInstance::DrawInstance() {
	isVisible = false;
	setVisible(true);
}
DrawInstance::~DrawInstance() {
	setVisible(false);
}
void DrawInstance::setVisible(bool newVisible) {
	if (isVisible != newVisible) {
		isVisible = newVisible;
		if (isVisible)
			engine->renderSystem.pushDrawcall(*this);
		else
			engine->renderSystem.popDrawcall(*this);
	}
}


//template<class T> TPointer<T> instantiate(T *obj, bool transient) {
//	TPointer<T> out = TPointer<T>(obj);
//	//if (out.isType<Drawcall>())
//	//	engine->renderSystem.drawcalls.push_back(out.make<Drawcall>());
//
//	if (transient)
//		engine->transientObjs.registerObject(out.make<Object>());
//	else
//		engine->runTimeObjs.registerObject(out.make<Object>());
//	return out;
//}
//template<class T> TPointer<T> getObject(string name, bool transient) {
//	if (transient)
//		return engine->transientObjs.getObject(name);
//	else
//		return engine->runTimeObjs.getObject(name);
//	return nullptr;
//}

void loadAssets(list<string> names) {
	engine->assetSystem.loadAssets(names);
}
void unLoadAssets(list<string> names) {
	engine->assetSystem.unloadAssets(names);
}
template<class T> T *getAsset(string name) {
	return (T *)engine->assetSystem.getAsset(name);
}


//
//bool isPressed(sf::Keyboard::Key k) {
//	return engine->eventSystem.inputManager.isPressed(k);
//}
//bool isClicked(sf::Keyboard::Key k) {
//	return engine->eventSystem.inputManager.isClick(k);
//}