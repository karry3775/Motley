#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/freeglut.h>
#include <iostream>

#include <glog/logging.h>
#include <string>

// source :
// https://www.geeksforgeeks.org/rendering-triangle-using-openglusing-shaders/

std::string vertex_shader =
    "#version 430\n"
    "in vec3 pos;"
    "void main() {"
    "gl_Position = vec4(pos, 1);"
    "}";
std::string fragment_shader =
    "#version 430\n"
    "void main() {"
    "gl_FragColor = vec4(1, 0, 0, 1);"
    "}";

// Compile and create shader object and returns its id
GLuint compileShaders(std::string shader, GLenum type) {
    const char* shader_code = shader.c_str();
    GLuint shader_id = glCreateShader(type);

    if (shader_id == 0) {
        std::cout << "Error creating shaders\n";
        return 0;
    }

    // Attach source code to this object
    glShaderSource(shader_id, 1, &shader_code, nullptr);
    glCompileShader(shader_id);  // compile the shader object

    GLint compile_status;

    // check for compilation status
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compile_status);

    if (!compile_status) {  // If compilation was not successful
        int length;
        glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &length);
        char* c_message = new char[length];

        // Get additional information
        glGetShaderInfoLog(shader_id, length, &length, c_message);
        std::cout << "Cannot compile shader: " << c_message << std::endl;
        delete[] c_message;
        glDeleteShader(shader_id);
        return 0;
    }

    return shader_id;
}

// Creates a program containing vertex and fragment shader and links
// it and returns its 1D
GLuint linkProgram(GLuint vertex_shader_id, GLuint fragment_shader_id) {
    GLuint program_id = glCreateProgram();  // create a program

    if (program_id == 0) {
        std::cout << "Error creating shader program\n";
        return 0;
    }

    // Attach both the shaders to it
    glAttachShader(program_id, vertex_shader_id);
    glAttachShader(program_id, fragment_shader_id);

    // Create executable of this program
    glLinkProgram(program_id);

    GLint link_status;

    // Get the link status of this program
    glGetProgramiv(program_id, GL_LINK_STATUS, &link_status);

    if (!link_status) {  // if the linking failed
        std::cout << "Error linking program\n";
        glDetachShader(program_id, vertex_shader_id);
        glDetachShader(program_id, fragment_shader_id);
        glDeleteProgram(program_id);

        return 0;
    }

    return program_id;
}

// Load data in VBO and return the vbo's id
GLuint loadDataInBuffers() {
    // clang-format off
    GLfloat vertices[] = {-0.7, -0.7, 0, 
                           0.7, -0.7, 0, 
                           0, 0.7, 0};
    // clang-format on
    GLuint vbo_id;

    // allocate buffer space and pass data to it
    glGenBuffers(1, &vbo_id);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // unbind active buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return vbo_id;
}

// Initialize and put everything together
void init() {
    // clear the frameBuffer each frame with black color
    glClearColor(0, 0, 0, 0);

    GLuint vbo_id = loadDataInBuffers();

    GLuint v_shader_id = compileShaders(vertex_shader, GL_VERTEX_SHADER);
    GLuint f_shader_id = compileShaders(fragment_shader, GL_FRAGMENT_SHADER);

    GLuint program_id = linkProgram(v_shader_id, f_shader_id);

    // Get the 'pos' variable location inside this program
    GLuint pos_attribute_position = glGetAttribLocation(program_id, "pos");

    GLuint vao_id;
    glGenVertexArrays(1, &vao_id);  // Generate VAO

    // Bind it so that rest of the vao operations affect this vao
    glBindVertexArray(vao_id);

    // buffer from which 'pos' will recieve its data and the format of that data
    glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
    glVertexAttribPointer(pos_attribute_position, 3, GL_FLOAT, false, 0, 0);

    // Enable this attribute array linked to 'pos'
    glEnableVertexAttribArray(pos_attribute_position);

    // Use this program for rendering
    glUseProgram(program_id);
}

// Funtion that does the drawing
// glut call this function whenever it needs to redraw
void display() {
    // clear the color buffer before each drawing
    glClear(GL_COLOR_BUFFER_BIT);

    // draw triangles starting from index 0 using 3 indices
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // swap the buffers and hence show the buffers
    // content to the screen
    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 50);
    glutCreateWindow("Triangle using opengl!");
    glewInit();

    init();

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}