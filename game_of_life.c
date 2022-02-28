#include <stdio.h>
#include <stdlib.h>
#define SIZEFIELDX 80
#define SIZEFIELDY 25
int** input(int **a);
int** copy_arr(int **current, int **next);
int** comp(int **current, int **next);
int** null_arr(int **next);
void output(int **a);
void free_arr(int **a);
int finish_arr(int **current, int **next);
int extremelineX(int x);
int extremelineY(int y);

int main(void) {
    int **current = NULL, **next = NULL;
    current = input(current);
    if (current != NULL) {
        next = malloc(SIZEFIELDY * sizeof(int*));
        for (int z = 0; z < SIZEFIELDY; z++)
            next[z] = malloc(SIZEFIELDX * sizeof(int));
        next = null_arr(next);
        output(current);
        if (freopen("/dev/tty", "r", stdin) == NULL) {
            printf("n/a");
        } else {
            do {
                int c = getchar();
                if (c != 32)
                   continue;
                comp(current, next);
                current = copy_arr(current, next);
                next = null_arr(next);
                output(current);
            } while (finish_arr(current, next) == 1);
        }
        free_arr(current);
    } else {
            printf("n/a");
    }
    if (next != NULL)
        free_arr(next);
    return 0;
}

void free_arr(int **a) {
    for (int i = 0; i < SIZEFIELDY; i++)
        free(a[i]);
    free(a);
}

int** input(int **a) {
    int buf = 0;
    a = malloc(SIZEFIELDY * sizeof(int*));
    for (int z = 0; z < SIZEFIELDY; z++)
        a[z] = malloc(SIZEFIELDX * sizeof(int));
    for (int y = 0; y < SIZEFIELDY; y++) {
        for (int x = 0; x < SIZEFIELDX; x++) {
            a[y][x] = getchar();
            if  (a[y][x] < 48 || a[y][x] > 49) {
                buf = 1;
            }
        }
    }
    if (buf == 1) {
        for (int i = 0; i < SIZEFIELDY; i++)
            free(a[i]);
            free(a);
    }
    return a;
}

int** copy_arr(int **current, int **next) {
    for (int y = 0; y < SIZEFIELDY; y++)
        for (int x = 0; x < SIZEFIELDX; x++)
            current[y][x] = next[y][x];
    return current;
}

int** null_arr(int **next) {
    for (int y = 0; y < SIZEFIELDY; y++)
        for (int x = 0; x < SIZEFIELDX; x++)
            next[y][x] = 48;
    return next;
}

int** comp(int **current, int **next) {
    for (int y = 0; y < SIZEFIELDY; y++) {
        for (int x = 0; x < SIZEFIELDX; x++) {
            // checking the neighboorhood
            int cnt = 0;
            if (current[extremelineY(y - 1)][extremelineX(x)] == 49)
                cnt++;
            if (current[extremelineY(y - 1)][extremelineX(x + 1)] == 49)
                cnt++;
            if (current[extremelineY(y)][extremelineX(x + 1)] == 49)
                cnt++;
            if (current[extremelineY(y + 1)][extremelineX(x + 1)] == 49)
                cnt++;
            if (current[extremelineY(y + 1)][extremelineX(x)] == 49)
                cnt++;
            if (current[extremelineY(y + 1)][extremelineX(x - 1)] == 49)
                cnt++;
            if (current[extremelineY(y)][extremelineX(x - 1)] == 49)
                cnt++;
            if (current[extremelineY(y - 1)][extremelineX(x - 1)] == 49)
                cnt++;
            // checking if cell is live or dead
            if (current[y][x] == 49) {
                if (cnt < 2 || cnt > 3) {
                    next[y][x] = 48;
                    } else {
                        next[y][x] = 49;
                    }
            } else {
                if (cnt == 3) {
                    next[y][x] = 49;
                } else {
                    next[y][x] = 48;
                }
            }
        }
    }
    return next;
}

void output(int **a) {
    for (int x=0; x < SIZEFIELDX + 2; x++)
        printf("-");
    printf("\n");
    for (int y = 0; y < SIZEFIELDY; y++) {
        for (int x = 0; x < SIZEFIELDX + 2; x++) {
            if (x == 0 || x == 81) {
                printf("|");
                continue;
            }
            if (a[y][x - 1] == 49) {
                printf("#");
                } else {
                    printf(" ");
                }
            }
            printf("\n");
    }
    for (int x=0; x < SIZEFIELDX + 2; x++)
        printf("-");
    printf("\n");
}

int finish_arr(int **current, int **next) {
    int buf = 0;
    for (int y = 0; y < SIZEFIELDY; y++)
        for (int x = 0; x < SIZEFIELDX; x++) {
            if (current[y][x] != next[y][x])
                buf = 1;
        }
        return buf;
}

int extremelineX(int x) {
    if (x == -1)
        x = 79;
    if (x == 80)
        x = 0;
    return x;
}

int extremelineY(int y) {
    if (y == -1)
        y = 24;
    if (y == 25)
        y = 0;
    return y;
}
