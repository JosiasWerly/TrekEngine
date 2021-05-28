#include "AssetSystem.hpp"

IFactory *AssetSystem::getFactory(string ext) {
	ext = ext.substr(ext.find_last_of('.'));
	for (auto &f : factories) {
		if (f->checkExtension(ext))
			return f;
	}
	return nullptr;
}
IAsset *AssetSystem::getAsset(string name) {
	if (assets.count(name))
		return assets[name];
	return nullptr;
}
void AssetSystem::unloadAssets(list<string> names) {
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
void AssetSystem::loadAssets(list<string> names) {
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