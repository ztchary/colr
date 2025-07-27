CC=cc
CFLAGS=-Wall -Werror

colr: colr.c
	$(CC) $(CFLAGS) -o colr colr.c
