#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// the function to calculate coolness
double calculate_coolness(double T, double V) {
  return 35.74 + (0.6215 * T) - (35.75 * pow(V, 0.16)) + 0.4275 * T * pow(V, 0.16);
}

int main(int argc, char *argv[]) {
    // printing the default values when there are 0 arguments passed 
    if (argc == 1){
        printf("Temp\tWind\tCoolness\n");
        for (float T = -10; T <= 40; T+= 10){
	    for (double V = 5.0; V <= 15.0; V += 5.0) {
	        double coolness = calculate_coolness(T,V);
                print_row(T, V, coolness);
	       //  printf("%.1f\t%.1f\t%.1f\n", (double)T, V, coolness);
}
}
} 

    // checking the number of arguments 
    if (argc > 3) {
        printf("Usage: ./coolness [temperature] [wind speed]\n");
        exit(1);
}

    // determining how mant rows to print based on the number of arguments
    int num_rows = 1; // defaults to only 1 row
    if (argc == 3) {
        num_rows = 1;
}   else if (argc == 2) {
      num_rows = 11; // number of temperature rows
}

    // handling difference argument cases
    if (argc == 1) { // zero or 1 argument
       printf("Temp\tWind\tCoolness\n");
       for (int T = -10; T <= 40; T += 10) {
           for (double V = 5.0; V <= 15.0; V += 5.0) {
               double coolness = calculate_coolness(T,V);
               printf("%.1f\t%.1f\t%.1f\n", (double)T, V, coolness);


}

}

} else if (argc == 2) {
    double T = atof(argv[1]);
    if (T >= -99.0 && T <= 50.0) {
       printf("Temp\tWind\tCoolness\n");
       for (double V = 5.0; V <= 15.0; V += 5.0) {
           double coolness = calculate_coolness(T,V);
           printf("%.1f\t%.1f\t%.1f\n", T, V, coolness);
}

}   else {
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
