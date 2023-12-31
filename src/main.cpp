#include <cstdio>
#include "map.h"

extern "C" {
	#include "signal.h"
}

int main(int argc, char* argv[]) {
	if (argc != 2) {
		printf("Usage: %s\n", argv[0]);
		return 1;
	}

	sig_err("This is an error");
	sig_warn("This is a warning");
	sig_info("This is information");

	/*
	Map board(argv[1]);
	board.print();

	board.sonar(12, 0, 4);
	board.print();

	board.undo();
	board.print();

	board.undo();
	board.print();
	*/

	return 0;
}
