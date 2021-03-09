// Include standard headers
#include <cstdio>
#include <cstdlib>

// Inclue GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <shader.h>
#include <texture.h>

// Global variables :
// this is primarily to be a substitute for a future class
// member
GLFWwindow* window;
static const int width = 1024;
static const int height = 768;
static const char* title = "Textured cube";
static const float bg_color_r = 0.0f;
static const float bg_color_g = 0.0f;
static const float bg_color_b = 0.4f;
static const float bg_color_a = 0.0f;  // find out why alpha value is 0

void windowHintSubRoutine() {
    // Some basic routine about window hints
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void openWindow() {
    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (window == nullptr) {
        std::cerr << "Failed to open GLFW window.\n";
        glfwTerminate();
    }
}

void ensureEscapeKeyCapture() {
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
}

void setBackGroundColor() {
    // Setting to Dark blue color
    glClearColor(bg_color_r, bg_color_g, bg_color_b, bg_color_a);
}

void setDepthRelatedProps() {
    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);
}

GLuint getVertexArrayID() {
    GLuint vertex_array_id;
    glGenVertexArrays(1, &vertex_array_id);
    glBindVertexArray(vertex_array_id);

    return vertex_array_id;
}

GLuint getProgramIDForTexture() {
    GLuint program_id = loadShaders(
        "/home/kartik/Documents/Motley/OpenGl_exploration/src/"
        "TransformVertexShader.vertexshader",
        "/home/kartik/Documents/Motley/OpenGl_exploration/src/"
        "TextureFragmentShader.fragmentshader");
    return program_id;
}

glm::mat4 getProjectionMatrix() {
    return glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
}

glm::mat4 getViewMatrix() {
    return glm::lookAt(
        glm::vec3(4, 3, 3),  // Camera is at (4, 3, 3) in world space
        glm::vec3(0, 0, 0),  // and looks at origin
        glm::vec3(0, 1, 0)   // Head is up
    );
}

glm::mat4 getModelMatrix() { return glm::mat4(1.0f); }

GLuint getTexture() {
    return loadDDS(
        "/home/kartik/Documents/Motley/OpenGl_exploration/src/uvtemplate.DDS");
}

int main(int argc, char** argv) {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    // window hint subroutine
    windowHintSubRoutine();

    // Open a window
    openWindow();

    // create opengl context for the above window
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = true;  // Needed for core profile
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW\n";
        return -1;
    }

    // Ensure that we can capture press of escape key
    ensureEscapeKeyCapture();

    // set Background color
    setBackGroundColor();

    // set Depth related properties
    setDepthRelatedProps();

    // Create a vertex array id
    GLuint vertex_array_id = getVertexArrayID();

    // Get program id
    GLuint program_id = getProgramIDForTexture();

    // Get a handle for out "MVP" uniform
    GLuint matrix_id = glGetUniformLocation(program_id, "MVP");

    // Get projection matrix
    glm::mat4 projection_matrix = getProjectionMatrix();

    // Get view matrix for the camera
    glm::mat4 view_matrix = getViewMatrix();

    // Get model matrix
    glm::mat4 model_matrix = getModelMatrix();

    // Finally compile the model view projection matrix
    glm::mat4 MVP = projection_matrix * view_matrix * model_matrix;

    // Get texture
    GLuint texture = getTexture();

    // Get a handle for our  "myTextureSampler" uniform
    GLuint textured_id = glGetUniformLocation(program_id, "myTextureSampler");

    // Our vertices. Tree consecutive floats give a 3D vertex; Three consecutive
    // vertices give a triangle. A cube has 6 faces with 2 triangles each, so
    // this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat g_vertex_buffer_data[] = {
        -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,  -1.0f, 1.0f,  1.0f,  1.0f,
        1.0f,  -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,  -1.0f, 1.0f,  -1.0f,
        1.0f,  -1.0f, -1.0f, -1.0f, 1.0f,  -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f,
        1.0f,  -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f,
        1.0f,  1.0f,  -1.0f, 1.0f,  -1.0f, 1.0f,  -1.0f, 1.0f,  -1.0f, -1.0f,
        1.0f,  -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f, -1.0f, 1.0f,
        1.0f,  -1.0f, 1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  -1.0f, -1.0f, 1.0f,
        1.0f,  -1.0f, 1.0f,  -1.0f, -1.0f, 1.0f,  1.0f,  1.0f,  1.0f,  -1.0f,
        1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  -1.0f, -1.0f, 1.0f,  -1.0f,
        1.0f,  1.0f,  1.0f,  -1.0f, 1.0f,  -1.0f, -1.0f, 1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  -1.0f, 1.0f,  1.0f,  1.0f,  -1.0f, 1.0f};

    // Two UV coordinatesfor each vertex. They were created with Blender.
    static const GLfloat g_uv_buffer_data[] = {
        0.000059f, 1.0f - 0.000004f, 0.000103f, 1.0f - 0.336048f,
        0.335973f, 1.0f - 0.335903f, 1.000023f, 1.0f - 0.000013f,
        0.667979f, 1.0f - 0.335851f, 0.999958f, 1.0f - 0.336064f,
        0.667979f, 1.0f - 0.335851f, 0.336024f, 1.0f - 0.671877f,
        0.667969f, 1.0f - 0.671889f, 1.000023f, 1.0f - 0.000013f,
        0.668104f, 1.0f - 0.000013f, 0.667979f, 1.0f - 0.335851f,
        0.000059f, 1.0f - 0.000004f, 0.335973f, 1.0f - 0.335903f,
        0.336098f, 1.0f - 0.000071f, 0.667979f, 1.0f - 0.335851f,
        0.335973f, 1.0f - 0.335903f, 0.336024f, 1.0f - 0.671877f,
        1.000004f, 1.0f - 0.671847f, 0.999958f, 1.0f - 0.336064f,
        0.667979f, 1.0f - 0.335851f, 0.668104f, 1.0f - 0.000013f,
        0.335973f, 1.0f - 0.335903f, 0.667979f, 1.0f - 0.335851f,
        0.335973f, 1.0f - 0.335903f, 0.668104f, 1.0f - 0.000013f,
        0.336098f, 1.0f - 0.000071f, 0.000103f, 1.0f - 0.336048f,
        0.000004f, 1.0f - 0.671870f, 0.336024f, 1.0f - 0.671877f,
        0.000103f, 1.0f - 0.336048f, 0.336024f, 1.0f - 0.671877f,
        0.335973f, 1.0f - 0.335903f, 0.667969f, 1.0f - 0.671889f,
        1.000004f, 1.0f - 0.671847f, 0.667979f, 1.0f - 0.335851f};

    return 0;
}