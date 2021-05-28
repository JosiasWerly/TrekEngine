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
    Object();
    virtual ~Object();
    virtual void tick();
};

class UObjectSystem {
    list<TPointer<Object>> objs;
public:
    void registerObject(TPointer<Object> newInstace);
    void unloadMemory();
    TPointer<Object> getObject(string name);
    void tick();
};
#endif // !_ObjectSystem