#include "libft_malloc.h"
#include <stdio.h>
#include <stdint.h>

#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define RESET "\033[0m"

void int_tests(void) {
    int *ptr_1 = malloc(sizeof(int));
    int *ptr_2 = malloc(sizeof(int));
    int *ptr_3 = malloc(sizeof(int));
    int *ptr_4 = malloc(sizeof(int));

    if (!ptr_1 || !ptr_2 || !ptr_3 || !ptr_4) {
        ft_printf("malloc failed\n");
        return;
    }
    *ptr_1 = 12;
    *ptr_2 = 34;
    *ptr_3 = 56;
    *ptr_4 = 78;
    ft_printf("--------------------------------------------------------------------\n");

    ft_printf("ptr have the correct values: ");
    if (*ptr_1 == 12 && *ptr_2 == 34 && *ptr_3 == 56 && *ptr_4 == 78) {
        ft_printf(GREEN "PASS" RESET "\n\n");
    } else {
        ft_printf(RED "FAIL" RESET "\n\n");
    }

    ft_printf("ptr have different addrs: ");
    if (ptr_1 != ptr_2 && ptr_2 != ptr_3 && ptr_3 != ptr_4) {
        ft_printf(GREEN "PASS" RESET "\n\n");
    } else {
        ft_printf("1: %p\n2: %p\n3: %p\n4: %p\n", (void*)ptr_1, (void*)ptr_2, (void*)ptr_3, (void*)ptr_4);
        ft_printf(RED "FAIL" RESET "\n\n");
    }

    ft_printf("Checking memory alignment:\n");
    if (((uintptr_t)ptr_1 % ALIGNMENT == 0) && ((uintptr_t)ptr_2 % ALIGNMENT == 0) &&
        ((uintptr_t)ptr_3 % ALIGNMENT == 0) && ((uintptr_t)ptr_4 % ALIGNMENT == 0)) {
        ft_printf(GREEN "PASS" RESET ": All pointers are aligned to %d bytes\n\n", ALIGNMENT);
    } else {
        ft_printf(RED "FAIL" RESET ": Pointers are not properly aligned\n\n");
        ft_printf("ptr_1: %p (aligned: %s)\n", (void*)ptr_1, ((uintptr_t)ptr_1 % ALIGNMENT == 0) ? "yes" : "no");
        ft_printf("ptr_2: %p (aligned: %s)\n", (void*)ptr_2, ((uintptr_t)ptr_2 % ALIGNMENT == 0) ? "yes" : "no");
        ft_printf("ptr_3: %p (aligned: %s)\n", (void*)ptr_3, ((uintptr_t)ptr_3 % ALIGNMENT == 0) ? "yes" : "no");
        ft_printf("ptr_4: %p (aligned: %s)\n", (void*)ptr_4, ((uintptr_t)ptr_4 % ALIGNMENT == 0) ? "yes" : "no");
    }

    ft_printf("--------------------------------------------------------------------\n");
}

void free_tests(void) {
    int *ptr_1 = malloc(sizeof(int));
    int *ptr_2 = malloc(sizeof(int));
    int *ptr_3 = malloc(sizeof(int));
    int *ptr_4 = malloc(sizeof(int));

    if (!ptr_1 || !ptr_2 || !ptr_3 || !ptr_4) {
        ft_printf("malloc failed\n");
        return;
    }

    *ptr_1 = 12;
    *ptr_2 = 34;
    *ptr_3 = 56;
    *ptr_4 = 78;

    free(ptr_2);
    free(ptr_4);

    int *ptr_5 = malloc(sizeof(int));
    int *ptr_6 = malloc(sizeof(int));

    if (!ptr_5 || !ptr_6) {
        ft_printf("malloc failed\n");
        return;
    }

    *ptr_5 = 90;
    *ptr_6 = 100;

    ft_printf("--------------------------------------------------------------------\n");

    ft_printf("Checking if freed memory is reused correctly: ");
    if (*ptr_1 == 12 && *ptr_3 == 56 && *ptr_5 == 90 && *ptr_6 == 100) {
        ft_printf(GREEN "PASS" RESET "\n\n");
    } else {
        ft_printf(RED "FAIL" RESET "\n\n");
    }

    ft_printf("Checking if new allocations have different addresses: ");
    if (ptr_5 != ptr_1 && ptr_5 != ptr_3 && ptr_6 != ptr_1 && ptr_6 != ptr_3 && ptr_5 != ptr_6) {
        ft_printf(GREEN "PASS" RESET "\n\n");
    } else {
        ft_printf("ptr_1: %p, ptr_3: %p, ptr_5: %p, ptr_6: %p\n", (void*)ptr_1, (void*)ptr_3, (void*)ptr_5, (void*)ptr_6);
        ft_printf(RED "FAIL" RESET "\n\n");
    }

    ft_printf("Checking memory alignment for new allocations:\n");
    if (((uintptr_t)ptr_5 % ALIGNMENT == 0) && ((uintptr_t)ptr_6 % ALIGNMENT == 0)) {
        ft_printf(GREEN "PASS" RESET ": All new pointers are aligned to %d bytes\n\n", ALIGNMENT);
    } else {
        ft_printf(RED "FAIL" RESET ": New pointers are not properly aligned\n\n");
        ft_printf("ptr_5: %p (aligned: %s)\n", (void*)ptr_5, ((uintptr_t)ptr_5 % ALIGNMENT == 0) ? "yes" : "no");
        ft_printf("ptr_6: %p (aligned: %s)\n", (void*)ptr_6, ((uintptr_t)ptr_6 % ALIGNMENT == 0) ? "yes" : "no");
    }

    ft_printf("--------------------------------------------------------------------\n");
}

