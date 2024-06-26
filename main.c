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

void reuse_freed_chunks_test(void) {
    // Allocate some memory chunks
    int *ptr_1 = ft_malloc(sizeof(int));
    int *ptr_2 = ft_malloc(sizeof(int));
    int *ptr_3 = ft_malloc(sizeof(int));

    if (!ptr_1 || !ptr_2 || !ptr_3) {
        printf("ft_malloc failed\n");
        return;
    }

    // Free the second chunk
    ft_free(ptr_2);

    // Allocate a new chunk
    int *ptr_4 = ft_malloc(sizeof(int));

    printf("--------------------------------------------------------------------\n");
    printf("Checking if freed memory is reused correctly:\n");

    // Check if the new allocation reuses the freed chunk
    if (ptr_4 == ptr_2) {
        printf(GREEN "PASS" RESET ": Freed chunk reused for new allocation\n\n");
    } else {
        printf(RED "FAIL" RESET ": Freed chunk not reused for new allocation\n\n");
        printf("ptr_2: %p, ptr_4: %p\n", (void*)ptr_2, (void*)ptr_4);
    }

    printf("--------------------------------------------------------------------\n");
}

void small_size_alloc_tests(void) {
    // Define the number of small allocations and the size of each allocation
    const size_t num_allocs = 10;
    const size_t alloc_sizes[] = {64, 128, 256, 512, 1024};  // Sizes within the small allocation range

    void *pointers[num_allocs];

    // Allocate multiple small chunks of memory
    for (size_t i = 0; i < num_allocs; i++) {
        pointers[i] = ft_malloc(alloc_sizes[i % 5]);  // Use different sizes from the array
        if (!pointers[i]) {
            printf(RED "FAIL" RESET ": Allocation %zu failed\n", i);
            return;
        }
    }

    printf("--------------------------------------------------------------------\n");

    // Verify that all pointers are non-null and properly aligned
    for (size_t i = 0; i < num_allocs; i++) {
        if ((uintptr_t)pointers[i] % ALIGNMENT == 0) {
            printf(GREEN "PASS" RESET ": Allocation %zu is aligned to %d bytes\n", i, ALIGNMENT);
        } else {
            printf(RED "FAIL" RESET ": Allocation %zu is not properly aligned\n", i);
            printf("Pointer: %p (aligned: %s)\n", pointers[i], ((uintptr_t)pointers[i] % ALIGNMENT == 0) ? "yes" : "no");
        }
    }

    // Verify that all memory addresses are different
    int all_different = 1;
    for (size_t i = 0; i < num_allocs; i++) {
        for (size_t j = i + 1; j < num_allocs; j++) {
            if (pointers[i] == pointers[j]) {
                all_different = 0;
                printf(RED "FAIL" RESET ": Allocation %zu and %zu have the same address %p\n", i, j, pointers[i]);
            }
        }
    }

    if (all_different) {
        printf(GREEN "PASS" RESET ": All allocations have different addresses\n");
    }

    printf("--------------------------------------------------------------------\n");

    // Free the allocated memory
    for (size_t i = 0; i < num_allocs; i++) {
        ft_free(pointers[i]);
    }
}

void big_alloc_tests(void) {
    size_t big_size = 10 * 1024 * 1024; // 10 MB
    void *big_ptr = ft_malloc(big_size);

    if (!big_ptr) {
        printf("Big allocation failed\n");
        return;
    }

    printf("Checking big allocation:\n");
    if ((uintptr_t)big_ptr % ALIGNMENT == 0) {
        printf(GREEN "PASS" RESET ": Big allocation is aligned to %d bytes\n\n", ALIGNMENT);
    } else {
        printf(RED "FAIL" RESET ": Big allocation is not properly aligned\n\n");
        printf("big_ptr: %p (aligned: %s)\n", (void*)big_ptr, ((uintptr_t)big_ptr % ALIGNMENT == 0) ? "yes" : "no");
    }

    // Optionally fill the allocated memory to check for access errors
    memset(big_ptr, 0, big_size);

    ft_free(big_ptr);
}

void edge_case_tests(void) {
    void *zero_alloc = ft_malloc(0);
    printf("Checking zero-sized allocation:\n");
    if (zero_alloc) {
        printf(RED "FAIL" RESET ": Zero-sized allocation should return NULL\n\n");
    } else {
        printf(GREEN "PASS" RESET ": Zero-sized allocation returned NULL as expected\n\n");
    }

    // Allocate and free multiple times to check for stability
    void *ptrs[100];
    for (int i = 0; i < 100; i++) {
        ptrs[i] = ft_malloc(sizeof(int));
        if (!ptrs[i]) {
            printf(RED "FAIL" RESET ": Allocation failed at iteration %d\n\n", i);
            return;
        }
        ft_free(ptrs[i]);
    }
    printf(GREEN "PASS" RESET ": Multiple allocations and frees succeeded\n\n");

    // Check for address reuse after multiple allocations and frees
    void *first_alloc = ft_malloc(sizeof(int));
    ft_free(first_alloc);
    void *second_alloc = ft_malloc(sizeof(int));
    if (first_alloc == second_alloc) {
        printf(GREEN "PASS" RESET ": Address reused correctly after free\n\n");
    } else {
        printf(RED "FAIL" RESET ": Address not reused after free\n\n");
    }
}

int main(void) {
    int_tests();
    free_tests();
	reuse_freed_chunks_test();
	small_size_alloc_tests();
	big_alloc_tests();
    edge_case_tests();

    show_alloc_mem();
    return 0;
}