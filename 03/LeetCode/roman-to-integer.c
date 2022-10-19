int value(char a) {
    if (a == 'I') return 1;
    if (a == 'V') return 5;
    if (a == 'X') return 10;
    if (a == 'L') return 50;
    if (a == 'C') return 100;
    if (a == 'D') return 500;
    if (a == 'M') return 1000;
    return 0;
}

int romanToInt(char * s){
    int ans = value(s[strlen(s)-1]), temp, prev_max = value(s[strlen(s) - 1]);
    for (int i = strlen(s) - 2; i >= 0; i--) {
        temp = value(s[i]);
        if (temp < prev_max) ans -= temp;
        else ans += temp;
        prev_max = (prev_max < temp) ? temp : prev_max;
    }
    return ans;
}

// https://leetcode.com/submissions/detail/826124364/
