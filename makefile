% : %.c
	$(CC) $(CFLAGS) -o $@ $<

all: $(basename $(wildcard *.c))

clean:
	rm -f *.o 
