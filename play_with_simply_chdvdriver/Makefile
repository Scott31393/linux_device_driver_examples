CC=gcc
CFLAGS=-I.
OBJ = play.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

play: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
