#ifndef MEMTRACKER_H
#define MEMTRACKER_H

#include <stdlib.h>

void* mt_malloc(size_t size);
void* mt_calloc(size_t num, size_t size);
void* mt_realloc(void* ptr, size_t new_size);
void  mt_free(void* ptr);

void  mt_summary(void);   // print all active blocks
void  mt_finalize(void);  // free any leaked memory

#endif 
