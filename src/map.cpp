#include "map.h"

extern "C" {
	#include "signal.h"
}

#define ANSI_RESET "\033[0m"
#define INVALID_COLOR "\033[101m"
#define ISLAND_COLOR "\033[43m"
#define VALID_COLOR "\033[104m"
#define BORDER_COLOR "\033[100m"

bool is_between(
	const uint8_t value_1,
	const uint8_t value_2,
	const uint8_t range[4]
	) {
	return (
		(range[0] <= value_1 && value_1 <= range[1]) &&
		(range[2] <= value_2 && value_2 <= range[3])
		);
}

void sector(const uint8_t sector_number, uint8_t sector_bounds[4]) {
	switch (sector_number) {
		case 1:
			sector_bounds[0] = 1;
			sector_bounds[1] = 5;
			sector_bounds[2] = 1;
			sector_bounds[3] = 5;
			break;
		case 2:
			sector_bounds[0] = 1;
			sector_bounds[1] = 5;
			sector_bounds[2] = 6;
			sector_bounds[3] = 10;
			break;
		case 3:
			sector_bounds[0] = 1;
			sector_bounds[1] = 5;
			sector_bounds[2] = 11;
			sector_bounds[3] = 15;
			break;
		case 4:
			sector_bounds[0] = 6;
			sector_bounds[1] = 10;
			sector_bounds[2] = 1;
			sector_bounds[3] = 5;
			break;
		case 5:
			sector_bounds[0] = 6;
			sector_bounds[1] = 10;
			sector_bounds[2] = 6;
			sector_bounds[3] = 10;
			break;
		case 6:
			sector_bounds[0] = 6;
			sector_bounds[1] = 10;
			sector_bounds[2] = 11;
			sector_bounds[3] = 15;
			break;
		case 7:
			sector_bounds[0] = 11;
			sector_bounds[1] = 15;
			sector_bounds[2] = 1;
			sector_bounds[3] = 5;
			break;
		case 8:
			sector_bounds[0] = 11;
			sector_bounds[1] = 15;
			sector_bounds[2] = 6;
			sector_bounds[3] = 10;
			break;
		case 9:
			sector_bounds[0] = 11;
			sector_bounds[1] = 15;
			sector_bounds[2] = 11;
			sector_bounds[3] = 15;
			break;
		default:
			sig_err("Invalid Sector Number: %u\n       Undo to Recover", sector_number);
			break;
	}
}

Map::Map(const char *filename) {
	FILE* map_file = fopen(filename, "r");
	if (!map_file) {
		sig_err("Could Not Open File: %s\n", filename);
	fclose(map_file);
	}
	else {
		char line_buffer[256];
		fgets(line_buffer, sizeof(line_buffer), map_file);
		sscanf(line_buffer, "%hhu", &rows);
		fgets(line_buffer, sizeof(line_buffer), map_file);
		sscanf(line_buffer, "%hhu", &columns);
		data.resize(rows, std::vector<Space>(columns, Space::VALID));
		for (uint8_t i = 0; i < rows; ++i) {
			fgets(line_buffer, sizeof(line_buffer), map_file);
			for (uint8_t j = 0; j < columns; ++j) {
				switch (line_buffer[j]) {
				case ' ':
					data[i][j] = Space::VALID;
					break;
				case 'I':
					data[i][j] = Space::ISLAND;
					break;
				case '#':
					data[i][j] = Space::BORDER;
					break;
				default:
					data[i][j] = Space::BORDER;
					sig_err("Invalid Character: %c (%i)", line_buffer[j], line_buffer[j]);
					continue;
				}
			}
		}
		fclose(map_file);
	}
};

void Map::undo() {
	if (!history.empty()) {
		data = history.back();
		history.pop_back();
	} else {
		sig_warn("Undo history is empty.");
	}
}

void Map::clear() {
	if (!history.empty()) {
		data = history.at(0);
		history.clear();
	} else {
		sig_warn("Nothing to clear, history is already empty.");
	}
}

void Map::move(Direction direction) {
	history.push_back(data);
	for (uint8_t i = 1; i < rows - 1; ++i) {
		for (uint8_t j = 1; j < columns - 1; ++j) {
			switch (direction) {
				case NORTH:
					if (data[i][j] == VALID && history.back()[i+1][j] != VALID) { data[i][j] = INVALID; }
					if (data[i][j] == INVALID && history.back()[i+1][j] == VALID) { data[i][j] = VALID; }
					break;
				case SOUTH:
					if (data[i][j] == VALID && history.back()[i-1][j] != VALID) { data[i][j] = INVALID; }
					if (data[i][j] == INVALID && history.back()[i-1][j] == VALID) { data[i][j] = VALID; }
					break;
				case WEST:
					if (data[i][j] == VALID && history.back()[i][j+1] != VALID) { data[i][j] = INVALID; }
					if (data[i][j] == INVALID && history.back()[i][j+1] == VALID) { data[i][j] = VALID; }
					break;
				case EAST:
					if (data[i][j] == VALID && history.back()[i][j-1] != VALID) { data[i][j] = INVALID; }
					if (data[i][j] == INVALID && history.back()[i][j-1] == VALID) { data[i][j] = VALID; }
					break;
			}
		}
	}
};

