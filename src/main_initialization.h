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
 * @brief Initializes SDL, creates a window and renderer, and loads a Map.
 * 
 * @param window A reference to a pointer to an SDL_Window that will be created.
 * @param renderer A reference to a pointer to an SDL_Renderer that will be created.
 * @param map A reference to a pointer to a Map that will be loaded.
 * @param argc The number of command-line arguments.
 * @param argv An array of strings representing the command-line arguments.
 * @return true if the initialization is successful.
 * @return false if the initialization fails.
 */
bool main_initialize(SDL_Window*& window, SDL_Renderer*& renderer, Map*& map, int argc, char* argv[]);

#endif