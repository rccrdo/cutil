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

#ifndef cu_array_container_h
#define cu_array_container_h 1

#include <stdio.h>

#include "cu_debug.h"
#include "cu_memblock.h"


/* protected api */

/* minimum number of slots reserved in a cu_array_container
 * ! must be a power of two  */
#define cu_ARRAY_CONTAINER_MIN_RESERVED_SLOTS (unsigned int)32


struct cu_array_container {
	/* private */
	struct cu_memblock mblock;
	unsigned int size;	 /* in slots */
	unsigned int reserved; /* reserved memory (in slots) */
};


/**
 * Inits a cu_array_container
 * @ac cu_array_container to be used
 * @slot_size slots size (in bytes)
 */
inline void cu_array_container_init(struct cu_array_container* ac, unsigned int slot_size);

/**
 * Deinits a cu_array_container
 * @ac cu_array_container to be used
 */
inline void cu_array_container_deinit(struct cu_array_container* ac);

/**
 * Clears the container
 */
inline void cu_array_container_clear(struct cu_array_container* ac, unsigned int slot_size);


/**
 * Common helper for growing cu_array_container implementors
 * @ac cu_array_container to be used
 */
inline void cu_array_container_grow_once(struct cu_array_container* ac);


/**
 * Reserves container memory for the given number of slots
 * @ac cu_array_container to be used
 * @slot_size size of a slot (in bytes)
 * @num_slots requested new number of slots
 *
 * The number of slots reserved will be the nearest higher power of two for num_slots
 */
inline void cu_array_container_reserve(struct cu_array_container* ac, unsigned int slot_size,
                                       unsigned int num_slots);


/**
 * Grows the container when its size equals its reserved size
 */
inline void cu_array_container_check_size_and_grow(struct cu_array_container* ac);




void cu_array_container_init(struct cu_array_container* ac, unsigned int slot_size) {
	assert(ac);
	assert(slot_size);
	ac->reserved = cu_ARRAY_CONTAINER_MIN_RESERVED_SLOTS;
	ac->size = 0;
	cu_memblock_init(&ac->mblock, slot_size*cu_ARRAY_CONTAINER_MIN_RESERVED_SLOTS);
}


inline void cu_array_container_deinit(struct cu_array_container* ac) {
	assert(ac);
	cu_memblock_deinit(&ac->mblock);
}


void cu_array_container_clear(struct cu_array_container* ac, unsigned int slot_size) {
	assert(ac);
	assert(slot_size);
	ac->reserved = cu_ARRAY_CONTAINER_MIN_RESERVED_SLOTS;
	ac->size = 0;
	cu_memblock_set_size(&ac->mblock, slot_size*cu_ARRAY_CONTAINER_MIN_RESERVED_SLOTS);

}


void cu_array_container_grow_once(struct cu_array_container* ac)
{
	assert(ac);

	/* always grow by a factor of 2 */
	cu_memblock_set_size(&ac->mblock, ac->mblock.size*2);
	ac->reserved *= 2;  
}


void cu_array_container_reserve(struct cu_array_container* ac, unsigned int slot_size,
				unsigned int num_slots)
{
	assert(ac);
	assert(slot_size);
	assert(num_slots);

	/* respect lower threshold */
	if (num_slots < cu_ARRAY_CONTAINER_MIN_RESERVED_SLOTS)
		num_slots = cu_ARRAY_CONTAINER_MIN_RESERVED_SLOTS;
	else 
	{
		/* compute the next highest power of 2 for num_slots */
		num_slots--;
		num_slots |= num_slots >> 1;
		num_slots |= num_slots >> 2;
		num_slots |= num_slots >> 4;
		num_slots |= num_slots >> 8;
		num_slots |= num_slots >> 16;
		num_slots++;
	}

	if (ac->reserved != num_slots)
	{
		cu_memblock_set_size(&ac->mblock, num_slots*slot_size);
		ac->reserved = num_slots;
		/* avoid weird values for size */
		if (ac->size > ac->reserved)
			ac->size = ac->reserved;
	}
}


void cu_array_container_check_size_and_grow(struct cu_array_container* ac) {
	assert(ac);
	if (ac->reserved == ac->size) 
		cu_array_container_grow_once(ac);
}

#endif /* cu_array_container_h */

