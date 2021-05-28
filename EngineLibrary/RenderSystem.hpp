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
    bool enableDraw = true;
public:
    void setDraw();
    inline bool getDraw();

    virtual ~Drawcall();
    virtual void draw(sf::RenderWindow &w);
    bool operator==(const Drawcall &other) const;
};
class RenderSystem {
public:
    sf::RenderWindow renderWindow;
    list<TPointer<Drawcall>> drawcalls;
    list<TPointer<Drawcall>*> toDelete;

    void setup();
    void tick();
    void popDrawcall(Drawcall& ref);
};
#endif // !_RenderSystem