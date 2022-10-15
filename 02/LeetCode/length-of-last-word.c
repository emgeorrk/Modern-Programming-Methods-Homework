int lengthOfLastWord(char * s){
    int ans = 0;
    for (int i = strlen(s) - 1; i >= 0; i--) {
        if (s[i] == ' ' && ans != 0) break;
        if (s[i] != ' ') ans += 1;
    }
    return ans;
}

// https://leetcode.com/submissions/detail/808282824/
