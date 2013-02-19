#ifndef _MEMORY_MANAGER_
#define _MEMORY_MANAGER_

#include <stdlib.h>

#ifndef HEAPSTART
#define HEAPSTART ((uint8_t*)0x2000)
#endif

#ifndef HEAPSIZELOG
/* must be a power of 2 */
#define HEAPSIZELOG 13
#define HEAPSIZE (1 << HEAPSIZELOG)
#endif

void initialize_dynamic_memory();

void* __fastcall__ malloc (size_t size);
void __fastcall__ free (void* block);

#endif
