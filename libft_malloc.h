#ifndef LIBFT_MALLOC_H
#define LIBFT_MALLOC_H

#define _GNU_SOURCE
#include "./libft/libft.h"
#include "./printf/ft_printf.h"
#include <sys/mman.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
// #include <stdlib.h>
#include <stdint.h>

#ifdef __linux__
#define PAGESIZE sysconf(_SC_PAGESIZE)
#elif defined(__APPLE__) && defined(__MACH__)
#define PAGESIZE sysconf(_SC_PAGESIZE)
#else
#error "Unsupported operating system"
#endif

#define STANDARD_BLOCK 200
#define TINY_ALLOCS 100
#define SMALL_ALLOCS 100

#define TINY_SIZE 64
#define SMALL_SIZE 1024
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
	size_t				mem_in_use;
	size_t				large_threshold;
	int					initialized;

} t_base;

//utils
void*			align_memory(void* ptr);
t_meta_chunk	*add_block(t_meta_chunk *last, size_t size);
t_meta_chunk	*find_chunck(size_t size);
void			retard_init();
void			init_chunks_list(void *ptr, t_meta_chunk **head , size_t size, size_t nb_allocs);
void			show_alloc_mem_chunk();
int				init_base(void);
void			defrag_mem(t_meta_chunk **head);

//subject
void	show_alloc_mem();
void	free(void *ptr);
void	*malloc(size_t size);
void	*realloc(void *prt, size_t size);


#endif