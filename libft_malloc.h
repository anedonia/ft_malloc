#ifndef LIBFT_MALLOC_H
#define LIBFT_MALLOC_H

#include "./libft/libft.h"
#include "./printf/ft_printf.h"
#include <sys/mman.h>
#include <sys/resource.h>
#include <unistd.h>
#include <stdlib.h>

struct s_meta_chunk;

typedef struct s_meta_chunk {
	size_t				size;
	struct s_meta_chunk	*next;
	int					free;

} t_meta_chunk;

typedef struct s_base{
	t_meta_chunk	*tiny_chunk_list;
	t_meta_chunk	*small_chunk_list;
	t_meta_chunk	*large_chunk_list;
	int				initialized;
} t_base;

void	show_alloc_mem();
void	ft_free(void *ptr);
void	*ft_malloc(size_t size);
void	*ft_realloc(void *prt, size_t size);


#endif