// stems words and prints them one per line

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stemmer.h"

#define MAXWORD 100

int main(void) {
    char word[MAXWORD + 1];
    while (scanf("%s", word) == 1) {
        int end = stem(word, 0, strlen(word) - 1);
        word[end + 1] = '\0';
        printf("%s\n", word);
    }
}
