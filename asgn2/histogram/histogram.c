#include <stdio.h>
#include <stdlib.h>
#define NUM_BINS 16

int main(void) {
    int bins[NUM_BINS];
    int max_value = 0;
    int input;

    // Initialize bins to 0
    for (int i = 0; i < NUM_BINS; i++) {
        bins[i] = 0;
    }
    // Read input and update bins
    while (scanf("%d", &input) != EOF) {
        if (input < 0) {
            continue;
        }
        // Update max_value if necessary
        if (input > max_value) {
            max_value = input;
        }
        // Calculate bin index and increment bin count
        int bin_index = input * NUM_BINS / max_value;
        bins[bin_index]++;
    }
    // Print histogram
    for (int i = 0; i < NUM_BINS; i++) {
        printf("%2d - %2d : ", i * max_value / NUM_BINS, (i + 1) * max_value / NUM_BINS);
        for (int j = 0; j < bins[i]; j++) {
            printf("*");
        }
        printf("\n");
    }
    return 0;
}
