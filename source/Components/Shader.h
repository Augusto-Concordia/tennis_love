#pragma once

#ifndef __gl_h_

#include "glad/glad.h" // include glad to get all the required OpenGL headers

#endif

#include "glm/vec2.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <memory>
#include <unordered_map>

class Shader {
public:
    class Library {
    private:
        static std::unordered_map<const char*, uint32_t> shader_library;
        static std::unordered_map<const char*, std::shared_ptr<Shader>> compiled_shader_library;

    public:
        Library();

        static std::shared_ptr<Shader> CreateShader(const char *vertexShaderPath, const char * fragmentShaderPath);
        static std::shared_ptr<Shader> CreateShader(uint32_t vertexShaderId, uint32_t fragmentShaderPath);

        static uint32_t AddShader(const char* name, GLenum type, GLsizei count, const char *code, const GLint *length = nullptr);
        static std::shared_ptr<Shader> AddProgram(const char* name, uint32_t vertexId, uint32_t fragmentId);

    private:
        static std::string ReadShaderCode(const char* shaderCodePath);
    };

public:
    uint32_t program_id;
    uint32_t vertex_shader_id;
    uint32_t fragment_shader_id;

public:
    Shader(uint32_t vertexShaderId, uint32_t fragmentShaderId, uint32_t programId);

    void Use() const; //activates the shader

    void SetBool(const char *name, bool value) const; // utility function to set a bool value
    void SetInt(const char *name, int value) const;  // utility function to set a int value
    void SetFloat(const char *name, float value) const; // utility function to set a float value
    void SetVec2(const char *name, float valueX, float valueY) const; // utility function to set a vector 2
    void SetVec3(const char *name, float valueX, float valueY, float valueZ) const; // utility function to set a vector 3
    void SetModelMatrix(const glm::mat4& transform) const; // utility function to set model matrix
    void SetViewProjectionMatrix(const glm::mat4& transform) const; // utility function to set projection matrix
};

