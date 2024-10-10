#pragma once
#include <string>
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Mesh.h"

class Model{
public:
    Model(std::string const &path, bool gamma = false);
    ~Model();
    void loadModel(std::string const &path);
    void draw(Shader& shader);

    std::vector<Mesh*> meshes;
private:
    std::vector<Texture> textures_loaded;
    std::string directory;
    bool gammaCorrection;

    void processNode(aiNode* node, const aiScene* scene);
    Mesh* processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
    unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma = false);
};