#include <cstdio>
#include "map.h"

int main(int argc, char* argv[]) {
	if (argc != 2) {
		printf("Usage: %s\n", argv[0]);
		return 1;
	}

	Map board(argv[1]);
	board.print();

	board.sonar(12, 0, 4);
	board.print();

	board.undo();
	board.print();

	board.undo();
	board.print();

	return 0;
}
