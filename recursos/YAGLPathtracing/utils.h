/*
 * utils.h
 *
 *  Created on: Oct 27, 2018
 *      Author: jack
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <stdarg.h>  // For va_start, etc.
#include <memory>    // For std::unique_ptr
#include <stdio.h>
#include <string>

std::string string_format(const std::string fmt_str, ...) {
    int final_n, n = ((int)fmt_str.size()) * 2; /* Reserve two times as much as the length of the fmt_str */
    std::unique_ptr<char[]> formatted;
    va_list ap;
    while(1) {
        formatted.reset(new char[n]); /* Wrap the plain char array into the unique_ptr */
        strcpy(&formatted[0], fmt_str.c_str());
        va_start(ap, fmt_str);
        final_n = vsnprintf(&formatted[0], n, fmt_str.c_str(), ap);
        va_end(ap);
        if (final_n < 0 || final_n >= n)
            n += abs(final_n - n + 1);
        else
            break;
    }
    return std::string(formatted.get());
}



#endif /* UTILS_H_ */
