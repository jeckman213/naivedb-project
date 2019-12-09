CC = gcc

all:
	$(CC) naivedb.c -c -lm
	$(CC) create.c -c -lm
	$(CC) fileconverter.c -c -lm
	$(CC) indexer.c -c -lm
	$(CC) srchindx.c -c -lm
	$(CC) hashFunction.c -c -lm
	$(CC) input.c -c -lm
	$(CC) interfaceFunctions.c -c -lm
	$(CC) naivedb.o -o naivedb
	$(CC) create.o -o create
	$(CC) fileconverter.o -lm -o fileconverter
	$(CC) indexer.o -o indexer
	$(CC) srchindx.o -o srchindx
	$(CC) interfaceFunctions.o -o interfaceFunctions

clean:
	rm *.o
