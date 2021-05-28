#pragma once
#ifndef _DllSystem
#define _DllSystem

#include <string>
#include <tchar.h>
#include <thread>
using namespace std;


struct HINSTANCE__;
typedef HINSTANCE__ *HINSTANCE;

class DynamicLibrary {
	HINSTANCE instance;
	string dllPath;

	void dllBeGone();
public:
	virtual ~DynamicLibrary();
	bool load(string dllPath = "");
	void unload();
	template<class T> T getFunc(string data);

	bool isLoaded() { return instance; }
	string getPath() { return dllPath; };
	HINSTANCE &getHandler() { return instance; };
};
#endif // !_DllSystem