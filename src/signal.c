#include "signal.h"

#include <stdio.h>
#include <stdarg.h>

#define RESET "\033[0m"
#define ERR_COL "\033[1;31m"
#define WARN_COL "\033[1;33m"
#define INFO_COL "\033[1;36m"

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