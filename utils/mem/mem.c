#include <assert.h>
#include <stdlib.h>
#include "cmprss_common.h"
#include "mem.h"

void* 
mem_calloc(uint32 size)
{
	void *ptr = calloc(size, 1);
	assert(ptr);
	return ptr;
}

void 
mem_free(void *ptr)
{
	if (ptr) {
		free(ptr);
	}
}
