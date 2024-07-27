#pragma once
#include <map>

#include "../Shaders/Shader.h"
#include "../Textures/Texture.h"

class ResourceManager
{
private:
    ResourceManager() {}

    static Shader LoadShaderFromFile(const char* vPath, const char* fPath, const char* gPath = "");
    static Texture LoadTextureFromImage(const char* path, bool alpha);
public:
    static std::map<const char*, Shader> Shaders;
    static std::map<const char*, Texture> Textures;

    static Shader GetShaderFromFile(const char* vShader, const char* fShader, const char* gShader, const char* name);
    static Shader GetShader(const char* name);
    static Texture GetTextureFromImage(const char* path, bool alpha, const char* name);
    static Texture GetTexture(const char* name);

    static void Clean();
};
