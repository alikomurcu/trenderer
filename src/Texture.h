#pragma once
#include "stb_image.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include <string>

class Texture
{  
public:
    Texture(std::string path, std::string type);
    ~Texture();
    void bind();
    void unbind();
    std::string type;
private:
    unsigned int ID;
    unsigned char* data;
    int width, height, nrChannels;
    void loadTexture(std::string path);
};