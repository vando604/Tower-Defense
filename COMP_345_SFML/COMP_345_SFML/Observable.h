/*******************************************************************************************************************/
//Used to implement the observer pattern
/*******************************************************************************************************************/

#pragma once
#include "Observer.h"

class Observable {
public:
	Observable();
	virtual ~Observable();
	void addObserver(Observer* o);
	void removeObserver(Observer* o);

protected:
	void notify();

private:
	const int observerCap = 10;
	Observer** observers;
};