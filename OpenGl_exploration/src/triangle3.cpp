// This file builds upon the triangle2 file
// and abstracts out the shader creation and compilation
// calls

// We will start with the standard header
#include <iostream>
// NOTE: Order matters here GLEW first and then GLFW
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>

#include <shader2.h>

// Window dimensions
const GLint WIDTH = 800, HEIGHT = 600;

void enableGLFWOptions() {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
}

int main(int argc, char** argv) {
    // Step 1: Initialize the GLFW
    if (!glfwInit()) {
        std::cerr << "Unable to initialize GLFW\n";
        return EXIT_FAILURE;
    }

    // Step 2: Provide options for glfw
    enableGLFWOptions();

    // Step 3: Now we can create the window thing
    GLFWwindow* window =
        glfwCreateWindow(WIDTH, HEIGHT, "Triangle 3", nullptr, nullptr);

    // Step 4: Check if the thing was created successfully
    if (window == nullptr) {
        std::cerr << "Failed to create window\n";
        return EXIT_FAILURE;
    }

    // Step 5: If the window was created we need to create context
    glfwMakeContextCurrent(window);

    // Step 6: We would have successfully created the window at this point
    // and now we cn extract the screen_width and screen_height from it
    int screen_width, screen_height;
    glfwGetFramebufferSize(window, &screen_width, &screen_height);

    // Step 7: Initialize glew, this is what is going to allow
    // us interact with all the nice fragment and shader sources
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Unable to initialize glew\n";
        return EXIT_FAILURE;
        // temp: Do we need to remove the window at this point
    }

    // Step 8: Define the view port dimensions this is why we used the
    // glfwGetFrame BufferSize command to gete the screen_width and
    // screen_height
    glViewport(0, 0, screen_width, screen_height);

    Shader our_shader("core.vs", "core.frag");

    // Step 13: Create the vertex data
    // clang-format off
    GLfloat vertices[] = 
    {
        // position            // color
        -0.5f, -0.5f, 0.0f,    1.0f, 0.0f, 0.0f,// bottom left
        0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f, // bottom right
        0.0f, 0.5f, 0.0f,      0.0f, 0.0f, 1.0f, // middle top 
    };
    // clang-format on

    // Step 14: Generate and bind a vertex buffer object and vertex array object
    // Not very clear at this point
    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
                          (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
                          (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    // Step 15: Game loop
    while (!glfwWindowShouldClose(window)) {
        // Check for polling events
        glfwPollEvents();

        // Render
        // Clear the colorbuffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        our_shader.use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        // Swap the screen buffers
        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();

    return EXIT_SUCCESS;
}
