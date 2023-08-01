# Make variables guide
# $@	Target of the rule
# $%	The target member's name, if the rule's target is an archive
# $<	Name of the first dependency
# $^	List of all dependencies
# $?	List of all dependencies newer than the target
# $*	The "stem" of an implicit or pattern rule

CC = gcc
CFLAGS = -g -O3 -Wall -Wextra
LDFLAGS = -fsanitize=address -fsanitize=undefined

lineqsolve: main.o fractions.o
	${CC} ${CFLAGS} ${LDFLAGS} $^ -o $@

main.o: main.c main.h
	${CC} -c ${CFLAGS} ${LDFLAGS} $^

fractions.o: fractions.c fractions.h
	${CC} -c ${CFLAGS} ${LDFLAGS} $^

test: test.o fractions.o
	${CC} ${CFLAGS} ${LDFLAGS} $^ -o $@

test.o: test.c
	${CC} -c ${CFLAGS} ${LDFLAGS} $^
