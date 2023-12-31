#ifndef MAP_H
#define MAP_H

#include <cstdint>
#include <vector>
#include <cstdint>
#include <cstdio>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

enum Space {
	VALID,
	INVALID,
	ISLAND,
	BORDER,
	TEMP,
	TEMP_2
};

enum Direction {
	NORTH,
	SOUTH,
	EAST,
	WEST
};

class Map {
private:
	uint8_t rows;
	uint8_t columns;
	std::vector<std::vector<Space>> data;
	std::vector<std::vector<std::vector<Space>>> history;

public:
	/**
	 * @brief Constructor for the Map class.
	 * @param filename The name of the file containing the map configuration.
	 */
	Map(const char *filename);

	/**
	 * @brief Undo the last map modification.
	 */
	void undo();
	/**
	 * @brief Clear the entire map history.
	 */
	void clear();

	/**
	 * @brief Calculate possible positions after movement in the specified direction.
	 * @param direction The moved direction.
	 */
	void move(Direction direction);
	/**
	 * @brief Calculate possible positions given two parameters (one true, one false).
	 * @param sector_number The sector number (0 for not specifying sector).
	 * @param row The target row for sonar (0 for not specifying row).
	 * @param column The target column for sonar (0 for not specifying column, default).
	 */
	void sonar(const uint8_t sector, const uint8_t row, const uint8_t column);
	/**
	 * @brief Calculate possible positions given presence in a sector.
	 * @param sector_number The sector tested.
	 * @param present Whether the opponent was within the tested sector.
	 */
	void drone(const uint8_t sector, const bool present);
	/**
	 * @brief Calculate possible positions given a hit.
	 * @param row The row of the hit.
	 * @param column The column of the hit.
	 * @param direct True for a direct hit, false for an indirect hit.
	 */
	void hit(const uint8_t row, const uint8_t column, const bool direct);
	/**
	 * @brief Calculate possible positions given a launch.
	 * @param row The row targeted by the launch.
	 * @param column The column targeted by the launch.
	 */
	void launch(const uint8_t row, const uint8_t column);
	 /**
	 * @brief Calculate possible positions given opponent silencing.
	 */
	void silence();

	/**
	 * @brief 
	 * 
	 * @param renderer 
	 * @param font 
	 */
	void render(SDL_Renderer* renderer ,TTF_Font* font);

	/**
	 * @brief 
	 * 
	 * @param renderer 
	 * @param number 
	 * @param rect 
	 * @param font 
	 */
	void render_letter(SDL_Renderer* renderer, int number, SDL_Rect rect, TTF_Font* font);
	
	/**
	 * @brief 
	 * 
	 * @param renderer 
	 * @param number 
	 * @param rect 
	 */
	void render_number(SDL_Renderer* renderer, int number, SDL_Rect rect, TTF_Font* font);

	/**
	 * @brief Print the current state of the map.
	 */
	void print();
};

#endif