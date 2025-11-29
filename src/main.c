#include "include/context.h"
#include "include/project.h"
#include <stdalign.h>
#include <stdio.h>
#include <stdlib.h>
#include "include/ecs/archetype/arhetype_init.h"
#include "include/ecs/component/component.h"

int main(int argc, char **argv) {
    printf("%s %s\n", PROJECT_NAME, PROJECT_VERSION);

    Context *ctx = create_context(64);

    Archetype *arch = archetype_init(ctx, COMP_POSITION | COMP_ROTATION);
    Archetype *arch1 = archetype_init(ctx, COMP_POSITION);
    Archetype *arch2 = archetype_init(ctx, COMP_ROTATION);
    Archetype *arch3 = archetype_init(ctx, COMP_ROTATION);

    return EXIT_SUCCESS;
}
