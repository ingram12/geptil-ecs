#include "include/context.h"
#include "include/project.h"
#include "include/ecs/archetype/archetype_init.h"
#include "include/ecs/component/components.gen.h"
#include "include/ecs/entity/entity_init.h"
#include "include/ecs/query/query.h"
#include "include/logger/logger.h"
#include "systems/move.h"
#include "include/vulkan/vulkan_draw.h"
#include <stdlib.h>

int main(int argc, char **argv) {
    LOG_INFO("Starting %s version %s", PROJECT_NAME, PROJECT_VERSION);

    Geptil_Context ctx = {0};
    geptil_init_context(&ctx);

    const ComponentIndex components[] = {COMP_POSITION, COMP_EXAMPLE};
    Geptil_ComponentMask component_mask = geptil_build_component_mask(components, sizeof(components) / sizeof(components[0]));
    u32 archetype_id1 = geptil_archetype_init(&ctx, component_mask);

    const ComponentIndex comp1[] = {COMP_POSITION, COMP_ROTATION, COMP_EXAMPLE};
    Geptil_ComponentMask component_mask1 = geptil_build_component_mask(comp1, sizeof(comp1) / sizeof(comp1[0]));
    u32 archetype_id = geptil_archetype_init(&ctx, component_mask1);


    Geptil_EntityId entity_id = geptil_entity_init(&ctx, archetype_id, 0);
    geptil_entity_init(&ctx, archetype_id1, 0);
    geptil_entity_init(&ctx, archetype_id1, 0);

    Geptil_Entity *entity = geptil_get_entity_by_id(&ctx.ecs, entity_id);

    Geptil_Position *pos = &ctx.ecs.archetypes[entity->archetype_index].positions[entity->archetype_entity_index];

    Geptil_Archetype *arch = geptil_get_archetype_by_id(&ctx.ecs, entity->archetype_index);

    const ComponentIndex comp2[] = {COMP_POSITION};
    Geptil_ComponentMask component_mask2 = geptil_build_component_mask(comp2, sizeof(comp2) / sizeof(comp2[0]));
    u32 query_id = geptil_init_query(&ctx.arena, &ctx.ecs, component_mask2);

    geptil_system_move(&ctx);

    Geptil_VulkanContext vk_ctx = ctx.vulkan;
    while (!glfwWindowShouldClose(vk_ctx.window)) {
        glfwPollEvents();
        draw_frame(&vk_ctx);
    }

    return EXIT_SUCCESS;
}
