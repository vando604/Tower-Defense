#include "CritterFactory.h"

CritterFactory::CritterFactory(){}
CritterFactory::~CritterFactory(){}

Critter* CritterFactory::createCritter(std::string type, int level) {
	if (type == "normal")
		return new NormalCritter(level);

	if (type == "slow")
		return new SlowCritter(level);

	if (type == "fast")
		return new FastCritter(level);
	else
		return NULL;
}