//Practica 8
//Martinez Martinez Ivan
//Fecha de entrega: 04/10/2026
//Número de cuenta: 320323764


// Std. Includes
#include <string>
#include <iostream>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GL includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other Libs
#include "SOIL2/SOIL2.h"
#include "stb_image.h"

// Properties
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Function prototypes
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void DoMovement();

// Camera
Camera camera(glm::vec3(0.0f, 2.0f, 8.0f));
bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;

// Timing
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

// --- VARIABLES PARA EL CICLO DÍA Y NOCHE ---
// Empezamos al mediodía (Pi/2 = 90 grados hacia arriba)
float timeOfDay = glm::half_pi<float>();
float timeSpeed = 1.0f;
float sunRadius = 15.0f;    // Distancia de los astros al centro

int main()
{
    // Init GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Martinez Martinez Ivan", nullptr, nullptr);
    if (nullptr == window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);
    glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);
    glfwSetKeyCallback(window, KeyCallback);
    glfwSetCursorPosCallback(window, MouseCallback);

    glewExperimental = GL_TRUE;
    if (GLEW_OK != glewInit()) return EXIT_FAILURE;

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glEnable(GL_DEPTH_TEST);

    // Setup shaders
    Shader lightingShader("Shader/lighting.vs", "Shader/lighting.frag");
    Shader lampshader("Shader/lamp.vs", "Shader/lamp.frag");

    // --- CARGA DE MODELOS ---
    Model dog((char*)"Models/RedDog.obj");
    Model road((char*)"Models/Road.obj");
    Model Mesa((char*)"Models/mesa.obj");
    Model Espagueti((char*)"Models/Bread.obj");
    Model Plato((char*)"Models/Plate.obj");
    Model vela((char*)"Models/objCandle.obj");

    // --- VÉRTICES PARA LOS CUBOS (SOL Y LUNA TIPO MINECRAFT) ---
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.5f, -0.5f, -0.5f,  0.5f,  0.5f, -0.5f,  0.5f,  0.5f, -0.5f, -0.5f,  0.5f, -0.5f, -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,  0.5f, -0.5f,  0.5f,  0.5f,  0.5f,  0.5f,  0.5f,  0.5f,  0.5f, -0.5f,  0.5f,  0.5f, -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f, -0.5f,  0.5f, -0.5f, -0.5f, -0.5f, -0.5f, -0.5f, -0.5f, -0.5f, -0.5f, -0.5f,  0.5f, -0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,  0.5f,  0.5f, -0.5f,  0.5f, -0.5f, -0.5f,  0.5f, -0.5f, -0.5f,  0.5f, -0.5f,  0.5f,  0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,  0.5f, -0.5f, -0.5f,  0.5f, -0.5f,  0.5f,  0.5f, -0.5f,  0.5f, -0.5f, -0.5f,  0.5f, -0.5f, -0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,  0.5f,  0.5f, -0.5f,  0.5f,  0.5f,  0.5f,  0.5f,  0.5f,  0.5f, -0.5f,  0.5f,  0.5f, -0.5f,  0.5f, -0.5f
    };
    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    glm::mat4 projection = glm::perspective(camera.GetZoom(), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);

    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwPollEvents();
        DoMovement();

        // --- 1. MATEMÁTICAS (POSICIÓN SOL Y LUNA) ---
        float sunX = cos(timeOfDay) * sunRadius;
        float sunY = sin(timeOfDay) * sunRadius;
        float sunZ = 5.0f;

        float moonX = cos(timeOfDay + glm::pi<float>()) * sunRadius;
        float moonY = sin(timeOfDay + glm::pi<float>()) * sunRadius;
        float moonZ = 5.0f;

        // Color del cielo 
        float skyFactor = (sin(timeOfDay) + 1.0f) / 2.0f;
        glm::vec3 daySky(0.4f, 0.6f, 0.9f);
        glm::vec3 nightSky(0.02f, 0.02f, 0.08f);
        glm::vec3 currentSky = glm::mix(nightSky, daySky, skyFactor);

        glClearColor(currentSky.r, currentSky.g, currentSky.b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // --- 2. LÓGICA DE LUZ PRINCIPAL ---
        lightingShader.Use();
        GLint lightPosLoc = glGetUniformLocation(lightingShader.Program, "light.position");
        GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");

        glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);

        glm::vec3 activeAmbient, activeDiffuse, activeSpecular;

        if (sunY >= 0.0f) // ES DE DÍA
        {
            float intensity = sunY / sunRadius;
            glUniform3f(lightPosLoc, sunX, sunY, sunZ);

            activeAmbient = glm::vec3(0.3f, 0.3f, 0.3f) * intensity;
            activeDiffuse = glm::vec3(0.9f, 0.9f, 0.8f) * intensity;
            activeSpecular = glm::vec3(0.5f, 0.5f, 0.5f) * intensity;
        }
        else // ES DE NOCHE
        {
            float intensity = moonY / sunRadius;
            glUniform3f(lightPosLoc, moonX, moonY, moonZ);

            activeAmbient = glm::vec3(0.1f, 0.1f, 0.15f) + (glm::vec3(0.1f, 0.1f, 0.2f) * intensity);
            activeDiffuse = glm::vec3(0.2f, 0.3f, 0.6f) * intensity;
            activeSpecular = glm::vec3(0.1f, 0.1f, 0.3f) * intensity;
        }

        glUniform3f(glGetUniformLocation(lightingShader.Program, "light.ambient"), activeAmbient.x, activeAmbient.y, activeAmbient.z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "light.diffuse"), activeDiffuse.x, activeDiffuse.y, activeDiffuse.z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "light.specular"), activeSpecular.x, activeSpecular.y, activeSpecular.z);

        // Materiales genéricos
        glUniform3f(glGetUniformLocation(lightingShader.Program, "material.ambient"), 0.8f, 0.8f, 0.8f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 0.8f, 0.8f, 0.8f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "material.specular"), 0.2f, 0.2f, 0.2f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 32.0f);

        glm::mat4 view = camera.GetViewMatrix();
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

        // --- 3. DIBUJAR LA ESCENA ---
        glm::mat4 modelRoad(1.0f);
        modelRoad = glm::translate(modelRoad, glm::vec3(0.0f, -1.0f, 0.0f));
        modelRoad = glm::scale(modelRoad, glm::vec3(2.0f, 1.0f, 2.0f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelRoad));
        road.Draw(lightingShader);

        glm::mat4 modelDog1(1.0f);
        modelDog1 = glm::translate(modelDog1, glm::vec3(-4.5f, 1.2f, 0.0f));
        modelDog1 = glm::scale(modelDog1, glm::vec3(5.0f, 5.0f, 5.0f));
        modelDog1 = glm::rotate(modelDog1, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelDog1));
        dog.Draw(lightingShader);

        glm::mat4 modelDog2(1.0f);
        modelDog2 = glm::translate(modelDog2, glm::vec3(4.5f, 1.2f, 0.0f));
        modelDog2 = glm::scale(modelDog2, glm::vec3(5.0f, 5.0f, 5.0f));
        modelDog2 = glm::rotate(modelDog2, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelDog2));
        dog.Draw(lightingShader);

        glm::mat4 modelMesa(1.0f);
        modelMesa = glm::translate(modelMesa, glm::vec3(0.0f, -0.5f, -0.7f));
        modelMesa = glm::scale(modelMesa, glm::vec3(0.8f, 0.8f, 0.8f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelMesa));
        Mesa.Draw(lightingShader);

        glm::mat4 modelPlato(1.0f);
        modelPlato = glm::translate(modelPlato, glm::vec3(-0.5f, 1.3f, 0.0f));
        modelPlato = glm::scale(modelPlato, glm::vec3(0.4f, 0.4f, 0.4f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelPlato));
        Plato.Draw(lightingShader);

        glm::mat4 modelEspagueti(1.0f);
        modelEspagueti = glm::translate(modelEspagueti, glm::vec3(-0.5f, 1.4f, 0.0f));
        modelEspagueti = glm::scale(modelEspagueti, glm::vec3(0.1f, 0.1f, 0.1f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelEspagueti));
        Espagueti.Draw(lightingShader);

        glm::mat4 modelVela(1.0f);
        modelVela = glm::translate(modelVela, glm::vec3(0.5f, 1.3f, 1.5f));
        modelVela = glm::scale(modelVela, glm::vec3(0.3f, 0.3f, 0.3f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelVela));
        vela.Draw(lightingShader);

        // =======================================================
        // --- 4. DIBUJAR LOS CUBOS (ASTROS ESTILO MINECRAFT) ---
        // =======================================================
        lampshader.Use();
        glUniformMatrix4fv(glGetUniformLocation(lampshader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(lampshader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

        glBindVertexArray(VAO);

        // 4a. Dibujar el SOL
        glm::mat4 modelSun = glm::mat4(1.0f);
        modelSun = glm::translate(modelSun, glm::vec3(sunX, sunY, sunZ));
        modelSun = glm::scale(modelSun, glm::vec3(1.5f)); // Sol grandote
        glUniformMatrix4fv(glGetUniformLocation(lampshader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelSun));

        // Efecto atardecer: Se vuelve naranja
        float solFactor = glm::clamp(sunY / sunRadius, 0.0f, 1.0f);
        glm::vec3 sunColor = glm::mix(glm::vec3(1.0f, 0.4f, 0.0f), glm::vec3(1.0f, 1.0f, 0.8f), solFactor);
        glUniform3f(glGetUniformLocation(lampshader.Program, "lampColor"), sunColor.r, sunColor.g, sunColor.b);

        glDrawArrays(GL_TRIANGLES, 0, 36);

        // 4b. Dibujar la LUNA
        glm::mat4 modelMoon = glm::mat4(1.0f);
        modelMoon = glm::translate(modelMoon, glm::vec3(moonX, moonY, moonZ));
        modelMoon = glm::scale(modelMoon, glm::vec3(0.9f)); // Luna más pequeña
        glUniformMatrix4fv(glGetUniformLocation(lampshader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelMoon));

        // Color de luna: Azulado brillante
        glUniform3f(glGetUniformLocation(lampshader.Program, "lampColor"), 0.8f, 0.9f, 1.0f);

        glDrawArrays(GL_TRIANGLES, 0, 36);

        glBindVertexArray(0);
        // =======================================================

        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
    return 0;
}

void DoMovement()
{
    if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP]) camera.ProcessKeyboard(FORWARD, deltaTime);
    if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN]) camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT]) camera.ProcessKeyboard(LEFT, deltaTime);
    if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT]) camera.ProcessKeyboard(RIGHT, deltaTime);

    // Controles de Tiempo (Día y Noche)
    if (keys[GLFW_KEY_L])
    {
        timeOfDay -= timeSpeed * deltaTime;
        if (timeOfDay < 0.0f) timeOfDay += glm::two_pi<float>();
    }
    if (keys[GLFW_KEY_O])
    {
        timeOfDay += timeSpeed * deltaTime;
        if (timeOfDay > glm::two_pi<float>()) timeOfDay -= glm::two_pi<float>();
    }
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
        glfwSetWindowShouldClose(window, GL_TRUE);

    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS) keys[key] = true;
        else if (action == GLFW_RELEASE) keys[key] = false;
    }
}

void MouseCallback(GLFWwindow* window, double xPos, double yPos)
{
    if (firstMouse)
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }

    GLfloat xOffset = xPos - lastX;
    GLfloat yOffset = lastY - yPos;

    lastX = xPos;
    lastY = yPos;

    camera.ProcessMouseMovement(xOffset, yOffset);
}