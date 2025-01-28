CC := gcc
CFLAGS := -ansi -Wall -Wextra

all: unityhash

unityhash: hash.c
	$(CC) $(CFLAGS) -I. $? -o $@ $(LDFLAGS)

clean:
	rm -f unityhash unityhash.exe *.o

.PHONY: clean
