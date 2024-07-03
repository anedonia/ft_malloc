#include "libft_malloc.h"

extern t_base chunk_base;

t_meta_chunk *add_block(t_meta_chunk *last, size_t size)
{

	t_meta_chunk *chunk;

	size_t total_chunk_size = (sizeof(t_meta_chunk) + size) * 10;
	size_t total_size = (total_chunk_size + PAGESIZE - 1) & ~(PAGESIZE - 1);

	ft_printf("total_size : %u, limit is : %u\n", total_size, chunk_base.limit * PAGESIZE);

	void *ptr_one;
	ptr_one = mmap(NULL, total_size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	if (ptr_one == MAP_FAILED || total_size >= chunk_base.limit)
	{
		ft_printf("mmap failed\n");
		return 0;
	}
	ft_memset(ptr_one, 0, total_size);
	chunk_base.mem_in_use += total_size;

	init_chunks_list(ptr_one, &last->next, size, 10);
	chunk = find_chunck(size);
	return chunk;
}