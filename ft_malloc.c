#define TINY_SIZE 64
#define SMALL_SIZE 1024

// #define TINY_SIZE 100000000000
// #define SMALL_SIZE 1024


// #define SMALL_ALLOCS 1000
// #define TINY_ALLOCS 3000
#define TINY_ALLOCS 200
#define SMALL_ALLOCS 20


#include "libft_malloc.h"

t_base chunk_base;

void add_back(t_meta_chunk *new, t_meta_chunk **head)
{
	if (*head == NULL)
	{
		ft_printf("new head\n");
		*head = new;
	}
	else
	{
		t_meta_chunk *current = *head;
		while (current->next)
			current = current->next;
		current->next = new;
	}
}

void* align_memory(void* ptr) {
    uintptr_t addr = (uintptr_t)ptr;
    if (addr % ALIGNMENT != 0) {
        addr += ALIGNMENT - (addr % ALIGNMENT);
    }
    return (void*)addr;
}

void init_chunks_list(void *ptr, t_meta_chunk **head , size_t size, size_t nb_allocs){

    void *current_ptr = align_memory(ptr);
	*head = (t_meta_chunk *)current_ptr;

    for (size_t i = 0; i < nb_allocs; i++) {
        current_ptr = align_memory(current_ptr);
        t_meta_chunk *chunk = (t_meta_chunk*)current_ptr;
        chunk->free = 1;
        chunk->size = size;

        if (i < nb_allocs - 1) {
            void *next_ptr = (char*)current_ptr + sizeof(t_meta_chunk) + size;
            next_ptr = align_memory(next_ptr);
            chunk->next = (t_meta_chunk*)next_ptr;
            current_ptr = next_ptr;
        } else {
            chunk->next = NULL;
        }
    }
}

// void *add_block(){

// }

void retard_init(){
	chunk_base.tiny_chunk_list = NULL;
	chunk_base.small_chunk_list = NULL;
}

int init_base(void)
{
	if (!chunk_base.initialized)
	{
		struct rlimit limit;

		if (getrlimit(RLIMIT_AS, &limit) == 0)
		{
			if (limit.rlim_cur == RLIM_INFINITY)
				chunk_base.limit = (size_t)-1;
			else
				chunk_base.limit = limit.rlim_cur;
		}
		else 
			return 0;

		chunk_base.large_chunk_list = NULL;
		chunk_base.initialized = 1;

		void *ptr_one;
		void *ptr_two;

		size_t total_chunk_size = (sizeof(t_meta_chunk) + TINY_SIZE) * TINY_ALLOCS;
		size_t total_size = (total_chunk_size + PAGESIZE -1) & ~(PAGESIZE - 1);

		ft_printf("total_size : %u, limit is : %u\n", total_size, chunk_base.limit * PAGESIZE);

		ptr_one = mmap(NULL, total_size , PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
		if (ptr_one == MAP_FAILED || total_size >= chunk_base.limit){
			retard_init();
			ft_printf("mmap failed\n");
			return 0;
		}
		ft_memset(ptr_one, 0, total_size);
		chunk_base.mem_in_use += total_size;

		total_chunk_size = (sizeof(t_meta_chunk) + SMALL_SIZE) * SMALL_ALLOCS;
		total_size = (total_chunk_size + PAGESIZE -1) & ~(PAGESIZE - 1);

		ft_printf("total_size : %u\n", total_size);

		ptr_two = mmap(NULL, total_size , PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
		if (ptr_two == MAP_FAILED || total_size >= chunk_base.limit){
			retard_init();
			ft_printf("mmap failed\n");
			return 0;
		}
		ft_memset(ptr_two, 0, total_size);
		chunk_base.mem_in_use += total_size;

		init_chunks_list(ptr_one, &chunk_base.tiny_chunk_list , TINY_SIZE, TINY_ALLOCS);
		init_chunks_list(ptr_two, &chunk_base.small_chunk_list ,SMALL_SIZE, SMALL_ALLOCS);


	}
	return 1;
}



t_meta_chunk *find_chunck(size_t size){
	size = ALIGN(size);
	t_meta_chunk *current;

	if (size < TINY_SIZE)
		current = chunk_base.tiny_chunk_list;
	else if (size < SMALL_SIZE)
		current = chunk_base.small_chunk_list;
	else
		current = chunk_base.large_chunk_list;
	while (current && !(current->free && current->size >= size)){
		void *data_ptr = (void *)((char *)current + sizeof(t_meta_chunk));
		data_ptr = align_memory(data_ptr);
		// ft_printf("this chunk at	: %p is free :%d size : %d\n",
		// 	(char *)data_ptr, 
		// 	current->free, current->size);	
		current = current->next;
	}
	if (current){
		void *data_ptr = (void *)((char *)current + sizeof(t_meta_chunk));
		data_ptr = align_memory(data_ptr);
		// ft_printf("chunk selected	: %p is free :%d size : %d\n\n",
		// 	(char *)data_ptr,
		// 	current->free, current->size);
		current->free = 0;
	}
	return current;
}


t_meta_chunk *add_chunk(size_t size) {
	size = ALIGN(size);
	size_t total_chunk_size = size + sizeof(t_meta_chunk) + (ALIGNMENT - 1);
	size_t total_size = (total_chunk_size + PAGESIZE -1) & ~(PAGESIZE - 1);

	void * ptr = mmap(NULL, total_size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	if (ptr == MAP_FAILED){
		ft_printf("mmap failed\n");
		return NULL;
	}
	ft_memset(ptr, 0, total_size);
	chunk_base.mem_in_use += total_size;

	t_meta_chunk *chunk = (t_meta_chunk *)ptr;
	chunk->size = total_size;
	chunk->free = 0;
	chunk->next = NULL;

	add_back(chunk, &(chunk_base.large_chunk_list));
	return (chunk);
}

void *ft_malloc(size_t size) {
	if (!init_base() || size == 0){
		ft_printf("init error or size 0\n");
		return NULL;
	}
	t_meta_chunk *chunk = NULL;

	chunk = find_chunck(size);
	if (!chunk)
		chunk = add_chunk(size);
	if (chunk){
		void *data_ptr = (char*)chunk + sizeof(t_meta_chunk);
        data_ptr = align_memory(data_ptr);
        return data_ptr;
	}


	return NULL;
};
