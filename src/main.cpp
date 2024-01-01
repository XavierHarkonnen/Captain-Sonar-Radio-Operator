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
							switch (i) {
								case SONAR: {
									char *sonar_input = sig_query("Enter Sonar results (sector, row, column) separated by spaces as NUMBER NUMBER LETTER.  0 implies a non-used parameter.");
									int sector, row;
									char column;

									if (sscanf(sonar_input, "%d %d %c", &sector, &row, &column) == 3) {
										if ('a' <= column && column <= 'z') {
											column = column - 'a' + 1;
										} else if ('A' <= column && column <= 'Z') {
											column = column - 'A' + 1;
										} else {
											sig_err("Invalid input format for column. Please enter a valid letter.");
											break;
										}
										board_map->sonar(sector, row, column);
									} else {
										sig_err("Invalid input format. Please enter three space-separated values.");
									}
									break;
								}
								case DRONE: {
									char *sonar_input = sig_query("Enter Drone results (sector, present) separated by spaces as NUMBER LETTER.  Enter 'y' if the opponent was present.");
									int sector;
									char present;

									if (sscanf(sonar_input, "%d %c", &sector, &present) == 2) {
										if (present == 'y') { board_map->drone(sector, true); }
										else { board_map->drone(sector, false); }
									} else {
										sig_err("Invalid input format. Please enter two space-separated values.");
									}
									break;
								}
								case HIT: {
									char *sonar_input = sig_query("Enter Hit location (column, row, direct) separated by spaces as NUMBER LETTER LETTER. Enter 'y' if the hit was direct");
									int row;
									char column, direct;

									if (sscanf(sonar_input, "%d %c %c", &row, &column, &direct) == 3) {
										if ('a' <= column && column <= 'z') {
											column = column - 'a' + 1;
										} else if ('A' <= column && column <= 'Z') {
											column = column - 'A' + 1;
										} else {
											sig_err("Invalid input format for column. Please enter a valid letter.");
											break;
										}
										if (direct == 'y') { board_map->hit(row, column, true); }
										else { board_map->hit(row, column, false); }
									} else {
										sig_err("Invalid input format. Please enter two space-separated values.");
									}
									break;
								}
								case LAUNCH: {
									char *sonar_input = sig_query("Enter Hit location (column, row, direct) separated by spaces as NUMBER LETTER LETTER. Enter 'y' if the hit was direct");
									int row;
									char column;

									if (sscanf(sonar_input, "%d %c", &row, &column) == 2) {
										if ('a' <= column && column <= 'z') {
											column = column - 'a' + 1;
										} else if ('A' <= column && column <= 'Z') {
											column = column - 'A' + 1;
										} else {
											sig_err("Invalid input format for column. Please enter a valid letter.");
											break;
										}
										board_map->launch(row, column);
									} else {
										sig_err("Invalid input format. Please enter two space-separated values.");
									}
									break;
								}
								case SILENCE:
									board_map->silence();
									break;
							}
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

	TTF_CloseFont(button_font);
	TTF_CloseFont(grid_font);
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	delete board_map;

	return 0;
}