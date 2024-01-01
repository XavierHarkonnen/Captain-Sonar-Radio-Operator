#ifndef ERROR_H
#define ERROR_H

/**
 * @brief Signal occurrence of error to user
 * 
 * @param message Formatted message to accompany error
 * @param ... Variables to be formatted within message
 */
void sig_err(const char *message, ...);
/**
 * @brief Signal warning to user
 * 
 * @param message Formatted message to accompany warning
 * @param ... Variables to be formatted within message
 */
void sig_warn(const char *message, ...);
/**
 * @brief Signal non-critical data to user
 * 
 * @param message Formatted message to accompany info
 * @param ... Variables to be formatted within message
 */
void sig_info(const char *message, ...);
/**
 * @brief Asks the user for information
 * 
 * @param message Formatted message to accompany query
 * @param ... Variables to be formatted within message
 */
char *sig_query(const char *message, ...);

#endif