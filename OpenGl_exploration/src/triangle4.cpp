// To create a textured triangle using SOIL2 (added as a submodule)

// Standard io header
#include <iostream>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// SOIL
#include <SOIL2.h>

// shader
#include <shader2.h>

const GLchar* vertex_shader_path =
    "/home/kartik/Documents/Motley/OpenGl_exploration/src/core2.vs";
const GLchar* fragment_shader_path =
    "/home/kartik/Documents/Motley/OpenGl_exploration/src/core2.frag";

const GLchar* texture_image_path =
    "/home/kartik/Documents/Motley/OpenGl_exploration/images/texture_1.jpg";

GLuint WIDTH = 800, HEIGHT = 600;

void enableGLFWOptions() {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
}

int main(int argc, char** argv) {
    // Step 1: Initialize glfw
    if (!glfwInit()) {
        std::cerr << "Failed to Initialized glfw\n";
        return EXIT_FAILURE;
    }

    // Step 2: enable options for glfw
    enableGLFWOptions();

    // Step 3: Create a window
    GLFWwindow* window =
        glfwCreateWindow(WIDTH, HEIGHT, "TEXTURED TRIANGLE", nullptr, nullptr);

    // Step 4: Vertify that window was created
    if (window == nullptr) {
        std::cerr << "Failed to create window\n";
        return EXIT_FAILURE;
    }

    // Step 4: Make the context current for window
    glfwMakeContextCurrent(window);

    // Step 5: Create the view port
    int screen_width, screen_height;
    glfwGetFramebufferSize(window, &screen_width, &screen_height);
    glViewport(0, 0, screen_width, screen_height);

    // Step 6: Initialize Glew, to access the modern opengl way
    // of using vertex shaders and fragment shaders
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to Initialize glew\n";
        return EXIT_FAILURE;
    }

    // New code
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Step 7; Autocreate the shader objects
    Shader our_shader(vertex_shader_path, fragment_shader_path);

    // Step 8: Define the vertex data along with color information
    // Yeah you heard it now we support it in the shader along with texture
    // support
    // clang-format off
    GLfloat vertices[] = {
        // position            // color             // Texture Coordinates
        0.5f, 0.5f, 0.0f,      1.0f, 0.0f, 0.0f,    1.0f, 1.0f,  // top right corner
        0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,    1.0f, 0.0f, // bottom right corner
        -0.5f, -0.5f, 0.0f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f, // bottom left corner
        -0.5f, 0.5f, 0.0f,     0.5f, 1.0f, 0.5f,    0.0f, 1.0f // top left corner

    };

    GLuint indices[] = {
        0, 1, 3, // First Triangle
        1, 2, 3, // Second Triangle  
    };

    // clang-format on

    // Step 9: Generate and bind a vertex buffer object and vertex array object
    // Not very clear at this point
    GLuint VBO, VAO, EBO;  // element buffer object
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    // Binding VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Binding EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
                 GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(
        0, 3, GL_FLOAT, GL_FALSE,
        8 /*4 different corners 2 for each*/ * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // Color attribute
    glVertexAttribPointer(
        1, 3, GL_FLOAT, GL_FALSE,
        8 /*4 different corners 2 for each*/ * sizeof(GLfloat),
        (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    // Texture coordinate attribute
    glVertexAttribPointer(
        2, 2, GL_FLOAT, GL_FALSE,
        8 /*4 different corners 2 for each*/ * sizeof(GLfloat),
        (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);  // Unbind VAO

    // Create texture
    GLuint texture;
    int width, height;
    // Gen texture object
    glGenTextures(1, &texture);
    // Bind texture
    glBindTexture(GL_TEXTURE_2D, texture);

    // Set texture params
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Set texture filtering
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Loading texture
    unsigned char* image =
        SOIL_load_image(texture_image_path, &width, &height, 0, SOIL_LOAD_RGBA);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, image);

    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);  // unbind

    // Step 10: Game loop
    while (!glfwWindowShouldClose(window)) {
        // Check for polling events
        glfwPollEvents();

        // Render
        // Clear the colorbuffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        our_shader.use();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glUniform1i(
            glGetUniformLocation(our_shader.shader_program, "our_texture"), 0);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // Swap the screen buffers
        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();

    return EXIT_SUCCESS;

    return 0;
}