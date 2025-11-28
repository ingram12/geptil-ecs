#include <stdio.h>
#include <stdlib.h>
#include "include/project.h"
#include "include/context.h"

int main(int argc, char **argv) {
	printf("%s %s\n", PROJECT_NAME, PROJECT_VERSION);
	if (argc > 1) {
		printf("Args:");
		for (int i = 1; i < argc; ++i) printf(" %s", argv[i]);
		printf("\n");
	}

    Context* ctx = create_context(64);

	return EXIT_SUCCESS;
}
