/*******************************************************************************************************************/
//This type of critter is the type that moves fast on the map and has low health.
/*******************************************************************************************************************/

#pragma once
#include "Critter.h"

class FastCritter : public Critter {
public:
	FastCritter(int level);
	~FastCritter();
	int getSpeed();
	void setSpeed(int speed);
	int getHP();
	void setHP(int HP);
	float getHPBarWidth();
	void setHPBarWidth(float HPBarWidth);
	int getMaxHP() const;
	int getReward();
	void setReward(int reward);
	CritterStatus getCritterStatus();
	void setCritterStatus(CritterStatus critterStatus, float statusDuration);
};

