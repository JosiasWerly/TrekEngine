#pragma once
#ifndef _RenderSystem
#define _RenderSystem

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <string>
#include <iostream>
#include <list>
#include <set>
#include <thread>
using namespace std;
using namespace sf;

#include "Pointer.hpp"

class RenderSystem;
class Drawcall {
public:
    virtual ~Drawcall();
    virtual void draw(sf::RenderWindow &w);
    bool operator==(const Drawcall &other) const;
};

class RenderSystem {
public:
    unsigned int i;
    sf::RenderWindow renderWindow;
    list<Drawcall*> drawcalls;

    void setup();
    void tick();
    void popDrawcall(Drawcall &ref) {
        drawcalls.remove(&ref);
    }
    void pushDrawcall(Drawcall &ref) {
        drawcalls.push_back(&ref);
    }
};
#endif // !_RenderSystem