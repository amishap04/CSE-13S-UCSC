#include <stdio.h>
#include <stdlib.h>


int main() {
    int bin_size = 1;
    int bins[16] = {0};
    int range = 16;
    int input;


    while (scanf("%d", &input) != EOF) {
        if (input >= range) {
           // double the range and bin size
           bin_size *= 2;
           range *= 2;

           // compressing the 16 bins into the first 8 bins
           for (int i = 0; i < 8; i++) {
               bins[i] = bins[i] + bins[i + 8];
               bins[i + 8] = 0;
}
}

        // calculate the bin index for the input
        int bin_index = input / bin_size;
        bins[bin_index]++;
}

    // printing the histogram
    for (int i = 0; i < 16; i++) {
        printf("%3d - %3d : %d\n", i * bin_size, (i + 1) * bin_size - 1, num_bins, bin_size, max_value);
}

    return 0;
}
