#include <example1.h>

namespace example_1 {

Example1::Example1() {
    // TODO
}

bool Example1::run() {
    // Initialize GLFW
    glewExperimental = true;  // Needed for core profile

    if (!glfwInit()) {
        LOG(FATAL) << "Failed to Initialize GLFW\n";
        return false;
    }

    createWindow();

    return true;
}

bool Example1::createWindow() {
    glfwWindowHint(GLFW_SAMPLES, 4);                // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,
                   GLFW_OPENGL_CORE_PROFILE);  // We don't want the old OpenGL

    // Open a window and create its OpenGl context
    GLFWwindow* window;
    window = glfwCreateWindow(1024, 768, "Example 1", nullptr, nullptr);

    if (window == nullptr) {
        LOG(FATAL) << "Failed to open GLFW window, If you have an Intel GPU, "
                      "they are not 3.3 compatible. Try the 2.1 version";
        return false;
    }

    glfwMakeContextCurrent(window);  // Initialize GLEW
    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        LOG(FATAL) << "Failed to Initialize GLEW\n";
        return false;
    }

    // Ensure we can capture the escape key being pressed
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    do {
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }  // CHeck if the ESC key was pressed or the window was closed
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0);

    return true;
}

}  // namespace example_1