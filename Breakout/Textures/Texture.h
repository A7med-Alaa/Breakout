#pragma once

struct Texture
{
    
    unsigned int ID;
    
    int internal_format;
    int image_format;

    int wrap_s;
    int wrap_t;
    int min_filter;
    int mag_filter;
    
    void Generate(const int width, const int height, const unsigned char* data);
    Texture();
    void Bind() const;
    
};
