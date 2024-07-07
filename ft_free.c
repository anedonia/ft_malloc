#include "libft_malloc.h"
#include <stdio.h>

extern t_base chunk_base;

void remove_chunk(t_meta_chunk **head, t_meta_chunk *chunk){

	if (*head == NULL || chunk == NULL)
		return;
	if (chunk == *head){
		*head = chunk->next;
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

// void remove_and_free_nodes(t_meta_chunk **head) {
//     t_meta_chunk *current = *head;
//     t_meta_chunk *prev = NULL;
// 	printf("current size : %ld\n", current->size);
//     while (current != NULL) {
//         if (current->free) {
//             t_meta_chunk *to_free = current;
//             if (prev == NULL) {
//                 *head = current->next;
//             } else {
//                 prev->next = current->next;
//             }
//             current = current->next;
//             if (munmap(to_free, 96) != 0) {
//                 ft_printf("munmap failed\n");
//                 return;
//             }
//         } else {
//             prev = current;
//             current = current->next;
//         }
//     }
// }

// void defrag_mem(t_meta_chunk **head){
//     t_meta_chunk *current = *head;

//     while (current) {
// 		t_meta_chunk *remove = current;
// 		current = current->next;
//         ft_printf("current is at: %p, next is: %p, size is: %d\n", current, current->next, current->size);
//         if (remove->free) {
//             chunk_base.mem_in_use -= remove->size;
//             remove_chunk(head, remove);
//             ft_printf("Removing chunk at: %p, next is: %p, size is: %d\n", remove, current, current->size);
//             // if (munmap(remove, 1) != 0){
// 			// 	return;
// 			// }
//         }
//     }
// }

void print_chunks(t_meta_chunk *head) {
    t_meta_chunk *current = head;
    while (current) {
        printf("Chunk at: %p, size: %zu, free: %d, next: %p\n", (void *)current, current->size, current->free, (void *)current->next);
        current = current->next;
    }
}

void free(void *ptr){
	init_base();
    if (!ptr) {
        return;
    }
	uintptr_t addr = (uintptr_t)ptr - sizeof(t_meta_chunk);
    if (addr % ALIGNMENT != 0) {
        addr -= ALIGNMENT - (addr % ALIGNMENT);
    }

    t_meta_chunk *chunk = (t_meta_chunk *)addr;

    // printf("Freeing chunk at address: %p\n", (void*)chunk);
    // printf("Chunk size: %zu\n", chunk->size);
    // printf("Chunk free status: %d\n", chunk->free);
    // printf("Chunk next pointer: %p\n", (void*)chunk->next);

    chunk->free = 1;
	if (chunk->size > 1024)
	{
		chunk_base.mem_in_use -= chunk->size;
		remove_chunk(&chunk_base.large_chunk_list, chunk);
		if (munmap(chunk, chunk->size) != 0)
			return;
	}
	// // if (LARGE_THRESHOLD > chunk_base.mem_in_use)
	// if (1)
	// {
	// 	printf("Before defragmentation:\n");
	// 	print_chunks(chunk_base.tiny_chunk_list);
	// 	print_chunks(chunk_base.small_chunk_list);
	// 	remove_and_free_nodes(&chunk_base.tiny_chunk_list);

	// 	remove_and_free_nodes(&chunk_base.small_chunk_list);
	// 	printf("After defragmentation:\n");
	// 	print_chunks(chunk_base.tiny_chunk_list);
	// 	print_chunks(chunk_base.small_chunk_list);
	// 	// defrag_mem(&chunk_base.tiny_chunk_list);
	// 	// defrag_mem(&chunk_base.small_chunk_list);
	// }
}