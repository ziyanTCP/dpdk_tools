//
// Created by ziyan on 1/15/20.
//

/* getchar example : typewriter */
#include <stdio.h>

test_getchar(){
    char c;
    puts ("Enter character. Include a dot ('.') in a sentence to exit:");
    do {
        c=getchar();
        putchar (c);
    } while (c != '.');
    return 0;
}