void reuse_freed_chunks_test(void) {
    // Allocate some memory chunks
    int *ptr_1 = malloc(sizeof(int));
    int *ptr_2 = malloc(sizeof(int));
    int *ptr_3 = malloc(sizeof(int));

    if (!ptr_1 || !ptr_2 || !ptr_3) {
        ft_printf("malloc failed\n");
        return;
    }

    // Free the second chunk
    free(ptr_2);

    // Allocate a new chunk
    int *ptr_4 = malloc(sizeof(int));

    ft_printf("--------------------------------------------------------------------\n");
    ft_printf("Checking if freed memory is reused correctly:\n");

    // Check if the new allocation reuses the freed chunk
    if (ptr_4 == ptr_2) {
        ft_printf(GREEN "PASS" RESET ": Freed chunk reused for new allocation\n\n");
    } else {
        ft_printf(RED "FAIL" RESET ": Freed chunk not reused for new allocation\n\n");
        ft_printf("ptr_2: %p, ptr_4: %p\n", (void*)ptr_2, (void*)ptr_4);
    }
	free(ptr_4);
    ft_printf("--------------------------------------------------------------------\n");
}

void small_size_alloc_tests(void) {
    // Define the number of small allocations and the size of each allocation
    const size_t num_allocs = 10;
    const size_t alloc_sizes[] = {32, 128, 256, 512, 992};  // Sizes within the small allocation range

    void *pointers[num_allocs];

    // Allocate multiple small chunks of memory
    for (size_t i = 0; i < num_allocs; i++) {
        pointers[i] = malloc(alloc_sizes[i % 5]);  // Use different sizes from the array
        if (!pointers[i]) {
            ft_printf(RED "FAIL" RESET ": Allocation %zu failed\n", i);
            return;
        }
    }

    ft_printf("--------------------------------------------------------------------\n");

    // Verify that all pointers are non-null and properly aligned
    for (size_t i = 0; i < num_allocs; i++) {
        if ((uintptr_t)pointers[i] % ALIGNMENT == 0) {
            ft_printf(GREEN "PASS" RESET ": Allocation %u is aligned to %d bytes\n", i, ALIGNMENT);
        } else {
            ft_printf(RED "FAIL" RESET ": Allocation %zu is not properly aligned\n", i);
            ft_printf("Pointer: %p (aligned: %s)\n", pointers[i], ((uintptr_t)pointers[i] % ALIGNMENT == 0) ? "yes" : "no");
        }
    }

    // Verify that all memory addresses are different
    int all_different = 1;
    for (size_t i = 0; i < num_allocs; i++) {
        for (size_t j = i + 1; j < num_allocs; j++) {
            if (pointers[i] == pointers[j]) {
                all_different = 0;
                ft_printf(RED "FAIL" RESET ": Allocation %zu and %zu have the same address %p\n", i, j, pointers[i]);
            }
        }
    }

    if (all_different) {
        ft_printf(GREEN "PASS" RESET ": All allocations have different addresses\n");
    }

    ft_printf("--------------------------------------------------------------------\n");

    // Free the allocated memory
    for (size_t i = 0; i < num_allocs; i++) {
        free(pointers[i]);
    }
}

