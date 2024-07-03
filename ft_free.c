#include "libft_malloc.h"
#include <stdio.h>

extern t_base chunk_base;

void defrag_mem(){
	
}

void remove_chunk(t_meta_chunk **head, t_meta_chunk *chunk){

	if (*head == NULL || chunk == NULL)
		return;
	if (chunk == *head){
		*head = chunk->next;
		return;
	}
	else
	{
		t_meta_chunk *prev = *head;
		t_meta_chunk *temp = (*head)->next;
		while (temp != NULL && temp != chunk){
			prev = temp;
			temp = temp->next;
		}
		if (!temp)
			return;
		prev->next = temp->next;
	}
}

void free(void *ptr){
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
	if (chunk->size > 1024){
		chunk_base.mem_in_use -= chunk->size;
		remove_chunk(&chunk_base.large_chunk_list , chunk);
		munmap(chunk, chunk->size);
	}

}