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
#include "cu_memblock.h"

/* buil with:  
   gcc -g -O3 -Wall -o cu_memblock.test -I../src/ cu_memblock.test.c
*/

#define times (unsigned int) 200000
#define SET_CHAR (char) 0x05
//#define VERBOSE

int main() {
	unsigned int i;
	printf(" * test cu_memblock\n");
	printf(" ! check memory usage while running the test (it shouldn't grow)\n\n");

	printf(" * check leak 1\n");
	for (i=1; i< times; i++)
	{
#ifdef VERBOSE
		printf("%d\n", i);
#endif
		struct cu_memblock mb;
		cu_memblock_init(&mb, i);
		cu_memblock_set(&mb, 0);
		cu_memblock_deinit(&mb);
	}

	printf(" * check _set_size\n");
	{
		struct cu_memblock mb;
		cu_memblock_init(&mb, 1);
		for (i=1; i< times; i++)
		{
#ifdef VERBOSE
			printf("%d\n", i);
#endif
			cu_memblock_set_size(&mb, i);
			cu_memblock_set(&mb, 0xFF);
		}
		cu_memblock_deinit(&mb);
	}


	printf(" * check _assign\n");
	{
		struct cu_memblock mb;
		cu_memblock_init(&mb, 1);
		char rnd_pattern[times];
		for (i=1; i< times; i++)
			rnd_pattern[i] = (char)i;

		for (i=1; i< times; i++)
		{
#ifdef VERBOSE
			printf("%d\n", i);
#endif
			cu_memblock_assign(&mb, (const char*) rnd_pattern, i);
			if (strncmp((const char*)rnd_pattern, (const char*)mb.mem, i)!=0) 
				printf(" ! assign failed at iteration: %d:\n", i);
		}
		cu_memblock_deinit(&mb);
	}


	printf(" * check _set\n");
	{
		struct cu_memblock mb;
		cu_memblock_init(&mb, 1);
		for (i=1; i< times; i++)
		{
			unsigned int j;
#ifdef VERBOSE
			printf("%d\n", i);
#endif
			cu_memblock_set_size(&mb, i);
			cu_memblock_set(&mb, SET_CHAR);
			for (j=0; j< i; j++) 
				if ( *(((char*)mb.mem) +j)!=SET_CHAR)
					printf(" ! set failed at iteration: %d and position %d:\n", i, j);            
		}
		cu_memblock_deinit(&mb);
	}


	return 0;
}
