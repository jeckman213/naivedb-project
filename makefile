CC = gcc
CFLAGS = -g
OBJECTS = main.o create.o fileconverter.o

naivedb: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -lm -o naivedb
%.o: %.c
	$(CC) $(CFLAGS) -c $< -lm
clean:
	rm *.o $(OBJECTS)
