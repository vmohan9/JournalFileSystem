all: 
	gcc -pthread Journal.c writes.c reads.c faulty_pgm.c -o jfs