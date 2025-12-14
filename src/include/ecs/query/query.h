#pragma once

#include "../ecs.h"

u32 geptil_init_query(Geptil_Arena *arena, Geptil_Ecs *ecs, const Geptil_ComponentMask component_mask);

// Rematch all queries to archetypes, useful after archetypes have changed
void geptil_rematch_all_queries(Geptil_Arena *arena, Geptil_Ecs *ecs);
