#ifndef MAIN_INITIALIZATION_H
#define MAIN_INITIALIZATION_H

#include <SDL2/SDL.h>
#include "map.h"
#include "button.h"

extern "C" {
	#include "signal.h"
}

constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 600;
constexpr int GRID_FONT_SIZE = 48;
constexpr int BUTTON_FONT_SIZE = 24;
constexpr int BUTTON_WIDTH = 180;
constexpr int BUTTON_HEIGHT = 70;
const SDL_Color BUTTON_COLOR = {128, 128, 128, 255};

enum Buttons {
	SONAR,
	DRONE,
	HIT,
	LAUNCH,
	SILENCE,
	NUM_BUTTONS
};

bool main_initialize(
	SDL_Window*& window,
	SDL_Renderer*& renderer,
	TTF_Font *&grid_font,
	TTF_Font *&button_font,
	Map*& map,
	Button *buttons,
	int argc,
	char* argv[]
	);

#endif