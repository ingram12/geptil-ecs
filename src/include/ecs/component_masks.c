#include "ecs.h"
#include <string.h>

ComponentMask build_component_masks(const uint32_t *components, size_t count)
{
    ComponentMask out_mask = {0};

    for (size_t i = 0; i < count; ++i) {
        uint32_t comp = components[i];
        uint32_t idx = comp / 64;
        uint32_t bit = comp % 64;

        if (idx < COMPONENT_MASK_COUNT) {
            out_mask.mask[idx] |= (1ULL << bit);
        }
    }

    return out_mask;
}
