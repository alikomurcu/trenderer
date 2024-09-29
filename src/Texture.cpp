#define STB_IMAGE_IMPLEMENTATION
#include "Texture.h"

Texture::Texture()
{
}

Texture::Texture(std::string path, std::string type)
    : type(type), path(path)
{
    loadTexture(path);
}

Texture::~Texture()
{
}

void Texture::bind()
{
    glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::loadTexture(std::string path)
{
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    
    // TODO: make this cross-graphics API
    // in opengl the texture coordinates start from the bottom left corner, so we need to flip the image
    stbi_set_flip_vertically_on_load(true);

    data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        GLenum format;
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3)
            format = GL_RGB;
        else if (nrChannels == 4)
            format = GL_RGBA;

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    	// set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	    // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }

    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);
}