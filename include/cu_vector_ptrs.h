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

#ifndef cu_vector_ptrs_h
#define cu_vector_ptrs_h 1

#include "cu_debug.h"
#include "cu_array_container.h"


struct cu_vector_ptrs {
	/* private */
	struct cu_array_container ac;
};

/**
 * Inits a cu_vector_ptrs
 * @v cu_vector_ptrs to be used
 */
inline void cu_vector_ptrs_init(struct cu_vector_ptrs* v);

/**
 * Deinits a cu_vector_ptrs
 * @v cu_vector_ptrs to be used
 */
inline void cu_vector_ptrs_deinit(struct cu_vector_ptrs* v);

/**
 * Returns the element at a given position
 * @v cu_vector_ptrs to be used
 * @at index of the elemnt
 */
inline void* cu_vector_ptrs_at(struct cu_vector_ptrs* v,
                               unsigned int at);
/**
 * Sets the element at a given position
 * @v cu_vector_ptrs to be used
 * @at index of the elemnt
 * @value new value
 */
inline void cu_vector_ptrs_set(struct cu_vector_ptrs* v,
                               unsigned int at,
                               void* value);


/**
 * Clears the vector
 * @v cu_vector_ptrs to be used
 */
inline void cu_vector_ptrs_clear(struct cu_vector_ptrs* v);

/**
 * Pushes a new element at the back of the vector
 * @v cu_vector_ptrs to be used
 * @value new value
 */
inline void cu_vector_ptrs_push_back(struct cu_vector_ptrs* v,
                                     void* value);

/**
 * Reserves memory for the given number of ptrss
 * @v cu_vector_ptrs to be used
 * @r number of ptrss
 */
inline void cu_vector_ptrs_reserve(struct cu_vector_ptrs* v,
                                   unsigned int num_slots);

/**
 * Returns the number of reserved slots
 * @v cu_vector_ptrs to be used
 */
inline unsigned int cu_vector_ptrs_reserved(struct cu_vector_ptrs* v);

/**
 * Returns the size of the vector
 * @v cu_vector_ptrs to be used
 */
inline unsigned int cu_vector_ptrs_size(struct cu_vector_ptrs* v);


/**
 * Clones two vectors
 * @dest destination vector
 * @src source vector
 */
inline void cu_vector_ptrs_clone(struct cu_vector_ptrs* dest,
                                 struct cu_vector_ptrs* src );


void cu_vector_ptrs_init(struct cu_vector_ptrs* v)
{
	assert(v);
	cu_array_container_init(&v->ac, sizeof(void*));
}

void cu_vector_ptrs_deinit(struct cu_vector_ptrs* v)
{
	assert(v);
	cu_array_container_deinit(&v->ac);
}


void* cu_vector_ptrs_at(struct cu_vector_ptrs* v,
                        unsigned int at)
{
	assert(v);
	assert(at < v->ac.size);
	return ((void**) v->ac.mblock.mem)[at];
}


void cu_vector_ptrs_set(struct cu_vector_ptrs* v,
                        unsigned int at,
                        void* value)
{
	assert(v);
	assert(at < v->ac.size);
	((void**) v->ac.mblock.mem)[at] = value;
}


void cu_vector_ptrs_clear(struct cu_vector_ptrs* v)
{
	assert(v);
	cu_array_container_clear(&v->ac, sizeof(void*));
}


void cu_vector_ptrs_push_back(struct cu_vector_ptrs* v,
                              void* value)
{
	assert(v);

	/* check for the need of more memory */
	cu_array_container_check_size_and_grow(&v->ac);
  
	((void**)v->ac.mblock.mem)[v->ac.size] = value;
	v->ac.size ++;
}


void cu_vector_ptrs_reserve(struct cu_vector_ptrs* v,
                            unsigned int num_slots)
{
	assert(v);
	assert(num_slots);
	cu_array_container_reserve(&v->ac, sizeof(void*), num_slots);
}


unsigned int cu_vector_ptrs_reserved(struct cu_vector_ptrs* v) {
	assert(v);
	return v->ac.reserved;
}


unsigned int cu_vector_ptrs_size(struct cu_vector_ptrs* v) {
	assert(v);
	return v->ac.size;
}


void cu_vector_ptrs_clone(struct cu_vector_ptrs* dest,
                          struct cu_vector_ptrs* src )
{
	assert(dest);
	assert(src);
	cu_vector_ptrs_clear(dest);
  
	for (unsigned int i=0; i< cu_vector_ptrs_size(src); i++)
		cu_vector_ptrs_push_back(dest, cu_vector_ptrs_at(src,i));
}
                                 
#endif /* cu_vector_ptrs_h */

