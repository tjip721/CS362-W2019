CFLAGS= -Wall -fpic -coverage -lm -std=c99

testme: testme.c
	gcc -o testme testme.c -g  $(CFLAGS)

test: testme
	valgrind testme &> quizOutput.txt || true
	gcov testme.c >> quizOutput.txt
	cat testme.c.gcov >> quizOutput.txt
