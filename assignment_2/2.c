#include <stdio.h>
#define MAX_LENGTH 1024

/* length of string(char*) */
int _strlen(char *string) {
    int cnt = 0;
    while(string[cnt] != '\0') {
        cnt++;
    }
    return cnt;
}

/* check whether given word is palindrome */
int isPalindrome(char *word) {
    int left = 0, right = _strlen(word)-1;
    int i = 0;
    for(i = 0; i < (right+1) / 2; i++) {
        if(word[left+i] != word[right-i]) {
            return 0;
        }
    }
    return 1;
}

int main() {
    char word[MAX_LENGTH];
    printf("Word: ");
    scanf("%s", word);
    if(isPalindrome(word)) {
        printf("%s is palindrome\n", word);
    } 
    else {
        printf("%s is not palindrome\n", word);
    }
    return 0;
}
