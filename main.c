// #include "libft_malloc.h"
// #include <stdio.h>
// #define GREEN "\033[0;32m"
// #define RED "\033[0;31m"
// #define RESET "\033[0m"

// void int_tests(void){

// 	int *ptr_1 = ft_malloc(sizeof(int));
// 	int *ptr_2 = ft_malloc(sizeof(int));
// 	int *ptr_3 = ft_malloc(sizeof(int));
// 	int *ptr_4 = ft_malloc(sizeof(int));

// 	if (!ptr_1 || !ptr_2 || !ptr_3 || !ptr_4){
// 		printf("ft_malloc failed\n");
// 		return;
// 	}

// 	*ptr_1 = 12;
// 	*ptr_2 = 34;
// 	*ptr_3 = 56;
// 	*ptr_4 = 78;

// 	ft_printf("--------------------------------------------------------------------\n");

// 	ft_printf("ptr have the correct values : ptr_1 = 12\n");
// 	if (*ptr_1 == 12 && *ptr_2 == 34 && *ptr_3 == 56 && *ptr_4 == 78)
// 	{
// 		printf(GREEN "PASS" RESET "\n\n");
// 	}
// 	else
// 	{
// 		printf(RED "FAIL" RESET "\n\n");
// 	}
// 	ft_printf("ptr have different addrs :\n");
// 	if (ptr_1 != ptr_2 && ptr_2 != ptr_3 && ptr_3 != ptr_4)
// 	{
// 		printf(GREEN "PASS" RESET "\n\n");
// 	}
// 	else
// 	{
// 		printf("1 : %p\n 2 : %p\n 3 : %p\n 4 : %p\n", ptr_1, ptr_2, ptr_3, ptr_4);
// 		printf(RED "FAIL" RESET "\n\n");
// 	}
	
// 	ft_printf("Checking memory alignment:\n");
//     if (((size_t)ptr_1 % ALIGNMENT == 0) && ((size_t)ptr_2 % ALIGNMENT == 0) &&
//         ((size_t)ptr_3 % ALIGNMENT == 0) && ((size_t)ptr_4 % ALIGNMENT == 0)) {
//         printf(GREEN "PASS" RESET ": All pointers are aligned to %d bytes\n\n", ALIGNMENT);
//     } else {
//         printf(RED "FAIL" RESET ": Pointers are not properly aligned\n\n");
//         printf("ptr_1: %p (aligned: %s)\n", ptr_1, ((size_t)ptr_1 % ALIGNMENT == 0) ? "yes" : "no");
//         printf("ptr_2: %p (aligned: %s)\n", ptr_2, ((size_t)ptr_2 % ALIGNMENT == 0) ? "yes" : "no");
//         printf("ptr_3: %p (aligned: %s)\n", ptr_3, ((size_t)ptr_3 % ALIGNMENT == 0) ? "yes" : "no");
//         printf("ptr_4: %p (aligned: %s)\n", ptr_4, ((size_t)ptr_4 % ALIGNMENT == 0) ? "yes" : "no");
//     }

// 	ft_printf("--------------------------------------------------------------------\n");
// }

// void free_tests(void) {
//     int *ptr_1 = ft_malloc(sizeof(int));
//     int *ptr_2 = ft_malloc(sizeof(int));
//     int *ptr_3 = ft_malloc(sizeof(int));
//     int *ptr_4 = ft_malloc(sizeof(int));

// 	if (!ptr_1 || !ptr_2 || !ptr_3 || !ptr_4){
// 		printf("ft_malloc failed\n");
// 		return;
// 	}

//     *ptr_1 = 12;
//     *ptr_2 = 34;
//     *ptr_3 = 56;
//     *ptr_4 = 78;

//     ft_free(ptr_2);
//     ft_free(ptr_4);

//     int *ptr_5 = ft_malloc(sizeof(int));
//     int *ptr_6 = ft_malloc(sizeof(int));

