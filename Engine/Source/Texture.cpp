//
// Created by Shreejit Murthy on 2/10/2024.
//

#include "Texture.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <iostream>

#include <glm/gtc/matrix_transform.hpp>

#include "System.hpp"

Texture::Texture(const std::string& path) {
    glGenTextures(1, &_ID);
    glBindTexture(GL_TEXTURE_2D, _ID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    std::string texturePath = System::findPathUpwards(path);

    unsigned char* data = stbi_load(texturePath.c_str(), &_width, &_height, &_nrChannels, 4);
    if (data) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
    } else {
        std::cerr << "Failed to load texture" << std::endl;
    }

    TextureQuad quad = {0, 0, static_cast<float>(_width), static_cast<float>(_height)};

    _applyQuad(quad);

    _genBuffers();
}

void Texture::_applyQuad(TextureQuad quad) {
    _quad = quad;
    float u0 = _quad.x / _width;
    float v0 = _quad.y / _height;
    float u1 = (_quad.x + _quad.w) / _width;
    float v1 = (_quad.y + _quad.h) / _height;

    float halfWidth  = _quad.w / 2.0f;
    float halfHeight = _quad.h / 2.0f;

    _vertices = {
            /*     positions         tx coords        colors     */
            halfWidth,  halfHeight,   u1, v1,    1.0f, 0.0f, 0.0f,  // top right
            halfWidth,  -halfHeight,  u1, v0,    0.0f, 1.0f, 0.0f,  // bottom right
            -halfWidth, -halfHeight,  u0, v0,    0.0f, 0.0f, 1.0f,  // bottom left
            -halfWidth, halfHeight,   u0, v1,    1.0f, 1.0f, 0.0f   // top left
    };
}

void Texture::_genBuffers() {
    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);
    glGenBuffers(1, &_EBO);

    glBindVertexArray(_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices), _vertices.data(), GL_STATIC_DRAW);

    std::array<unsigned int, 6> indices = {
            0, 1, 3,  // first triangle
            1, 2, 3   // second triangle
    };

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(4 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void Texture::_updateVBO() {
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(_vertices), _vertices.data());
}

bool is_zero_colour(glm::vec4 colour) {
    return !(colour.x || colour.y || colour.z || colour.w);
}

void Texture::draw(glm::vec2 position, Shader shader, TextureQuad quad, glm::vec2 scale, float rotation, glm::vec4 tint) {
    if (quad.w == 0.f) {
        quad = (TextureQuad){0, 0, static_cast<float>(_width), static_cast<float>(_height)};
    }
    _applyQuad(quad);
    _updateVBO();

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.f));
    glm::vec3 finalScale = glm::vec3(scale.x == 0 ? 1.f : scale.x, scale.y == 0 ? 1.0f : scale.y, 1.0f);
    model = glm::scale(model, finalScale);
    float rot = glm::radians(rotation);
    model = glm::rotate(model, rot, glm::vec3(0.f, 0.f, 1.f));

    // Colour tinting
    tint = is_zero_colour(tint)
                     ? glm::vec4(1.f, 1.f, 1.f, 1.f)
                     : glm::vec4(tint.r, tint.g, tint.b, tint.a);

    // not a fan of doing this, but it works
    shader.use();
    shader.set_mat4("model", model);
    shader.set_vec4("tint", tint);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _ID);
    glBindVertexArray(_VAO);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

int Texture::getWidth() {
    return _width;
}

int Texture::getHeight() {
    return _height;
}

Texture::~Texture() {
    glDeleteTextures(1, &_ID);
}
