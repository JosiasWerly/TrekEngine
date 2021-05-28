#include "DllSystem.hpp"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

//#define _HAS_STD_BYTE 0
#include <libloaderapi.h>

void DynamicLibrary::dllBeGone() {
	FreeLibraryAndExitThread(instance, DWORD(0));
}
DynamicLibrary::~DynamicLibrary() {
	if (instance)
		unload();
}
bool DynamicLibrary::load(string dllPath) {
	if (instance)
		return false;
	if (dllPath != "")
		this->dllPath = dllPath;
	auto STRtoWSTR = [](string &from)->wstring {
		wstring out;
		for (size_t i = 0; i < from.length(); i++)
			out += from.at(i);
		return out;
	};
	wstring wFullPath = STRtoWSTR(dllPath);
	instance = LoadLibrary((LPCWSTR)wFullPath.c_str());
	if (!instance)
		return false;
	return true;
}
void DynamicLibrary::unload() {
	std::thread th(&DynamicLibrary::dllBeGone, this);
	th.join();
	instance = nullptr;
}
long long DynamicLibrary::_getFunc(string &fName){
	return (long long)GetProcAddress(instance, (LPCSTR)fName.c_str());
}
//template<class T> T DynamicLibrary::getFunc(string data) {
//	T p = nullptr;
//	p = (T)GetProcAddress(instance, (LPCSTR)data.c_str());
//	return p;
//}
