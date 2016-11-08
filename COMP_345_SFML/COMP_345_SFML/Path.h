/*******************************************************************************************************************/
//Used to display the paths on the map
/*******************************************************************************************************************/

#pragma once
#include "Entity.h"
#include <string>

class Path : public Entity {
public:
	Path();
	Path(std::string image_name);
};