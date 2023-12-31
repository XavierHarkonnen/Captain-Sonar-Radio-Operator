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

	for (;;) {
		// input polling
		break;
	}
	return 0;
}