void big_alloc_tests(void) {
    size_t big_size = 10 * 1024 * 1024; // 10 MB
    void *big_ptr = malloc(big_size);

    if (!big_ptr) {
        ft_printf("Big allocation failed\n");
        return;
    }

    ft_printf("Checking big allocation:\n");
    if ((uintptr_t)big_ptr % ALIGNMENT == 0) {
        ft_printf(GREEN "PASS" RESET ": Big allocation is aligned to %d bytes\n\n", ALIGNMENT);
    } else {
        ft_printf(RED "FAIL" RESET ": Big allocation is not properly aligned\n\n");
        ft_printf("big_ptr: %p (aligned: %s)\n", (void*)big_ptr, ((uintptr_t)big_ptr % ALIGNMENT == 0) ? "yes" : "no");
    }

    // Optionally fill the allocated memory to check for access errors
    memset(big_ptr, 0, big_size);

    free(big_ptr);
}

void edge_case_tests(void) {
    void *zero_alloc = malloc(0);
    ft_printf("Checking zero-sized allocation:\n");
    if (zero_alloc) {
        ft_printf(RED "FAIL" RESET ": Zero-sized allocation should return NULL\n\n");
    } else {
        ft_printf(GREEN "PASS" RESET ": Zero-sized allocation returned NULL as expected\n\n");
    }
	free(zero_alloc);

    // Allocate and free multiple times to check for stability
    void *ptrs[100];
    for (int i = 0; i < 100; i++) {
        ptrs[i] = malloc(sizeof(int));
        // ptrs[i] = malloc(100);
        if (!ptrs[i]) {
            ft_printf(RED "FAIL" RESET ": Allocation failed at iteration %d\n\n", i);
            return;
        }
        free(ptrs[i]);
    }
    ft_printf(GREEN "PASS" RESET ": Multiple allocations and frees succeeded\n\n");

    // Check for address reuse after multiple allocations and frees
    void *first_alloc = malloc(sizeof(int));
    free(first_alloc);
    void *second_alloc = malloc(sizeof(int));
    if (first_alloc == second_alloc) {
        ft_printf(GREEN "PASS" RESET ": Address reused correctly after free\n\n");
    } else {
        ft_printf(RED "FAIL" RESET ": Address not reused after free\n\n");
    }
}

void realloc_tests(void) {
    ft_printf("Starting realloc tests...\n");

    // Test realloc with NULL pointer (should behave like malloc)
    ft_printf("Test 1: realloc with NULL pointer\n");
    int *ptr_1 = realloc(NULL, sizeof(int) * 4);
    if (ptr_1 == NULL) {
        ft_printf(RED "FAIL" RESET ": realloc with NULL pointer returned NULL\n");
    } else {
        ft_printf(GREEN "PASS" RESET ": realloc with NULL pointer allocated memory\n");
    }
    free(ptr_1);

    // Test realloc to a larger size
    ft_printf("Test 2: realloc to a larger size\n");
    int *ptr_2 = malloc(sizeof(int) * 4);
    for (int i = 0; i < 4; i++) {
        ptr_2[i] = i;
    }
    int *ptr_3 = realloc(ptr_2, 400);
    if (ptr_3 == NULL) {
        ft_printf(RED "FAIL" RESET ": realloc to a larger size returned NULL\n");
    } else {
        int success = 1;
        for (int i = 0; i < 4; i++) {
            if (ptr_3[i] != i) {
                success = 0;
                break;
            }
        }
        if (success) {
            ft_printf(GREEN "PASS" RESET ": realloc to a larger size preserved data\n");
        } else {
            ft_printf(RED "FAIL" RESET ": realloc to a larger size did not preserve data\n");
        }
    }
    free(ptr_3);

    // Test realloc to a smaller size
    ft_printf("Test 3: realloc to a smaller size\n");
    int *ptr_4 = malloc(sizeof(int) * 8);
    for (int i = 0; i < 8; i++) {
        ptr_4[i] = i;
    }
    int *ptr_5 = realloc(ptr_4, sizeof(int) * 4);
    if (ptr_5 == NULL) {
        ft_printf(RED "FAIL" RESET ": realloc to a smaller size returned NULL\n");
    } else {
        int success = 1;
        for (int i = 0; i < 4; i++) {
            if (ptr_5[i] != i) {
                success = 0;
                break;
            }
        }
        if (success) {
            ft_printf(GREEN "PASS" RESET ": realloc to a smaller size preserved data\n");
        } else {
            ft_printf(RED "FAIL" RESET ": realloc to a smaller size did not preserve data\n");
        }
    }
    free(ptr_5);

    // Test realloc with size of zero (should behave like free)
    ft_printf("Test 4: realloc with size of zero\n");
    int *ptr_6 = malloc(sizeof(int) * 4);
    int *ptr_7 = realloc(ptr_6, 0);
    if (ptr_7 != NULL) {
        ft_printf(RED "FAIL" RESET ": realloc with size of zero did not return NULL\n");
    } else {
        ft_printf(GREEN "PASS" RESET ": realloc with size of zero returned NULL\n");
    }
	  // Test realloc with string data preservation
    ft_printf("Test 6: realloc with string data preservation\n");
    char *str_1 = malloc(6);
    strcpy(str_1, "Hello");
    ft_printf("Original string: %s\n", str_1);

    // Increase size
    char *str_2 = realloc(str_1, 900);
    if (str_2 == NULL) {
        ft_printf(RED "FAIL" RESET ": realloc for string data preservation returned NULL\n");
    } else {
        strcpy(str_2 + 5, " World");
        ft_printf("New string after realloc and append: %s\n", str_2);
        if (strcmp(str_2, "Hello World") == 0) {
            ft_printf(GREEN "PASS" RESET ": realloc preserved string data correctly when increasing size\n");
        } else {
            ft_printf(RED "FAIL" RESET ": realloc did not preserve string data correctly when increasing size\n");
        }
    }

    // Reduce size
    char *str_3 = realloc(str_2, 6);
    if (str_3 == NULL) {
        ft_printf(RED "FAIL" RESET ": realloc for reducing string data returned NULL\n");
    } else {
        ft_printf("String after reducing size: %s\n", str_3);
        if (strncmp(str_3, "Hello", 5) == 0) {
            ft_printf(GREEN "PASS" RESET ": realloc preserved string data correctly when reducing size\n");
        } else {
            ft_printf(RED "FAIL" RESET ": realloc did not preserve string data correctly when reducing size\n");
        }
    }
    free(str_3);

    ft_printf("Realloc tests completed.\n");
}

