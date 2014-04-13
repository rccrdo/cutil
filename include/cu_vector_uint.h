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

#ifndef cu_vector_uint_h
#define cu_vector_uint_h 1

#include "cu_debug.h"
#include "cu_array_container.h"


struct cu_vector_uint {
	/* private */
	struct cu_array_container ac;
};

/**
 * Inits a cu_vector_uint
 * @v cu_vector_uint to be used
 */
inline void cu_vector_uint_init(struct cu_vector_uint* v);

/**
 * Deinits a cu_vector_uint
 * @v cu_vector_uint to be used
 */
inline void cu_vector_uint_deinit(struct cu_vector_uint* v);

/**
 * Returns the element at a given position
 * @v cu_vector_uint to be used
 * @at index of the elemnt
 */
inline unsigned int cu_vector_uint_at(struct cu_vector_uint* v,
                                      unsigned int at);
/**
 * Sets the element at a given position
 * @v cu_vector_uint to be used
 * @at index of the elemnt
 * @value new value
 */
inline void cu_vector_uint_set(struct cu_vector_uint* v,
                               unsigned int at,
                               unsigned int value);

/**
 * Clears the vector
 * @v cu_vector_uint to be used
 */
inline void cu_vector_uint_clear(struct cu_vector_uint* v);

/**
 * Pushes a new element at the back of the vector
 * @v cu_vector_uint to be used
 * @value new value
 */
inline void cu_vector_uint_push_back(struct cu_vector_uint* v,
                                     unsigned int value);

/**
 * Reserves memory for the given number of uints
 * @v cu_vector_uint to be used
 * @r number of uints
 */
inline void cu_vector_uint_reserve(struct cu_vector_uint* v,
                                   unsigned int num_slots);

/**
 * Returns the number of reserved slots
 * @v cu_vector_uint to be used
 */
inline unsigned int cu_vector_uint_reserved(struct cu_vector_uint* v);


/**
 * Returns the size of the vector
 * @v cu_vector_uint to be used
 */
inline unsigned int cu_vector_uint_size(struct cu_vector_uint* v);


inline void cu_vector_uint_clone(struct cu_vector_uint* dest,
                                 struct cu_vector_uint* src );

void cu_vector_uint_init(struct cu_vector_uint* v) {
	assert(v);
	cu_array_container_init(&v->ac, sizeof(unsigned int));
}

void cu_vector_uint_deinit(struct cu_vector_uint* v) {
	assert(v);
	cu_array_container_deinit(&v->ac);
}


unsigned int cu_vector_uint_at(struct cu_vector_uint* v,
                               unsigned int at)
{
	assert(v);
	assert(at < v->ac.size);
	return ((unsigned int*)v->ac.mblock.mem)[at];
}


void cu_vector_uint_set(struct cu_vector_uint* v,
                        unsigned int at,
                        unsigned int value)
{
	assert(v);
	assert(at < v->ac.size);
	((unsigned int*)v->ac.mblock.mem)[at] = value;
}


void cu_vector_uint_clear(struct cu_vector_uint* v)
{
	assert(v);
	cu_array_container_clear(&v->ac, sizeof(unsigned int));
}


void cu_vector_uint_push_back(struct cu_vector_uint* v,
                              unsigned int value)
{
	assert(v);

	/* check for the need of more memory */
	cu_array_container_check_size_and_grow(&v->ac);
  
	((unsigned int*)v->ac.mblock.mem)[v->ac.size] = value;
	v->ac.size ++;
}


void cu_vector_uint_reserve(struct cu_vector_uint* v,
                            unsigned int num_slots)
{
	assert(v);
	assert(num_slots);
	cu_array_container_reserve(&v->ac, sizeof(unsigned int), num_slots);
}


unsigned int cu_vector_uint_reserved(struct cu_vector_uint* v)
{
	assert(v);
	return v->ac.reserved;
}


inline unsigned int cu_vector_uint_size(struct cu_vector_uint* v)
{
	assert(v);
	return v->ac.size;
}


void cu_vector_uint_clone(struct cu_vector_uint* dest,
                          struct cu_vector_uint* src )
{
	assert(dest);
	assert(src);
	cu_vector_uint_clear(dest);
  
	for (unsigned int i=0; i< cu_vector_uint_size(src); i++)
		cu_vector_uint_push_back(dest, cu_vector_uint_at(src,i));
}

#endif /*cu_vector_uint_h*/

