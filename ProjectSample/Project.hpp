#pragma once
#define TProject

#include <EngineLibrary/Trekkier.hpp>

using namespace std;

class MyDraw :
    public DrawInstance {

    sf::RectangleShape r;
public:
    MyDraw() {
        r.setSize({ 100, 100 });
        r.setPosition({ 100, 100 });
    }
    virtual void tick() {
        cout << "fff" << endl;
    }
    virtual void draw(sf::RenderWindow &w) {
        w.draw(r);
    }
};


class SampleProject : 
	public Project {
public:
    ~SampleProject() {
    }
    void attached() {
    }
    void detached() {
    }
    void beginPlay() {
    }
    void endPlay() {
    }
};