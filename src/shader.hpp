#ifndef SHADER_HPP
#define SHADER_HPP

// Reference:
// https://learnopengl.com/Getting-started/Shaders "Our own shader class"

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

enum ShaderType { light, depth };

static const std::string FRAG_SHADER = "#version 330 core\n"
"out vec4 FragColor;\n"
"\n"
"in VS_OUT {\n"
"    vec3 FragPos;\n"
"    vec3 Normal;\n"
"    vec2 TexCoords;\n"
"    vec4 FragPosLightSpace;\n"
"} fs_in;\n"
"\n"
"uniform sampler2D shadowMap;\n"
"\n"
"uniform vec3 lightPos;\n"
"uniform vec3 viewPos;\n"
"uniform vec3 objectColor;\n"
"uniform bool shadowEnabled;\n"
"\n"
"float ShadowCalculation(vec4 fragPosLightSpace)\n"
"{\n"
"    // perform perspective divide\n"
"    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;\n"
"    // transform to [0,1] range\n"
"    projCoords = projCoords * 0.5 + 0.5;\n"
"    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)\n"
"    float closestDepth = texture(shadowMap, projCoords.xy).r;\n"
"    // get depth of current fragment from light's perspective\n"
"    float currentDepth = projCoords.z;\n"
"    // calculate bias (based on depth map resolution and slope)\n"
"    vec3 normal = normalize(fs_in.Normal);\n"
"    vec3 lightDir = normalize(lightPos - fs_in.FragPos);\n"
"    float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);\n"
"    // check whether current frag pos is in shadow\n"
"    // float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;\n"
"    // PCF\n"
"    float shadow = 0.0;\n"
"    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);\n"
"    for(int x = -1; x <= 1; ++x)\n"
"    {\n"
"        for(int y = -1; y <= 1; ++y)\n"
"        {\n"
"            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r;\n"
"            shadow += (currentDepth - bias > pcfDepth) && shadowEnabled ? 1.0 : 0.0;\n"
"        }\n"
"    }\n"
"    shadow /= 9.0;\n"
"\n"
"    // keep the shadow at 0.0 when outside the far_plane region of the light's frustum.\n"
"    if(projCoords.z > 1.0)\n"
"        shadow = 0.0;\n"
"\n"
"    return shadow;\n"
"}\n"
"\n"
"void main()\n"
"{\n"
"    vec3 color = objectColor;\n"
"    vec3 normal = normalize(fs_in.Normal);\n"
"    vec3 lightColor = vec3(0.3);\n"
"    // ambient\n"
"    vec3 ambient = 0.8 * color;\n"
"    // diffuse\n"
"    vec3 lightDir = normalize(lightPos - fs_in.FragPos);\n"
"    float diff = max(dot(lightDir, normal), 0.0);\n"
"    vec3 diffuse = diff * lightColor;\n"
"    // specular\n"
"    vec3 viewDir = normalize(viewPos - fs_in.FragPos);\n"
"    vec3 reflectDir = reflect(-lightDir, normal);\n"
"    float spec = 0.0;\n"
"    vec3 halfwayDir = normalize(lightDir + viewDir);\n"
"    spec = pow(max(dot(normal, halfwayDir), 0.0), 64.0);\n"
"    vec3 specular = spec * lightColor;\n"
"    // calculate shadow\n"
"    float shadow = ShadowCalculation(fs_in.FragPosLightSpace);\n"
"    vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * color;\n"
"\n"
"    FragColor = vec4(lighting, 1.0);\n"
"}\n";

static const std::string VERTEX_SHADER = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aNormal;\n"
"layout (location = 2) in vec2 aTexCoords;\n"
"\n"
"out vec2 TexCoords;\n"
"\n"
"out VS_OUT {\n"
"    vec3 FragPos;\n"
"    vec3 Normal;\n"
"    vec2 TexCoords;\n"
"    vec4 FragPosLightSpace;\n"
"} vs_out;\n"
"\n"
"uniform mat4 projection;\n"
"uniform mat4 view;\n"
"uniform mat4 model;\n"
"uniform mat4 lightSpaceMatrix;\n"
"\n"
"void main()\n"
"{\n"
"    vs_out.FragPos = vec3(model * vec4(aPos, 1.0));\n"
"    vs_out.Normal = transpose(inverse(mat3(model))) * aNormal;\n"
"    vs_out.TexCoords = aTexCoords;\n"
"    vs_out.FragPosLightSpace = lightSpaceMatrix * vec4(vs_out.FragPos, 1.0);\n"
"    gl_Position = projection * view * model * vec4(aPos, 1.0);\n"
"}\n";

