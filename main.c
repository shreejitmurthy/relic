#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL3/SDL.h>
#include <glad/glad.h>

#include "core.h"
#include "graphics.h"

int main() {
    app_t app = app_init((app_desc_t){
        .title = "Window",
        .w = 800,
        .h = 600
    });

    gfx_init(app.w, app.h);
    gfx_push_blend_state((blend_state_t){
        .enabled = true,
        .src_alpha = GL_ONE_MINUS_SRC_ALPHA
    });

    while (app.open) {
        app_poll_event(&app);

        // draw
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.2f, 0.3f, 0.3f, 1.f);

        SDL_GL_SwapWindow(app.window);
    }
    // cleanup
    app_destroy(app);

}