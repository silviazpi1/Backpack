#include "aux.h"

// Function that generates the tables for Dynamic Programming
void calculateObjects(struct object *object_types, int max_weight, int num_objects, bool *P, int *C)
{
    // Initialize first row of the matrices to false and zero
    for (int i = 0; i < num_objects; i++)
    {
        *((P + i * max_weight) + 0) = false;
        *((C + i * max_weight) + 0) = 0;
    }

    // Go through C and P Matrices and fills them up
    for (int i = 0; i < num_objects; i++)
    {
        for (int j = 1; j < max_weight; j++)
        {
            if (i == 0 && j < object_types[i].weight) // If lightest object and weight is bigger than j weight
            {
                *((C + i * max_weight) + j) = 0;     // Set C[i, j] to 0
                *((P + i * max_weight) + j) = false; // Set P[i, j] to False
            }
            else if (i == 0) // If lightest object and weight is not smaller than j weight, write object value to C
            {
                *((C + i * max_weight) + j) = object_types[i].value; // C[i, j] = 1 + C[i,j-T[0]]
                *((P + i * max_weight) + j) = true;                  // Set P[i, j] to True
            }
            else if (j < object_types[i].weight) // If the quantity is smaller than the value of the coin
            {
                *((C + i * max_weight) + j) = *((C + (i - 1) * max_weight) + j); // C[i, j] = C[i-1, j]
                *((P + i * max_weight) + j) = false;                             // Set P[i, j] to False
            }
            else
            {
                *((C + i * max_weight) + j) = max(*((C + (i - 1) * max_weight) + (j - object_types[i].weight)) + object_types[i].value, *((C + (i - 1) * max_weight) + j)); // C[i,j] = máximo(V[i-1,j], V[i-1,j-pesoDe(objetos[j])] + valorDe(objetos[j]))
                *((P + i * max_weight) + j) = (*((C + i * max_weight) + j) != *((C + (i - 1) * max_weight) + j));                                                           // Set P[i, j] to True if C[i, j] is different from C[i-1, j]
            }
        }
    }

    // Print C matrix to check
    printf("\n");
    for (int i = 0; i < num_objects; i++)
    {
        for (int j = 1; j < max_weight; j++)
            printf("%d\t", *((C + i * max_weight) + j));
        printf("\n");
    }
}

// Function that given the tables of Dynamic Programming finds the most efficient way to give change back
void backpack(int change, int num_coins, int *coin_types, bool *permutations, int *coins, int *solution)
{
    int i = num_coins, j = change - 1, index;

    // Initialize solution vector to zero
    for (index = 0; index < num_coins; index++)
        solution[index] = 0;

    // While there is more than one type of coin and there's still some change to give back
    while (i != 0 && j != 0)
    {
        if (*((permutations + i * change) + j) == false) // If this coin is not used, skip it
            i--;
        else // Otherwise
        {
            solution[i] = solution[i] + 1; // Add one of these coins to the solution vector
            j = j - coin_types[i];         // Substract its value from the pending change
        }
    }

    // If there are is only one type of coin, add the number of coins needed to give back the change left
    if (i == 0)
        solution[0] = (*((coins + i * change) + j) + solution[0]);
}