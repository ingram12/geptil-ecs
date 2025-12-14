// AUTO-GENERATED FILE BY gen_components.py

#include "components.gen.h"

void components_storage_init(Arena *arena, Archetype *arch, ComponentMask component_mask, u32 capacity)
{
    arch->positions = (component_mask.mask[0] & (1ULL << COMP_POSITION)) ? (Position *)arena_alloc(arena, sizeof(Position) * capacity) : NULL;
    arch->rotations = (component_mask.mask[0] & (1ULL << COMP_ROTATION)) ? (Rotation *)arena_alloc(arena, sizeof(Rotation) * capacity) : NULL;
    arch->examples = (component_mask.mask[0] & (1ULL << COMP_EXAMPLE)) ? (Example *)arena_alloc(arena, sizeof(Example) * capacity) : NULL;
}

void archetype_grow_capacity(Arena *arena, Archetype *arch)
{
    arch->entities = (u32 *)arena_realloc(
        arena,
        arch->entities,
        sizeof(u32) * arch->entity_capacity,
        sizeof(u32) * arch->entity_capacity * 2
    );

    if (arch->positions) {
        arch->positions = (Position *)arena_realloc(
            arena,
            arch->positions,
            sizeof(Position) * arch->entity_capacity,
            sizeof(Position) * arch->entity_capacity * 2
        );
    }
    if (arch->rotations) {
        arch->rotations = (Rotation *)arena_realloc(
            arena,
            arch->rotations,
            sizeof(Rotation) * arch->entity_capacity,
            sizeof(Rotation) * arch->entity_capacity * 2
        );
    }
    if (arch->examples) {
        arch->examples = (Example *)arena_realloc(
            arena,
            arch->examples,
            sizeof(Example) * arch->entity_capacity,
            sizeof(Example) * arch->entity_capacity * 2
        );
    }

    arch->entity_capacity *= 2;
}
