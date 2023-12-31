#include "signal.h"

#include <stdio.h>
#include <stdarg.h>

#define ANSI_RESET "\033[0m"
#define BOLD_RED "\033[1;31m"
#define BOLD_YELLOW "\033[1;33m"

void sig_error(const char *message, ...) {
    va_list args;
    va_start(args, message);

	printf("%sERROR:%s ", BOLD_RED, ANSI_RESET);
    vprintf(message, args);
	printf("\n");

    va_end(args);
}

void sig_warn(const char *message, ...) {
    va_list args;
    va_start(args, message);

	printf("%sWARNING:%s ", BOLD_RED, ANSI_RESET);
    vprintf(message, args);
	printf("\n");

    va_end(args);
}