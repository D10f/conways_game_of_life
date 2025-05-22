#ifndef _MAIN_H
#define _MAIN_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <time.h>

#define SDL_INIT_FLAGS          (SDL_INIT_VIDEO | SDL_INIT_AUDIO)
#define SDL_WINDOW_FLAGS        SDL_WINDOW_BORDERLESS
#define SDL_RENDERER_FLAGS      SDL_RENDERER_ACCELERATED

#define IMG_FLAGS               (IMG_INIT_PNG | IMG_INIT_JPG)

#define WINDOW_TITLE            "Conway's Game of Life"
#define WINDOW_WIDTH            1280
#define WINDOW_HEIGHT           720

#define CELL_SIZE               10
#define CELL_COLOR              155, 155, 155, 255

#define RENDERER_COLOR          0, 0, 0, 255

#define WRAP_AROUND             1

#endif // !_MAIN_H
