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
class DrawLineQuerry : public Drawcall {
public:
    struct QuerryData{
        Vector2f a, b;
        Color c = Color::White;
    };
    list<QuerryData> querried;
    void draw(sf::RenderWindow &w) {
        sf::Vertex line[2];
        for (auto &p : querried){
            line[0].position = p.a;
            line[1].position = p.b;
            line[1].color = line[0].color = p.c;
            w.draw(line, 2, sf::Lines);
        }
        querried.clear();
    }
};

class RenderSystem {
public:
    sf::RenderWindow renderWindow;
    list<Drawcall *> drawcalls;
    DrawLineQuerry linesQuerry;

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