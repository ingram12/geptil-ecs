// AUTO-GENERATED FILE BY gen_components.py
#pragma once

#include <stdint.h>
#include "../../memory/arena.h"

#define COMPONENT_COUNT 2

typedef enum {
    COMP_POSITION = 1u << 0,
    COMP_ROTATION = 1u << 1,
} ComponentMask;

typedef struct Position {
    float x;
    float y;
    float z;
} Position;

typedef struct Rotation {
    float w;
    float x;
    float y;
    float z;
} Rotation;

typedef struct {
    Position *positions;
    Rotation *rotations;
} ComponentStorage;

void components_storage_init(Arena *arena, ComponentStorage *storage, uint32_t mask, uint32_t capacity);
