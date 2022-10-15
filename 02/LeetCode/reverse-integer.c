int reverse(long long x){
    long long ans = 0, sign = 1;
    if (x < 0) {
        sign = -1;
        x *= -1;
    }
    while (x > 0) {
        ans *= 10;
        ans += x % 10;
        x /= 10;
    }
    ans *= sign;
    int overflow_checker = ans;
    return (overflow_checker == ans) ? ans : 0;
}

// https://leetcode.com/submissions/detail/808267718/
