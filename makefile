CC = gcc
CFLAGS = -g
OBJECTS = main.o create.o

naivedb: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o naivedb
%.o: %.c
	$(CC) $(CFLAGS) -c $<
clean:
	rm *.o $(OBJECTS)
