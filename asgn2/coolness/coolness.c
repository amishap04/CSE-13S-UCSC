#include <math.h>
#include <stdio.h>

double calculate_coolness(double temperature, double windspeed) {
  return 35.74 + 0.6215 * temperature - 35.75 * pow(windspeed, 0.16) +
         0.4275 * temperature * pow(windspeed, 0.16);
}

int main(void) {
  double temperature = 20.5;
  double windspeed = 10.2;
  double coolness = calculate_coolness(temperature, windspeed);
  printf("Coolness: %f\n", coolness);
  return 0;
}
