#include <stdint.h>
#include "buddy.h"

#define NULL (void*)0

/* Round up to next power of 2
 *
 * http://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2
 *
 * Input: a number 'n'
 * Output: a number 'k' such that log_2(k) is an integer and k >= n
 */
uint16_t powerOfTwo16(uint16_t n) {
  --n;
  n |= n >> 1;
  n |= n >> 2;
  n |= n >> 4;
  n |= n >> 8;
  return ++n;
}

uint8_t powerOfTwo8(uint8_t n) {
  --n;
  n |= n >> 1;
  n |= n >> 2;
  n |= n >> 4;
  return ++n;
}

/* Find log2 of 16 bit integer
 *
 * http://graphics.stanford.edu/~seander/bithacks.html#IntegerLog
 */
uint16_t log2(uint16_t n)
{
  register uint16_t r; // result of log2(v) will go here
  register uint16_t shift;

  r = (n > 0xFF  ) << 3; n >>= r;
  shift = (n > 0xF   ) << 2; n >>= shift; r |= shift;
  shift = (n > 0x3   ) << 1; n >>= shift; r |= shift;
  r |= (n >> 1);
  return r;
}

/* ---------------------------------------------------------------- */
// Begin buddy allocator

// Beginning of heap pointer
uint8_t* heapstart = HEAPSTART;
// End of heap pointer
uint8_t* heapend = HEAPSTART + HEAPSIZE;

// Structure of free blocks
typedef struct buddyblock {
  // freesz is a union of free and logsz
  // free is 0x8000 and logsz is 0x7FFF
  uint8_t freesz;
  uint8_t _padding;
  struct buddyblock* next;
} bblock_t;

uint8_t bb_free(bblock_t* bb)
{ return bb->freesz & 0x80; }
uint8_t bb_size(bblock_t* bb)
{ return bb->freesz & 0x7F; }

// Array of pointers to free blocks of each size.
// Value is NULL when no free blocks exist
bblock_t* freelists[HEAPSIZELOG] = { NULL };

// Find the buddy for a bblock_t
bblock_t* bb_buddy(bblock_t* bb)
{
  uint16_t logsz;
  size_t offset;

  logsz = 1 << (uint16_t)bb_size(bb);
  offset = (uint8_t*)bb - HEAPSTART;
  return (bblock_t*)(HEAPSTART + (logsz ^ offset));
}

// Initialize a buddy block
void bb_init(bblock_t* bb, uint8_t freesz, bblock_t* next)
{ bb->freesz = freesz; bb->next = next; }

bblock_t* bb_alloc(size_t logsz) {
  bblock_t* block, buddy;
  if (logsz >= HEAPSIZELOG) return NULL;
  block = freelists[logsz];
  if (block == NULL) {
    // Alloc larger block
    block = bb_alloc(logsz+1);
    // Short circuit failure
    if (block == NULL) return NULL;
    // Reassign size
    block->freesz = logsz;
    // Find buddy with new size
    buddy = bb_buddy(block);
    // Initialize new buddy
    bb_init(buddy, 0x80 | logsz, NULL);
    // Add new buddy to freelist
    freelists[logsz] = buddy;
    // Return allocated subblock
    return block;
  }
  // Remove block from free store
  freelists[logsz] = block->next;
  // Mark block as not free
  block->freesz &= 0x7F;
  // Return allocated block
  return block;
}

void bb_dealloc(bblock_t*) {
  // Best free NA
}


// Glue the standard functions onto the buddy allocator
void* __fastcall__ malloc (size_t size) {
  size_t logsz = powerOfTwo16(size+1);
  return bb_alloc(logsz)->next;
}
void __fastcall__ free (void* block) {
  bb_dealloc((bblock_t*)((uint8_t*)block - 1));
}
