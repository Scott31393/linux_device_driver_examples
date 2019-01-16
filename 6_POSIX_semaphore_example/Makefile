CC=gcc
CFLAGS=-I.
#DEPS = hellomake.h
OBJ = main.o
D_LIBS = -lpthread -D_REENTRANT -lrt

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(D_LIBS)