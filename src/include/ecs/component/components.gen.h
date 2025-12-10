// AUTO-GENERATED FILE BY gen_components.py
#pragma once

#include <stdint.h>
#include "../../memory/arena.h"

#define COMPONENT_COUNT 3
#define COMPONENT_MASK_COUNT 1

typedef enum {
    COMP_POSITION = 0,
    COMP_ROTATION = 1,
    COMP_EXAMPLE = 2,
} ComponentMask;

typedef struct Position {
    double x;
    double y;
    double z;
} Position;

typedef struct Rotation {
    float w;
    float x;
    float y;
    float z;
} Rotation;

typedef struct Example {
    int value;
} Example;

typedef struct Archetype {
    uint32_t entity_count;
    uint32_t entity_capacity;

    uint32_t *entities;
    Position *positions;
    Rotation *rotations;
    Example *examples;
} Archetype;

void components_storage_init(Arena *arena, Archetype *arch, uint64_t masks[COMPONENT_MASK_COUNT], uint32_t capacity);
