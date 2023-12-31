#include <cstdio>
#include <cstring>
#include "map.h"

extern "C" {
	#include "signal.h"
}

int main(int argc, char* argv[]) {
	if (argc != 2) {
		sig_err("Program takes map filename as sole argument");
		return 1;
	}

	Map board(argv[1]);

	board.print();

	sig_err("This is an error");
	sig_warn("This is a warning");
	sig_info("This is information");

	/*
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
