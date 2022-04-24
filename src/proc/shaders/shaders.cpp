#include "shaders.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include <glad/glad.h>

const char* world_vertex_shader = "#version 430 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aNormal;\n"
    "layout (location = 2) in vec2 aTexCoord;\n"
    "uniform mat4 proj;\n"
    "uniform mat4 view;\n"
    "uniform mat4 model;\n"
    "uniform mat4 MVP;\n"
    "out vec2 TexCoord;\n"
    "out vec3 normal_o;\n"
    "out vec3 FragPos;\n"
    "void main()\n"
    "{\n"
    "   TexCoord = aTexCoord;\n"
    "   normal_o = mat3(transpose(inverse(model))) * aNormal;\n"
    "   FragPos = vec3(model * vec4(aPos, 1.0));\n"
    "   gl_Position = proj * view * vec4(FragPos, 1.0);\n"
    //"   gl_Position = MVP * vec4(aPos, 1.0);\n"
    "}\0";

const char *world_fragment_shader = "#version 430 core\n"
    "out vec4 FragColor;\n"
    "in vec2 TexCoord;\n"
    "in vec3 normal_o;\n"
    "in vec3 FragPos;\n"

    "uniform vec4 color;\n"
    "uniform vec3 viewPos;\n"
    "uniform float ambientStrength;\n"
    "uniform float specularStrength;\n"

    "struct Material {\n"
    "   sampler2D diffuse;\n"
    "   sampler2D specular;\n"
    "   float   shininess;\n"
    "   bool    can_reflect;\n"
    "};\n"
    "uniform Material material;\n"
    "struct Light {\n"
        "vec4 lightColor;\n"
        "vec3 lightPos;\n"
        "vec3    ambient;\n"
        "vec3    diffuse;\n"
        "vec3    specular;\n"
    "};\n"
    "uniform Light lights[1];\n"
    "struct DirectionalLight {\n"
        "vec3 direction;\n"
        "vec3 ambient;\n"
        "vec3 diffuse;\n"
        "vec3 specular;\n"
    "};\n"
    "uniform DirectionalLight sun;\n"
    "vec3 calcLight(Light light, vec3 normal, vec3 fragPos) {\n"
        "vec3 ambient = light.ambient * texture(material.diffuse, TexCoord).rgb;\n"
        "\n //Diffuse \n"
        "   vec3 lightDir = normalize(light.lightPos - fragPos);\n"
        "   float diff = max(dot(normal, lightDir), 0.0);\n"
        "   vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoord).rgb;\n"
        "\n //Specular\n"
        "   vec3 specular = vec3(0.0, 0.0, 0.0);\n"
        "   if (material.can_reflect) {\n"
            "   vec3 viewDir = normalize(viewPos - fragPos);\n"
            "   vec3 halfDir = normalize(lightDir + viewDir);\n"
            "   vec3 reflectDir = reflect(-lightDir, normal);\n"
            "   float spec = pow(max(dot(normal, halfDir), 0.0), material.shininess);\n"
            "   specular = light.specular * (spec * texture(material.specular, TexCoord).rgb) * light.lightColor.xyz;\n"
        "   } else {\n"
            "   vec3 reflectDir = reflect(-lightDir, normal);\n"
            "   float spec = pow(max(dot(normal, reflectDir), 0.0), material.shininess);\n"
            "   specular = light.specular * (spec * texture(material.specular, TexCoord).rgb) * light.lightColor.xyz;\n"
        "   }\n"
        "\n // calculate the final color\n"
        "   vec3 result = (ambient + diffuse + specular);\n"
        "   // attenuate the light\n"
        "   float attenuation = 1.0 / (1.0 + (0.1 * length(light.lightPos - fragPos)));\n"
        "   result = result * attenuation;\n"
        "   return result;\n"
    "}\n"
    "vec3 calcDirectionalLight(DirectionalLight light, vec3 normal, vec3 fragPos) {\n"
        "vec3 ambient = light.ambient * texture(material.diffuse, TexCoord).rgb;\n"
        "\n //Diffuse \n"
        "   vec3 lightDir = normalize(-light.direction);\n"
        "   float diff = max(dot(normal, lightDir), 0.0);\n"
        "   vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoord).rgb;\n"
        "\n //Specular\n"
        "   vec3 viewDir = normalize(viewPos - fragPos);\n"
        "   vec3 reflectDir = reflect(-lightDir, normal);\n"
        "   float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);\n"
        "   vec3 specular = light.specular * (spec * texture(material.specular, TexCoord).rgb);\n"
        "\n // calculate the final color\n"
        "   vec3 result = (ambient + diffuse + specular);\n"
        "   return result;\n"
    "}\n"

    "float linearizeDepth(float depth) {\n"
        "return (2.0 * 0.1 * 1000.0) / (1000.0 + 0.1 - (depth * 2.0 - 1.0) * (1000.0 - 0.1));\n"
    "}\n"

    "void main()\n"
    "{\n"
   "   //FragColor = texture(ourTexture, TexCoord);\n"
    "   vec3 normal = normalize(normal_o);\n"
    "   vec3 result = vec3(0.0);\n"
    "   for (int i = 0; i < 1; i++) {\n"
    "       //result += calcLight(lights[i], normal, FragPos);\n"
    "   }\n"
    "   result += calcDirectionalLight(sun, normal, FragPos);\n"
    "   FragColor = vec4(result, 1.0);\n"
    
    "   // Gamma correction\n"
    "   FragColor.rgb = pow(FragColor.rgb, vec3(2.2));\n"
    "}\0"; 


