#include "../ecs.h"

ComponentMask geptil_build_component_mask(const ComponentIndex *components, const size_t count)
{
    ComponentMask out_mask = {0};

    for (size_t i = 0; i < count; ++i) {
        u32 comp = components[i];
        u32 idx = comp / 64;
        u32 bit = comp % 64;

        if (idx < COMPONENT_MASK_COUNT) {
            out_mask.mask[idx] |= (1ULL << bit);
        }
    }

    return out_mask;
}
