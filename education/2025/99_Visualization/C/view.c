#include <stdio.h>
#include <math.h>

int main() {
    FILE *gp = popen("gnuplot -persistent", "w");
    if (!gp) return 1;

    fprintf(gp, "set title 'Sine Wave'\n");
    fprintf(gp, "plot '-' with lines\n");

    for (double x = 0; x <= 2*M_PI; x += 0.1)
        fprintf(gp, "%lf %lf\n", x, sin(x));

    fprintf(gp, "e\n");  // end of data
    pclose(gp);
    return 0;
}
