#include "include/context.h"
#include "include/project.h"
#include <stdalign.h>
#include <stdio.h>
#include <stdlib.h>
#include "include/ecs/archetype/archetype_init.h"
#include "include/ecs/component/components.gen.h"
#include "include/ecs/entity/entity_init.h"
#include "include/ecs/query/query.h"

#include "systems/move.h"

int main(int argc, char **argv) {
    printf("%s %s\n", PROJECT_NAME, PROJECT_VERSION);

    Context ctx = {0};
    init_context(&ctx);

    const ComponentIndex components[] = {COMP_POSITION, COMP_EXAMPLE};
    ComponentMask component_mask = build_component_mask(components, sizeof(components) / sizeof(components[0]));
    u32 archetype_id1 = archetype_init(&ctx, component_mask);

    const ComponentIndex comp1[] = {COMP_POSITION, COMP_ROTATION, COMP_EXAMPLE};
    ComponentMask component_mask1 = build_component_mask(comp1, sizeof(comp1) / sizeof(comp1[0]));
    u32 archetype_id = archetype_init(&ctx, component_mask1);


    EntityId entity_id = entity_init(&ctx, archetype_id, 0);
    entity_init(&ctx, archetype_id1, 0);
    entity_init(&ctx, archetype_id1, 0);

    Entity *entity = get_entity_by_id(&ctx.ecs, entity_id);

    Position *pos = &ctx.ecs.archetypes[entity->archetype_index].positions[entity->archetype_entity_index];

    Archetype *arch = get_archetype_by_id(&ctx.ecs, entity->archetype_index);

    const ComponentIndex comp2[] = {COMP_POSITION};
    ComponentMask component_mask2 = build_component_mask(comp2, sizeof(comp2) / sizeof(comp2[0]));
    u32 query_id = init_query(&ctx.arena, &ctx.ecs, component_mask2);

    system_move(&ctx);

    return EXIT_SUCCESS;
}
