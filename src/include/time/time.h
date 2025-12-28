#pragma once

#include "../core_types.h"

typedef struct {
    /* ===== Real Time ===== */
    f64 real_now;        // текущее wall-clock время
    f64 real_dt;         // реальная дельта (clamped)
    f64 real_dt_raw;     // сырая дельта (без защиты)

    /* ===== Simulation Time ===== */
    f64 sim_time;        // симуляционное время (ticks * tick_dt)
    u64 sim_tick;        // номер текущего тика
    f64 tick_dt;         // фиксированная дельта одного тика

    /* ===== Accumulator ===== */
    f64 accumulator;    // накопитель real_dt для sim ticks

    /* ===== State ===== */
    u64 frame_index;     // рендер-фреймы
    bool paused;

    /* ===== Internal ===== */
    f64 _last_real_time;
} Geptil_Time;

// Initialize the time state
void geptil_time_init(Geptil_Time *t, f64 tick_dt);

// Updates `t` using GLFW's high-resolution timer.
void geptil_time_update(Geptil_Time *t);
