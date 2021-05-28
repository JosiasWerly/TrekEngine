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
	UObjectSystem runTimeObjs, transientObjs;
	RenderSystem renderSystem;
	ProjectSystem projectSystem;
	EventSystem eventSystem;
	AssetSystem assetSystem;

	bool playing = false;
	Engine();

	void play();
	void endPlay();
	inline bool isPlaying();
	void tick();
};

extern __declspec(selectany) Engine *engine = nullptr;
template<class T> static TPointer<T> instantiate(T *obj = nullptr, bool transient = false);
template<class T> static TPointer<T> getObject(string name, bool transient = false);

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
