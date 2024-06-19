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
void show_alloc_mem(){
	int total;
	total = 0;
	t_meta_chunk *current;
	current = chunk_base.tiny_chunk_list;
	ft_printf("TINY : %p\n", current);
	while (current) {
		//FIXME: je pense qu'il faut ajouter le offset
		ft_printf("%p - %p : %d bytes\n", &current, &current + sizeof(t_meta_chunk) + current->size, current->size);  
		total += current->size;
		current = current->next;
	}
	current = chunk_base.small_chunk_list;
	ft_printf("SMALL : %p\n", current);
	while (current) {
		//FIXME: je pense qu'il faut ajouter le offset
		ft_printf("%p - %p : %d bytes\n", &current, (char *)current + sizeof(t_meta_chunk), current->size);  
		total += current->size;
		current = current->next;
	}
	current = chunk_base.large_chunk_list;
	ft_printf("LARGE : %p\n", current);
	while (current) {
		//FIXME: je pense qu'il faut ajouter le offset
		ft_printf("%p - %p : %d bytes\n", &current, (char *)current + sizeof(t_meta_chunk), current->size);  
		total += current->size;
		current = current->next;
	}
	ft_printf("Total : %d bytes\n", total);
}

void *ft_malloc(size_t size) {
	init_base();
	t_meta_chunk *chunk;

	chunk = (find_chunck(size));
	if (!chunk) {
		chunk = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
		chunk->size = size;
		chunk->free = 0;
	}
	if (chunk){
		chunk_base.tiny_chunk_list = chunk;
		return (char *)chunk + sizeof(t_meta_chunk);
	}
	return NULL;
};