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
	long long _getFunc(string &fName);
public:
	virtual ~DynamicLibrary();
	bool load(string dllPath = "");
	void unload();
	template<class T> T getFunc(string data) {
		return (T)_getFunc(data);
	}
	bool isLoaded() { return instance; }
	string getPath() { return dllPath; };
	HINSTANCE &getHandler() { return instance; };
};

#ifdef TProject
#define TApi __declspec(dllexport)
#else
#define TApi __declspec(dllimport)
#endif

#endif // !_DllSystem