#include "Path.h"
#include "GameConstants.h"
#include <string>
using namespace std;

Path::Path() : Entity(GameConstants::PATH_IMAGE_NAME){}

Path::Path(string image_name) : Entity(image_name){}