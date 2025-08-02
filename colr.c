#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHUNK 64000
#define MAX_ARGS 128

void error(const char *msg) {
	fprintf(stderr, "\x1b[31m[ERR]\x1b[0m %s\n", msg);
	exit(1);
}

char *ext_arg(char ***argv) {
	char *ret = **argv;
	*argv = &(*argv)[1];
	return ret;
}

struct cmpstr {
	char *str;
	size_t len;
	char eq;
};

// TODO: add more colors, 8 bit color maybe? also need a better method for this
char argtocol[256] = {
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  34, 36, 0,  0,  0,  32, 0,  0,  0,  0,  0,  35, 0,  0,
	0,  0,  31, 0,  0,  0,  0,  0,  0,  33, 0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
};

int main(int argc, char **argv) {
	char *in  = malloc(CHUNK);
	(void)ext_arg(&argv);
	char *arg;

	struct cmpstr *cmpstrs = malloc(MAX_ARGS * sizeof(struct cmpstr));
	size_t cmpstri = 0;

	while ((arg = ext_arg(&argv)) != NULL) {
		char *str = ext_arg(&argv);
		if (cmpstri > MAX_ARGS) error("too many arguments");
		if (str == NULL) error ("wrong number of arguments");
		if (strlen(arg) != 2 || *arg != '-') error("failed to parse arguments");
		size_t argcol = arg[1];
		if (argtocol[argcol] == 0) error("invalid argument");
		struct cmpstr s = {
			.str = str,
			.len = strlen(str),
			.eq = argtocol[argcol],
		};
		cmpstrs[cmpstri++] = s;
	}

	while (fgets(in, CHUNK, stdin) != 0) {
		for (size_t off = 0; in[off]; off++) {
			for (size_t stri = 0; stri < cmpstri; stri++) {
				if (strncmp(&in[off], cmpstrs[stri].str, cmpstrs[stri].len) == 0) {
					fwrite(in, 1, off, stdout);
					printf("\x1b[%dm%s\x1b[0m", cmpstrs[stri].eq, cmpstrs[stri].str);
					in += off + cmpstrs[stri].len;
					off = -1;
					break;
				}
			}
		}
		printf("%s", in);
	}
}
