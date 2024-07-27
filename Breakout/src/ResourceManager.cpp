#include "ResourceManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include <stb/stb_image.h>

Shader ResourceManager::LoadShaderFromFile(const char* vPath, const char* fPath, const char* gPath)
{
    std::string vShaderSource;
    std::string fShaderSource;
    std::string gShaderSource;
    
    std::ifstream vShaderFile(vPath);
    std::ifstream fShaderFile(fPath);
    try
    {
        std::stringstream v_shaderstream;
        std::stringstream f_shaderstream;

        v_shaderstream << vShaderFile.rdbuf();
        f_shaderstream << fShaderFile.rdbuf();

        vShaderSource = v_shaderstream.str();
        fShaderSource = f_shaderstream.str();

        vShaderFile.close();
        fShaderFile.close();
    } catch (std::ifstream::failure& e)
    {
        std::cout << "Failed to read file" << e.what();
    }

    if(!strcmp(gPath, ""))
    {
        try
        {
            std::ifstream gShaderFile(gPath);
            std::stringstream g_shaderstream;
            
            g_shaderstream << gShaderFile.rdbuf();

            gShaderSource = g_shaderstream.str();
            gShaderFile.close();
        } catch (std::ifstream::failure& e)
        {
            std::cout << "Failed to read file" << e.what();
        }
    }

    Shader shader(vShaderSource.c_str(), fShaderSource.c_str(), gShaderSource.empty() ? "" : gShaderSource.c_str());
    return shader;
}

Texture ResourceManager::LoadTextureFromImage(const char* path, bool alpha)
{
    int width, height, channels;
    const unsigned char* data = stbi_load(path, &width, &height, &channels, 0);
    Texture texture;

    if(alpha == true)
    {
        texture.image_format = GL_RGBA;
        texture.internal_format = GL_RGBA;
    }

    texture.Generate(width, height, data);
    return texture;
}

Shader ResourceManager::GetShaderFromFile(const char* vShader, const char* fShader, const char* gShader, const char* name)
{
    Shaders[name] = LoadShaderFromFile(vShader, fShader, gShader);
    return Shaders[name];
}

Shader ResourceManager::GetShader(const char* name)
{
    return Shaders[name];
}

Texture ResourceManager::GetTextureFromImage(const char* path, bool alpha, const char* name)
{
    Textures[name] = LoadTextureFromImage(path, alpha);
    return Textures[name];
}

Texture ResourceManager::GetTexture(const char* name)
{
    return Textures[name];
}

void ResourceManager::Clean()
{
    for (auto iter : Shaders)
        glDeleteProgram(iter.second.ID);

    for (auto iter: Textures)
        glDeleteTextures(1, &iter.second.ID);
}
