#define TINY_SIZE 64
#define SMALL_SIZE 1024



#include "libft_malloc.h"

t_base chunk_base;

void init_base(void)
{
	if (!chunk_base.initialized)
	{
		chunk_base.tiny_chunk_list = NULL;
		chunk_base.small_chunk_list = NULL;
		chunk_base.large_chunk_list = NULL;
		chunk_base.initialized = 1;
	}
}

t_meta_chunk *find_chunck(size_t size){
	t_meta_chunk *current;

	if (size < TINY_SIZE)
		current = chunk_base.tiny_chunk_list;
	else if (size > SMALL_SIZE)
		current = chunk_base.small_chunk_list;
	else
		return NULL;
	while (current && !(current->free && current->size >= size)){
		current = current->next;
	}
	return current;
}

void add_back(t_meta_chunk *new) {
	t_meta_chunk **head = &(chunk_base.tiny_chunk_list);
	if (*head == NULL){
		ft_printf("new head\n");
		*head = new;
	}
	else {
		t_meta_chunk *current = *head;
		while (current->next)
			current = current->next;
		current->next = new;
	}
}

t_meta_chunk *add_chunk(size_t size) {
	size = ALIGN(size);
	size_t total_size = size + sizeof(t_meta_chunk) + (ALIGNMENT - 1);

	void * ptr = mmap(NULL, total_size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	if (ptr == MAP_FAILED){
		ft_printf("mmap failed\n");
		return NULL;
	}

	//align the ptr correctly
	void *aligned_ptr = (void*)(((size_t)ptr + sizeof(t_meta_chunk) + (ALIGNMENT -1)) & ~(ALIGNMENT - 1));
	t_meta_chunk *chunk = (t_meta_chunk *)aligned_ptr - 1;
	chunk->size = size;
	chunk->free = 0;
	chunk->next = NULL;

	add_back(chunk);
	return (chunk);
}

void *ft_malloc(size_t size) {
	init_base();
	t_meta_chunk *chunk;

	// chunk = (find_chunck(size));
	chunk = add_chunk(size);

	if (chunk){
		return (char *)chunk + sizeof(t_meta_chunk);
	}


	return NULL;
};