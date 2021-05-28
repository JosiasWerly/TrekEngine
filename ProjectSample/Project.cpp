#include "Project.hpp"
class MyDraw :
    public DrawInstance {

    sf::RectangleShape r;
public:
    MyDraw() {
        name = "D";
        r.setSize({ 20, 20 });
        r.setPosition({ 100, 100 });
    }
    virtual void tick() {
        cout << "fff" << endl;
    }
    virtual void draw(sf::RenderWindow &w) {
        w.draw(r);
    }
};

MyDraw* myDraw;

void SampleProject::attached() {
    engine->renderSystem.renderWindow.setSize({ 800, 600 });
    instantiate<MyDraw>(new MyDraw);
    
    cout << "attach" << endl;
}
void SampleProject::detached() {
    cout << "detach" << endl;
}
void SampleProject::beginPlay() {
    myDraw = getObject<MyDraw>("D").getValue();
}
void SampleProject::endPlay() {
}