The C Programming Language, Second Edition
By Brian Kernigan and Dennis Ritchie

This Repo contains the following:
1) Some Book Examples
2) My Solutions
3) Book Solutions

C USAGE:
gcc foo.c; ./a.out

to include the math lib
gcc foo.c -lm

RUN ALL TESTS:
sh all_tests.sh

RUN A PROGRAM THAT DEPENDS ON lib.c
gcc -Wno-parentheses lib.c your_program.c ;./a.out
