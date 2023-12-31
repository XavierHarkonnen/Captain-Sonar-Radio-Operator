#ifndef MAIN_INITIALIZATION_H
#define MAIN_INITIALIZATION_H

#include <SDL2/SDL.h>
#include "map.h"

extern "C" {
	#include "signal.h"
}

constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 600;
constexpr int GRID_FONT_SIZE = 48;
constexpr int BUTTON_FONT_SIZE = 48;


bool main_initialize(
	SDL_Window*& window,
	SDL_Renderer*& renderer,
	TTF_Font *&grid_font,
	TTF_Font *&button_font,
	Map*& map,
	int argc,
	char* argv[]
	);

#endif