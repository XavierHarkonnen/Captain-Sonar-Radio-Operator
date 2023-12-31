#include "button.h"

Button::Button(int x, int y, int w, int h, const SDL_Color &color, const std::string &button_text, TTF_Font *button_font) {
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	background_color = color;
	text = button_text;
	font = button_font;
}

Button::~Button() {
	// Clean up resources
}

void Button::render(SDL_Renderer* renderer) {
	// Render the button background
	SDL_SetRenderDrawColor(renderer, background_color.r, background_color.g, background_color.b, background_color.a);
	SDL_RenderFillRect(renderer, &rect);

	// Render the text
	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), {255, 255, 255, 255});
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	int text_width, text_height;
	SDL_QueryTexture(texture, nullptr, nullptr, &text_width, &text_height);

	SDL_Rect text_rect;
	text_rect.x = rect.x + (rect.w - text_width) / 2;
	text_rect.y = rect.y + (rect.h - text_height) / 2;
	text_rect.w = text_width;
	text_rect.h = text_height;

	SDL_RenderCopy(renderer, texture, nullptr, &text_rect);

	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}

bool Button::is_mouse_over(int mouse_x, int mouse_y) {
	return (mouse_x >= rect.x && mouse_x < rect.x + rect.w && mouse_y >= rect.y && mouse_y < rect.y + rect.h);
}

bool Button::is_clicked(SDL_Event& e) {
	if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
		int mouse_x, mouse_y;
		SDL_GetMouseState(&mouse_x, &mouse_y);
		return is_mouse_over(mouse_x, mouse_y);
	}
	return false;
}
