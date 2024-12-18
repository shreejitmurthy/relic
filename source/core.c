#include "core.h"

#include <stdlib.h>

#include <log/log.h>
#include <glad/glad.h>

app_t app_init(app_desc_t desc) {
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        // log_error("Initialise Error: %s", SDL_GetError());
        exit(1);
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
#if __APPLE__
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
#endif

    app_t app;
    app.w = desc.w;
    app.h = desc.h;
    app.window = SDL_CreateWindow(desc.title, desc.w, desc.h, SDL_WINDOW_OPENGL);
    app.ctx = SDL_GL_CreateContext(app.window);

    if (gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress) == 0) {
        // log_error("Failed to initialise GLAD");
        exit(1);
    }

    SDL_GL_SetSwapInterval(1);

    app.open = true;

    return app;
}

void app_poll_event(app_t* app) {
    while (SDL_PollEvent(&app->e)) {
        switch (app->e.type) {
            case SDL_EVENT_QUIT:
                app->open = false;
                break;

            // case SDL_EVENT_KEY_DOWN:
            //     if (app->e.key.key == SDLK_ESCAPE) {
            //         app->open = false;
            //         break;
            //     }

            default:
                break;
        }
    }
}

void app_destroy(app_t app) {
    SDL_DestroyWindow(app.window);
    SDL_GL_DestroyContext(app.ctx);
    SDL_Quit();
}