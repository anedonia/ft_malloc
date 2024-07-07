#include "libft_malloc.h"

extern void *malloc(size_t size);

void *realloc(void* ptr, size_t size){
	init_base();
	if (!ptr)
		return NULL;
	if (size == 0){
		free(ptr);
		return NULL;
	}

	uintptr_t addr = (uintptr_t)ptr - sizeof(t_meta_chunk);
    if (addr % ALIGNMENT != 0) {
        addr -= ALIGNMENT - (addr % ALIGNMENT);
    }

    t_meta_chunk *chunk = (t_meta_chunk *)addr;
	if (chunk->size > size){
		return ptr;
	}
    void *new_ptr = malloc(size);
	ft_memcpy(new_ptr, ptr, size);
	return new_ptr;
}