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
   gcc -g -O2 -Wall -o cu_vector_uint.test -I../src/ cu_vector_uint.test.c
*/

#define times (unsigned int) 50000000
#define SET_CHAR (char) 0x05
//#define VERBOSE

#define BENCH_LIBSB
//#define BENCH_STD

//#define BENCH_RESERVE
#define BENCH_PUSH_BACK

#ifdef BENCH_LIBSB
#include "cu_vector_uint.h"
#endif

#ifdef BENCH_STD
#include <vector>
#endif

int main() {
	unsigned int i;
	printf(" * test cu_vector_uint\n");
	printf(" ! check memory usage while running the test (it shouldn't grow)\n\n");


#ifdef BENCH_RESERVE
#ifdef BENCH_LIBSB
	printf(" * check reserve\n");
	for (i=1; i< times; i++)
	{
#ifdef VERBOSE
		printf("%d\n", i);
#endif
		struct cu_vector_uint vector;
		cu_vector_uint_init(&vector);
		cu_vector_uint_reserve(&vector, 40000);
		cu_memset(vector.ac.mblock.mem, 0, vector.ac.mblock.size);
		cu_vector_uint_deinit(&vector);
	}
#endif
    
#ifdef BENCH_STD
	printf(" * check reserve std \n");
	for (i=1; i< times; i++)
	{
#ifdef VERBOSE
		printf("%d\n", i);
#endif
		std::vector<unsigned int> vector;
		vector.reserve(40000);
		memset(vector.data(), 0, vector.capacity()*sizeof(unsigned int));
	}
#endif
#endif

#ifdef BENCH_PUSH_BACK
#ifdef BENCH_LIBSB
	printf(" * push_back \n");
	{
		struct cu_vector_uint vector;
		cu_vector_uint_init(&vector);

		for (i=1; i< times; i++)
		{
#ifdef VERBOSE
			printf("%d\n", i);
#endif
			cu_vector_uint_push_back(&vector, i);
			if (cu_vector_uint_size(&vector)!=i)
				printf(" ! size differ at iteration: %d:\n", i);                
			if (cu_vector_uint_at(&vector, i-1)!=i) 
				printf(" ! values differ at iteration: %d:\n", i);
		}
		cu_vector_uint_deinit(&vector);
	}
#endif
  
#ifdef BENCH_STD
	printf(" * push_back std\n");
	{
		std::vector<unsigned int> vector;

		for (i=1; i< times; i++)
		{
#ifdef VERBOSE
			printf("%d\n", i);
#endif
			vector.push_back(i);
			if (vector.size()!=i)
				printf(" ! size differ at iteration: %d:\n", i);                
			if (vector[i-1]!=i) 
				printf(" ! values differ at iteration: %d:\n", i);
		}
	}
#endif
#endif

	return 0;
}
