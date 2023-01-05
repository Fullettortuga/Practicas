CC = gcc -Wall -Wextra 
CFLAGS = -g -c
SOURCE= rmsf.c

all: rmsf

rmsf: rmsf.o
	$(CC) rmsf.o -o rmsf

rmsf.o: rmsf.c
	$(CC) $(CFLAGS) rmsf.c

clean:
	rm -rf *.o rmsf

install:
	cp rmsf /usr/local/bin

uninstall:
	rm -rf /usr/local/bin/rmsf

test.sh:
	./test.sh



