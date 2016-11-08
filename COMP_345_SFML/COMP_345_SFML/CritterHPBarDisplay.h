/*******************************************************************************************************************/
// This is the class that is in charge of keeping track of the CritterHPWidth as HP changes so we can update the HP 
// Bar in the GUI
/*******************************************************************************************************************/
#pragma once
#include "Critter.h"
#include "Observer.h"
#include "Map.h"
class CritterHPBarDisplay : public Observer
{
public:
	CritterHPBarDisplay(Critter* critter);
	~CritterHPBarDisplay();
	void update();

private:
	Critter* critter;
}; 

