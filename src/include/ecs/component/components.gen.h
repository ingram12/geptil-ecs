// AUTO-GENERATED FILE BY gen_components.py
#pragma once

#include <stdint.h>
#include "../../memory/arena.h"
#include "../../core_types.h"

#define COMPONENT_COUNT 3
#define COMPONENT_MASK_COUNT 1

typedef struct Geptil_ComponentMask {
    uint64_t mask[COMPONENT_MASK_COUNT];
} Geptil_ComponentMask;

typedef enum {
    COMP_POSITION = 0,
    COMP_ROTATION = 1,
    COMP_EXAMPLE = 2,
} ComponentIndex;

typedef struct Geptil_Position {
    f64 x;
    f64 y;
    f64 z;
} Geptil_Position;

typedef struct Geptil_Rotation {
    f32 w;
    f32 x;
    f32 y;
    f32 z;
} Geptil_Rotation;

typedef struct Geptil_Example {
    f64 value;
} Geptil_Example;

typedef struct Geptil_Archetype {
    uint32_t entity_count;
    uint32_t entity_capacity;

    uint32_t *entities;
    Geptil_Position *positions;
    Geptil_Rotation *rotations;
    Geptil_Example *examples;
} Geptil_Archetype;

void geptil_components_storage_init(Geptil_Arena *arena, Geptil_Archetype *arch, Geptil_ComponentMask component_mask, u32 capacity);
void geptil_archetype_grow_capacity(Geptil_Arena *arena, Geptil_Archetype *arch);
