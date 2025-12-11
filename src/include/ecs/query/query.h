#pragma once

#include "../ecs.h"
#include "../../context.h"

Entity* get_entity_by_id(const Context *ctx, const EntityId entity_id);
