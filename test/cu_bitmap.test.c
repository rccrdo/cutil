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

#include <stdio.h>
#include <string.h>

/* buil with:  
   gcc -g -O2 -Wall -o cu_bitmap.test -I../src/ cu_bitmap.test.c
*/

#define times (unsigned int) 100000000
#define SET_CHAR (char) 0x05
//#define VERBOSE

#define BENCH_LIBSB
//#define BENCH_STD

#define BENCH_SEQ_ACCESS

#ifdef BENCH_LIBSB
#include "cu_bitmap.h"
#endif

#ifdef BENCH_STD
#include <vector>
#endif

int main() {
	unsigned int i;
	printf(" * test cu_bitmap\n");

#ifdef BENCH_LIBSB
	printf(" * build cu_bitmap\n");
	struct cu_bitmap bitmap;
	cu_bitmap_init(&bitmap, times);
	for (i=0; i<times; i++)
		if (i & 0x0101) cu_bitmap_set_bit(&bitmap, i);
#endif
  
#ifdef BENCH_STD
	printf(" * build std_bitmap\n");
	std::vector<bool> std_bitmap(times);
	for (i=0; i<times; i++)
	{
		if (i & 0x0101) std_bitmap[i] = true;
	}
#endif


#ifdef BENCH_SEQ_ACCESS
#ifdef BENCH_LIBSB
	printf(" * check sequential access\n");
	for (i=0; i<times; i++)
		if ((i & 0x0101) && !cu_bitmap_get_bit(&bitmap, i))
			printf("bit has bad value at place %d\n", i );
#endif
    
#ifdef BENCH_STD
	printf(" * check sequential access STD\n");
	for (i=0; i<times; i++)
		if ((i & 0x0101) && !std_bitmap[i])
			printf("bit has bad value at place %d\n", i );
#endif
#endif


#ifdef BENCH_LIBSB
	cu_bitmap_deinit(&bitmap);
#endif

	return 0;
}
