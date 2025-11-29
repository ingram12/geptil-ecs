#include "component_init.h"
#include "../../logger/logger.h"

ComponentType *component_init(Ecs *ecs, const char *name, size_t size, size_t alignment) {
    if (ecs->component_type_count >= ecs->max_components_count) {
        LOG_FATAL("Exceeded maximum number of component types");
    }

    ComponentType *ct = &ecs->component_types[ecs->component_type_count];
    ct->name = name;
    ct->size = size;
    ct->alignment = alignment;
    ct->id = ecs->component_type_count;
    ecs->component_type_count++;

    return ct;
}
