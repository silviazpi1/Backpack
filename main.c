#include "libs/dynamicP.h"

int main(int argc, char *argv[])
{
    int num_objects, max_weight;

    printf("\e[1;1H\e[2J"); // Clear console
    printf(ANSI_COLOR_MAGENTA "DYNAMIC PROGRAMMING: " ANSI_COLOR_RESET "BACKPACK\n");

    // Get the maximum weight to carry
    printf("\nIntroduce the maximum weight that the backpack can carry: ");
    scanf("%d", &max_weight);

    // Create the vector with the different existing objects
    printf("\nIntroduce the number of objects: ");
    scanf("%d", &num_objects);
    struct object object_types[num_objects];

    // Fill the vector with the values of the existing objects
    printf("\nIntroduce one by one the values of the different existing objects:\n");
    for (int i = 0; i < num_objects; i++)
    {
        printf("\nWeight:");
        scanf("%d", &object_types[i].weight);
        printf("Value:");
        scanf("%d", &object_types[i].value);
    }

    // Sort the vector
    QuickSort(object_types, 0, num_objects - 1);

    if (object_types[0].weight > max_weight) // If the the lightest object weights more than the max_weight, no object can be carried
        printf("No object can be carried, the lightest object is heavier than the max weight allowed\n");
    else // Otherwise
    {
        // Generate the tables (Dynamic Programming)
        // Matrices are created and one more space is added to create the tables from 0...L (both included)
        int C[num_objects][max_weight + 1];
        bool P[num_objects][max_weight + 1];
        calculateObjects(object_types, max_weight + 1, num_objects, (bool *)P, (int *)C);

        // Calculate the objects to carry (using the generated tables)
        int solution[num_objects];
        backpack(object_types, max_weight + 1, num_objects, (bool *)P, (int *)C, solution);

        // Pack up the backpack
        printf("\nThe most efficient way to pack is:\n");
        for (int i = 0; i < num_objects; i++)
        {
            if (solution[i] != 0)
                printf("%d objects of weight %d and value %d\n", solution[i], object_types[i].weight, object_types[i].value);
        }
        printf("\n");
    }

    printf(ANSI_COLOR_MAGENTA "END OF PROGRAM" ANSI_COLOR_RESET "\n");

    return 0;
}