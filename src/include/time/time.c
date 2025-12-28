#include "time.h"
#include <GLFW/glfw3.h>

static const f64 MAX_REAL_DT = 0.25;

void geptil_time_init(Geptil_Time *t, f64 tick_dt)
{
    f64 now = glfwGetTime();

    *t = (Geptil_Time){
        .real_now        = now,
        .real_dt         = 0.0,
        .real_dt_raw     = 0.0,
        .sim_time        = 0.0,
        .sim_tick        = 0,
        .tick_dt         = tick_dt,
        .accumulator     = 0.0,
        .frame_index     = 0,
        .paused          = false,
        ._last_real_time = now
    };
}

void geptil_time_update(Geptil_Time *t)
{
    f64 now = glfwGetTime();

    f64 raw_dt = now - t->_last_real_time;
    t->real_dt_raw = raw_dt;

    if (raw_dt < 0.0)
        raw_dt = 0.0;

    if (raw_dt > MAX_REAL_DT)
        raw_dt = MAX_REAL_DT;

    t->real_dt = raw_dt;
    t->real_now = now;
    t->_last_real_time = now;

    if (!t->paused)
        t->accumulator += raw_dt;

    t->frame_index++;
}
