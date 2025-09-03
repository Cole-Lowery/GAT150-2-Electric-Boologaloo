#pragma once

//core
#include "Core/Factory.h"
#include "Core/File.h"
#include "Core/Logger.h"
#include "Core/Random.h"
#include "Core/Singleton.h"
#include "Core/StringHelper.h"
#include "Time.h"
#include "Core/Json.h"

//framework
#include "Framework/Object.h"
#include "Framework/Actor.h"
#include "Framework/Game.h"
#include "Framework/Scene.h"

//math
#include "Math/Math.h"
#include "Math/Transform.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Rect.h"

//physics
#include "Physics/Collidable.h"
#include "Physics/Physics.h"
#include "Physics/PhysicsBody.h"

//Resources
#include "Resources/Resource.h"
#include "Resources/ResourceManager.h"

//event manager
#include "Event/Event.h"
#include "Event/EventManager.h"
#include "Event/Observer.h"

// third-party libraries
#include <SDL3/SDL.h>
#include <fmod.hpp>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

// standard library
#include <string>
#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <cmath>
#include <map>
#include <list>
#include <cstdlib>
#include <algorithm>
#include <filesystem>
#include <fmod_errors.h>
