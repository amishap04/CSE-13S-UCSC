#include <stdio.h>
#include <stdlib.h>

#define NUMBINS 16

int main() {
  int bins[NUMBINS] = {0};
  int bin_size = 1;
  int MAXIMUMVALUE = bin_size * NUMBINS;
  int input_num;

  while (scanf("%d", &input_num) != EOF) {
    if (input_num < 0) {
        continue;
    }

    while (input_num >= MAXIMUMVALUE) {
      bin_size *= 2;
      MAXIMUMVALUE = bin_size * NUMBINS;

      for (int i = 0; i < NUMBINS / 2; i++) {
        bins[i] = bins[2*i] + bins[2*i + 1];
      }

      for (int i = NUMBINS / 2; i < NUMBINS; i++) {
        bins[i] = 0;
      }
    }

    int index = input_num / bin_size;
    bins[index] += 1;
  }

  for (int i = 0; i < NUMBINS; i++) {
    printf("[%3d:%3d] ", i*bin_size, (i+1)*bin_size-1);
    for (int j = 0; j < bins[i]; j++) {
      printf("*");
    }
    printf("\n");
  }

  return 0;
}
