#include "libft_malloc.h"

int main (void){
	int *test;
	test = ft_malloc(10);
	*test = 1234567;
	
	ft_printf("--------------------------------------------------------------------\n");
	ft_printf("test sur ptr expected : %d ft_malloc : %d\n", 1234567, *test);
	ft_printf("\n\n\n\n\n\n");
	ft_printf("--------------------------------------------------------------------\n");
	show_alloc_mem();
}