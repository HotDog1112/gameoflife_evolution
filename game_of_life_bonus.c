#include<stdio.h>
int min(int a, int b, int c) {
int min = 0;


    if (a < b && a < c) {
        min = a;
    } else if (c < min) {
        min = c;
    } else {
        min = b;
    }
    printf("%d", min);
 return min;   
}
int main(void){
int a, b, c;
    scanf("%d %d %d", &a, &b, &c);
    min(a, b, c);
    

    return 0;
}