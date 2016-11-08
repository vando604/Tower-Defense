/*******************************************************************************************************************/
// This type of critter is the type that moves slowly on the map and has high health.
/*******************************************************************************************************************/

#pragma once
#include "Critter.h"

class SlowCritter : public Critter {
public:
	SlowCritter();
	SlowCritter(int level);
	~SlowCritter();
	int getSpeed();
	void setSpeed(int speed);
	int getMaxHP() const;
	int getHP();
	void setHP(int newHP);
	float getHPBarWidth();
	void setHPBarWidth(float HPBarWidth);
	int getReward();
	void setReward(int reward);
	CritterStatus getCritterStatus();
	void setCritterStatus(CritterStatus critterStatus, float statusDuration);
};

