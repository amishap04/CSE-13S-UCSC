#include <stdio.h>
#include <stdlib.h>

#define NUM_BINS 16

void printHistogram(int bins[], int binSize, int range);

int main() {
    int bins[NUM_BINS] = {0};
    int binSize = 1;
    int range = NUM_BINS;
    int num;

    while (scanf("%d", &num) != EOF) {
        if (num < 0) {
            continue; // Ignore negative numbers.
        }

        // If the number is outside the range, expand the bins.
        while (num >= range) {
            // Compress current bins into the first half.
            for (int i = 0; i < NUM_BINS / 2; i++) {
                bins[i] = bins[2 * i] + bins[2 * i + 1];
            }

            // Clear the second half of the bins.
            for (int i = NUM_BINS / 2; i < NUM_BINS; i++) {
                bins[i] = 0;
            }

            // Double the bin size and range.
            binSize *= 2;
            range *= 2;
        }

        // Increment the appropriate bin.
        bins[num / binSize]++;
    }

    // Print the histogram.
    printHistogram(bins, binSize, range);

    return 0;
}

void printHistogram(int bins[], int binSize, int range) {
    printf("Histogram (bin size: %d, range: 0 to %d):\n", binSize, range - 1);
    for (int i = 0; i < NUM_BINS; i++) {
        printf("%3d - %3d : ", i * binSize, (i + 1) * binSize - 1);
        for (int j = 0; j < bins[i]; j++) {
            printf("#");
        }
        printf("\n");
    }
}
