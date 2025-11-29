#include "include/context.h"
#include "include/project.h"
#include <stdalign.h>
#include <stdio.h>
#include <stdlib.h>
#include "include/ecs/component/component_init.h"
#include "include/ecs/archetype/arhetype_init.h"

int main(int argc, char **argv) {
    printf("%s %s\n", PROJECT_NAME, PROJECT_VERSION);

    Context *ctx = create_context(64);

    component_init(ctx->ecs, "Position", sizeof(float) * 3, alignof(float));
    component_init(ctx->ecs, "Rotation", sizeof(float) * 4, alignof(float));

    Archetype *arch = archetype_init(ctx, 0b11);
  
    return EXIT_SUCCESS;
}
