#include "Trekkier.hpp"



#ifdef TProject

class SStack : 
	public Stack{
public:
	SStack() {
		for (size_t i = 0; i < size; i++)
			val[i] = 0;
	}

	void push(int i) {
		val[it++ % size] = i;
	}
	int totalSum() {
		int out = 0;
		for (size_t i = 0; i < size; i++)
			out += val[i];
		return out;
	}
	int *getValue() {
		return val;
	}

};



Stack *getStack() {
	static SStack s;
	return &s;
}
#endif // TProject