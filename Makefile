CC=gcc
CFLAGS=-Wall -Wextra 


all: execT execS 


mainT.o: mainT.c avlT.h 
	$(CC) $(CFLAGS) -c $< -o $@

avlT.o: avlT.c avlT.h 
	$(CC) $(CFLAGS) -c $< -o $@

execT: mainT.o avlT.o
	$(CC) $(CFLAGS) $^ -o $@



mainS.o: mainS.c avlS.h 
	$(CC) $(CFLAGS) -c $< -o $@

avlS.o: avlS.c avlS.h 
	$(CC) $(CFLAGS) -c $< -o $@

execS: mainS.o avlS.o
	$(CC) $(CFLAGS) $^ -o $@
