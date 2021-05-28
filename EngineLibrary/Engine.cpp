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
		else if (event.type & (sf::Event::KeyPressed | sf::Event::KeyReleased)) {
			inputManager.processEvent(event);
		}
	}
}


Engine::Engine() {
	eventSystem.renderWindow = &renderSystem.renderWindow;
}
void Engine::play() {	
	if (playing)
		endPlay();
	playing = true;
	//projectSystem.attachedProject->beginPlay();
	cout << "playing" << endl;
	
}
void Engine::endPlay() {
	playing = false;
	//projectSystem.attachedProject->endPlay();
	runTimeObjs.unloadMemory();
	cout << "endPlay" << endl;
}
bool Engine::isPlaying() {
	return playing;
}
void Engine::tick() {
	if (projectSystem.deprecatedProject()) {
		runTimeObjs.unloadMemory();
		projectSystem.detachProject();
		projectSystem.loadProject(this);
	}
	renderSystem.tick();
	transientObjs.tick();
	eventSystem.tick();

	if (playing)
		runTimeObjs.tick();
}

template<class T> TPointer<T> instantiate(T *obj, bool transient) {
	TPointer<T> out = TPointer<T>(obj);
	//if (out.isType<Drawcall>())
	//	engine->renderSystem.drawcalls.push_back(out.make<Drawcall>());

	if (transient)
		engine->transientObjs.registerObject(out.make<Object>());
	else
		engine->runTimeObjs.registerObject(out.make<Object>());
	return out;
}
template<class T> TPointer<T> getObject(string name, bool transient) {
	if (transient)
		return engine->transientObjs.getObject(name);
	else
		return engine->runTimeObjs.getObject(name);
	return nullptr;
}

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