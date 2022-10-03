#include <stdio.h>

int main() {
    int a, b;
    scanf("%d %d", &a, &b);
    int ans = 0;
    while (a > 0) {
        a -= b;
        ans++;
    }
    if (a < 0) ans--;
    printf("%d", ans);
    return 0;
}
