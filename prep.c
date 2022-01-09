#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int *unique_integers(size_t, int *);

int *unique_integers(size_t len, int *array)
{
    int *uniques;
    unsigned long index = 0;
    int counter;

    uniques = malloc(sizeof(int) * len);

    while (index < len)
    {
        counter = 0;
        for (unsigned long j = 0, k = len; j < k + 1; ++j)
        {
            if (index != j)
            {
                if (array[index] == array[j])
                    counter++;
            }
        }

        if (counter == 0)
            uniques[index] = array[index];
        ++index;
    }

    return uniques;
}

int main(int argv, char **argc)
{
    printf("%d %s\n", argv, argc[0]);

    /*------------------------------------------------------*/
    int * uniques;
    int nums[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int nums2[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int nums3[] = {7, 11, 24, 3, 7, 99, 6, 10, 23, 9, 11};

    size_t t = sizeof(nums) / sizeof(nums[0]);
    size_t t2 = sizeof(nums2) / sizeof(nums2[0]);
    size_t t3 = sizeof(nums3) / sizeof(nums3[0]);

    uniques = unique_integers(t, nums);
    for (unsigned long index = 0; index < 11; ++index)
    {
        printf("%d ", uniques[index]);
    }

    printf("\n");
    uniques = unique_integers(t2, nums2);
    for (unsigned long index = 0; index < 11; ++index)
    {
        printf("%d ", uniques[index]);
    }

    printf("\n");
    uniques = unique_integers(t3, nums3);
    for (unsigned long index = 0; index < 11; ++index)
    {
        printf("%d ", uniques[index]);
    }
    printf("\n");

    free(uniques);
    /*------------------------------------------------------*/
}