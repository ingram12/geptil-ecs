#include "ecs_tick.h"
#include "../systems/move.h"

void geptil_ecs_tick(Geptil_Context *ctx) {
    geptil_system_move(ctx);
}