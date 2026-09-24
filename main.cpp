#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>

#include "objloader.hpp"

//Arina Sabzevari (40205861)
//Parsa Ghadimi (40203370)
//Zineb Alaoui Aziz (40215844)

GLFWwindow* window;

// Initial transformation values
glm::vec3 scale(1.0f);
glm::vec3 position(0.0f, 0.0f, 0.0f);
float rotationY = 0.0f;

void processInput(GLFWwindow* window) {
    float d = 0.05f;
    float rotationSpeed = 0.5f;
    float scaleStep = 0.05f;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // Translation
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) position.y += d;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) position.y -= d;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) position.x -= d;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) position.x += d;

    // Rotation
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) rotationY += rotationSpeed;
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) rotationY -= rotationSpeed;

    // Scaling
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
        scale += glm::vec3(scaleStep);

    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
        scale -= glm::vec3(scaleStep);
        // Prevent scale from going negative or too small
        if (scale.x < 0.1f) scale = glm::vec3(0.1f);
    }

    // Reset all
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        position = glm::vec3(0.0f);
        scale = glm::vec3(1.0f);
        rotationY = 0.0f;
    }
}

int main() {
    if (!glfwInit()) return -1;

    window = glfwCreateWindow(800, 600, "Cybertruck Viewer", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glewInit();

    glEnable(GL_DEPTH_TEST);

    std::vector<glm::vec3> vertices;
    std::vector<unsigned int> indices;
    if (!loadOBJ("tri.obj", vertices, indices)) {
        std::cerr << "Failed to load OBJ file.\n";
        return -1;
    }
    std::cout << "Loaded " << vertices.size() << " vertices and " << indices.size() / 3 << " faces.\n";

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Projection
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f/600.0f, 0.1f, 100.0f);
        glLoadMatrixf(glm::value_ptr(projection));

        // View and Model
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, position);
        model = glm::rotate(model, glm::radians(rotationY), glm::vec3(0, 1, 0));
        model = glm::scale(model, scale);
        glm::mat4 mvp = view * model;
        glLoadMatrixf(glm::value_ptr(mvp));

        // Wireframe rendering
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glColor3f(0.0f, 1.0f, 0.0f);
        glBegin(GL_TRIANGLES);
        for (size_t i = 0; i < indices.size(); ++i) {
            glm::vec3 v = vertices[indices[i]];
            glVertex3f(v.x, v.y, v.z);
        }
        glEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}


// g++ main.cpp objloader.cpp -o cybertruck_viewer \
  -std=c++11 -stdlib=libc++ \
  -I/opt/homebrew/include \
  -L/opt/homebrew/lib \
  -lglfw -lGLEW -framework OpenGL

// ./cybertruck_viewer