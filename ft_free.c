#include "libft_malloc.h"
#include <stdio.h>

extern t_base chunk_base;


void ft_free(void *ptr){
    if (!ptr) {
        return;
    }
	uintptr_t addr = (uintptr_t)ptr - sizeof(t_meta_chunk);
    if (addr % ALIGNMENT != 0) {
        addr -= ALIGNMENT - (addr % ALIGNMENT);
    }
	// printf("addr : %lX\n", addr);

    t_meta_chunk *chunk = (t_meta_chunk *)addr;

    // printf("Freeing chunk at address: %p\n", (void*)chunk);
    // printf("Chunk size: %zu\n", chunk->size);
    // printf("Chunk free status: %d\n", chunk->free);
    // printf("Chunk next pointer: %p\n", (void*)chunk->next);

    chunk->free = 1;

}