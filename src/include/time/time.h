#pragma once

#include "../core_types.h"

typedef struct {
    /* ===== Real Time ===== */
    f64 real_now;        // current wall-clock time
    f64 real_dt;         // real delta (clamped)
    f64 real_dt_raw;     // raw delta (no clamping)

    /* ===== Simulation Time ===== */
    f64 sim_time;        // simulation time (ticks * tick_dt)
    u64 sim_tick;        // current tick number
    f64 tick_dt;         // fixed delta per tick

    /* ===== Accumulator ===== */
    f64 accumulator;    // accumulates real_dt for sim ticks

    /* ===== State ===== */
    u64 frame_index;     // render frames
    bool paused;

    /* ===== Internal ===== */
    f64 _last_real_time;
} Geptil_Time;

// Initialize the time state
void geptil_time_init(Geptil_Time *t, f64 tick_dt);

// Updates `t` using GLFW's high-resolution timer.
void geptil_time_update(Geptil_Time *t);
