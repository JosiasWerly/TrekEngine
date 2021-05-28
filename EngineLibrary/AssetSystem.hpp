#ifndef _AssetSystem
#define _AssetSystem
#include <string>
#include <iostream>
#include <list>
#include <set>
#include <map>
#include <thread>
using namespace std;

class IAsset {
public:
    virtual ~IAsset() {}
};
class IFactory {
public:
    virtual bool checkExtension(string ext) = 0;
    virtual IAsset *mountAsset(string path) = 0;
    virtual void dismountAsset(IAsset *newAsset) = 0;
};
class AssetSystem {
public:
    list<IFactory *> factories;
    map<string, IAsset *> assets;

    IFactory *getFactory(string ext);
    IAsset *getAsset(string name);
    void unloadAssets(list<string> names);
    void loadAssets(list<string> names);
};
#endif // !_AssetSystem