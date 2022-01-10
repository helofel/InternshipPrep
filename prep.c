#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int *unique_integers(size_t, int *);
void sort_the_summary(size_t, int *);
int comparator(const void *, const void *);
int comparator_2(const void *, const void *);

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

void sort_the_summary(size_t len, int *array)
{
    int **result;
    int **new_res;
    int counter;
    const int inf = INFINITY;

    result = malloc(sizeof(int *) * (int)len);
    for (unsigned long index = 0; index < len; ++index)
    {
        result[index] = malloc(sizeof(int) * 2);
    }

    for (unsigned long index = 0; index < len; ++index)
    {
        for (unsigned long j = 0; j < 2; ++j)
        {
            result[index][j] = inf;
        }
    }

    for (unsigned long index = 0; index < len; ++index)
    {
        result[index][0] = inf;
        result[index][1] = inf;
    }

    for (unsigned long index = 0; index < len; ++index)
    {
        counter = 1;
        for (unsigned long i = 0; i < len; ++i)
        {
            if (index == i)
            {
                continue;
            }

            if (array[index] == array[i])
            {
                ++counter;
            }
        }
        //printf("num: %d freq: %d\n", array[index], counter);
        for (unsigned long k = 0; k < len; ++k)
        {
            if (result[k][0] == array[index])
            {
                break;
            }
            else if (result[k][0] == inf)
            {
                result[k][0] = array[index];
                result[k][1] = counter;
                break; //THIS BREAK WAS REALLY IMPORTANT
            }
        }
    }

    //resizing array to get rid of infs
    int bound = 0;
    for (int index = 0; index < (int)len; ++index)
    {
        if (result[index][0] == inf)
        {
            break;
        }
        bound++;
        //printf("%d %d\n", result[index][0], result[index][1]);
    }

    new_res = malloc(sizeof(int *) * bound);

    for (int index = 0; index < (int)len; ++index)
    {
        new_res[index] = malloc(sizeof(int) * 2);
    }

    for (int index = 0; index < bound; ++index)
    {
        for (int j = 0; j < 2; ++j)
        {
            if (result[index][0] != inf)
            {
                new_res[index][0] = result[index][0];
                new_res[index][1] = result[index][1];
            }
        }
    }

    printf("\nResized array: \n");
    for (int index = 0; index < bound; ++index)
    {
        printf("%d %d\n", new_res[index][0], new_res[index][1]);
    }

    printf("\n");

    printf("\n");
    //Sort by descending frequency
    qsort(new_res, bound, sizeof(new_res[0]), comparator);

    for (int index = 0; index < bound; ++index)
    {
        printf("%d %d\n", new_res[index][0], new_res[index][1]);
    }

    printf("\n");
    //Sort by ascending value while maintaining descending frequencies
    qsort(new_res, bound, sizeof(new_res[0]), comparator_2);

    for (int index = 0; index < bound; ++index)
    {
        printf("%d %d\n", new_res[index][0], new_res[index][1]);
    }

    free(result);
    free(new_res);
}

int comparator(const void *a, const void *b)
{
    const int *l = *(const int **)a;
    const int *r = *(const int **)b;
    return (r[1] - l[1]);
}

int comparator_2(const void *a, const void *b)
{
    const int *l = *(const int **)a;
    const int *r = *(const int **)b;
    if (r[1] == l[1])
        return (l[0] - r[0]);

    return (r[1] - l[1]);
}

int main(int argv, char **argc)
{
    printf("%d %s\n", argv, argc[0]);

    /*------------------------------------------------------*/
    int *uniques;
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

    int arr[] = {3, 3, 1, 2, 1};
    sort_the_summary(sizeof(arr) / sizeof(arr[0]), arr);

    return 0;
}