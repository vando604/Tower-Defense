/*******************************************************************************************************************/
//Used to implement the strategy pattern
/*******************************************************************************************************************/

#pragma once
#include <iostream>
#include <vector>
#include "Critter.h"
using namespace std;

class Strategy {
public:
	virtual int execute(vector<Critter*> critters, int towerX, int towerY, int towerRange) = 0;
};