#include "Shader.h"

std::unordered_map<const char *, uint32_t> Shader::Library::shader_library;
std::unordered_map<const char *, std::shared_ptr<Shader>> Shader::Library::compiled_shader_library;

Shader::Shader(uint32_t vertexShaderId, uint32_t fragmentShaderId, uint32_t programId) {
    vertex_shader_id = vertexShaderId;
    fragment_shader_id = fragmentShaderId;
    program_id = programId;
}

void Shader::Use() const {
    glUseProgram(program_id);
}

void Shader::SetBool(const char *name, bool value) const {
    glProgramUniform1ui(program_id, glGetUniformLocation(program_id, name), (int) value);
}

void Shader::SetInt(const char *name, int value) const {
    glProgramUniform1i(program_id, glGetUniformLocation(program_id, name), value);
}

void Shader::SetFloat(const char *name, float value) const {
    glProgramUniform1f(program_id, glGetUniformLocation(program_id, name), value);
}

void Shader::SetVec2(const char *name, float valueX, float valueY) const {
    glProgramUniform2f(program_id, glGetUniformLocation(program_id, name), valueX, valueY);
}

void Shader::SetVec3(const char *name, float valueX, float valueY, float valueZ) const {
    glProgramUniform3f(program_id, glGetUniformLocation(program_id, name), valueX, valueY, valueZ);
}

void Shader::SetModelMatrix(const glm::mat4 &transform) const {
    glProgramUniformMatrix4fv(program_id, glGetUniformLocation(program_id, "u_modelTransform"), 1, GL_FALSE, glm::value_ptr(transform));
}

void Shader::SetViewProjectionMatrix(const glm::mat4 &transform) const {
    glProgramUniformMatrix4fv(program_id, glGetUniformLocation(program_id, "u_viewProjection"), 1, GL_FALSE, glm::value_ptr(transform));
}

Shader::Library::Library() {
    Shader::Library::shader_library = std::unordered_map<const char *, uint32_t>();
    Shader::Library::compiled_shader_library = std::unordered_map<const char *, std::shared_ptr<Shader>>();
}

std::shared_ptr<Shader> Shader::Library::CreateShader(const char *vertexShaderPath, const char *fragmentShaderPath) {
    std::string shaderCode;
    uint32_t vertex_id;
    uint32_t fragment_id;
    std::shared_ptr<Shader> compiled_shader;

    if (Shader::Library::shader_library.contains(vertexShaderPath)) {
        vertex_id = Shader::Library::shader_library[vertexShaderPath];
    } else {
        shaderCode = Shader::Library::ReadShaderCode(vertexShaderPath);

        vertex_id = Shader::Library::AddShader(vertexShaderPath, GL_VERTEX_SHADER, 1, shaderCode.c_str());
    }

    if (Shader::Library::shader_library.contains(fragmentShaderPath)) {
        fragment_id = Shader::Library::shader_library[fragmentShaderPath];
    } else {
        shaderCode = Shader::Library::ReadShaderCode(fragmentShaderPath);

        fragment_id = Shader::Library::AddShader(fragmentShaderPath, GL_FRAGMENT_SHADER, 1, shaderCode.c_str());
    }

    const char *shader_name = std::to_string(vertex_id).append("-").append(std::to_string(fragment_id)).c_str();

    if (Shader::Library::compiled_shader_library.contains(shader_name)) {
        compiled_shader = Shader::Library::compiled_shader_library[shader_name];
    } else {
        compiled_shader = Shader::Library::AddProgram(shader_name, vertex_id, fragment_id);
    }

    return compiled_shader;
}

std::shared_ptr<Shader> Shader::Library::CreateShader(uint32_t vertexShaderId, uint32_t fragmentShaderId) {
    auto vertexShaderIdCString = std::to_string(vertexShaderId);
    auto fragmentShaderIdCString = std::to_string(fragmentShaderId);

    std::shared_ptr<Shader> compiled_shader = AddProgram(
            std::to_string(vertexShaderId).append("-").append(std::to_string(fragmentShaderId)).c_str(), vertexShaderId,
            fragmentShaderId);

    return compiled_shader;
}

uint32_t
Shader::Library::AddShader(const char *name, GLenum type, GLsizei count, const char *code, const GLint *length) {
    uint32_t shader_id;
    int success;
    char log[512];

    shader_id = glCreateShader(type);
    glShaderSource(shader_id, count, &code, length);
    glCompileShader(shader_id);

    //error printing, if any
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(shader_id, 512, nullptr, log);

        std::cout << "ERROR::SHADER::" << ((type == GL_VERTEX_SHADER) ? "VERTEX" : "FRAGMENT")
                  << "::COMPILATION_FAILED -> " << log << std::endl;
    }

    Shader::Library::shader_library[name] = shader_id;

    return shader_id;
}

std::shared_ptr<Shader> Shader::Library::AddProgram(const char *name, uint32_t vertexId, uint32_t fragmentId) {
    int program_id;
    int success;
    char log[512];

    program_id = glCreateProgram();
    glAttachShader(program_id, vertexId);
    glAttachShader(program_id, fragmentId);
    glLinkProgram(program_id);

    //error printing, if any
    glGetProgramiv(program_id, GL_LINK_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(program_id, 512, nullptr, log);

        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED -> " << log << std::endl;
    }

    std::shared_ptr<Shader> compiled_shader = std::make_shared<Shader>(vertexId, fragmentId, program_id);

    Shader::Library::compiled_shader_library[name] = compiled_shader;

    return compiled_shader;
}

std::string Shader::Library::ReadShaderCode(const char *shaderCodePath) {
    std::string shaderCodeString; //actual shader code
    std::ifstream shaderFile; //file handler

    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        //opens files
        shaderFile.open(shaderCodePath);

        std::stringstream shaderStream;

        //reads files buffers into streams
        shaderStream << shaderFile.rdbuf();

        //closes file handlers
        shaderFile.close();

        shaderCodeString = shaderStream.str();
    } catch (std::ifstream::failure &e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ -> " << e.what() << std::endl << "Path: "
                  << shaderCodePath << std::endl;
        return {};
    }

    return shaderCodeString;
}
