// AUTO-GENERATED FILE BY gen_components.py
#pragma once

#include "../../core_types.h"
#include "../../memory/arena.h"

#define COMPONENT_COUNT 3
#define COMPONENT_MASK_COUNT 1

typedef struct {
    u64 mask[COMPONENT_MASK_COUNT];
} ComponentMask;

typedef enum {
    COMP_POSITION = 0,
    COMP_ROTATION = 1,
    COMP_EXAMPLE = 2,
} ComponentIndex;

typedef struct Position {
    f64 x;
    f64 y;
    f64 z;
} Position;

typedef struct Rotation {
    f32 w;
    f32 x;
    f32 y;
    f32 z;
} Rotation;

typedef struct Example {
    u32 value;
} Example;

typedef struct Archetype {
    u32 entity_count;
    u32 entity_capacity;

    u32 *entities;
    Position *positions;
    Rotation *rotations;
    Example *examples;
} Archetype;

void components_storage_init(Arena *arena, Archetype *arch, ComponentMask component_mask, u32 capacity);
void archetype_grow_capacity(Arena *arena, Archetype *arch);
