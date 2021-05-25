#pragma once 
#ifndef _ObjectSystem
#define _ObjectSystem
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <string>
#include <iostream>
#include <list>
#include <set>
#include <thread>

#include "RenderSystem.hpp"
using namespace std;

class Object {
public:
    string name;
    Object() {
    }
    virtual ~Object() {
    }
    virtual void tick() {
    }
};
class DrawInstance :
    public Object,
    public Drawcall {
public:
    virtual ~DrawInstance() {
    }

    virtual void draw(sf::RenderWindow &w) = 0;
};


class UObjectSystem {
    list<TPointer<Object>> objs;
public:
    void registerObject(TPointer<Object> newInstace) {
        objs.push_back(newInstace);
    }
    void unloadMemory() {
        for (auto &o : objs)
            o.free();
        objs.clear();
    }
    TPointer<Object> getObject(string name) {
        for (auto o : objs){
            if (o.isValid() && o()->name == name)
                return o;
        }
        return nullptr;
    }
    void tick() {
        for (auto &o : objs) {
            if (o.isValid()) {
                o()->tick();
            }
        }
    }
};
#endif // !_ObjectSystem