#ifndef _AssetSystem
#define _AssetSystem
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

    IFactory *getFactory(string ext) {
        ext = ext.substr(ext.find_last_of('.'));
        for (auto &f : factories) {
            if (f->checkExtension(ext))
                return f;
        }
        return nullptr;
    }
    IAsset *getAsset(string name) {
        if (assets.count(name))
            return assets[name];
        return nullptr;
    }
    void unloadAssets(list<string> names) {
        for (auto &n : names) {
            if (assets.count(n) > 0) {
                IFactory *fac = getFactory(n);
                if (fac) {
                    fac->dismountAsset(assets[n]);
                    cout << ">> " << n << endl;
                }
            }
        }
    }
    void loadAssets(list<string> names) {
        for (auto &n : names) {
            if (!assets.count(n)) {
                IFactory *fac = getFactory(n);
                if (fac) {
                    IAsset *asset = fac->mountAsset(n);
                    if (asset) {
                        assets[n] = asset;
                        cout << "<< " << n << endl;
                    }
                }
            }
        }
    }
};
#endif // !_AssetSystem