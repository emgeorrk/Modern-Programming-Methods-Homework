int firstUniqChar(char * s) {
    int count[26];
    for (int i = 0; i < 26; i++) count[i] = 0;
    for (int i = 0; i < strlen(s); i++) {
        count[s[i] % 97]++;
    }
    for (int i = 0; i < strlen(s); i++) {
        if (count[s[i] % 97] == 1) return i;
    }
    return -1;
}

// https://leetcode.com/submissions/detail/826131987/
