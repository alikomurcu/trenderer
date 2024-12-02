#pragma once
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <glm.hpp>
#include <iostream>
#include <vector>
#include "Shader.h"
#include "Texture.h"

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoord;
    glm::vec3 tangent;
    glm::vec3 bitangent;
};

class Mesh
{
public:
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    ~Mesh();
    void draw(Shader &shader);
    bool operator==(const Mesh& other) const;
private:
    unsigned int VAO, VBO, EBO;
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    void setupMesh();
};