#include <stdio.h>

int main() {
    int a;
    scanf("%d", &a);
    if (a % 3 == 0) printf("fizz");
    if (a % 5 == 0) printf("buzz");
    return 0;
}
