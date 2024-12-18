#pragma once
#include <stdlib.h>
#include <cglm/cglm.h>
#include <stdbool.h>

#define WRAP_REPEAT   (uint32_t)GL_REPEAT
#define WRAP_MREPEAT  (uint32_t)GL_MIRRORED_REPEAT
#define WRAP_EEDGE    (uint32_t)GL_CLAMP_TO_EDGE
#define WRAP_BCLAMP   (uint32_t)GL_CLAMP_TO_BORDER

#define FILTER_NEAR    (uint32_t)GL_NEAREST
#define FILTER_LINEAR  (uint32_t)GL_LINEAR
#define FILTER_NMN     (uint32_t)GL_NEAREST_MIPMAP_NEAREST
#define FILTER_NML     (uint32_t)GL_NEAREST_MIPMAP_LINEAR
#define FILTER_LML     (uint32_t)GL_LINEAR_MIPMAP_LINEAR
#define FILTER_LMN     (uint32_t)GL_LINEAR_MIPMAP_NEAREST

typedef struct blend_state_t {
    bool enabled;
    uint32_t src_alpha;
    uint32_t dst_alpha;
    uint32_t src_color;
    uint32_t dst_color;
} blend_state_t;

void gfx_init(uint16_t w, uint16_t h);
void gfx_push_blend_state(blend_state_t blend_state);

typedef struct texture_t {
    uint32_t id;
    uint32_t vao, vbo, ebo;
    int width, height, channels;
    vec4 quad;
    float vertices[32];
    uint32_t indices[6];
    mat4 model;
    vec4 tint;
} texture_t;

typedef struct tex_params_t {
    uint32_t min_filter;
    uint32_t mag_filter;
    uint32_t wrap_s;
    uint32_t wrap_t;
} tex_params_t;

typedef struct texture_desc_t {
    const char* path;
    tex_params_t params;
} texture_desc_t;

// TODO
texture_t texture_init();
