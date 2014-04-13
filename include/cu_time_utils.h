/*
 * Copyright (c) 2007-2008 Riccardo Lucchese, riccardo.lucchese at gmail.com
 * 
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 * 
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 * 
 *    1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 
 *    2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 
 *    3. This notice may not be removed or altered from any source
 *    distribution.
 */

#ifndef cu_time_utils_h
#define cu_time_utils_h 1

#include <sys/time.h>
#include "cu_debug.h"


/**
 * Returns passed time between two given instants in microseconds
 * @old a struct timeval filled with valid data
 * @current a struct timeval filled with valid data
 */
inline unsigned int cu_time_passed(struct timeval* old, struct timeval* current);



unsigned int cu_time_passed(struct timeval* old, struct timeval* current) {
	assert(old);
	assert(current);
	return ((1000000*(current->tv_sec - old->tv_sec) + current->tv_usec) - old->tv_usec);
}

#endif /* cu_time_utils_h */

