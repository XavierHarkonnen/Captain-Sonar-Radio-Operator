#include "main_initialization.h"

bool main_initialize(SDL_Window*& window, SDL_Renderer*& renderer, Map*& map, int argc, char* argv[]) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		sig_err("SDL initialization failed: %s\n", SDL_GetError());
		return false;
	}

	window = SDL_CreateWindow(
		"SDL2 Interface Example",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN
	);

	if (!window) {
		sig_err("Window creation failed: %s\n", SDL_GetError());
		SDL_Quit();
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer) {
		sig_err("Renderer creation failed: %s\n", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_Quit();
		return false;
	}

	if (argc != 2) {
		sig_err("Program takes map filename as the sole argument");
		return false;
	}
	map = new Map(argv[1]);

	return true;
}
