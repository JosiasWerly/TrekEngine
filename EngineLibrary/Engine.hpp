#ifndef _Engine
#define _Engine
#include "Pointer.hpp"
#include "RenderSystem.hpp"
#include "DllSystem.hpp"
#include "ProjectSystem.hpp"
#include "ObjectSystem.hpp"
#include "AssetSystem.hpp"


class InputManager {
	typedef sf::Keyboard::Key TKey;
	set<TKey> clickKeys, pressedKeys;
public:
	bool isClick(TKey k) {
		return clickKeys.count(k);
	}
	bool isPressed(TKey k) {
		return clickKeys.count(k) || pressedKeys.count(k);
	}

	void processEvent(sf::Event &e) {
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
};
class EventSystem {
public:
	sf::RenderWindow *renderWindow = nullptr;
	InputManager inputManager;

	inline void tick() {
		sf::Event event;
		while (renderWindow->pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				renderWindow->close();
			else if (event.type & (sf::Event::KeyPressed | sf::Event::KeyReleased)) {
				inputManager.processEvent(event);
			}
		}
	}
};

class Engine {
public:
	UObjectSystem runTimeObjs, transientObjs;

	RenderSystem renderSystem;
	ProjectSystem projectSystem;
	EventSystem eventSystem;
	AssetSystem assetSystem;

	bool playing = false;
	Engine() {
		eventSystem.renderWindow = &renderSystem.renderWindow;
	}

	void play() {
		if (playing)
			endPlay();
		playing = true;
		projectSystem.attachedProject->beginPlay();
		cout << "playing" << endl;
	}
	void endPlay() {
		playing = false;
		projectSystem.attachedProject->endPlay();
		runTimeObjs.unloadMemory();
		cout << "endPlay" << endl;
	}
	inline bool isPlaying() {
		return playing;
	}
	void tick() {
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
};

extern __declspec(selectany) Engine *engine = nullptr;
template<class T> static TPointer<T> instantiate(T *obj = nullptr, bool transient = false) {
	TPointer<T> out = TPointer<T>(obj);
	//if (out.isType<Drawcall>())
	//	engine->renderSystem.drawcalls.push_back(out.make<Drawcall>());

	if (transient)
		engine->transientObjs.registerObject(out.make<Object>());
	else
		engine->runTimeObjs.registerObject(out.make<Object>());
	return out;
}
template<class T> static TPointer<T> getObject(string name, bool transient = false) {
	if (transient)
		return engine->transientObjs.getObject(name);
	else
		return engine->runTimeObjs.getObject(name);
	return nullptr;
}

inline void loadAssets(list<string> names) {
	engine->assetSystem.loadAssets(names);
}
inline void unLoadAssets(list<string> names) {
	engine->assetSystem.unloadAssets(names);
}
template<class T> T *getAsset(string name) {
	return (T *)engine->assetSystem.getAsset(name);
}

static bool isPressed(sf::Keyboard::Key k) {
	return engine->eventSystem.inputManager.isPressed(k);
}
static bool isClicked(sf::Keyboard::Key k) {
	return engine->eventSystem.inputManager.isClick(k);
}


#endif // !_Engine
