#include "CritterHPBarDisplay.h"


CritterHPBarDisplay::CritterHPBarDisplay(Critter* critter)
{
	this->critter = critter;
}


CritterHPBarDisplay::~CritterHPBarDisplay()
{
}

void CritterHPBarDisplay::update(){
	// sets the HPBarWidth as HP changes
	critter->setHPBarWidth(critter->getHP() * 28 / critter->getMaxHP());
}
