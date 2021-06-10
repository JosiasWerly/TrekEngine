#pragma once 


#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <string>
#include <iostream>
#include <list>
#include <set>
#include <thread>

#include "DllSystem.hpp"


class Stack {
protected:
	int val[10];
	int size = sizeof(val) / sizeof(int);
	int it = 0;
	Stack() {
		for (size_t i = 0; i < size; i++)
			val[i] = 0;
	}
public:	
	virtual void push(int i) = 0;
	virtual int totalSum() = 0;
	virtual int *getValue() = 0;
};

extern "C" TApi Stack *getStack();

using namespace std;
using namespace sf;