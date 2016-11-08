/*******************************************************************************************************************/
//Using the factory pattern to generate a specific critter (depending on type).
/*******************************************************************************************************************/

#pragma once
#include "Critter.h"
#include"SlowCritter.h"
#include "NormalCritter.h"
#include "FastCritter.h"

class CritterFactory {
public:
	~CritterFactory();
	static Critter* createCritter(std::string type, int level);

private:
	CritterFactory();
};

