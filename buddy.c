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

/* Find ceil(log2()) of 16 bit integer
 *
 * I AM CREDIT TO TEAM
 */
static uint16_t log2_b[] = {0x2, 0xC, 0xF0, 0xFF00};
static uint16_t log2_S[] = {1, 2, 4, 8};

uint16_t log2(uint16_t n)
{
  uint16_t r = 0;
  --n;

  if (n & log2_b[3])
    {
      n >>= log2_S[3];
      r |= log2_S[3];
    } 
  if (n & log2_b[2])
    {
      n >>= log2_S[2];
      r |= log2_S[2];
    } 
  if (n & log2_b[1])
    {
      n >>= log2_S[1];
      r |= log2_S[1];
    } 
  if (n & log2_b[0])
    {
      n >>= log2_S[0];
      r |= log2_S[0];
    } 
  return r+1;
}

/* ---------------------------------------------------------------- */
// Begin buddy allocator

// Structure of free blocks
typedef struct buddyblock {
  uint8_t free;
  uint8_t size;
  struct buddyblock* next;
  struct buddyblock* prev;
} bblock_t;

#define BBLOCK_HEADER_SIZE 2

// Array of pointers to free blocks of each size.
// Value is NULL when no free blocks exist
bblock_t* freelists[HEAPSIZELOG] = { NULL };

// Find the buddy for a bblock_t
bblock_t* bb_buddy(bblock_t* bb)
{
  uint16_t logsz;
  size_t offset;

  logsz = 1 << (uint16_t)bb->size;
  offset = (uint8_t*)bb - HEAPSTART;
  return (bblock_t*)(HEAPSTART + (logsz ^ offset));
}

// Initialize a buddy block
void bb_init(bblock_t* bb, uint8_t sz, bblock_t* next, bblock_t* prev)
{ bb->free = 1; bb->size = sz; bb->next = next; bb->prev = prev; }

bblock_t* bb_alloc(size_t logsz) {
  bblock_t *block, *buddy;

  if (logsz > HEAPSIZELOG) return NULL;
  block = freelists[logsz-1];
  if (block == NULL) {
    // Alloc larger block
    block = bb_alloc(logsz+1);
    // Short circuit failure
    if (block == NULL) return NULL;
    // Reassign size
    block->size = logsz;
    // Mark as no longer free
    block->free = 0;
    // Find buddy with new size
    buddy = bb_buddy(block);
    // Initialize new buddy
    bb_init(buddy, logsz, NULL, NULL);
    // Add new buddy to freelist
    freelists[logsz-1] = buddy;
    // Return allocated subblock
    return block;
  }
  // Remove block from free store
  freelists[logsz-1] = block->next;
  if (block->next)
    block->next->prev = NULL;
  // Mark block as not free
  block->free = 0;
  // Return allocated block
  return block;
}

void bb_dealloc(bblock_t* bb) {
  // Best free NA
  bblock_t* buddy;
  bb->free = 1;
  if (bb->size == HEAPSIZELOG) {
    bb->next = NULL;
    bb->prev = NULL;
    freelists[HEAPSIZELOG-1] = bb;
    return;
  }

  buddy = bb_buddy(bb);
  if (buddy->free) {
    if (buddy->next != NULL) buddy->next->prev = buddy->prev;
    if (buddy->prev != NULL) buddy->prev->next = buddy->next;
    if (buddy->prev == NULL) freelists[buddy->size-1] = buddy->next;
    bb = bb < buddy ? bb : buddy;
    ++bb->size;
    bb_dealloc(bb);
  } else {
    bb->next = freelists[bb->size-1];
    bb->prev = NULL;
    if (bb->next != NULL)
      bb->next->prev = bb;
    freelists[bb->size-1] = bb;
  }
}

void initialize_dynamic_memory() {
  bb_init((bblock_t*)HEAPSTART, HEAPSIZELOG, NULL, NULL);
  freelists[HEAPSIZELOG-1] = (bblock_t*)HEAPSTART;
}

// Glue the standard functions onto the buddy allocator
void* __fastcall__ malloc (size_t size) {
  size_t logsz;

  logsz = log2(size+1);
  return (uint8_t*)bb_alloc(logsz) + BBLOCK_HEADER_SIZE;
}
void __fastcall__ free (void* block) {
  bb_dealloc((bblock_t*)((uint8_t*)block - BBLOCK_HEADER_SIZE));
}
