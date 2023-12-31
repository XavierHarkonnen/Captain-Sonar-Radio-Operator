#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "map.h"
#include "main_initialization.h"
#include "button.h"

int main(int argc, char* argv[]) {
	TTF_Font *font = nullptr;
	SDL_Window *window = nullptr;
	SDL_Renderer *renderer = nullptr;
	Map *Board_Map = nullptr;

	if (!main_initialize(window, renderer, font, Board_Map, argc, argv)) {
		return 1;
	}

	Button Sonar_Button(500, 50, 200, 100, {255, 0, 0, 255}, "Sonar", font);
	Button Drone_Button(500, 200, 200, 100, {255, 0, 0, 255}, "Drone", font);
	Button Silence_Button(500, 350, 200, 100, {255, 0, 0, 255}, "Silence", font);

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
					else if (Silence_Button.is_clicked(e)) { Board_Map->silence(); }
					break;
				case SDL_KEYDOWN:
					switch (e.key.keysym.sym) {
						case SDLK_UP:
							Board_Map->move(NORTH);
							break;
						case SDLK_DOWN:
							Board_Map->move(SOUTH);
							break;
						case SDLK_LEFT:
							Board_Map->move(WEST);
							break;
						case SDLK_RIGHT:
							Board_Map->move(EAST);
							break;
						case SDLK_z:
							if (SDL_GetModState() & KMOD_CTRL) { Board_Map->undo(); }
							break;
						case SDLK_BACKSPACE:
							Board_Map->undo();
							break;
						case SDLK_DELETE:
							Board_Map->clear();
							break;
						


            }

			}
		}

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);

		Board_Map->render(renderer, font);
		Sonar_Button.render(renderer);
		Drone_Button.render(renderer);
		Silence_Button.render(renderer);

		SDL_RenderPresent(renderer);
	}
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	delete Board_Map;
	return 0;
}