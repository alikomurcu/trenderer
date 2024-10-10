#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
{
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;
    setupMesh();
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

bool Mesh::operator==(const Mesh& other) const
{
    for (int i = 0; i < vertices.size(); i++)
	{
        float epsilon = 0.0001f;
        float distance = glm::distance(vertices[i].position, other.vertices[i].position);
        std::cout << distance << std::endl;
		if (distance > epsilon) // means not equal
			return false;
		if (vertices[i].normal != other.vertices[i].normal)
			return false;
		if (vertices[i].texCoord != other.vertices[i].texCoord)
			return false;
	}
	for (int i = 0; i < indices.size(); i++)
	{
		if (indices[i] != other.indices[i])
			return false;
	}
	return true;
}

void Mesh::setupMesh()
{
    // Generate VAO, VBO, EBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // Bind VAO
    glBindVertexArray(VAO);
    // Bind and set VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
    // Bind and set EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
    // Set the vertex attribute pointers
    // Vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // Vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    // Vertex texture coordinates
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
    // Unbind VAO
    glBindVertexArray(0);
}

void Mesh::draw(Shader &shader)
{
    // Bind appropriate textures
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    unsigned int heightNr = 1;
    shader.use();
    for (unsigned int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i); // Active proper texture unit before binding
        std::string number;
        std::string name = textures[i].type;
        if (name == "diffuse_map")
            number = std::to_string(diffuseNr++);
        else if (name == "specular_map")
            number = std::to_string(specularNr++);
        else if (name == "normal_map")
            number = std::to_string(normalNr++);
        else if (name == "height_map")
            number = std::to_string(heightNr++);
        // Set the sampler to correct texture unit
        shader.setInt(("material." + name + number).c_str(), i);
        // Bind the texture
        // glBindTexture(GL_TEXTURE_2D, textures[i].ID);
        textures[i].bind(); //GL_TEXTURE_2D
    }
    // Draw mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // Always good practice to set everything back to defaults once configured.
    glActiveTexture(GL_TEXTURE0);
}