#include "libft_malloc.h"
#include <stdio.h>

extern t_base chunk_base;

void remove_chunk(t_meta_chunk **head, t_meta_chunk *chunk){

	if (*head == NULL || chunk == NULL)
		return;
	if (chunk == *head){
		*head = chunk->next;
	}
	else
	{
		t_meta_chunk *prev = *head;
		t_meta_chunk *temp = (*head)->next;
		while (temp != NULL && temp != chunk){
			prev = temp;
			temp = temp->next;
		}
		if (!temp)
			return;
		prev->next = temp->next;
	}
}

int remove_block(t_meta_chunk **head, t_meta_chunk *to_remove, t_meta_chunk *next, size_t nbpage)
{
	int res = 1;

	if (*head == NULL || to_remove == NULL || !next || to_remove == *head){
		return res;
	}
	else
	{
		t_meta_chunk *prev = *head;
		t_meta_chunk *temp_l = (*head)->next;
		while (temp_l != NULL && temp_l != to_remove)
		{
			prev = temp_l;
			temp_l = temp_l->next;
		}
		if (!temp_l){
			return res;
		}
		prev->next = next;
	}
	if (munmap(to_remove, nbpage * PAGESIZE) != 0)
	{
		ft_printf("munmap failed in block removing\n");
		return res;
	}
	chunk_base.mem_in_use -= nbpage * PAGESIZE;
	return res; 
}

void defrag_mem(t_meta_chunk **head){
    t_meta_chunk *current = *head;
    t_meta_chunk *temp;
	size_t data_size = (*head)->size + 32;
	int i;

    while (current != NULL && current->next != NULL) {
        if ((uintptr_t)current % PAGESIZE == 0 && current->free) {
			temp = current;
			i = 0;
            while (current != NULL && current->free) {
				i++;
				if (current && i * data_size / PAGESIZE == 1 && (uintptr_t)current % PAGESIZE == 0){
					remove_block(head, temp, current, 1);
					break;
				}
				current = current->next;
			}

		}
		else
			current = current->next;
	}
}

void print_chunks(t_meta_chunk *head) {
    t_meta_chunk *current = head;
	int i = 0;
    while (current) {
		i++;
        current = current->next;
    }
    printf("total : %d\n", i);
}

int number_chunks(t_meta_chunk *head) {
    t_meta_chunk *current = head;
	int i = 0;
    while (current) {
		i++;
        current = current->next;
    }
	return (i);
}

void free(void *ptr){
	init_base();
    if (!ptr) {
        return;
    }
	uintptr_t addr = (uintptr_t)ptr - sizeof(t_meta_chunk);
    if (addr % ALIGNMENT != 0) {
        addr -= ALIGNMENT - (addr % ALIGNMENT);
    }
    t_meta_chunk *chunk = (t_meta_chunk *)addr;

    chunk->free = 1;
	if (chunk->size > 1000)
	{
		chunk_base.mem_in_use -= chunk->size;
		remove_chunk(&chunk_base.large_chunk_list, chunk);
		if (munmap(chunk, chunk->size) != 0)
			return;
	}
	// if (chunk_base.large_threshold < chunk_base.mem_in_use)
	if (number_chunks(chunk_base.small_chunk_list) > 1000)
	{
		// printf("chunk nb before : %d\n",number_chunks(chunk_base.tiny_chunk_list));
		// printf("chunk nb before : %d\n",number_chunks(chunk_base.small_chunk_list));
		// print_chunks(chunk_base.tiny_chunk_list);
		// print_chunks(chunk_base.small_chunk_list);
		if (chunk_base.tiny_chunk_list)
			defrag_mem(&chunk_base.tiny_chunk_list);
		if (chunk_base.small_chunk_list)
			defrag_mem(&chunk_base.small_chunk_list);
		// chunk_base.large_threshold *= 1.1;

		// printf("chunk nb after : %d\n",number_chunks(chunk_base.tiny_chunk_list));
		// printf("chunk nb after : %d\n",number_chunks(chunk_base.small_chunk_list));
		// print_chunks(chunk_base.tiny_chunk_list);
		// print_chunks(chunk_base.small_chunk_list);
	}
}