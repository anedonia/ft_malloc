#include "./libft_malloc.h"

extern t_base chunk_base;

void show_alloc_mem(){
	int total;
	total = 0;
	t_meta_chunk *current;
	current = chunk_base.tiny_chunk_list;
	ft_printf("TINY : 0X%X\n", current);
	while (current) {
		ft_printf("0X%X - 0X%X : %d bytes\n", (char *)current + sizeof(t_meta_chunk), (char *)current + current->size + sizeof(t_meta_chunk), current->size);  
		total += current->size;
		current = current->next;
	}
	current = chunk_base.small_chunk_list;
	ft_printf("SMALL : 0X%X\n", &current);
	while (current) {
		ft_printf("0X%X - 0X%X : %d bytes\n",(char *)current + sizeof(t_meta_chunk), (char *)current + current->size + sizeof(t_meta_chunk), current->size);  
		total += current->size;
		current = current->next;
	}
	current = chunk_base.large_chunk_list;
	ft_printf("LARGE : 0X%X\n", &current);
	while (current) {
		ft_printf("0X%X - 0X%X : %d bytes\n", (char *)current + sizeof(t_meta_chunk), (char *)current + current->size + sizeof(t_meta_chunk), current->size);  
		total += current->size;
		current = current->next;
	}
	ft_printf("Total : %d bytes\n", total);
}