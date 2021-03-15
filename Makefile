CC = gcc
CFLAGS = -g

all : 1-4 3-6 5-2 4-2 4-6

1-4 : 1-4.c
	$(CC) $(CFLAGS) -o $@ $< -lm

3-6 : 3-6.o arbrebin.o fap.o
	$(CC) $(CFLAGS) -o $@ 3-6.o arbrebin.o fap.o -lm

3-6.o : 3-6.c
	$(CC) $(CFLAGS) -c 3-6.c

5-2 : 5-2.c
	$(CC) $(CFLAGS) -o $@ $< -lm

4-2 : 4-2.c
	$(CC) $(CFLAGS) -o $@ $<
	
4-6 : 4-6.c
	$(CC) $(CFLAGS) -o $@ $< -lm

arbrebin.o : arbrebin.c arbrebin.h
	$(CC) $(CFLAGS) -c arbrebin.c

fap.o : fap.c fap.h
	$(CC) $(CFLAGS) -c fap.c

clean:
	rm -rf 1-4 3-6 4-2 5-2 4-6 *.o
