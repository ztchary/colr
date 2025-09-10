#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHUNK 64000

void help() {
	fprintf(stderr, "Usage: colr [ -<color> <pattern> ... ]\n\
  -r       red\n\
  -g       green\n\
  -y       yellow\n\
  -b       blue\n\
  -m       magenta\n\
  -c       cyan\n\
  -e[4m    arbitrary ansi escape\n\
  -xABC012 rgb hex color \n");
	fflush(stderr);
}

void error(const char *msg) {
	fprintf(stderr, "\e[31m[ERR]\e[0m %s\n", msg);
	help();
	exit(1);
}

char *ext_arg(char ***argv) {
	char *ret = **argv;
	*argv = &(*argv)[1];
	return ret;
}

struct cmpstr {
	char *str;
	int len;
	char *esc;
};

char *argtoesc(char *arg) {
	switch (*arg) {
		case 'r': return strdup("\e[91m");
		case 'g': return strdup("\e[92m");
		case 'y': return strdup("\e[93m");
		case 'b': return strdup("\e[94m");
		case 'm': return strdup("\e[95m");
		case 'c': return strdup("\e[96m");
		case 'e': {
			char *o = malloc(256);
			sprintf(o, "\e%s", arg + 1);
			return o;
		}
		case 'x': {
			long int hex = strtol(arg + 1, NULL, 16);
			char *o = malloc(32);
			sprintf(o, "\e[38;2;%ld;%ld;%ldm", (hex >> 16) & 0xff, (hex >> 8) & 0xff, (hex >> 0) & 0xff);
			return o;
		}
		default: return NULL;
	}
}

int main(int argc, char **argv) {
	char *buf = malloc(CHUNK);
	char *in = buf;
	(void)ext_arg(&argv);
	char *arg;

	int num_cmpstr = argc / 2;

	struct cmpstr *cmpstrs = malloc(num_cmpstr * sizeof(struct cmpstr));
	int cmpstri = 0;

	while ((arg = ext_arg(&argv)) != NULL) {
		char *str = ext_arg(&argv);
		if (str == NULL) error ("wrong number of arguments");
		if (*arg != '-') error(arg);
		if (*arg == 'h') help();
		char *esc = argtoesc(arg + 1);
		if (esc == NULL) error("invalid argument");
		struct cmpstr s = {
			.str = str,
			.len = strlen(str),
			.esc = esc,
		};
		cmpstrs[cmpstri++] = s;
	}

	while (fgets(in, CHUNK, stdin) != 0) {
		for (int off = 0; in[off]; off++) {
			for (int stri = 0; stri < cmpstri; stri++) {
				if (strncmp(&in[off], cmpstrs[stri].str, cmpstrs[stri].len) == 0) {
					fwrite(in, 1, off, stdout);
					printf("%s%s\e[0m", cmpstrs[stri].esc, cmpstrs[stri].str);
					in += off + cmpstrs[stri].len;
					off = -1;
					break;
				}
			}
		}
		printf("%s", in);
		in = buf;
	}
	for (int i = 0; i < num_cmpstr; i++) {
		free(cmpstrs[i].esc);
	}
}

