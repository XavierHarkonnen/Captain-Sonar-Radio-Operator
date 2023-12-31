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
				case SDL_KEYDOWN:
					switch (e.key.keysym.sym) {
						case SDLK_UP:
							board->move(NORTH);
							break;
						case SDLK_DOWN:
							board->move(SOUTH);
							break;
						case SDLK_LEFT:
							board->move(WEST);
							break;
						case SDLK_RIGHT:
							board->move(EAST);
							break;
						case SDLK_z:
							if (SDL_GetModState() & KMOD_CTRL) { board->undo(); }
							break;

            }

			}
		}

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);

		board->render(renderer);

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	delete board;
	return 0;
}