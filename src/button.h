#ifndef BUTTON_H
#define BUTTON_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

#include "map.h"

class Button {
public:
	SDL_Rect rect;
	SDL_Color background_color;
	std::string text;
	TTF_Font* font;

	Button();
	Button(int x, int y, int w, int h, const SDL_Color &color, const std::string &button_text, TTF_Font *button_font);
	~Button();

	void render(SDL_Renderer *renderer);
	bool is_mouse_over(int mouse_x, int mouse_y);
	bool is_clicked(SDL_Event &e);

};

#endif