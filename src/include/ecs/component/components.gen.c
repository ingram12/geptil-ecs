// AUTO-GENERATED FILE BY gen_components.py

#include "components.gen.h"

void components_storage_init(Arena *arena, ComponentStorage *storage, uint32_t mask, uint32_t capacity)
{
    storage->positions = (mask & COMP_POSITION) ? (Position *)arena_alloc(arena, sizeof(Position) * capacity) : NULL;
    storage->rotations = (mask & COMP_ROTATION) ? (Rotation *)arena_alloc(arena, sizeof(Rotation) * capacity) : NULL;
}
