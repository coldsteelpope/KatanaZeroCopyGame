#pragma once

#include <iostream>
#include <list>
#include <map>
#include <Windows.h>
#include <algorithm>
#include <vector>
#include <deque>

#include <io.h>


#include "fmod.h"
#include "fmod.hpp"
#pragma comment(lib, "fmodex_vc.lib")

using namespace std;

#include "Defines.h"
#include "PictureSize.h"




#ifdef _DEBUG

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifndef DBG_NEW 
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 
#define new DBG_NEW 

#endif
#endif
