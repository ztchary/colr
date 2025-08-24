CC=cc
CFLAGS=-Wall -Werror

colr: colr.c
	$(CC) $(CFLAGS) -o colr colr.c

install: colr
	install -m 755 colr /usr/bin

