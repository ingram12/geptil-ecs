#include "include/context.h"
#include "include/project.h"
#include <stdalign.h>
#include <stdio.h>
#include <stdlib.h>
#include "include/ecs/archetype/archetype_init.h"
#include "include/ecs/component/components.gen.h"
#include "include/ecs/entity/entity_init.h"
#include "include/ecs/query/query.h"

int main(int argc, char **argv) {
    printf("%s %s\n", PROJECT_NAME, PROJECT_VERSION);

    Context ctx = {0};
    init_context(&ctx);

    const ComponentIndex components[] = {COMP_POSITION, COMP_EXAMPLE};
    archetype_init(&ctx, components, sizeof(components) / sizeof(components[0]));

    const ComponentIndex comp1[] = {COMP_POSITION, COMP_ROTATION, COMP_EXAMPLE};
    uint32_t archetype_id = archetype_init(&ctx, comp1, sizeof(comp1) / sizeof(comp1[0]));

    EntityId entity_id = entity_init(&ctx, archetype_id, 0);

    Entity *entity = get_entity_by_id(&ctx, entity_id);

    Position *pos = &ctx.ecs.archetypes[entity->archetype_index].positions[entity->archetype_entity_index];

    pos->x = 1.0;
    pos->y = 2.0;
    pos->z = 3.0;

    Archetype *arch = get_archetype_by_id(&ctx, entity->archetype_index);

    return EXIT_SUCCESS;
}
