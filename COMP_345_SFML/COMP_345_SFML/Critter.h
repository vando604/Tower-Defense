/*******************************************************************************************************************/
//The Critter abstract class where every type of critter will inherit from it. It also extends Entity to be displayed
//in the map
/*******************************************************************************************************************/

#pragma once
#include "Entity.h"

enum CritterStatus { NORMAL, BURN };

class Critter : public Entity {
public:
	virtual int getSpeed() = 0;
	virtual int getHP() = 0;
	virtual int getMaxHP() const = 0;
	virtual int getReward() = 0;
	virtual float getHPBarWidth() = 0;
	virtual CritterStatus getCritterStatus() = 0;
	virtual void setHP(int HP) = 0;
	virtual void setReward(int reward) = 0;
	virtual void setSpeed(int speed) = 0;
	virtual void setHPBarWidth(float HPBarWidth) = 0;
	virtual void setCritterStatus(CritterStatus critterStatus, float statusDuration) = 0;
	void move();
	int getStep();
	void tick(sf::Time pausedTime);
	~Critter(){};
	Critter();
	Critter(std::string imageName);

protected:
	int maxHP;
	int HP;
	int speed;
	int reward;
	int level;
	int step;
	float HPBarWidth;
	CritterStatus critterStatus;
	sf::Clock critterClock;
	float statusTime;
};