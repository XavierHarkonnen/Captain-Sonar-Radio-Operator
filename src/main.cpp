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

	if (!main_initialize(
		window,
		renderer,
		grid_font,
		button_font,
		board_map,
		argc,
		argv
		)) {
		return 1;
	}

	Button Sonar_Button(500, 50, 200, 100, {255, 0, 0, 255}, "Sonar", grid_font);
	Button Drone_Button(500, 200, 200, 100, {255, 0, 0, 255}, "Drone", grid_font);
	Button Silence_Button(500, 350, 200, 100, {255, 0, 0, 255}, "Silence", grid_font);

	SDL_Event e;
	bool running = true;
	while (running) {
		while (SDL_PollEvent(&e) != 0) {
			switch (e.type) {
				case SDL_QUIT:
					running = false;
					break;
				case SDL_MOUSEBUTTONDOWN:
					if (Sonar_Button.is_clicked(e)) { printf("Sonar Clicked!\n"); }
					else if (Drone_Button.is_clicked(e)) { printf("Drone Clicked!\n"); }
					else if (Silence_Button.is_clicked(e)) { board_map->silence(); }
					break;
				case SDL_KEYDOWN:
					switch (e.key.keysym.sym) {
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
		Sonar_Button.render(renderer);
		Drone_Button.render(renderer);
		Silence_Button.render(renderer);

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