// 	if (!ptr_5 || !ptr_6){
// 		printf("ft_malloc failed\n");
// 		return;
// 	}
//     *ptr_5 = 90;
//     *ptr_6 = 100;

//     ft_printf("--------------------------------------------------------------------\n");

//     ft_printf("Checking if freed memory is reused correctly:\n");
//     if (*ptr_1 == 12 && *ptr_3 == 56 && *ptr_5 == 90 && *ptr_6 == 100) {
//         printf(GREEN "PASS" RESET "\n\n");
//     } else {
//         printf(RED "FAIL" RESET "\n\n");
//     }

//     ft_printf("Checking if new allocations have different addresses:\n");
//     if (ptr_5 != ptr_1 && ptr_5 != ptr_3 && ptr_6 != ptr_1 && ptr_6 != ptr_3 && ptr_5 != ptr_6) {
//         printf(GREEN "PASS" RESET "\n\n");
//     } else {
//         printf("ptr_1: %p, ptr_3: %p, ptr_5: %p, ptr_6: %p\n", ptr_1, ptr_3, ptr_5, ptr_6);
//         printf(RED "FAIL" RESET "\n\n");
//     }

//     ft_printf("Checking memory alignment for new allocations:\n");
//     if (((size_t)ptr_5 % ALIGNMENT == 0) && ((size_t)ptr_6 % ALIGNMENT == 0)) {
//         printf(GREEN "PASS" RESET ": All new pointers are aligned to %d bytes\n\n", ALIGNMENT);
//     } else {
//         printf(RED "FAIL" RESET ": New pointers are not properly aligned\n\n");
//         printf("ptr_5: %p (aligned: %s)\n", ptr_5, ((size_t)ptr_5 % ALIGNMENT == 0) ? "yes" : "no");
//         printf("ptr_6: %p (aligned: %s)\n", ptr_6, ((size_t)ptr_6 % ALIGNMENT == 0) ? "yes" : "no");
//     }

//     ft_printf("--------------------------------------------------------------------\n");
// }

// int main (void){
// 	int_tests();
// 	free_tests();

// 	show_alloc_mem();
// }
#include "libft_malloc.h"
#include <stdio.h>
#include <stdint.h>

#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define RESET "\033[0m"

void int_tests(void) {
    int *ptr_1 = ft_malloc(sizeof(int));
    int *ptr_2 = ft_malloc(sizeof(int));
    int *ptr_3 = ft_malloc(sizeof(int));
    int *ptr_4 = ft_malloc(sizeof(int));

    if (!ptr_1 || !ptr_2 || !ptr_3 || !ptr_4) {
        printf("ft_malloc failed\n");
        return;
    }

    *ptr_1 = 12;
    *ptr_2 = 34;
    *ptr_3 = 56;
    *ptr_4 = 78;

    printf("--------------------------------------------------------------------\n");

    printf("ptr have the correct values: ");
    if (*ptr_1 == 12 && *ptr_2 == 34 && *ptr_3 == 56 && *ptr_4 == 78) {
        printf(GREEN "PASS" RESET "\n\n");
    } else {
        printf(RED "FAIL" RESET "\n\n");
    }

    printf("ptr have different addrs: ");
    if (ptr_1 != ptr_2 && ptr_2 != ptr_3 && ptr_3 != ptr_4) {
        printf(GREEN "PASS" RESET "\n\n");
    } else {
        printf("1: %p\n2: %p\n3: %p\n4: %p\n", (void*)ptr_1, (void*)ptr_2, (void*)ptr_3, (void*)ptr_4);
        printf(RED "FAIL" RESET "\n\n");
    }

    printf("Checking memory alignment:\n");
    if (((uintptr_t)ptr_1 % ALIGNMENT == 0) && ((uintptr_t)ptr_2 % ALIGNMENT == 0) &&
        ((uintptr_t)ptr_3 % ALIGNMENT == 0) && ((uintptr_t)ptr_4 % ALIGNMENT == 0)) {
        printf(GREEN "PASS" RESET ": All pointers are aligned to %d bytes\n\n", ALIGNMENT);
    } else {
        printf(RED "FAIL" RESET ": Pointers are not properly aligned\n\n");
        printf("ptr_1: %p (aligned: %s)\n", (void*)ptr_1, ((uintptr_t)ptr_1 % ALIGNMENT == 0) ? "yes" : "no");
        printf("ptr_2: %p (aligned: %s)\n", (void*)ptr_2, ((uintptr_t)ptr_2 % ALIGNMENT == 0) ? "yes" : "no");
        printf("ptr_3: %p (aligned: %s)\n", (void*)ptr_3, ((uintptr_t)ptr_3 % ALIGNMENT == 0) ? "yes" : "no");
        printf("ptr_4: %p (aligned: %s)\n", (void*)ptr_4, ((uintptr_t)ptr_4 % ALIGNMENT == 0) ? "yes" : "no");
    }

    printf("--------------------------------------------------------------------\n");
}

