#include "Project.hpp"
static BatchDrawInstance *draws = nullptr;



class Content {
public:
    class Tile *owned = nullptr;
};

class Tile {
    Vector2f pos;
    RectangleShape r;

    friend Content;

    list<Content *> contents;
public:
    Tile(Vector2f pos, Vector2f size) :
        pos(pos){
        r.setSize(size);
        r.setFillColor(Color::Black);
        r.setOutlineThickness(-0.5);
        r.setOutlineColor(Color::Red);
        r.setPosition(pos);
        *draws << r;
    }
    ~Tile() {
        *draws >> r;
    }
    void attach(Content *c) {
        contents.push_back(c);
        c->owned = this;
    }
    void detach(Content *c) {
        contents.remove(c);
        c->owned = nullptr;
    }
};




class Level : 
    public Object{
public:   

    vector<vector<Tile *>> w;    
    void createWorld(vector<vector<Tile *>> &out, Vector2f tileSize, Vector2f worldSize) {
        int qtdX = (worldSize.x / tileSize.x),
            qtdY = (worldSize.y / tileSize.y);
        out.resize(qtdX);
        for (size_t x = 0; x < qtdX; x++) {
            for (size_t y = 0; y < qtdY; y++) {
                Vector2f pos = { x * tileSize.x, y * tileSize.y };
                out[x].push_back(new Tile(pos, tileSize));
            }
        }
    }
    Level() {
        createWorld(w, { 10, 10 }, { 800, 600 });

    }
    void tick() {

    }
};











































void SampleProject::attached() {
    //engine->renderSystem.renderWindow.setSize({ 800, 600 });
    //engine->renderSystem.renderWindow.setFramerateLimit(30);
    draws = new BatchDrawInstance;
    instantiate<Level>(new Level);
}
void SampleProject::detached() { 
    draws->draws.clear();
}
void SampleProject::beginPlay() {
}
void SampleProject::endPlay() {
}