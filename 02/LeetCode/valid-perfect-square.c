int bs(int l, int r, int num) {
    int m = (l+r)/2;
    if (m*m >= num) return bs(l, m, num);
    else return bs(m, r, num);
}

bool isPerfectSquare(int num){
    long long l = 1, r = num, m;
    while (r - l > 1) {
        m = (r + l)/2;
        if (m*m >= num) r = m;
        else l = m;
    }
    return (r*r == num) ? true : false;
}

// https://leetcode.com/submissions/detail/808296055/
