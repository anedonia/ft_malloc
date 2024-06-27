#include "libft_malloc.h"
#include <stdio.h>

extern t_base chunk_base;


void ft_free(void *ptr){
    if (!ptr) {
        return;
    }

    // The data pointer provided is already aligned, so calculate the metadata pointer
    uintptr_t data_addr = (uintptr_t)ptr;

    // Subtracting the size of metadata from the data pointer to get the potential metadata pointer
    uintptr_t metadata_addr = data_addr - sizeof(t_meta_chunk);
    t_meta_chunk *chunk = (t_meta_chunk *)metadata_addr;

    // Calculate the aligned data pointer from the potential metadata pointer to ensure correctness
    void *calculated_data_ptr = align_memory((void *)((uintptr_t)chunk + sizeof(t_meta_chunk)));

    // Verify if the calculated data pointer matches the original data pointer
    if (calculated_data_ptr != ptr) {
        return;
    }

    // Print the content of the chunk for debugging
    printf("Freeing chunk at address: %p\n", (void*)chunk);
    printf("Chunk size: %zu\n", chunk->size);
    printf("Chunk free status: %d\n", chunk->free);
    printf("Chunk next pointer: %p\n", (void*)chunk->next);

    // Mark the chunk as free
    chunk->free = 1;

    // Optional: Coalesce adjacent free chunks (if needed)
    // This step would involve checking neighboring chunks and merging them if they are free
}