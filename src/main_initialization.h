#ifndef MAIN_INITIALIZATION_H
#define MAIN_INITIALIZATION_H

#include <SDL2/SDL.h>
#include "map.h"

extern "C" {
	#include "signal.h"
}

constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 600;

/**
 * @brief 
 * 
 * @param window 
 * @param renderer 
 * @param board 
 * @param argc 
 * @param argv 
 * @return true 
 * @return false 
 */
bool main_initialize(SDL_Window*& window, SDL_Renderer*& renderer, Map*& map, int argc, char* argv[]);

#endif