#ifndef HEADER_H
#define HEADER_H

/* DEFINITIONS =================================================================================================== */

#define PI 3.141592f

#define RESET true
#define DEBUG_MODE true
#define PRIORITARY true

#define COLLIDEABLE true
#define NOT_COLLIDEABLE false

#define SHOW_COL_BOX true
#define DO_NOT_SHOW_COL_BOX false

#define SHOW_HITBOX true
#define DO_NOT_SHOW_HITBOX false

#define USE_DEFERRED_RENDER true
#define DO_NOT_USE_DEFERRED_RENDER false

#define USE_FADE_FX true
#define DO_NOT_USE_FADE_FX false

/* CORE ========================================================================================================== */

#include <algorithm>
#include <cmath>
#include <deque>
#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <sys/types.h>
#include <dirent.h>
#include <thread>
#include <utility>
#include <vector>
#include <list>
#include <stack>
#include <string>
#include <sstream>
#include <fstream>
#include <filesystem>

/* UTILS ========================================================================================================= */

#include "ErrorHandler.h"

/* SFML ========================================================================================================== */

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#endif
