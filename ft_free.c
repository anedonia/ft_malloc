#include "libft_malloc.h"

extern t_base chunk_base;


void ft_free(void *ptr){
	if (!ptr)
		return;
	t_meta_chunk *chunk = ptr -  sizeof(t_meta_chunk);
	chunk->free = 1;
}