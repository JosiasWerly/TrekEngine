#include "Project.hpp"
static BatchDrawInstance *draws = nullptr;

class CacheInstance;
class ContentCache {
public:
    map<unsigned char, list<class CacheInstance*>> content;

    CacheInstance *create();
    void destroy(CacheInstance *inst);
};
class CacheInstance {
    friend ContentCache;
    ContentCache &cache;
    map<unsigned char, bool> layers;

    CacheInstance(ContentCache &cache) :
        cache(cache) {
    }
    ~CacheInstance() {
        for (auto &p : layers)
            if (p.second)
                setLayer(p.first, false);
    }
    void *target = nullptr;
public:
    void setTarget(void *trg) {
        target = trg;
    }
    void *getTarget() {
        return target;
    }
    void setLayer(unsigned char eType, bool enable) {
        layers[eType] = enable;
        if (enable)
            cache.content[eType].push_back(this);
        else
            cache.content[eType].remove(this);
    }
};
CacheInstance *ContentCache::create() {
    CacheInstance *out = new CacheInstance(*this);
    return out;
}
void ContentCache::destroy(CacheInstance *inst) {
    delete inst;
}






enum class eCacheType{
    none
};
class Content {
public:
    class Tile *owned = nullptr;
    ~Content(){}
};

class Tile {
    Vector2f pos;
    RectangleShape r;
public:
    Tile(Vector2f pos, Vector2f size) :
        pos(pos){
        r.setSize(size);
        r.setFillColor(Color::Red);
        r.setOutlineThickness(-0.5);
        r.setOutlineColor(Color::Red);
        r.setPosition(pos);
        //*draws << r;
    }
    ~Tile() {
        //*draws >> r;
    }

};



class Ball {
    CircleShape r;
public:
    Vector2f pos, vel;
    float rad;
    Ball(Vector2f pos = {100, 100}, Vector2f vel = { 1, 1 }, float radius = 10) :
        pos(pos),
        vel(vel),
        rad(radius){
        r.setRadius(radius);
        r.setPosition(pos);
        r.setFillColor(Color::Blue);
        r.setOrigin({ radius, radius });
        //r.setOutlineThickness(-0.5);
        r.setOutlineColor(Color::Red);
        //*draws << r;
    }
    ~Ball() {
        //*draws >> r;
    }
    void tick() {
        pos.x += vel.x;
        pos.y += vel.y;
        if (pos.x > 800)
            pos.x = 0;
        else if (pos.x < 0)
            pos.x = 800;

        if (pos.y > 600)
            pos.y = 0;
        else if (pos.y < 0)
            pos.y = 600;
        r.setPosition(pos);
    }
    void setColor(Color c) {
        r.setFillColor(c);
    }
};
class Level :
    public Object{
public:
    vector<Ball*> balls;    
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
        for (size_t i = 0; i < 100; i++) {
            balls.push_back(new Ball({ float(rand() % 200 + 100), float(rand() % 200 + 100) }, { rand()%10-5/10.f, rand() % 10 - 5 / 10.f }, 10));
        }
    }
    void tick() {
        unsigned int sz = balls.size();
        for (size_t i = 0; i < sz; i++){
            for (size_t ii = i + 1; ii < sz; ii++) {
                Ball
                    &a = *balls[i],
                    &b = *balls[ii];
                Vector2f dir = { a.pos.x - b.pos.x,  a.pos.y - b.pos.y };
                float dis = sqrtf(powf(dir.x, 2) + powf(dir.y, 2));
                if (dis <= a.rad + b.rad) {
                    a.setColor(Color::Red);
                    b.setColor(Color::Red);
                }
                engine->renderSystem.linesQuerry.querried.push_back({ a.pos , b.pos, Color(dis*3, dis * 3, dis * 3, 255)});
            }
        }
        //cout << tests << endl;
        for (auto& b: balls)
            b->tick();
    }
};











































void SampleProject::attached() {
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