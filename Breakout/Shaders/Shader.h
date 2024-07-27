#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <map>
#include <string>

class Shader
{
private:
    int m_programID;
    std::map<const char*, int> m_uniformsIDsCache;

    int GetUniformLocation(const char* name);
    
    void checkForErrors( int shader, const char* type) const;
public:
    Shader(std::string vShader, std::string fShader, std::string gShader);

    const char* LoadShaderFromFile(const char* filePath) const;

    void Use() const;
    unsigned int GetProgramID() const { return m_programID; }
    
    void setVec3(const char* name, glm::vec3 value);
    void setMat4(const char* name, glm::mat4 value);
    void setFloat(const char* name, float value);
    void setInt(const char* name, int value);

};
