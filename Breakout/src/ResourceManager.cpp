#include "ResourceManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <GL/glew.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

std::map<std::string, Shader> ResourceManager::Shaders;
std::map<std::string, Texture> ResourceManager::Textures;

Shader ResourceManager::LoadShaderFromFile(const char* vPath, const char* fPath, const char* gPath)
{
    std::string vShaderSource;
    std::string fShaderSource;
    std::string gShaderSource;
    try
    {
        std::ifstream vShaderFile(vPath);
        std::ifstream fShaderFile(fPath);
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

    if(gPath != nullptr)
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

    const char* vSource = vShaderSource.c_str();
    const char* fSource = fShaderSource.c_str();
    const char* gShader = gShaderSource.c_str();
    
    Shader shader;
    shader.Compile(vSource, fSource, gPath == nullptr ? nullptr : gShader);
    return shader;
}

Texture ResourceManager::LoadTextureFromImage(const char* path, bool alpha)
{
    Texture texture;

    if(alpha == true)
    {
        texture.image_format = GL_RGBA;
        texture.internal_format = GL_RGBA;
    }
    int width, height, channels;
    unsigned char* data = 0;
    data = stbi_load(path, &width, &height, &channels, 0);

    if(stbi_failure_reason())
    {
        std::cout << "Error:\n";
        std::cout << "\n" << stbi_failure_reason() << "\n";
    }
    
    if(data)
    {
        texture.Generate(width, height, data);
    }
    stbi_image_free(data);
    return texture;
}

Shader ResourceManager::LoadShader(const char* vShader, const char* fShader, const char* gShader, const std::string& name)
{
    Shaders[name] = LoadShaderFromFile(vShader, fShader, gShader);
    return Shaders[name];
}

Shader ResourceManager::GetShader(const std::string& name)
{
    return Shaders[name];
}

Texture ResourceManager::LoadTexture(const char* path, bool alpha, const std::string& name)
{
    Textures[name] = LoadTextureFromImage(path, alpha);
    return Textures[name];
}

Texture ResourceManager::GetTexture(const std::string& name)
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