Shader ReadShader(const char *file, ShaderType type) {
    Shader shader;
    shader.type = type;

    std::ifstream stream(file);
    if (stream.fail()) {
        std::cout << "Failed to open file " << file << std::endl;
        return shader;
    }

    std::string line;
    std::stringstream ss;
    while (std::getline(stream, line)) {
        ss << line << "\n";
    }
    stream.close();

    shader.source = ss.str().c_str();

    return shader;
}

void NewProgram(Program *p) {
    for (unsigned int i = 0; i < p->shaders.size(); i++) {
        //For every shader we need to compile them
        switch (p->shaders[i].type) {
            case VERTEX_SHADER:
                p->shaders[i].id = glCreateShader(GL_VERTEX_SHADER);
                break;
            case FRAGMENT_SHADER:
                p->shaders[i].id = glCreateShader(GL_FRAGMENT_SHADER);
                break;
            case GEOMETRY_SHADER:
                p->shaders[i].id = glCreateShader(GL_GEOMETRY_SHADER);
                break;
            case TESS_CONTROL_SHADER:
                p->shaders[i].id = glCreateShader(GL_TESS_CONTROL_SHADER);
                break;
            case TESS_EVAL_SHADER:
                p->shaders[i].id = glCreateShader(GL_TESS_EVALUATION_SHADER);
                break;
        }
        glShaderSource(p->shaders[i].id, 1, &p->shaders[i].source, NULL);
        glCompileShader(p->shaders[i].id);

        //Check if the shader compiled successfully
        int success;
        char infoLog[512];
        glGetShaderiv(p->shaders[i].id, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(p->shaders[i].id, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::";
            switch (p->shaders[i].type)
            {
            case VERTEX_SHADER:
                std::cout << "VERTEX";
                break;
            case FRAGMENT_SHADER:
                std::cout << "FRAGMENT";
                break;
            case GEOMETRY_SHADER:
                std::cout << "GEOMETRY";
                break;
            case TESS_CONTROL_SHADER:
                std::cout << "TESS_CONTROL";
                break;
            case TESS_EVAL_SHADER:
                std::cout << "TESS_EVAL";
                break;
            }

            std::cout << "::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

    }

    //Create the program
    p->id = glCreateProgram();
    for (unsigned int i = 0; i < p->shaders.size(); i++) { //Attach all shaders to the program
        glAttachShader(p->id, p->shaders[i].id);
    }
    glLinkProgram(p->id);

    //Check if the program linked successfully
    int success;
    char infoLog[512];
    glGetProgramiv(p->id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(p->id, 512, NULL, infoLog);
        std::cout << "ERROR::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    //Delete the shaders
    for (unsigned int i = 0; i < p->shaders.size(); i++) {
        glDeleteShader(p->shaders[i].id);
    }
}

//****************
// Uniforms

unsigned int GetUniformLocation(Program *p, const std::string& name) {
    // Check if the uniform is already in the cached map
    auto it = p->uniform_locations.find(name);
    if (it != p->uniform_locations.end()) {
        return it->second;
    }

    // If not, get the uniform location and cache it
    unsigned int location = glGetUniformLocation(p->id, name.c_str());
    if(location != -1) {
        p->uniform_locations[name] = location;
    }
    
    return location;
}

void BindFloat(Program p, const std::string& name, const float& value) {
    glUniform1f(GetUniformLocation(&p, name), value);
}

void BindInt(Program p, const std::string& name, const int& value) {
    glUniform1i(GetUniformLocation(&p, name), value);
}

void BindBool(Program p, const std::string& name, const bool& value) {
    glUniform1i(GetUniformLocation(&p, name), value);
}

void BindVec4(Program p, const std::string& name, const vec4& v) {
    glUniform4f(GetUniformLocation(&p, name), v.x, v.y, v.z, v.w);
}

void BindVec3(Program p, const std::string& name, const vec3& v) {
    glUniform3f(GetUniformLocation(&p, name), v.x, v.y, v.z);
}

void BindMat4(Program p, const std::string& name, const mat4& m) {
    glUniformMatrix4fv(GetUniformLocation(&p, name), 1, GL_TRUE, &m.m[0][0]);
}
