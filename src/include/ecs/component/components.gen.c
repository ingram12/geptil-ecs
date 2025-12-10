// AUTO-GENERATED FILE BY gen_components.py

#include "components.gen.h"

void components_storage_init(Arena *arena, Archetype *arch, uint64_t masks[COMPONENT_MASK_COUNT], uint32_t capacity)
{
    arch->positions = (masks[0] & (1ULL << COMP_POSITION)) ? (Position *)arena_alloc(arena, sizeof(Position) * capacity) : NULL;
    arch->rotations = (masks[0] & (1ULL << COMP_ROTATION)) ? (Rotation *)arena_alloc(arena, sizeof(Rotation) * capacity) : NULL;
    arch->examples = (masks[0] & (1ULL << COMP_EXAMPLE)) ? (Example *)arena_alloc(arena, sizeof(Example) * capacity) : NULL;
}
