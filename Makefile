# Make variables guide
# $@	Target of the rule
# $%	The target member's name, if the rule's target is an archive
# $<	Name of the first dependency
# $^	List of all dependencies
# $?	List of all dependencies newer than the target
# $*	The "stem" of an implicit or pattern rule

CC = gcc
CFLAGS = -g -O0 -Wall -Wextra -std=c99 -pedantic
LDFLAGS = -fsanitize=address -fsanitize=undefined

lineqsolve: main.o fractions.o
	${CC} ${LDFLAGS} $^ -o $@

main.o: main.h

fractions.o: fractions.h

test: fractions.o

all: lineqsolve test
