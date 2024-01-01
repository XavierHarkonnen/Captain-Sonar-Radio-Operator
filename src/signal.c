#include "signal.h"

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#define RESET "\033[0m"
#define ERR_COL "\033[1;31m"
#define WARN_COL "\033[1;33m"
#define INFO_COL "\033[1;36m"
#define QUERY_COL "\033[1;35m"

void sig_err(const char *message, ...) {
	va_list args;
	va_start(args, message);

	printf("%sERROR:%s ", ERR_COL, RESET);
	vprintf(message, args);
	printf("\n");

	va_end(args);
}

void sig_warn(const char *message, ...) {
	va_list args;
	va_start(args, message);

	printf("%sWARNING:%s ", WARN_COL, RESET);
	vprintf(message, args);
	printf("\n");

	va_end(args);
}

void sig_info(const char *message, ...) {
	va_list args;
	va_start(args, message);

	printf("%sINFO:%s ", INFO_COL, RESET);
	vprintf(message, args);
	printf("\n");

	va_end(args);
}

char *sig_query(const char *message, ...) {
	va_list args;
	va_start(args, message);

	printf("%sQUERY:%s ", QUERY_COL, RESET);
	vprintf(message, args);
	printf("\n");

	char buffer[256];
		if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
			size_t len = strlen(buffer);
			if (len > 0 && buffer[len - 1] == '\n') {
				buffer[len - 1] = '\0';
			}
		return strdup(buffer);
	}

	return NULL;
}
