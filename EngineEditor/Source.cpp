#pragma once
#define TProject
#include <EngineLibrary/Trekkier.hpp>


int main() {
	
    DynamicLibrary dl;
    dl.load("C:\\Users\\josia\\Desktop\\Bigmoxi\\Sandbox\\EngineTest\\Trek\\Build\\Debug\\x64\\EngineLibrary\\EngineLibrary.dll");
    if (dl.isLoaded()) {
        cout << "at least loaded" << endl;
		auto fn = dl.getFunc<Stack *(*)()>("getStack");
		Stack *s = fn();
		int i = 0;
		while (true) {
			cin >> i;
			s->push(i);
			cout << "sum:" << s->totalSum() << endl;
		}
    }


    return 0;
}