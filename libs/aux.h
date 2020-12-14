#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_RESET "\x1b[0m"

#include <stdio.h>
#include <stdbool.h>

struct object
{
    int value;
    int weight;
};

int min(int a, int b)
{
    if (a < b)
        return a;
    else
        return b;
}

int max(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}

void swapInt(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void swapStruct(struct object *a, struct object *b)
{
    struct object temp = *a;
    *a = *b;
    *b = temp;
}

int QuickSort(struct object *list, int left, int right)
{
    int pivot = left, aux;

    if (left < right)
    {
        for (int i = left + 1; i <= right; i++)
        {
            if (list[i].weight < list[left].weight)
            {
                pivot += 1;
                swapStruct(&list[i], &list[pivot]);
            }
        }

        swapStruct(&list[left], &list[pivot]);

        QuickSort(list, left, pivot - 1);
        QuickSort(list, pivot + 1, right);
    }
}