#ifndef _FPS_H
#define _FPS_H

#include "main.h"

struct Fps {
    uint64_t last_time;
    uint64_t target_frame_rate;
    uint64_t carry_delay;
    uint64_t max_delay;
    uint32_t fps_last_time;
    uint32_t fps_counter;
    uint8_t  fps_display;
};

uint8_t fps_new(struct Fps **fps);
void fps_free(struct Fps **fps);
void fps_display_toggle(struct Fps *fps);
void fps_update(struct Fps *fps);

#endif // !_FPS_H
