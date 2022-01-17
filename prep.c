#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *unique_integers(size_t, int *);
void sort_the_summary(size_t, int *);
void reverse(size_t, size_t, void *);
int comparator(const void *, const void *);
int comparator_2(const void *, const void *);
int bsearchcmp(const void *, const void *);

struct data
{
    int value;
    int frequency;
};

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

    const float inf = INFINITY;

    result = malloc(sizeof(int *) * (int)len);
    for (unsigned long index = 0; index < len; ++index)
    {
        result[index] = malloc(sizeof(int) * 2);
    }

    for (unsigned long index = 0; index < len; ++index)
    {
        for (unsigned long j = 0; j < 2; ++j)
        {
            result[index][j] = (int)inf;
        }
    }

    for (unsigned long index = 0; index < len; ++index)
    {
        result[index][0] = (int)inf;
        result[index][1] = (int)inf;
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
            else if (result[k][0] == (int)inf)
            {
                result[k][0] = array[index];
                result[k][1] = counter;
                break; //THIS BREAK WAS REALLY IMPORTANT
            }
        }
    }

    //resizing array to get rid of (int)infs
    int bound = 0;
    for (int index = 0; index < (int)len; ++index)
    {
        if (result[index][0] == (int)inf)
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
            if (result[index][0] != (int)inf)
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

void reverse(size_t low, size_t high, void * ptr){
    int * new_ptr = (int *)ptr;
    if(low < high){
        int temp = new_ptr[low];
        new_ptr[low] = new_ptr[high];
        new_ptr[high] = temp;  
        reverse(++low, --high, ptr);
    }
}

int bsearchcmp(const void *a, const void *b)
{
    struct data *l = (struct data *)a;
    struct data *r = (struct data *)b;
    return (r->value - l->value);
}

int main(int argv, char **argc)
{
    printf("%d %s\n\n", argv, argc[0]);

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

    /*------------------------------------------------------*/
    int a[] = {1,2,3,4,5,6,7,8,9};
    unsigned long n = sizeof(a) / sizeof(a[0]);
    reverse(0, n - 1, a);

    printf("\n");
    for(unsigned long index = 0; index < n; ++index){
        printf("%d ", a[index]);
    }
    printf("\n");

    /*---------------------------------------------------*/
    unsigned long length_1 = sizeof(nums) / sizeof(nums[0]);
    unsigned long length_2 = sizeof(nums2) / sizeof(nums2[0]);
    unsigned long length_3 = sizeof(nums3) / sizeof(nums3[0]);

    struct data *Data_1 = malloc(sizeof(struct data) * (int)length_1);
    struct data *Data_2 = malloc(sizeof(struct data) * (int)length_2);
    struct data *Data_3 = malloc(sizeof(struct data) * (int)length_3);
    struct data *temp;
    //struct data *temp = malloc(sizeof(struct data));

    for (int index = 0; index < (int)length_1; ++index)
    {
        temp = (struct data *)bsearch(&nums[index], nums, length_1, sizeof(int), bsearchcmp);
        if (temp != NULL)
            continue;
        Data_1[index].value = nums[index];
        Data_1[index].frequency = 0;
    }

    printf("\n\nUsing binary Search\n");
    for (int index = 0; index < (int)length_1; ++index)
    {
        printf("%2d %2d\n", Data_1[index].value, Data_1[index].frequency);
    }
    printf("\n");
    /////////////////////////////////////
    for (int index = 0; index < (int)length_2; ++index)
    {
        temp = (struct data *)bsearch(&nums2[index], nums2, length_2, sizeof(int), bsearchcmp);
        if (temp != NULL)
            continue;
        Data_2[index].value = nums2[index];
        Data_2[index].frequency = 0;
    }

    for (int index = 0; index < (int)length_2; ++index)
    {
        printf("%2d %2d\n", Data_2[index].value, Data_2[index].frequency);
    }
    printf("\n");
    /////////////////////////////////////
    for (int index = 0; index < (int)length_3; ++index)
    {
        temp = (struct data *)bsearch(&nums3[index], nums3, length_3, sizeof(int), bsearchcmp);
        if (temp != NULL)
            continue;
        Data_3[index].value = nums3[index];
        Data_3[index].frequency = 0;
    }

    for (int index = 0; index < (int)length_3; ++index)
    {
        printf("%2d %2d\n", Data_3[index].value, Data_3[index].frequency);
    }
    printf("\n");

    free(Data_1);
    free(Data_2);
    free(Data_3);
    //free(temp);
    /*---------------------------------------------------*/

    return 0;
}