static const std::string DEPTH_VERTEX_SHADER = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"\n"
"uniform mat4 lightSpaceMatrix;\n"
"uniform mat4 model;\n"
"\n"
"void main()\n"
"{\n"
"    gl_Position = lightSpaceMatrix * model * vec4(aPos, 1.0);\n"
"}\n";

static const std::string DEPTH_FRAG_SHADER = "#version 330 core\n"
"\n"
"void main()\n"
"{\n"
"    // gl_FragDepth = gl_FragCoord.z;\n"
"}\n";

class Shader {
public:
    
    inline void setup(const char *vShaderCode, const char *fShaderCode) {
        // compile shaders
        unsigned int vertex, fragment;
        // vertex shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        checkCompileErrors(vertex, "VERTEX");
        // fragment shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        checkCompileErrors(fragment, "FRAGMENT");
        // shader program
        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);
        checkCompileErrors(ID, "PROGRAM");
        // delete the shaders as they're already linked and no longer necessery
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }
    
    // ------------------------------------------------------------------------
    // constructor for shaders using the default shader code we provide
    Shader(ShaderType type) {
        if (type == light){
            const char *vShaderCode = VERTEX_SHADER.c_str();
            const char *fShaderCode = FRAG_SHADER.c_str();
            setup(vShaderCode, fShaderCode);
        } else {
            const char *vShaderCode = DEPTH_VERTEX_SHADER.c_str();
            const char *fShaderCode = DEPTH_FRAG_SHADER.c_str();
            setup(vShaderCode, fShaderCode);
        }
    }

    // ------------------------------------------------------------------------
    // constructor for shader from a specified file path
    Shader(const char *vertexPath, const char *fragmentPath) {
        // 1. retrieve the vertex/fragment source code from filePath
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        // ensure ifstream objects can throw exceptions:
        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try {
            // open files
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;
            // read file's buffer contents into streams
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            // close file handlers
            vShaderFile.close();
            fShaderFile.close();
            // convert stream into string
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        } catch (std::ifstream::failure e) {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ\n";
        }
        const char *vShaderCode = vertexCode.c_str();
        const char *fShaderCode = fragmentCode.c_str();
        // 2. compile shaders
        setup(vShaderCode, fShaderCode);
    }

    // activate the shader
    // ------------------------------------------------------------------------
    void use() const {
        glUseProgram(ID);
    }

    // shader destructor
    // ------------------------------------------------------------------------
    ~Shader() {
        glUseProgram(0);
        if (ID != 0) {
            glDeleteProgram(ID);
        }
    }

    // utility uniform functions
    // ------------------------------------------------------------------------
    void setBool(const std::string &name, bool value) const {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
    }
    // ------------------------------------------------------------------------
    void setInt(const std::string &name, int value) const {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }
    // ------------------------------------------------------------------------
    void setFloat(const std::string &name, float value) const {
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }
    // ------------------------------------------------------------------------
    void setVec2(const std::string &name, const glm::vec2 &value) const {
        glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }
    void setVec2(const std::string &name, float x, float y) const {
        glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
    }
    // ------------------------------------------------------------------------
    void setVec3(const std::string &name, const glm::vec3 &value) const {
        glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }
    void setVec3(const std::string &name, float x, float y, float z) const {
        glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
    }
    // ------------------------------------------------------------------------
    void setVec4(const std::string &name, const glm::vec4 &value) const {
        glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }
    void setVec4(
        const std::string &name, float x, float y, float z, float w) const {
        glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
    }
    // ------------------------------------------------------------------------
    void setMat2(const std::string &name, const glm::mat2 &mat) const {
        glUniformMatrix2fv(
            glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    void setMat3(const std::string &name, const glm::mat3 &mat) const {
        glUniformMatrix3fv(
            glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    void setMat4(const std::string &name, const glm::mat4 &mat) const {
        glUniformMatrix4fv(
            glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    
private:
    // shader program id
    unsigned int ID;

    // utility function for checking shader compilation/linking errors.
    // ------------------------------------------------------------------------
    void checkCompileErrors(GLuint shader, std::string type) {
        GLint success;
        GLchar infoLog[1024];
        if (type != "PROGRAM") {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type
                          << "\n" << infoLog << "\n -- " 
                          << "---------------------------------------------------"
                          << " -- \n";
            }
        } else {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success) {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type 
                          << "\n" << infoLog << "\n -- " 
                          << "---------------------------------------------------"
                          << " -- \n";
            }
        }
    }
};

#endif
