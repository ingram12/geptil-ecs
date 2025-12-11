#pragma once

#include "../../context.h"
#include "../ecs.h"

EntityId entity_init(Context *ctx, uint32_t archetype_id, uint32_t flags);
