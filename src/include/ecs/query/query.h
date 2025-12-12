#pragma once

#include "../ecs.h"
#include "../../context.h"

Entity* get_entity_by_id(const Context *ctx, const EntityId entity_id);
Archetype* get_archetype_by_id(const Context *ctx, const uint32_t archetype_id);
Archetype* get_archetype_by_component_mask(const Context *ctx, const ComponentMask component_mask);
