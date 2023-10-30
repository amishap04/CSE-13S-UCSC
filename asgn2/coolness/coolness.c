#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to calculate coolness
double calculate_coolness(double T, double V) {
    return 35.74 + (0.6215 * T) - (35.75 * pow(V, 0.16)) + 0.4275 * T * pow(V, 0.16);
}

int main(int argc, char *argv[]) {
    int headers_printed = 0; // Flag to check if headers have been printed
    // Print the default values when there are zero arguments
    if (argc == 1) {
        for (int T = -10; T <= 40; T += 10) {
            if (!headers_printed) {
                printf("Temp\tWind\tCoolness\n"); // Print headers only once at the beginning
                headers_printed = 1; // Set the flag to indicate that headers have been printed
            } else {
                printf("\n"); // Add a newline before each new temperature category
            }
            for (double V = 5.0; V <= 15.0; V += 5.0) {
                double coolness = calculate_coolness(T, V);
                printf("%.1f\t%.1f\t%.1f\n", (double)T, V, coolness);
            }
        }
    }
    // Check the number of arguments
    if (argc > 3) {
        printf("Usage: ./coolness [temperature] [wind speed]\n");
        exit(1);
    }

    // Handle different argument cases
    if (argc == 0) { // Case: Zero or one argument
        for (int T = -10; T <= 40; T += 10) {
            for (double V = 5.0; V <= 15.0; V += 5.0) {
                double coolness = calculate_coolness(T, V);
                printf("%.1f\t%.1f\t%.1f\n", (double)T, V, coolness);
            }
        }
    } 
     else if (argc == 2) {
        double T = atof(argv[1]);
        if (T >= -99.0 && T <= 50.0) {
            printf("Temp\tWind\tCoolness\n");
            for (double V = 5.0; V <= 15.0; V += 5.0) {
                double coolness = calculate_coolness(T, V);
                printf("%.1f\t%.1f\t%.1f\n", T, V, coolness);
            }
        } else {
            printf("Error: Coolness. Acceptable input values are -99<=T<=50 and 0.5<=V.\n");
            exit(1);
        }
    } else if (argc == 3) {
        double T = atof(argv[1]);
        double V = atof(argv[2]);
        if (T >= -99.0 && T <= 50.0 && V >= 0.5) {
            printf("Temp\tWind\tCoolness\n");
            double coolness = calculate_coolness(T, V);
            printf("%.1f\t%.1f\t%.1f\n", T, V, coolness);
        } else {
            printf("Error: Coolness. Acceptable input values are -99<=T<=50 and 0.5<=V.\n");
            exit(1);
        }
    }

    return 0;
}

