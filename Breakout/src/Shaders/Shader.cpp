#include "Shader.h"

#include <iostream>
#include <gl/glew.h>

int Shader::GetUniformLocation(const char* name)
{
    if(!m_uniformsIDsCache[name])
    {
        int location = glGetUniformLocation(ID, name);
        if(location == GL_INVALID_VALUE || location == GL_INVALID_OPERATION)
        {
            std::cout << "Error: Invalid value uniform location\n";
        }
        m_uniformsIDsCache.insert({name, location});
        return location;
    }
    return m_uniformsIDsCache[name];
}

void Shader::checkForErrors(int shader, const char* type) const
{
    int success;
    char info[512];
    if(!strcmp(type, "program"))
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(shader, 512, nullptr, info);
            std::cout << "Error while compiling " << type << ":\n" << info;
        }
    } else
    {
        glGetProgramiv(ID, GL_LINK_STATUS, &success);
        if(!success)
        {
            glGetProgramInfoLog(ID, 512, nullptr, info);
            std::cout << "Error while compiling " << type << ":\n" << info;
        }
    }
}

void Shader::Compile(const char* vShader, const char* fShader, const char* gShader)
{
    int geometryShader = 0;
    
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vShader, nullptr);
    glCompileShader(vertexShader);

    checkForErrors(vertexShader, "Vertex Shader");
    
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fShader, nullptr);
    glCompileShader(fragmentShader);

    checkForErrors(fragmentShader, "Fragment Shader");

    if(gShader != nullptr)
    {
        geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geometryShader, 1, &gShader, nullptr);
        glCompileShader(geometryShader);
    
        checkForErrors(geometryShader, "Geometry Shader");
    }

    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    if(gShader != nullptr) glAttachShader(ID, geometryShader);
    glLinkProgram(ID);
    checkForErrors(ID, "program");
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    if(gShader != nullptr) glDeleteShader(geometryShader);
}

void Shader::Use() const
{
    glUseProgram(ID);
}

void Shader::setVec3(const char* name, const glm::vec3& value)
{
    glUniform3f(GetUniformLocation(name), value.x, value.y, value.z);
}

void Shader::setMat4(const char* name, const glm::mat4& value)
{
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &value[0][0]);
}

void Shader::setFloat(const char* name, float value)
{
    glUniform1f(GetUniformLocation(name), value);
}

void Shader::setInt(const char* name, int value)
{
    glUniform1i(GetUniformLocation(name), value);
}
