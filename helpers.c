#include "libft_malloc.h"

extern t_base chunk_base;

t_meta_chunk *add_block(t_meta_chunk *last, size_t size)
{

	t_meta_chunk *chunk;

	size_t total_chunk_size =  size * STANDARD_BLOCK;
	size_t total_size = (total_chunk_size + PAGESIZE - 1) & ~(PAGESIZE - 1);

	// ft_printf("total_size : %u, limit is : %u\n", total_size, chunk_base.limit * PAGESIZE);

	void *ptr_one;
	ptr_one = mmap(NULL, total_size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	if (ptr_one == MAP_FAILED || total_size >= chunk_base.limit)
	{
		ft_printf("mmap failed\n");
		return 0;
	}
	ft_memset(ptr_one, 0, total_size);
	chunk_base.mem_in_use += total_size;

	if (!last)
	{
		if (size == 64){
			init_chunks_list(ptr_one, &chunk_base.tiny_chunk_list, TINY_SIZE, STANDARD_BLOCK);
			ft_printf("block changement de tete\n", size);
		}
		else{
			ft_printf("block changement de tete\n", size);
			init_chunks_list(ptr_one, &chunk_base.small_chunk_list, SMALL_SIZE, STANDARD_BLOCK);
		} 
	}
	else 
		init_chunks_list(ptr_one, &last->next, size, STANDARD_BLOCK);
	chunk = find_chunck(size - 32);
	return chunk;
}