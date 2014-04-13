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

#ifndef cu_bitmap_h
#define cu_bitmap_h 1

#include <stdio.h>

#include "cu_debug.h"
#include "cu_memblock.h"


struct cu_bitmap {
	/* private */
	struct cu_memblock mblock;
};


/**
 * Inits a cu_bitmap
 * @ac cu_bitmap to be used
 */
inline void cu_bitmap_init(struct cu_bitmap* bm,
                           unsigned int size);

/**
 * Deinits a cu_bitmap
 * @ac cu_bitmap to be used
 */
inline void cu_bitmap_deinit(struct cu_bitmap* bm);

/**
 * Clears all bits in a cu_bitmap to zero
 * @ac cu_bitmap to be used
 */
inline void cu_bitmap_clear(struct cu_bitmap* bm);

/**
 * Returns the number of usable bits in a cu_bitmap
 * @ac cu_bitmap to be used
 */
inline unsigned int cu_bitmap_size(struct cu_bitmap* bm);

/**
 * Sets a bit
 * @ac cu_bitmap to be used
 * @at bit's index
 *
 * Bits are indexed from 0 to (cu_bitmap_size(..)-1).
 */
inline void cu_bitmap_set_bit(struct cu_bitmap* bm,
                              unsigned int at);

/**
 * Clears the bit
 * @ac cu_bitmap to be used
 * @at bit's index
 *
 * Bits are indexed from 0 to (cu_bitmap_size(..)-1).
 */
inline void cu_bitmap_clear_bit(struct cu_bitmap* bm,
                                unsigned int at);

/**
 * Returns the state of a bit
 * @ac cu_bitmap to be used
 * @at bit's index
 *
 * Bits are indexed from 0 to (cu_bitmap_size(..)-1). Returns 0 for a cleared bit
 * and 1 for a set bit
 */
inline unsigned int cu_bitmap_get_bit(struct cu_bitmap* bm,
                                      unsigned int at);

/**
 * Clones two bitmaps
 * @dest destination bitmap
 * @src source bitmap
 */
inline void cu_bitmap_clone(struct cu_bitmap* dest,
                            struct cu_bitmap* src);



void cu_bitmap_init(struct cu_bitmap* bm,
                    unsigned int size) {
	assert(bm);
	assert(size);
	cu_memblock_init(&bm->mblock, size);
}


void cu_bitmap_deinit(struct cu_bitmap* bm)
{
	assert(bm);
	cu_memblock_deinit(&bm->mblock);
}


void cu_bitmap_clear(struct cu_bitmap* bm)
{
	assert(bm);
	cu_memblock_set(&bm->mblock, 0);
}


unsigned int cu_bitmap_size(struct cu_bitmap* bm)
{
	assert(bm);
	return bm->mblock.size;
}


void cu_bitmap_set_bit(struct cu_bitmap* bm,
                       unsigned int at)
{
	assert(bm);
	assert(at< bm->mblock.size);
	((unsigned int*)bm->mblock.mem)[at/(sizeof(unsigned int)*8)] |= (0x1 << (at%(sizeof(unsigned int)*8)));
}


void cu_bitmap_clear_bit(struct cu_bitmap* bm,
                         unsigned int at)
{
	assert(bm);
	assert(at< bm->mblock.size);
	((unsigned int*)bm->mblock.mem)[at/(sizeof(unsigned int)*8)] &= (!(0x1 << (at%(sizeof(unsigned int)*8))));
}


unsigned int cu_bitmap_get_bit(struct cu_bitmap* bm, unsigned int at)
{
	assert(bm);
	assert(at< bm->mblock.size);
	return ((unsigned int*)bm->mblock.mem)[at/(sizeof(unsigned int)*8)] & (0x1 << (at%(sizeof(unsigned int)*8)));
}


void cu_bitmap_clone(struct cu_bitmap* dest,
                     struct cu_bitmap* src)
{
	assert(dest);
	assert(src);  
	cu_memblock_clone(&dest->mblock, &src->mblock);
}


#endif /* cu_bitmap_h */

