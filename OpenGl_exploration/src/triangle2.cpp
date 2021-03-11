// Second attempt at just understanding the underyling structure
// of opengl - mostly attempting what general set of rules to follow
// when writing a modern opengl program
// Again starting with a triangle drawing tutorial
// source :
// https://www.youtube.com/watch?v=EIpxcNl2WJU&list=PLRtjMdoYXLf6zUMDJVRZYV-6g6n62vet8&index=13

// Standard header
#include <iostream>

// GLEW -- opengl specific
#define GLEW_STATIC  // --> Why ?
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Window dimensions
const GLint WIDTH = 800, HEIGHT = 600;

// Defining our shader inline
// Will probably move to its own shader file,
// but for understanding its better to have a look at the code
// all at one place in order to understand the structure better
// and especially because arbitrary abstraction for wrappers over
// opengl can generally suck.
const GLchar *vertex_shader_source =
    "#version 330 core\n"
    "layout ( location = 0 ) in vec3 position;\n"
    "void main()\n"
    "{\n"
    "gl_Position = vec4( position.x, position.y, position.z, 1.0 );\n"
    "}";

const GLchar *fragment_shader_source =
    "#version 330 core\n"
    "out vec4 color;\n"
    "void main()\n"
    "{\n"
    "color = vec4( 1.0f, 0.5f, 0.2f, 1.0f );\n"  // r, g, b, a
    "}";

// At this stage we would like to some boiler plate code
// that will act as a driver for our rendering in opengl
int main(int argc, char **argv) {
    // Step 1: Initialize GLFW
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW\n";
        return EXIT_FAILURE;
    }

    // Step 2: After glfw has successfully initialized, we need to
    // set the required options (SELF NOTE: think of this
    // as the options in ceres for example)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,
                   GL_TRUE);  // --> this might be just for MAC
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Step 3: After GLFW has been initialized and options are set
    // we can create a window
    GLFWwindow *window =
        glfwCreateWindow(WIDTH, HEIGHT, "Triangle 2", nullptr, nullptr);

    if (window == nullptr) {
        std::cout << "Failed to create GLFW window\n";
        return EXIT_FAILURE;
    }

    // Step 4 : Context creation for our window
    glfwMakeContextCurrent(window);

    // Step 5: After successfull creation of window, we can get the frame buffer
    // size from it
    int screen_width, screen_height;
    glfwGetFramebufferSize(window, &screen_width, &screen_height);

    // Step 6: After doing all the nice stuff with GLFW, we can also initialize
    // glew
    glewExperimental =
        GL_TRUE;  // This is set to true so GLEW knows to use a modern
    // approach to retrieve function pointers and extensions. If I am guessing
    // correctly it is basically for retrieveing vertex/fragment shaders

    // Initialize GLEW to setup the OpenGl function pointers
    if (glewInit() != GLEW_OK) {
        std::cout << "Failed to Initialize GLEW\n";
        return EXIT_FAILURE;
    }

    // Step 7 : Define the viewport dimensions
    glViewport(0, 0, screen_width, screen_height);

    // Step 8 : Load and compile vertex shader objects
    // this is the way of modern opengl
    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source, nullptr);
    glCompileShader(vertex_shader);

    // Check for any compilation errors
    GLint success;
    GLchar info_log[512];

    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(vertex_shader, 512, nullptr, info_log);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                  << info_log << "\n";
        return EXIT_FAILURE;
    }

    // Step 9: Load and compile fragment shader objects
    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source, nullptr);
    glCompileShader(fragment_shader);

    // Check for any compilation erros
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment_shader, 512, nullptr, info_log);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                  << info_log << "\n";
        return EXIT_FAILURE;
    }

    // Step 10: Link the shaders
    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    // As usual check for any compilation errors
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success) {
        // Get the info log
        glGetProgramInfoLog(shader_program, 512, nullptr, info_log);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                  << info_log << "\n";
        return EXIT_FAILURE;
    }

    // Step 11: Clean up of the intermediary objects
    // This is necessary since at this stage we would have already
    // linked the shaders to the program and they individual shaders
    // are not needed anymore
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    // Step 12: Create the vertex data
    // clang-format off
    GLfloat vertices[] = 
    {
        -0.5f, -0.5f, 0.0f, // bottom left 
        0.5f, -0.5f, 0.0f, // bottom right
        0.0f, 0.5f, 0.0f // top 
    };
    // clang-format on

    // Step 13: Generate and bind a vertex buffer object and vertex array object
    // Not very clear at this point
    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
                          (GLvoid *)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    // Step 14: Game loop
    while (!glfwWindowShouldClose(window)) {
        // Check for polling events
        glfwPollEvents();

        // Render
        // Clear the colorbuffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader_program);
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