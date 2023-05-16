//===============================================
#include <stdio.h>
#include <stdarg.h>
//===============================================
double average(int n, ...) {
    double lSum = 0.0;

    va_list lArgs;
    va_start(lArgs, n);

    for (int i = 0; i < n; i++) {
        double lNote = va_arg(lArgs, double);
        lSum += lNote;
    }

    va_end(lArgs);

    double lAverage = lSum/n;
    return lAverage;
}
//===============================================
int main(int _argc, char** _argv) {
    printf("Moyenne(10.0, 5.0) : %.2f\n", average(2, 10.0, 5.0));
    printf("Moyenne(12.0, 7.0, 15.0) : %.2f\n", average(3, 12.0, 7.0, 15.0));
    printf("Moyenne(17.0, 13.5, 16.0, 14.5) : %.2f\n", average(4, 17.0, 13.5, 16.0, 14.5));
    return 0;
}
//===============================================
