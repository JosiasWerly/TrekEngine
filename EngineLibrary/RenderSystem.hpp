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

#include "Pointer.hpp"

class RenderSystem;
class Drawcall {
    bool enableDraw = true;
public:
    void setDraw();
    inline bool getDraw() { return enableDraw; }

    virtual ~Drawcall() {}
    virtual void draw(sf::RenderWindow &w) {
    }
    bool operator==(const Drawcall &other) const {
        return 0;
    }
};
class RenderSystem {
public:
    sf::RenderWindow renderWindow;
    list<TPointer<Drawcall>> drawcalls;
    list<TPointer<Drawcall> *> toDelete;

    void setup() {
        renderWindow.create(sf::VideoMode(200, 200), "engine demo");
        renderWindow.setFramerateLimit(2);
    }
    void tick() {
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
    void popDrawcall(Drawcall& ref) {
        for (auto& d : drawcalls){
            
        }

    }
};
#endif // !_RenderSystem