#ifndef _Engine
#define _Engine
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <list>


#include "Pointer.hpp"
#include "RenderSystem.hpp"
#include "DllSystem.hpp"
#include "ProjectSystem.hpp"
#include "ObjectSystem.hpp"
#include "AssetSystem.hpp"

using namespace std;
using namespace sf;

class InputManager {
	typedef sf::Keyboard::Key TKey;
	set<TKey> clickKeys, pressedKeys;
public:
	bool isClick(TKey k);
	bool isPressed(TKey k);

	void processEvent(sf::Event &e);
};
class EventSystem {
public:
	sf::RenderWindow *renderWindow = nullptr;
	InputManager inputManager;

	inline void tick();
};



class Engine {
public:
	clock_t curTick;
	UObjectSystem runTimeObjs, transientObjs;
	RenderSystem renderSystem;
	ProjectSystem projectSystem;
	EventSystem eventSystem;
	AssetSystem assetSystem;

	bool playing = false;
	Engine();

	void play();
	void endPlay();
	bool isPlaying();
	void tick();
};

class DrawInstance :
	public Object,
	public Drawcall {
	bool isVisible;
public:
	DrawInstance();
	virtual ~DrawInstance();
	void setVisible(bool newVisible);
};

class BatchDrawInstance : 
	public DrawInstance {
public:
	list<Drawable*> draws;
	BatchDrawInstance(){}
	inline BatchDrawInstance &operator<<(Drawable &d){
		draws.push_back(&d);
		return *this;
	}
	inline BatchDrawInstance &operator>>(Drawable &d) {
		draws.remove(&d);
		return *this;
	}
	void draw(sf::RenderWindow &w) {
		for (auto &d : draws)
			w.draw(*d);
	}
};


extern __declspec(selectany) Engine *engine = nullptr;

template<class T> static TPointer<T> instantiate(T *obj = nullptr, bool transient = false) {
	TPointer<T> out = TPointer<T>(obj);
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

inline void loadAssets(list<string> names);
inline void unLoadAssets(list<string> names);
template<class T> T *getAsset(string name);

static bool isPressed(sf::Keyboard::Key k) {
	return engine->eventSystem.inputManager.isPressed(k);
}
static bool isClicked(sf::Keyboard::Key k) {
	return engine->eventSystem.inputManager.isClick(k);
}


#endif // !_Engine
