#pragma once

#include "../ecs.h"

u32 init_query(Arena *arena, Ecs *ecs, const ComponentMask component_mask);

// Rematch all queries to archetypes, useful after archetypes have changed
void rematch_all_queries(Arena *arena, Ecs *ecs);
