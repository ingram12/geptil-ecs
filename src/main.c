#include "include/context.h"
#include "include/project.h"
#include <stdalign.h>
#include <stdio.h>
#include <stdlib.h>
#include "include/ecs/archetype/arhetype_init.h"
#include "include/ecs/component/components.gen.h"

int main(int argc, char **argv) {
    printf("%s %s\n", PROJECT_NAME, PROJECT_VERSION);

    Context ctx = {0};
    init_context(&ctx, 64);

    Archetype *arch = archetype_init(&ctx, COMP_POSITION | COMP_ROTATION);
    archetype_init(&ctx, COMP_POSITION);
    archetype_init(&ctx, COMP_ROTATION);
    archetype_init(&ctx, COMP_ROTATION);

    return EXIT_SUCCESS;
}
