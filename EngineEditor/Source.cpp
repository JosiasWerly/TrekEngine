#include <EngineLibrary/Trekkier.hpp>


int main() {
    engine = new Engine;
    engine->renderSystem.setup();
    while (true) {
        if (isClicked(sf::Keyboard::Key::F1)) {
            if (engine->isPlaying())
                engine->endPlay();
            else
                engine->play();
        }
        engine->tick();
    }
    return 0;
}