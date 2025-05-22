#include "fps.h"
#include "main.h"
#include <SDL2/SDL_timer.h>

uint8_t fps_new(struct Fps **fps)
{
    *fps = calloc(1, sizeof(struct Fps));

    if (*fps == NULL) {
        fprintf(stderr, "Error initializing FPS\n");
        return 1;
    }

    struct Fps *f = *fps;

    f->target_frame_rate = TARGET_FPS;
    f->max_delay = 50;
    f->last_time = SDL_GetTicks64();
    f->carry_delay = 0;
    f->fps_last_time = f->last_time;
    f->fps_counter = 0;
    f->fps_display = 0;

    return 0;
}

void fps_free(struct Fps **fps)
{
    free(*fps);
    *fps = NULL;
}

void fps_update(struct Fps *fps)
{
    uint64_t time_to_wait = (1000 / TARGET_FPS) - (SDL_GetTicks64() - fps->last_time);

    if (time_to_wait > 0 && time_to_wait <= (1000 / TARGET_FPS))
        SDL_Delay(time_to_wait);

    fps->last_time = SDL_GetTicks64();
}