void large_allocation_test(void) {
    const size_t tiny_alloc_size = 32;
    const size_t big_alloc_size = 992;
    const size_t num_allocs = 5000;

    void *tiny_pointers[num_allocs];
    void *big_pointers[num_allocs];

    // Test tiny allocations
    ft_printf("Testing endurance tiny allocations...\n");
    for (size_t i = 0; i < num_allocs; i++) {
        tiny_pointers[i] = malloc(tiny_alloc_size);
        if (!tiny_pointers[i]) {
            ft_printf(RED "FAIL" RESET ": Tiny allocation %zu failed\n", i);
            return;
        }
    }
    ft_printf(GREEN "PASS" RESET ": Successfully allocated endurance tiny allocations\n");

    // Test big allocations
    ft_printf("Testing endurance  big allocations...\n");
    for (size_t i = 0; i < num_allocs; i++) {
        big_pointers[i] = malloc(big_alloc_size);
        if (!big_pointers[i]) {
            ft_printf(RED "FAIL" RESET ": Big allocation %zu failed\n", i);
            return;
        }
    }
    ft_printf(GREEN "PASS" RESET ": Successfully allocated endurance  big allocations\n");

    // Free tiny allocations
    ft_printf("Freeing tiny allocations...\n");
    for (size_t i = 0; i < num_allocs; i++) {
        free(tiny_pointers[i]);
    }
    ft_printf(GREEN "PASS" RESET ": Successfully freed tiny allocations\n");

    // Free big allocations
    ft_printf("Freeing big allocations...\n");
    for (size_t i = 0; i < num_allocs; i++) {
        free(big_pointers[i]);
    }
    ft_printf(GREEN "PASS" RESET ": Successfully freed big allocations\n");
}

extern t_base chunk_base;

extern void print_chunks(t_meta_chunk *head);
extern int number_chunks(t_meta_chunk *head);


int main(void) {

	// show_alloc_mem();
    int_tests();
    free_tests();
	reuse_freed_chunks_test();
	small_size_alloc_tests();
	big_alloc_tests();
	edge_case_tests();
	realloc_tests();
	large_allocation_test();
	show_alloc_mem_overview();
	// large_allocation_test();
	// show_alloc_mem_overview();
	// show_alloc_mem();
	// show_alloc_mem_chunk();


	return 0;
}