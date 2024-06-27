#include "./libft_malloc.h"

extern t_base chunk_base;
extern void* align_memory(void* ptr);

void show_alloc_mem()
{
	size_t i = 0;
	int total;
	total = 0;
	t_meta_chunk *current;
	current = chunk_base.tiny_chunk_list;
	ft_printf("TINY : 0X%X\n", current);
	while (current)
	{
		// if (!current->free)
		void *data_ptr = (void *)((char *)current + sizeof(t_meta_chunk));
		data_ptr = align_memory(data_ptr);
		ft_printf("0X%X - 0X%X : %d bytes --%u\n",
				  (char *)data_ptr,
				  (char *)data_ptr + current->size,
				  current->size, i);
		total += current->size;
		current = current->next;
		i++;
	}
	i = 0;
	current = chunk_base.small_chunk_list;
	ft_printf("SMALL : 0X%X\n", &current);
	while (current)
	{
		// if (!current->free)
		void *data_ptr = (void *)((char *)current + sizeof(t_meta_chunk));
		data_ptr = align_memory(data_ptr);
		ft_printf("0X%X - 0X%X : %d bytes --%u\n",
				  (char *)data_ptr,
				  (char *)data_ptr + current->size,
				  current->size, i);
		total += current->size;
		current = current->next;
		i++;
	}
	i = 0;
	current = chunk_base.large_chunk_list;
	ft_printf("LARGE : 0X%X\n", &current);
	while (current)
	{
		// if (!current->free)
		void *data_ptr = (void *)((char *)current + sizeof(t_meta_chunk));
		data_ptr = align_memory(data_ptr);
		ft_printf("0X%X - 0X%X : %d bytes --%u\n",
				  (char *)data_ptr,
				  (char *)data_ptr + current->size,
				  current->size, i);
		total += current->size;
		current = current->next;
		i++;
	}
	ft_printf("Total : %d bytes\n", total);
}