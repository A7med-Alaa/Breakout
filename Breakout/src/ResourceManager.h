#pragma once
#include <map>

#include "Shaders/Shader.h"
#include "Textures/Texture.h"

class ResourceManager
{
private:
    ResourceManager() {}

    static Shader LoadShaderFromFile(const char* vPath, const char* fPath, const char* gPath = "");
    static Texture LoadTextureFromImage(const char* path, bool alpha);
public:
    static std::map<std::string, Shader> Shaders;
    static std::map<std::string, Texture> Textures;
    
    static Shader LoadShader(const char* vShader, const char* fShader, const char* gShader, const std::string& name);
    static Shader GetShader(const std::string& name);
    static Texture LoadTexture(const char* path, bool alpha, const std::string& name);
    static Texture GetTexture(const std::string& name);

    static void Clean();
};
