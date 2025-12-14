// AUTO-GENERATED FILE BY gen_components.py

#include "components.gen.h"

void geptil_components_storage_init(Geptil_Arena *arena, Geptil_Archetype *arch, Geptil_ComponentMask component_mask, u32 capacity)
{
    arch->positions = (component_mask.mask[0] & (1ULL << (COMP_POSITION % 64))) ? (Geptil_Position *)geptil_arena_alloc(arena, sizeof(Geptil_Position) * capacity) : NULL;
    arch->rotations = (component_mask.mask[0] & (1ULL << (COMP_ROTATION % 64))) ? (Geptil_Rotation *)geptil_arena_alloc(arena, sizeof(Geptil_Rotation) * capacity) : NULL;
    arch->examples = (component_mask.mask[0] & (1ULL << (COMP_EXAMPLE % 64))) ? (Geptil_Example *)geptil_arena_alloc(arena, sizeof(Geptil_Example) * capacity) : NULL;
}

void geptil_archetype_grow_capacity(Geptil_Arena *arena, Geptil_Archetype *arch)
{
    arch->entities = (u32 *)geptil_arena_realloc(
        arena,
        arch->entities,        sizeof(u32) * arch->entity_capacity,
        sizeof(u32) * arch->entity_capacity * 2
    );

    // Reallocate component arrays
    if (arch->positions) {
        arch->positions = (Geptil_Position *)geptil_arena_realloc(
            arena,
            arch->positions,
            sizeof(Geptil_Position) * arch->entity_capacity,
            sizeof(Geptil_Position) * arch->entity_capacity * 2
        );
    }
    if (arch->rotations) {
        arch->rotations = (Geptil_Rotation *)geptil_arena_realloc(
            arena,
            arch->rotations,
            sizeof(Geptil_Rotation) * arch->entity_capacity,
            sizeof(Geptil_Rotation) * arch->entity_capacity * 2
        );
    }
    if (arch->examples) {
        arch->examples = (Geptil_Example *)geptil_arena_realloc(
            arena,
            arch->examples,
            sizeof(Geptil_Example) * arch->entity_capacity,
            sizeof(Geptil_Example) * arch->entity_capacity * 2
        );
    }
    arch->entity_capacity *= 2;
}

