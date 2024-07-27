#include "Shader.h"
#include <gl/glew.h>
#include <iostream>

int Shader::GetUniformLocation(const char* name)
{
    if(!m_uniformsIDsCache[name])
    {
        int location = glGetUniformLocation(m_programID, name);
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
        glGetProgramiv(m_programID, GL_LINK_STATUS, &success);
        if(!success)
        {
            glGetProgramInfoLog(m_programID, 512, nullptr, info);
            std::cout << "Error while compiling " << type << ":\n" << info;
        }
    }
}

Shader::Shader(const char* vShader, const char* fShader, const char* gShader)
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

    if(gShader == NULL)
    {
        geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geometryShader, 1, &gShader, nullptr);
        glCompileShader(geometryShader);

        checkForErrors(geometryShader, "Geometry Shader");
    }

    m_programID = glCreateProgram();
    glAttachShader(m_programID, vertexShader);
    glAttachShader(m_programID, fragmentShader);
    if(gShader != NULL) glAttachShader(m_programID, geometryShader);
    glLinkProgram(m_programID);
    checkForErrors(m_programID, "program");

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    if(gShader != NULL) glDeleteShader(geometryShader);
}

void Shader::Use() const
{
    glUseProgram(m_programID);
}

void Shader::setVec3(const char* name, glm::vec3 value)
{
    glUniform3f(GetUniformLocation(name), value.x, value.y, value.z);
}

void Shader::setMat4(const char* name, glm::mat4 value)
{
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setFloat(const char* name, float value)
{
    glUniform1f(GetUniformLocation(name), value);
}

void Shader::setInt(const char* name, int value)
{
    glUniform1i(GetUniformLocation(name), value);
}
