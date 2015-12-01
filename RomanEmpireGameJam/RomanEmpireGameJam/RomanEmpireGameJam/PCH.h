// PCH.h
#pragma once

//Native
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <fstream>
#include <string>
#include <stdio.h>
#include <time.h>
#include <typeinfo>
#include <memory>
#include <typeinfo>
#include <typeindex>
#include <functional>

//SDL
#include <SDL.h>
#include <SDL_image.h>

//Defines
//For use with raw ptrs
#define SAFE_DELETE(x) {if(x){delete x; x = nullptr;}}

//Typedef's

