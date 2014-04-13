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

#ifndef cu_memblock_h
#define cu_memblock_h 1


#include <stdlib.h>
#include <stdio.h>

#include "cu_debug.h"


struct cu_memblock {
	/* private */
	void* mem;
	unsigned int size;	/* in bytes */
};


/**
 * Inits a cu_memblock allocating the given amount of bytes
 * @mb ptr to the cu_memblock struct to be inited
 * @s amount of bytes to be reserved
 */
inline void cu_memblock_init(struct cu_memblock* mb,
                             unsigned int s);


/**
 * `deinits' a cu_memblock and frees his contents
 */
inline void cu_memblock_deinit(struct cu_memblock* mb);


/**
 * Reallocs the internal buffer to the given number of bytes
 * @mb cu_memblock to be used
 * @r new size in bytes
 */
inline void cu_memblock_set_size(struct cu_memblock* mb,
                                 unsigned int r);


/**
 * Copies the passed buffer to the cu_memblock
 * @mb cu_memblock to be used
 * @buf ptr to the memory chunk to copy
 * @len number of bytes to copy
 *
 * Implmentation takes care of calling cu_memblock_set_size
 * when the cu_memblock size is to little. 
 */
inline void cu_memblock_assign(struct cu_memblock* mb,
                               const void* buf,
                               unsigned int len);


/**
 * Memsets contents of cu_memblock to a given value
 * @mb cu_memblock to be used
 * @c value to use for memset
 */
inline void cu_memblock_set (struct cu_memblock* mb,
                             unsigned char c);


/**
 * Clones two memblocks
 * @dest destination block
 * @src source block
 */
inline void cu_memblock_clone(struct cu_memblock* dest,
                              struct cu_memblock* src);


void cu_memblock_init(struct cu_memblock* mb,
                      unsigned int s)
{
	assert(mb);
	assert(s);
	mb->size = s;
	mb->mem = malloc(s);

	if (!mb->mem) {
		printf("warning cu_memblock_init, malloc\n");
		assert(0);
	}
}


void cu_memblock_deinit(struct cu_memblock* mb) {
	assert(mb);
	free(mb->mem);
}


void cu_memblock_set_size(struct cu_memblock* mb,
                          unsigned int r)
{
	assert(mb);
	assert(r);
	mb->size = r;
	mb->mem = realloc(mb->mem, mb->size);

	if (!mb->mem) {
		printf("warning cu_memblock_set_size, realloc failed\n");
		assert(0);
	}
}


void cu_memblock_assign(struct cu_memblock* mb,
                        const void* buf,
                        unsigned int len) 
{
	assert(mb);
	assert(buf);
	assert(len);

	/* check if realloc is necessary */
	if (len > mb->size)
		cu_memblock_set_size(mb, len);
	memcpy(mb->mem,buf,len);
}


void cu_memblock_set(struct cu_memblock* mb,
                     unsigned char c)
{
	assert(mb);
	memset(mb->mem,c,mb->size);
}

void cu_memblock_clone(struct cu_memblock* dest,
                       struct cu_memblock* src)
{
	assert(dest);
	assert(src);
	cu_memblock_deinit(dest);
	cu_memblock_init(dest, src->size);
	cu_memblock_assign(dest, src->mem, src->size);
}

#endif /* cu_memblock_h */

