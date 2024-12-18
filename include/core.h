#pragma once

#include <SDL3/SDL.h>

typedef struct app_t {
    SDL_Window* window;
    SDL_GLContext ctx;
    uint16_t w, h;
    SDL_Event e;
    bool open;
} app_t;

typedef struct app_desc_t {
    const char* title;
    uint16_t w, h;
} app_desc_t;

app_t app_init(app_desc_t desc);
void app_poll_event(app_t* app);
void app_destroy(app_t app);
