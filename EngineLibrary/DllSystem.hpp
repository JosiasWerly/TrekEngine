#pragma once
#ifndef _DllSystem
#define _DllSystem

#include <windows.h>
#include <libloaderapi.h>

#include <tchar.h>
class DynamicLibrary {
    HINSTANCE instance;
    string dllPath;

    void dllBeGone() {
        FreeLibraryAndExitThread(instance, DWORD(0));
    }
public:
    virtual ~DynamicLibrary() {
        if (instance)
            unload();
    }
    bool load(string dllPath = "") {
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
    void unload() {
        std::thread th(&DynamicLibrary::dllBeGone, this);
        th.join();
        instance = nullptr;
    }
    template<class T> T getFunc(string data) {
        T p = nullptr;
        p = (T)GetProcAddress(instance, (LPCSTR)data.c_str());
        return p;
    }

    bool isLoaded() { return instance; }
    string getPath() { return dllPath; };
    HINSTANCE &getHandler() { return instance; };
};

#endif // !_DllSystem