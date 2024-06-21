#include "libft_malloc.h"
#include <stdio.h>
#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define RESET "\033[0m"

void int_tests(void){

	int *ptr_1 = ft_malloc(sizeof(int));
	int *ptr_2 = ft_malloc(sizeof(int));
	int *ptr_3 = ft_malloc(sizeof(int));
	int *ptr_4 = ft_malloc(sizeof(int));

	*ptr_1 = 12;
	*ptr_2 = 34;
	*ptr_3 = 56;
	*ptr_4 = 78;

	ft_printf("--------------------------------------------------------------------\n");

	ft_printf("ptr have the correct values : ptr_1 = 12\n");
	if (*ptr_1 == 12 && *ptr_2 == 34 && *ptr_3 == 56 && *ptr_4 == 78)
	{
		printf(GREEN "PASS" RESET "\n\n");
	}
	else
	{
		printf(RED "FAIL" RESET "\n\n");
	}
	ft_printf("ptr have different addrs :\n");
	if (ptr_1 != ptr_2 && ptr_2 != ptr_3 && ptr_3 != ptr_4)
	{
		printf(GREEN "PASS" RESET "\n\n");
	}
	else
	{
		printf("1 : %p\n 2 : %p\n 3 : %p\n 4 : %p\n", ptr_1, ptr_2, ptr_3, ptr_4);
		printf(RED "FAIL" RESET "\n\n");
	}
	
	ft_printf("Checking memory alignment:\n");
    if (((size_t)ptr_1 % ALIGNMENT == 0) && ((size_t)ptr_2 % ALIGNMENT == 0) &&
        ((size_t)ptr_3 % ALIGNMENT == 0) && ((size_t)ptr_4 % ALIGNMENT == 0)) {
        printf(GREEN "PASS" RESET ": All pointers are aligned to %d bytes\n\n", ALIGNMENT);
    } else {
        printf(RED "FAIL" RESET ": Pointers are not properly aligned\n\n");
        printf("ptr_1: %p (aligned: %s)\n", ptr_1, ((size_t)ptr_1 % ALIGNMENT == 0) ? "yes" : "no");
        printf("ptr_2: %p (aligned: %s)\n", ptr_2, ((size_t)ptr_2 % ALIGNMENT == 0) ? "yes" : "no");
        printf("ptr_3: %p (aligned: %s)\n", ptr_3, ((size_t)ptr_3 % ALIGNMENT == 0) ? "yes" : "no");
        printf("ptr_4: %p (aligned: %s)\n", ptr_4, ((size_t)ptr_4 % ALIGNMENT == 0) ? "yes" : "no");
    }

	ft_printf("--------------------------------------------------------------------\n");
}

int main (void){
	int_tests();

	

	show_alloc_mem();
}