#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// 8 directions
const int da[8] = {2, -2, -2, -1, -1, 1, 1, 2};
const int db[8] = {1, -1, 1, -2, 2, -2, 2, -1};
int w[8][8] = {
    {2, 3, 4, 4, 4, 4, 3, 2}, {3, 4, 6, 6, 6, 6, 4, 3},
    {4, 6, 8, 8, 8, 8, 6, 4}, {4, 6, 8, 8, 8, 8, 6, 4},
    {4, 6, 8, 8, 8, 8, 6, 4}, {4, 6, 8, 8, 8, 8, 6, 4},
    {3, 4, 6, 6, 6, 6, 4, 3}, {2, 3, 4, 4, 4, 4, 3, 2}}; // Numbers of branches
int ans[8][8];                                           // The Hamiltonian path
int legal(int a) {
    if (a >= 0 && a < 8)
        return 1;
    return 0;
} // Judge if the position is in the legal range
int main() {
    int a0, b0;
    scanf("%d %d", &a0, &b0); // Input starting position
    memset(ans, 0, sizeof(ans));
    int i, j, min, a, b, a_min, b_min;
    for (i = 1; i <= 64; i++) {
        ans[a0][b0] = i;
        min = 8;
        for (j = 0; j < 8; j++) {
            a = a0 + da[j], b = b0 + db[j];
            if (legal(a) && legal(b) && !ans[a][b] && --w[a][b] < min) {
                min = w[a][b];
                a_min = a, b_min = b;
            }
        }
        a0 = a_min, b0 = b_min; // Find the place with least branches
    }
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++)
            printf("%3d", ans[i][j]);
        printf("\n");
    } // Output the path
    return 0;
}