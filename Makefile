# Make variables guide
# $@	Target of the rule
# $%	The target member's name, if the rule's target is an archive
# $<	Name of the first dependency
# $^	List of all dependencies
# $?	List of all dependencies newer than the target
# $*	The "stem" of an implicit or pattern rule

CC ?= gcc
Cflags = -g -O3 -Wall -Wextra

lineqsolve: main.c
	${CC} $? ${Cflags} -o $@
