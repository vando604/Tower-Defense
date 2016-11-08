/*******************************************************************************************************************/
//This is the regular critter in the game (no specific special attribute).
/*******************************************************************************************************************/

#pragma once
#include "Critter.h"

class NormalCritter : public Critter {
public:
	NormalCritter(int level);
	~NormalCritter();
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

