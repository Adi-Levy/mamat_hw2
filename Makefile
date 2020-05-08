# Compiler to use
CC=gcc 				
# Flags to use
CFLAGS=-g -Wall		
# Linker to use
CCLINK=$(CC)		
# Libraries to use (empty for now)
LIBS=				
# Objects to link together
OBJS=party.o voter.o main.o
# The remove file command to be used with "clean" target
RM=rm -f

all: $(OBJS)
	$(CCLINK) -o Elect_MMT $(OBJS) $(LIBS)

party.o: party.c party.h
voter.o: voter.c voter.h
main.o: main.c party.h voter.h

clean:
	$(RM) *.o