//
// Created by Shreejit Murthy on ?/??/????.
//

#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

class Math {
public:
    // Using GLM's vec2 and vec3 types
    using Vec2 = glm::vec2;
    using Vec3 = glm::vec3;

    // Convert 3D vertex to 2D screen space
    static Vec2 ConvertToScreenSpace(const Vec3& vertex, int screenWidth, int screenHeight) {
        // Projection and normalization are simplified using GLM operations
        Vec2 screenSpaceVertex = Vec2((vertex.x + 1.0f) * 0.5f * screenWidth,
                                      (1.0f - vertex.y) * 0.5f * screenHeight);
        return screenSpaceVertex;
    }

    static Vec3 ConvertTo3DSpace(const Vec2& screenVertex, float z, int screenWidth, int screenHeight) {
        // Reversing screen space normalization
        Vec3 normalizedVertex = Vec3((2.0f * screenVertex.x / screenWidth) - 1.0f,
                                     1.0f - (2.0f * screenVertex.y / screenHeight),
                                     z);
        return normalizedVertex;
    }

    static std::vector<Vec2> ConvertVerticesToScreenSpace(const std::vector<Vec3>& vertices, int screenWidth, int screenHeight) {
        std::vector<Vec2> screenSpaceVertices;
        screenSpaceVertices.reserve(vertices.size());

        for (const auto& vertex : vertices) {
            screenSpaceVertices.push_back(ConvertToScreenSpace(vertex, screenWidth, screenHeight));
        }

        return screenSpaceVertices;
    }

    static std::vector<Vec3> ConvertScreenSpaceToVertices(const std::vector<Vec2>& screenSpaceVertices, float z, int screenWidth, int screenHeight) {
        std::vector<Vec3> vertices;
        vertices.reserve(screenSpaceVertices.size());

        for (const auto& screenVertex : screenSpaceVertices) {
            vertices.push_back(ConvertTo3DSpace(screenVertex, z, screenWidth, screenHeight));
        }

        return vertices;
    }
};