void free_tests(void) {
    int *ptr_1 = ft_malloc(sizeof(int));
    int *ptr_2 = ft_malloc(sizeof(int));
    int *ptr_3 = ft_malloc(sizeof(int));
    int *ptr_4 = ft_malloc(sizeof(int));

    if (!ptr_1 || !ptr_2 || !ptr_3 || !ptr_4) {
        printf("ft_malloc failed\n");
        return;
    }

    *ptr_1 = 12;
    *ptr_2 = 34;
    *ptr_3 = 56;
    *ptr_4 = 78;

    ft_free(ptr_2);
    ft_free(ptr_4);

    int *ptr_5 = ft_malloc(sizeof(int));
    int *ptr_6 = ft_malloc(sizeof(int));

    if (!ptr_5 || !ptr_6) {
        printf("ft_malloc failed\n");
        return;
    }

    *ptr_5 = 90;
    *ptr_6 = 100;

    printf("--------------------------------------------------------------------\n");

    printf("Checking if freed memory is reused correctly: ");
    if (*ptr_1 == 12 && *ptr_3 == 56 && *ptr_5 == 90 && *ptr_6 == 100) {
        printf(GREEN "PASS" RESET "\n\n");
    } else {
        printf(RED "FAIL" RESET "\n\n");
    }

    printf("Checking if new allocations have different addresses: ");
    if (ptr_5 != ptr_1 && ptr_5 != ptr_3 && ptr_6 != ptr_1 && ptr_6 != ptr_3 && ptr_5 != ptr_6) {
        printf(GREEN "PASS" RESET "\n\n");
    } else {
        printf("ptr_1: %p, ptr_3: %p, ptr_5: %p, ptr_6: %p\n", (void*)ptr_1, (void*)ptr_3, (void*)ptr_5, (void*)ptr_6);
        printf(RED "FAIL" RESET "\n\n");
    }

    printf("Checking memory alignment for new allocations:\n");
    if (((uintptr_t)ptr_5 % ALIGNMENT == 0) && ((uintptr_t)ptr_6 % ALIGNMENT == 0)) {
        printf(GREEN "PASS" RESET ": All new pointers are aligned to %d bytes\n\n", ALIGNMENT);
    } else {
        printf(RED "FAIL" RESET ": New pointers are not properly aligned\n\n");
        printf("ptr_5: %p (aligned: %s)\n", (void*)ptr_5, ((uintptr_t)ptr_5 % ALIGNMENT == 0) ? "yes" : "no");
        printf("ptr_6: %p (aligned: %s)\n", (void*)ptr_6, ((uintptr_t)ptr_6 % ALIGNMENT == 0) ? "yes" : "no");
    }

    printf("--------------------------------------------------------------------\n");
}

int main(void) {
    int_tests();
    free_tests();

    show_alloc_mem();
    return 0;
}