#pragma once
#include "stb_image.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include <string>

class Texture
{  
public:
    Texture();
    Texture(std::string path, std::string type);
    ~Texture();
    void bind();
    void unbind();
    std::string type;
    std::string path;
    unsigned int ID;
private:
    unsigned char* data;
    int width, height, nrChannels;
    void loadTexture(std::string path);
};