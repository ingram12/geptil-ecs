#include "include/context.h"
#include "include/project.h"
#include <stdalign.h>
#include <stdio.h>
#include <stdlib.h>
#include "include/ecs/archetype/arhetype_init.h"
#include "include/ecs/component/components.gen.h"
#include "include/ecs/entity/entity_init.h"

int main(int argc, char **argv) {
    printf("%s %s\n", PROJECT_NAME, PROJECT_VERSION);

    Context ctx = {0};
    init_context(&ctx);

    uint64_t component_masks[COMPONENT_MASK_COUNT] = {0};
    component_masks[0] |= (1ULL << COMP_POSITION);
    component_masks[0] |= (1ULL << COMP_ROTATION);
    component_masks[0] |= (1ULL << COMP_EXAMPLE);

    uint32_t archetype_id = archetype_init(&ctx, component_masks);
    uint32_t entity_id = entity_init(&ctx, archetype_id);

    return EXIT_SUCCESS;
}
