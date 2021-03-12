#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>

class Shader {
   public:
    GLuint shader_program;

    // Constructor to generate shader program on the fly
    Shader(const GLchar* vertex_shader_source_path,
           const GLchar* fragment_shader_source_path) {
        // Step 1: Retrieve the vertex/fragment souce code
        std::string vertex_code_string;
        std::string fragment_code_string;
        std::ifstream vertex_shader_file;
        std::ifstream fragment_shader_file;

        // esnures ifstream objects can throw exceptions
        vertex_shader_file.exceptions(std::ifstream::badbit);
        fragment_shader_file.exceptions(std::ifstream::badbit);

        try {
            // Open files
            vertex_shader_file.open(vertex_shader_source_path);
            fragment_shader_file.open(fragment_shader_source_path);
            std::stringstream vertex_shader_stream, fragment_shader_stream;
            // Read file's buffer contents into stream
            vertex_shader_stream << vertex_shader_file.rdbuf();
            fragment_shader_stream << fragment_shader_file.rdbuf();
            // Now that we have loaded stuff into streams
            // we do not need the file objects anymore, we can close them
            vertex_shader_file.close();
            fragment_shader_file.close();
            // Finally convert the stringstream objects to our string
            // codes vertex_code and fragment_code
            vertex_code_string = vertex_shader_stream.str();
            fragment_code_string = fragment_shader_stream.str();
        } catch (std::ifstream::failure e) {
            std::cerr << "ERROR:SHADER::FILE_NOT_SUCCESSFULLY_READ"
                      << "\n";
        }
        const GLchar* vertex_shader_code = vertex_code_string.c_str();
        const GLchar* fragment_shader_code = fragment_code_string.c_str();

        // Step 2: Compile shaders
        GLuint vertex_shader, fragment_shader;
        GLint success;
        GLchar info_log[512];

        // Vertex shader compilation
        vertex_shader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex_shader, 1, &vertex_shader_code, nullptr);
        glCompileShader(vertex_shader);
        // Check for compilation errors
        glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            // Get info log
            glGetShaderInfoLog(vertex_shader, 512, nullptr, info_log);
            std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                      << info_log << "\n";
            return;
        }

        // Fragment shader coompilation
        fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment_shader, 1, &fragment_shader_code, nullptr);
        glCompileShader(fragment_shader);
        // Check for compilation errors
        glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            // Get the info log
            glGetShaderInfoLog(fragment_shader, 512, nullptr, info_log);
            std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                      << info_log << "\n";
            return;
        }

        // Attach the shaders to a program
        shader_program = glCreateProgram();
        glAttachShader(shader_program, vertex_shader);
        glAttachShader(shader_program, fragment_shader);
        glLinkProgram(shader_program);

        // Check for linking errors
        glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
        if (!success) {
            // Get info log
            glGetProgramInfoLog(shader_program, 512, nullptr, info_log);
            std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                      << info_log << "\n";
            return;
        }

        // Clean up the shaders
        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
    }

    // Uses the current shader
    void use() { glUseProgram(this->shader_program); }
};