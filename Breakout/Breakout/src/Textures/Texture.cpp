#include "Texture.h"

#include <GL/glew.h>

void Texture::Generate(int width, int height, unsigned char* data)
{
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);

    glTexImage2D(GL_TEXTURE_2D, 0, internal_format, width, height, 0, image_format, GL_UNSIGNED_BYTE, data);
    glBindTexture(GL_TEXTURE_2D, 0);
}

//DEFAULTS
Texture::Texture()
    : internal_format(GL_RGB), image_format(GL_RGB), wrap_s(GL_REPEAT), wrap_t(GL_REPEAT), min_filter(GL_LINEAR), mag_filter(GL_LINEAR)
{
}

void Texture::Bind() const
{
    glBindTexture(GL_TEXTURE_2D, ID);
}
