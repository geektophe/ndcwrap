#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "cliw.h"

int main(int argc, char **argv) {
	int fd = open(FPATH, O_RDONLY);
	int retcode = 0;

	if (fd < 0) {
		perror("open");
		return 1;
	}

	struct stat st;
	fstat(fd, &st);
	int fsize = st.st_size;

	printf("file size: %d\n", fsize);

	char *content = malloc(fsize);

	if (content == NULL){
		perror("malloc");
		close(fd);
		return 2;
	}

	size_t rsize = read(fd, content, fsize);

	printf("read: %zu bytes\n", rsize);

	if (rsize != fsize) {
		printf("error: read content length deffers from file size");
		retcode = 3;
	} else {
		printf("content: \n%s", content);
	}

	free(content);
	close(fd);
	return retcode;
}
