//Practica 2
//Martinez Martinez Ivan
//Fecha de entrega: 28 de agosto del 2026
//Numero de cuenta: 320323764
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Shaders (Asegúrate de tener este encabezado y tus archivos .vs y .frag en la ruta correcta)
#include "Shader.h"

void resize(GLFWwindow* window, int width, int height);

const GLint WIDTH = 800, HEIGHT = 600;

int main() {
    glfwInit();

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Dibujo de Pato de Origami en 2D", NULL, NULL);
    glfwSetFramebufferSizeCallback(window, resize);

    // Verificación de errores de creación de ventana
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;

    // Verificación de errores de inicialización de GLEW
    if (GLEW_OK != glewInit()) {
        std::cout << "Failed to initialise GLEW" << std::endl;
        return EXIT_FAILURE;
    }

    // Información de OpenGL del sistema
    std::cout << "> Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "> Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "> Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "> SL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    // Carga y compilación de Shaders
    Shader ourShader("Shader/core.vs", "Shader/core.frag");

    // 1. Configuración de vértices de la silueta del pato de origami (Posición X,Y,Z + Color R,G,B)
    float vertices[] = {
        // --- COLA ---
        // Triángulo 1: Punta exterior cola
        -0.44f,  0.25f, 0.0f,   0.93f, 0.78f, 0.02f, // 0
        -0.46f, -0.38f, 0.0f,   0.93f, 0.78f, 0.02f, // 1
        -0.25f, -0.02f, 0.0f,   0.93f, 0.78f, 0.02f, // 2

        // Triángulo 2: Pliegue base cola
        -0.46f, -0.38f, 0.0f,   0.88f, 0.73f, 0.02f, // 3
        -0.25f, -0.45f, 0.0f,   0.88f, 0.73f, 0.02f, // 4
        -0.25f, -0.02f, 0.0f,   0.88f, 0.73f, 0.02f, // 5

        // --- CUERPO ---
        // Triángulo 3: Costado posterior
        -0.25f, -0.02f, 0.0f,   1.00f, 0.88f, 0.05f, // 6
        -0.25f, -0.45f, 0.0f,   1.00f, 0.88f, 0.05f, // 7
        -0.16f, -0.62f, 0.0f,   1.00f, 0.88f, 0.05f, // 8

        // Triángulo 4: Costado central
        -0.25f, -0.02f, 0.0f,   1.00f, 0.88f, 0.05f, // 9
        -0.16f, -0.62f, 0.0f,   1.00f, 0.88f, 0.05f, // 10
        -0.03f, -0.08f, 0.0f,   1.00f, 0.88f, 0.05f, // 11

        // Triángulo 5: Base inferior
        -0.03f, -0.08f, 0.0f,   0.95f, 0.82f, 0.04f, // 12
        -0.16f, -0.62f, 0.0f,   0.95f, 0.82f, 0.04f, // 13
         0.16f, -0.62f, 0.0f,   0.95f, 0.82f, 0.04f, // 14

         // --- PECHO Y CUELLO ---
         // Triángulo 6: Base del pecho
         -0.03f, -0.08f, 0.0f,   1.00f, 0.90f, 0.08f, // 15
          0.16f, -0.62f, 0.0f,   1.00f, 0.90f, 0.08f, // 16
          0.16f, -0.48f, 0.0f,   1.00f, 0.90f, 0.08f, // 17

          // Triángulo 7: Diamante frontal del pecho
           0.16f, -0.48f, 0.0f,   1.00f, 0.93f, 0.12f, // 18
           0.38f, -0.20f, 0.0f,   1.00f, 0.93f, 0.12f, // 19
           0.12f,  0.22f, 0.0f,   1.00f, 0.93f, 0.12f, // 20

           // Triángulo 8: Cuello frontal
           -0.03f, -0.08f, 0.0f,   1.00f, 0.90f, 0.08f, // 21
            0.16f, -0.48f, 0.0f,   1.00f, 0.90f, 0.08f, // 22
            0.12f,  0.22f, 0.0f,   1.00f, 0.90f, 0.08f, // 23

            // --- CUELLO POSTERIOR Y SOMBRA ---
            // Triángulo 9: Cuello alto
            -0.03f, -0.08f, 0.0f,   0.95f, 0.84f, 0.05f, // 24
             0.12f,  0.22f, 0.0f,   0.95f, 0.84f, 0.05f, // 25
            -0.06f,  0.35f, 0.0f,   0.95f, 0.84f, 0.05f, // 26

            // Triángulo 10: Sombra trasera del cuello
            -0.03f, -0.08f, 0.0f,   0.80f, 0.65f, 0.00f, // 27
            -0.06f,  0.35f, 0.0f,   0.80f, 0.65f, 0.00f, // 28
            -0.11f,  0.40f, 0.0f,   0.80f, 0.65f, 0.00f, // 29

            // --- CABEZA ---
            // Triángulo 11: Pliegue trasero de la cabeza
            -0.11f,  0.40f, 0.0f,   0.82f, 0.68f, 0.00f, // 30
             0.05f,  0.60f, 0.0f,   0.82f, 0.68f, 0.00f, // 31
             0.12f,  0.22f, 0.0f,   0.82f, 0.68f, 0.00f, // 32

             // Triángulo 12: Cara superior
              0.05f,  0.60f, 0.0f,   1.00f, 0.90f, 0.05f, // 33
              0.26f,  0.52f, 0.0f,   1.00f, 0.90f, 0.05f, // 34
              0.12f,  0.22f, 0.0f,   1.00f, 0.90f, 0.05f, // 35

              // Triángulo 13: Cara centro
               0.26f,  0.52f, 0.0f,   1.00f, 0.88f, 0.03f, // 36
               0.28f,  0.36f, 0.0f,   1.00f, 0.88f, 0.03f, // 37
               0.12f,  0.22f, 0.0f,   1.00f, 0.88f, 0.03f, // 38

               // Triángulo 14: Quijada
                0.28f,  0.36f, 0.0f,   0.96f, 0.84f, 0.02f, // 39
                0.28f,  0.24f, 0.0f,   0.96f, 0.84f, 0.02f, // 40
                0.12f,  0.22f, 0.0f,   0.96f, 0.84f, 0.02f, // 41

                // --- PICO ---
                // Triángulo 15: Pico naranja
                 0.28f,  0.36f, 0.0f,   0.98f, 0.45f, 0.08f, // 42
                 0.28f,  0.24f, 0.0f,   0.98f, 0.45f, 0.08f, // 43
                 0.50f,  0.37f, 0.0f,   0.98f, 0.45f, 0.08f, // 44

                 // --- OJO ---
                 // Triángulo 16: Ojo superior (negro)
                  0.17f,  0.42f, 0.0f,   0.10f, 0.10f, 0.10f, // 45
                  0.20f,  0.46f, 0.0f,   0.10f, 0.10f, 0.10f, // 46
                  0.23f,  0.42f, 0.0f,   0.10f, 0.10f, 0.10f, // 47

                  // Triángulo 17: Ojo inferior (negro)
                   0.17f,  0.42f, 0.0f,   0.10f, 0.10f, 0.10f, // 48
                   0.23f,  0.42f, 0.0f,   0.10f, 0.10f, 0.10f, // 49
                   0.20f,  0.38f, 0.0f,   0.10f, 0.10f, 0.10f, // 50

                   // Triángulo 18: Brillo del ojo (blanco)
                    0.185f, 0.435f, 0.0f,  1.00f, 1.00f, 1.00f, // 51
                    0.205f, 0.455f, 0.0f,  1.00f, 1.00f, 1.00f, // 52
                    0.205f, 0.435f, 0.0f,  1.00f, 1.00f, 1.00f  // 53
    };

    // 2. Índices para renderizar los 18 triángulos (54 vértices en total)
    unsigned int indices[] = {
         0,  1,  2, // Triángulo 1
         3,  4,  5, // Triángulo 2
         6,  7,  8, // Triángulo 3
         9, 10, 11, // Triángulo 4
        12, 13, 14, // Triángulo 5
        15, 16, 17, // Triángulo 6
        18, 19, 20, // Triángulo 7
        21, 22, 23, // Triángulo 8
        24, 25, 26, // Triángulo 9
        27, 28, 29, // Triángulo 10
        30, 31, 32, // Triángulo 11
        33, 34, 35, // Triángulo 12
        36, 37, 38, // Triángulo 13
        39, 40, 41, // Triángulo 14
        42, 43, 44, // Triángulo 15
        45, 46, 47, // Triángulo 16
        48, 49, 50, // Triángulo 17
        51, 52, 53  // Triángulo 18
    };

    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Atributo de Posición (layout = 0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // Atributo de Color (layout = 1)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Bucle de renderizado
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // Fondo gris oscuro/neutro para resaltar los pliegues
        glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ourShader.Use();

        // Renderizado de los 18 triángulos (54 índices)
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 54, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }

    // Liberación de recursos
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();
    return EXIT_SUCCESS;
}

void resize(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}