#include "include/context.h"
#include "include/project.h"
#include <stdalign.h>
#include <stdio.h>
#include <stdlib.h>
#include "include/ecs/archetype/archetype_init.h"
#include "include/ecs/component/components.gen.h"
#include "include/ecs/entity/entity_init.h"

int main(int argc, char **argv) {
    printf("%s %s\n", PROJECT_NAME, PROJECT_VERSION);

    Context ctx = {0};
    init_context(&ctx);

    const ComponentIndex components[] = {COMP_POSITION, COMP_EXAMPLE};
    uint32_t archetype_id = archetype_init(&ctx, components, sizeof(components) / sizeof(components[0]));

    const ComponentIndex components2[] = {COMP_POSITION, COMP_ROTATION, COMP_EXAMPLE};
    uint32_t archetype_id2 = archetype_init(&ctx, components2, sizeof(components2) / sizeof(components2[0]));

    uint32_t entity_id = entity_init(&ctx, archetype_id2, 0);

    Entity *entity = &ctx.ecs.entities[entity_id];

    return EXIT_SUCCESS;
}
