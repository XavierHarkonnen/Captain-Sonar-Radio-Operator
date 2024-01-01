#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "map.h"
#include "main_initialization.h"
#include "button.h"

int main(int argc, char* argv[]) {
	SDL_Window *window = nullptr;
	SDL_Renderer *renderer = nullptr;
	TTF_Font *grid_font = nullptr;
	TTF_Font *button_font = nullptr;
	Map *board_map = nullptr;
	Button buttons[NUM_BUTTONS];

	if (!main_initialize(
		window,
		renderer,
		grid_font,
		button_font,
		board_map,
		buttons,
		argc,
		argv
		)) {
		return 1;
	}

	SDL_Event event;
	bool running = true;
	while (running) {
		while (SDL_PollEvent(&event) != 0) {
			switch (event.type) {
				case SDL_QUIT:
					running = false;
					break;
				case SDL_MOUSEBUTTONDOWN:
					for (int i = 0; i < NUM_BUTTONS; ++i) {
						if (buttons[i].is_clicked(event)) {
							printf("%s Clicked!\n", buttons[i].text.c_str());
						}
					}
					break;
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym) {
						case SDLK_UP:
							board_map->move(NORTH);
							break;
						case SDLK_DOWN:
							board_map->move(SOUTH);
							break;
						case SDLK_LEFT:
							board_map->move(WEST);
							break;
						case SDLK_RIGHT:
							board_map->move(EAST);
							break;
						case SDLK_z:
							if (SDL_GetModState() & KMOD_CTRL) { board_map->undo(); }
							break;
						case SDLK_BACKSPACE:
							board_map->undo();
							break;
						case SDLK_DELETE:
							board_map->clear();
							break;
						


			}

			}
		}

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);

		board_map->render(renderer, grid_font);
		for (int i = 0; i < NUM_BUTTONS; ++i) {
			buttons[i].render(renderer);
		}


		SDL_RenderPresent(renderer);
	}
	TTF_CloseFont(grid_font);
	TTF_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	delete board_map;
	return 0;
}