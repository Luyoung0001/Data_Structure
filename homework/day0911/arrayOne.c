#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_DEGREE 100

void initializePolynomial(int polynomial[]) {
    for (int i = 0; i < MAX_DEGREE; i++) {
        polynomial[i] = 0;
    }
}

void printPolynomial(int polynomial[]) {
    int printed = 0;
    for (int i = MAX_DEGREE - 1; i >= 0; i--) {
        if (polynomial[i] != 0) {
            if (polynomial[i] > 0 && printed > 0) {
                printf(" + ");
            } else if (polynomial[i] < 0) {
                printf(" - ");
            }

            if (i == 0 || polynomial[i] != 1) {
                printf("%d", abs(polynomial[i]));
            }

            if (i > 0) {
                printf("x");
                if (i > 1) {
                    printf("^%d", i);
                }
            }

            printed++;
        }
    }
    printf("\n");
}

void addPolynomials(int result[], int poly1[], int poly2[]) {
    for (int i = 0; i < MAX_DEGREE; i++) {
        result[i] = poly1[i] + poly2[i];
    }
}

void subtractPolynomials(int result[], int poly1[], int poly2[]) {
    for (int i = 0; i < MAX_DEGREE; i++) {
        result[i] = poly1[i] - poly2[i];
    }
}

void derivative(int polynomial[], int result[]) {
    for (int i = 1; i < MAX_DEGREE; i++) {
        result[i - 1] = i * polynomial[i];
    }
}

int main() {
    int poly1[MAX_DEGREE];
    int poly2[MAX_DEGREE];
    int result[MAX_DEGREE];
    int derivativeResult[MAX_DEGREE] = {0};

    initializePolynomial(poly1);
    initializePolynomial(poly2);
    initializePolynomial(result);

    // Set coefficients for poly1 and poly2
    poly1[0] = 2;
    poly1[1] = 3;
    poly1[3] = 1;

    poly2[0] = -1;
    poly2[1] = 2;
    poly2[2] = -1;

    printf("Poly1: ");
    printPolynomial(poly1);

    printf("Poly2: ");
    printPolynomial(poly2);

    addPolynomials(result, poly1, poly2);
    printf("Poly1 + Poly2: ");
    printPolynomial(result);

    subtractPolynomials(result, poly1, poly2);
    printf("Poly1 - Poly2: ");
    printPolynomial(result);

    derivative(poly1, derivativeResult);
    printf("Derivative of Poly1: ");
    printPolynomial(derivativeResult);

    return 0;
}
