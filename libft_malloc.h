#ifndef LIBFT_MALLOC_H
#define LIBFT_MALLOC_H

#include "./libft/libft.h"
#include "./printf/ft_printf.h"
#include <sys/mman.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <stdlib.h>

#ifdef __linux__
#define PAGESIZE sysconf(_SC_PAGESIZE)
#elif defined(__APPLE__) && defined(__MACH__)
#define PAGESIZE sysconf(_SC_PAGESIZE)
#else
#error "Unsupported operating system"
#endif

#define ALIGNMENT 16
#define ALIGN(size) (((size) + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1))

struct s_meta_chunk;

typedef struct s_meta_chunk {
	size_t				size;
	struct s_meta_chunk	*next;
	int					free;

} t_meta_chunk;

typedef struct s_base{
	struct s_meta_chunk	*tiny_chunk_list;
	struct s_meta_chunk	*small_chunk_list;
	struct s_meta_chunk	*large_chunk_list;
	size_t 				limit;
	size_t				page_in_use;
	int					initialized;
} t_base;

void	show_alloc_mem();
void	ft_free(void *ptr);
void	*ft_malloc(size_t size);
void	*ft_realloc(void *prt, size_t size);


#endif