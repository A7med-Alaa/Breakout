#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <map>
#include <string>

class Shader
{
private:
    std::map<std::string, int> m_uniformsIDsCache;
    int GetUniformLocation(const char* name);

    void checkForErrors( int shader, const char* type) const;
public:
    unsigned int ID;
    Shader() {}

    void Use() const;
    
    void Compile(const char* vShader, const char* fShader, const char* gShader = nullptr);
    void setVec3(const char* name, const glm::vec3& value);
    void setMat4(const char* name, const glm::mat4& value);
    void setFloat(const char* name, float value);
    void setInt(const char* name, int value);

};
