#include "./libft_malloc.h"

extern t_base chunk_base;

void show_alloc_mem()
{
	for (int mod = 0; mod < 2; mod++)
	{
		size_t i = 0;
		int total;
		total = 0;
		t_meta_chunk *current = NULL;
		current = chunk_base.tiny_chunk_list;
		ft_printf("--------------------------------------------------------------------\n", mod);
		ft_printf("TINY : 0X%X\n", current);
		while (current)
		{
			if ((!current->free && mod == 1) || (mod == 0 && current->free))
			{
				void *data_ptr = (void *)((char *)current + sizeof(t_meta_chunk));
				data_ptr = align_memory(data_ptr);
				ft_printf("0X%X - 0X%X : %d bytes --%u, free: %d\n",
						  (char *)data_ptr,
						  (char *)data_ptr + current->size,
						  current->size, i,
						  current->free);
			}
			total += current->size;
			current = current->next;
			i++;
		}
		i = 0;
		current = chunk_base.small_chunk_list;
		ft_printf("SMALL : 0X%X\n", &current);
		while (current)
		{
			if ((!current->free && mod == 1) || (mod == 0 && current->free))
			{
				void *data_ptr = (void *)((char *)current + sizeof(t_meta_chunk));
				data_ptr = align_memory(data_ptr);
				ft_printf("0X%X - 0X%X : %d bytes --%u, free: %d\n",
						  (char *)data_ptr,
						  (char *)data_ptr + current->size,
						  current->size, i,
						  current->free);
			}
			total += current->size;
			current = current->next;
			i++;
		}
		i = 0;
		current = chunk_base.large_chunk_list;
		ft_printf("LARGE : 0X%X\n", &current);
		while (current)
		{
			if ((!current->free && mod == 1) || (mod == 0 && current->free))
			{
				void *data_ptr = (void *)((char *)current + sizeof(t_meta_chunk));
				data_ptr = align_memory(data_ptr);
				ft_printf("0X%X - 0X%X : %u bytes --%u, free: %d\n",
						  (char *)data_ptr,
						  (char *)data_ptr + current->size,
						  current->size, i,
						  current->free);
			}
			total += current->size;
			current = current->next;
			i++;
		}
		ft_printf("\nTotal			: %d bytes\n", total);
		ft_printf("Total mem in use	: %d bytes in %d pages\n",
			chunk_base.mem_in_use,
			chunk_base.mem_in_use / PAGESIZE );
		ft_printf("--------------------------------------------------------------------\n");
	}
}