#include "main_initialization.h"

#include <SDL2/SDL_ttf.h>

bool main_initialize(
	SDL_Window *&window,
	SDL_Renderer *&renderer,
	TTF_Font *&grid_font,
	TTF_Font *&button_font,
	Map*& map,
	int argc,
	char* argv[]
	) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		sig_err("SDL initialization failed: %s\n", SDL_GetError());
		return false;
	}

	if (TTF_Init() == -1) {
		sig_err("SDL True Type Font initialization failed: %s\n", SDL_GetError());
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

	grid_font = TTF_OpenFont("assets/OpenSans-Regular.ttf", GRID_FONT_SIZE);
	if (grid_font == nullptr) {
		sig_err("Grid font could not be found: %s\n", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return false;
	}
	
	button_font = TTF_OpenFont("assets/OpenSans-Regular.ttf", BUTTON_FONT_SIZE);
	if (button_font == nullptr) {
		sig_err("Button font could not be found: %s\n", SDL_GetError());
		TTF_CloseFont(grid_font);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return false;
	}

	if (argc != 2) {
		sig_err("Program takes map filename as the sole argument");
		TTF_CloseFont(button_font);
		TTF_CloseFont(grid_font);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return false;
	}
	map = new Map(argv[1]);

	return true;
}
