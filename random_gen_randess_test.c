#include <stdio.h>
#include <stdlib.h>

#define SEQ_LENGTH 10    // Length of the sequence of random numbers
#define VALUE_TO_CHECK 5 // Value to check the gap lengths for
#define MIN_GAP_LENGTH 3 // Minimum gap length to consider random

int main() {
    int sequence[SEQ_LENGTH];
    int i, gap_count, max_gap;
    int is_random = 1; // Flag to determine randomness, initially set to true

    unsigned int seed = 42u; // Seed value for LCG (explicitly unsigned)

    printf("Generated random numbers:\n");

    // Generate a sequence of 10 random numbers using LCG
    for (i = 0; i < SEQ_LENGTH; i++) {
        seed = (1103515245u * seed + 12345u) % 2147483648u; // LCG formula
        sequence[i] = seed % 10; // Generate a random number between 0 and 9
        printf("%d ", sequence[i]); // Print the generated random number
    }

    // Calculate the maximum gap length for the specified value
    gap_count = 0;
    max_gap = 0;
    for (i = 0; i < SEQ_LENGTH; i++) {
        if (sequence[i] == VALUE_TO_CHECK) {
            gap_count++;
        } else {
            if (gap_count > max_gap) {
                max_gap = gap_count;
            }
            gap_count = 0;
        }
    }

    // Check if the sequence appears random based on the maximum gap length
    if (max_gap >= MIN_GAP_LENGTH) {
        is_random = 1; // Considered random if the max gap is above threshold
    } else {
        is_random = 0; // Not considered random if the max gap is below threshold
    }

    // Display the maximum gap length found for the specified value
    printf("\n\nValue to check gap lengths for: %d\n", VALUE_TO_CHECK);
    printf("Maximum gap length for value %d: %d\n", VALUE_TO_CHECK, max_gap);

    // Print whether the sequence is considered random or not
    if (is_random) {
        printf("\nThe generated sequence appears to be random.\n");
    } else {
        printf("\nThe generated sequence does not appear to be random.\n");
    }

    return 0;
}
