#include "graphics.h"

#include <glad/glad.h>
#include <SDL3/SDL.h>

void gfx_init(uint16_t w, uint16_t h) {
    glViewport(0, 0, w, h);
}

void gfx_push_blend_state(blend_state_t blend_state) {
    blend_state.enabled ? glEnable(GL_BLEND) : glDisable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, blend_state.src_alpha);
    glBlendFunc(GL_DST_ALPHA, blend_state.dst_alpha);
    glBlendFunc(GL_SRC_COLOR, blend_state.src_color);
    glBlendFunc(GL_DST_COLOR, blend_state.dst_color);
}

