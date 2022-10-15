void reverseString(char* s, int sSize){
    for (int i = 0; i < sSize/2; i++) {
        char temp;
        temp = s[i];
        s[i] = s[sSize - i - 1];
        s[sSize - i - 1] = temp;
    }
    return s;
}

// https://leetcode.com/submissions/detail/823277533/
