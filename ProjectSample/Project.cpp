#include "Project.hpp"

class Level : 
    public Object{
public:
    Level();
    void tick();
};


void SampleProject::attached() {
    instantiate<Level>(new Level);
}
void SampleProject::detached() { 
}
void SampleProject::beginPlay() {
}
void SampleProject::endPlay() {
}





class MyDraw :
    public DrawInstance {
    Image im;
    Sprite r;
public:
    MyDraw() {
        cout << "foo" << endl;
        instantiate<MyDraw>(this, false);
        
        auto t = new Texture;
        im.create(800, 600, sf::Color::White);
        t->loadFromImage(im);
        r.setTexture(*t, true);        
    }
    ~MyDraw() {
        delete r.getTexture();
    }
    void setPos(float x, float y) {
        r.setPosition(x, y);
    }
    inline void setPixel(unsigned int x, unsigned int y, sf::Color c) {
        im.setPixel(x, y, c);        
    }
    inline void update() {
        ((Texture *)r.getTexture())->update(im);
    }
    virtual void draw(sf::RenderWindow &w) {
        w.draw(r);
    }
};


MyDraw *d;
float t =0;
Level::Level() {
    //engine->renderSystem.renderWindow.setSize({ 800, 600 });
    d = new MyDraw;    
}
void Level::tick() {
    for (size_t x = 0; x < 800; x++)
        for (size_t y = 0; y < 600; y++) {
            Color c(0, 0, 0, 255);
            float dis = x / 800.f*3.14;
            c.r = sin(dis + sin(t)/3.14) * 255;

            //c.b = sin(y / t*100.f) * 255;
            d->setPixel(x, y, c);
        }
    t += .5;
    d->update();
}