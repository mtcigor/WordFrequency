all: WordFrequency.exe

WordFrequency.exe: Files.o Hashing.o WordFrequency.o Main.o
	gcc -o WordFrequency Files.o Hashing.o WordFrequency.o Main.o

Main.o: Main.c HashStuff.h WordFrequency.h
	gcc -c Main.c

Hashing.o: Hashing.c HashStuff.h WordFrequency.h
	gcc -c Hashing.c

WordFrequency.o: WordFrequency.c WordFrequency.h HashStuff.h
	gcc -c WordFrequency.c

Files.o: Files.c WordFrequency.h HashStuff.h

clean:
	rm *.o