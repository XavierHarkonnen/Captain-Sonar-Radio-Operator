#ifndef ERROR_H
#define ERROR_H

#include <iostream>
#include <cstdio>

#define ANSI_RESET "\033[0m"
#define BOLD_RED "\033[1;31m"
#define BOLD_YELLOW "\033[1;33m"

template <typename... Args>
void error(const char *message, Args&&... values) {
	std::cerr << BOLD_RED << "ERROR: " << ANSI_RESET;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat-security"
	std::printf(message, std::forward<Args>(values)...);
#pragma GCC diagnostic pop
	std::cerr << std::endl;
}

template <typename... Args>
void warn(const char *message, Args&&... values) {
	std::cout << BOLD_YELLOW << "WARN: " << ANSI_RESET;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat-security"
	std::printf(message, std::forward<Args>(values)...);
#pragma GCC diagnostic pop
	std::cout << std::endl;
}

#endif