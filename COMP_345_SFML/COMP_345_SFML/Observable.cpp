#include "Observable.h"
#include "Observer.h"
#include <iostream>

Observable::Observable() {
	this->observers = new Observer*[observerCap];
	for (int i = 0; i < observerCap; ++i) {
		observers[i] = nullptr;
	}
}

Observable::~Observable() {
	delete[] this->observers;
}

void Observable::addObserver(Observer* o) {
	for (int i = 0; i < observerCap; ++i) {
		if (observers[i] == nullptr) {
			observers[i] = o;
			break;
		}
	}
}

void Observable::removeObserver(Observer* o) {
	for (int i = 0; i < observerCap; ++i) {
		if (observers[i] == o) {
			observers[i] = nullptr;
			break;
		}
	}
}

void Observable::notify() {
	for (int i = 0; i < observerCap; ++i) {
		if (observers[i] != nullptr) {
			observers[i]->update();
		}
	}
}