void Map::sonar(const uint8_t sector_number, const uint8_t row, const uint8_t column) {
	history.push_back(data);

	if (sector_number == 0) {
		for (uint8_t i = 1; i < rows - 1; ++i) {
			for (uint8_t j = 1; j < columns - 1; ++j) {
				if (data[i][j] == VALID) {
					if (!((i == row) ^ (j == column))) {
						data[i][j] = INVALID;
					}				
				}
			}
		}
	}
	else if (row == 0) {
		uint8_t sector_bounds[4];
		sector(sector_number, sector_bounds);

		for (uint8_t i = 1; i < rows - 1; ++i) {
			for (uint8_t j = 1; j < columns - 1; ++j) {
				if (data[i][j] == VALID) {
					if (!((is_between(i, j, sector_bounds)) ^ (j == column))) {
						data[i][j] = INVALID;
					}				
				}
			}
		}
	}
	else {
		uint8_t sector_bounds[4];
		sector(sector_number, sector_bounds);

		for (uint8_t i = 1; i < rows - 1; ++i) {
			for (uint8_t j = 1; j < columns - 1; ++j) {
				if (data[i][j] == VALID) {
					if (!((is_between(i, j, sector_bounds)) ^ (i == row))) {
						data[i][j] = INVALID;
					}				
				}
			}
		}
	}
};

void Map::drone(uint8_t sector_number, bool present) {
	history.push_back(data);

	uint8_t sector_bounds[4];
	sector(sector_number, sector_bounds);

	for (uint8_t i = 1; i < rows - 1; ++i) {
		for (uint8_t j = 1; j < columns - 1; ++j) {
			if (data[i][j] == VALID) {
				if (is_between(i, j, sector_bounds)) { data[i][j] = (Space) !present; }
				else { data[i][j] = (Space) present; }
			}
		}
	}
};

void Map::hit(const uint8_t row, const uint8_t column, const bool direct) {
	history.push_back(data);

	const uint8_t indirect_range[4] = {
		(uint8_t) (row-1),
		(uint8_t) (row+1),
		(uint8_t) (column-1),
		(uint8_t) (column+1)
		};

	for (uint8_t i = 1; i < rows - 1; ++i) {
		for (uint8_t j = 1; j < columns - 1; ++j) {
			if (direct && data[i][j] == VALID) {
				if (i == row && j == column) { data[i][j] = VALID; }
				else { data[i][j] =  INVALID; }
			}
			else if (!direct && data[i][j] == VALID) {
				if (i == row && j == column) { data[i][j] = INVALID; }
				else if (is_between(i, j, indirect_range)) {}
				else { data[i][j] =  INVALID; }
			}
		}
	}
};

void Map::launch(const uint8_t row, const uint8_t column) {
	history.push_back(data);

	data[row][column] = TEMP;

	for (uint8_t i = 0; i < 4; ++i) {
		for (uint8_t i = 1; i < rows - 1; ++i) {
			for (uint8_t j = 1; j < columns - 1; ++j) {
				if (
					data[i][j] == VALID &&
					(
						data[i+1][j] == TEMP ||
						data[i-1][j] == TEMP ||
						data[i][j+1] == TEMP ||
						data[i][j-1] == TEMP
					)
				) {
					data[i][j] = TEMP_2;
				}
			}
		}
		for (uint8_t i = 1; i < rows - 1; ++i) {
			for (uint8_t j = 1; j < columns - 1; ++j) {
				if (data[i][j] == TEMP_2) { data[i][j] = TEMP; }
			}
		}
	}

	for (uint8_t i = 1; i < rows - 1; ++i) {
		for (uint8_t j = 1; j < columns - 1; ++j) {
			if (data[i][j] == TEMP) { data[i][j] = VALID; }
			else if (data[i][j] == VALID) { data[i][j] = INVALID; }
		}
	}
};

void Map::silence() {
	history.push_back(data);

	for (uint8_t i = 0; i < 4; ++i) {
		for (uint8_t i = 1; i < rows - 1; ++i) {
			for (uint8_t j = 1; j < columns - 1; ++j) {
				if (
					data[i][j] == INVALID &&
					(
						data[i+1][j] == VALID ||
						data[i-1][j] == VALID ||
						data[i][j+1] == VALID ||
						data[i][j-1] == VALID
					)
				) {
					data[i][j] = TEMP;
				}
			}
		}
		for (uint8_t i = 1; i < rows - 1; ++i) {
			for (uint8_t j = 1; j < columns - 1; ++j) {
				if (data[i][j] == TEMP) { data[i][j] = VALID; }
			}
		}
	}
};

void Map::render(SDL_Renderer* renderer) {
    const int squareSize = 20;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            SDL_Rect rect;
            rect.x = j * squareSize;
            rect.y = i * squareSize;
            rect.w = squareSize;
            rect.h = squareSize;

            switch (data[i][j]) {
                case VALID:
                    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Green for valid
                    break;
                case INVALID:
                    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red for invalid
                    break;
                case ISLAND:
                    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Blue for island
                    break;
                case BORDER:
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White for border
                    break;
                default:
                    SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255); // Gray for unknown
                    break;
            }

            SDL_RenderFillRect(renderer, &rect);
        }
    }
}


void Map::print() {
	for (const std::vector<Space>& row : data) {
		for (Space value : row) {
			switch (value) {
				case VALID: printf("%s  %s", VALID_COLOR, ANSI_RESET); break;
				case INVALID: printf("%s  %s", INVALID_COLOR, ANSI_RESET); break;
				case ISLAND: printf("%sMM%s", ISLAND_COLOR, ANSI_RESET); break;
				case BORDER: printf("%s/\\%s", BORDER_COLOR, ANSI_RESET); break;
				default: printf("**"); break;
			}
		}
		printf("\n");
	}
}