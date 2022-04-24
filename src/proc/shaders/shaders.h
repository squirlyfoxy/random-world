#ifndef __SHADERS_H__
#define __SHADERS_H__

#include <vector>
#include <iostream>
#include <string>
#include <unordered_map>

#include <cpmath/cpmath.h>

extern const char *world_vertex_shader;
extern const char *world_fragment_shader;

enum ShaderType {
    VERTEX_SHADER,
    FRAGMENT_SHADER,
    GEOMETRY_SHADER,
    TESS_CONTROL_SHADER,
    TESS_EVAL_SHADER,
};

struct Shader {
    unsigned int id;
    ShaderType type;
    
    const char *source;
};

Shader ReadShader(const char *file, ShaderType type);

struct Program {
    unsigned int id;

    std::vector<Shader> shaders;

    // Cache for uniform locations (thanks cherno)
    std::unordered_map<std::string, int> uniform_locations;
};

void NewProgram(Program *p);

//**************************
// Uniforms

unsigned int GetUniformLocation(Program *p, const std::string& name);

void BindInt(Program p, const std::string& name, const int& value);
void BindFloat(Program p, const std::string& name, const float& value);
void BindBool(Program p, const std::string& name, const bool& value);
void BindVec4(Program p, const std::string& name, const vec4& v);
void BindVec3(Program p, const std::string& name, const vec3& v);
void BindMat4(Program p, const std::string& name, const mat4& m);

#endif