#include <SDL2/SDL.h>
#include "map.h"
#include "main_initialization.h"

int main(int argc, char* argv[]) {
	SDL_Window *window = nullptr;
	SDL_Renderer *renderer = nullptr;
	Map *board = nullptr;

	if (!main_initialize(window, renderer, board, argc, argv)) {
		return 1;
	}

	SDL_Event e;
	bool running = true;
	while (running) {
		while (SDL_PollEvent(&e) != 0) {
			switch (e.type) {
				case SDL_QUIT:
					running = false;
					break;
			}
		}

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);

		board.render(renderer);

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	delete board;
	return 0;
}