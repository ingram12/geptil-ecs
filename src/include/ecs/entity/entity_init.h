#pragma once

#include "../../context.h"
#include "../ecs.h"

EntityId entity_init(Context *ctx, u32 archetype_id, u32 flags);
