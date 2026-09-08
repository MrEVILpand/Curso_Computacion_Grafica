//Practica 4
//Martinez Martinez Ivan
//Fecha de entrega: 11 de septiembre de 2026
//Numero de cuenta: 320323764
#include<iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Shaders
#include "Shader.h"

void Inputs(GLFWwindow* window);

const GLint WIDTH = 800, HEIGHT = 600;
float movX = 0.0f;
float movY = 0.0f;
float movZ = -5.0f;
float rot = 0.0f;

int main() {
	glfwInit();
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Martinez Martinez Ivan", nullptr, nullptr);

	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	if (nullptr == window) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	glViewport(0, 0, screenWidth, screenHeight);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Usamos TUS SHADERS ORIGINALES (sin modificarlos)
	Shader ourShader("Shader/core.vs", "Shader/core.frag");

	// ARREGLO MAESTRO: 9 Cubos diferentes de color sólido (324 vértices en total)
	float vertices[] = {
		// 1. CUBO BLANCO (Gallina) - Grisáceo para resaltar del fondo | Vértices 0 a 35
		-0.5f,-0.5f, 0.5f, 0.90f,0.90f,0.90f,   0.5f,-0.5f, 0.5f, 0.90f,0.90f,0.90f,   0.5f, 0.5f, 0.5f, 0.90f,0.90f,0.90f,   0.5f, 0.5f, 0.5f, 0.90f,0.90f,0.90f,  -0.5f, 0.5f, 0.5f, 0.90f,0.90f,0.90f,  -0.5f,-0.5f, 0.5f, 0.90f,0.90f,0.90f,
		-0.5f,-0.5f,-0.5f, 0.90f,0.90f,0.90f,   0.5f,-0.5f,-0.5f, 0.90f,0.90f,0.90f,   0.5f, 0.5f,-0.5f, 0.90f,0.90f,0.90f,   0.5f, 0.5f,-0.5f, 0.90f,0.90f,0.90f,  -0.5f, 0.5f,-0.5f, 0.90f,0.90f,0.90f,  -0.5f,-0.5f,-0.5f, 0.90f,0.90f,0.90f,
		-0.5f, 0.5f, 0.5f, 0.90f,0.90f,0.90f,  -0.5f, 0.5f,-0.5f, 0.90f,0.90f,0.90f,  -0.5f,-0.5f,-0.5f, 0.90f,0.90f,0.90f,  -0.5f,-0.5f,-0.5f, 0.90f,0.90f,0.90f,  -0.5f,-0.5f, 0.5f, 0.90f,0.90f,0.90f,  -0.5f, 0.5f, 0.5f, 0.90f,0.90f,0.90f,
		 0.5f, 0.5f, 0.5f, 0.90f,0.90f,0.90f,   0.5f, 0.5f,-0.5f, 0.90f,0.90f,0.90f,   0.5f,-0.5f,-0.5f, 0.90f,0.90f,0.90f,   0.5f,-0.5f,-0.5f, 0.90f,0.90f,0.90f,   0.5f,-0.5f, 0.5f, 0.90f,0.90f,0.90f,   0.5f, 0.5f, 0.5f, 0.90f,0.90f,0.90f,
		-0.5f,-0.5f,-0.5f, 0.90f,0.90f,0.90f,   0.5f,-0.5f,-0.5f, 0.90f,0.90f,0.90f,   0.5f,-0.5f, 0.5f, 0.90f,0.90f,0.90f,   0.5f,-0.5f, 0.5f, 0.90f,0.90f,0.90f,  -0.5f,-0.5f, 0.5f, 0.90f,0.90f,0.90f,  -0.5f,-0.5f,-0.5f, 0.90f,0.90f,0.90f,
		-0.5f, 0.5f,-0.5f, 0.90f,0.90f,0.90f,   0.5f, 0.5f,-0.5f, 0.90f,0.90f,0.90f,   0.5f, 0.5f, 0.5f, 0.90f,0.90f,0.90f,   0.5f, 0.5f, 0.5f, 0.90f,0.90f,0.90f,  -0.5f, 0.5f, 0.5f, 0.90f,0.90f,0.90f,  -0.5f, 0.5f,-0.5f, 0.90f,0.90f,0.90f,

		// 2. CUBO NEGRO (Ojos) | Vértices 36 a 71
		-0.5f,-0.5f, 0.5f, 0.10f,0.10f,0.10f,   0.5f,-0.5f, 0.5f, 0.10f,0.10f,0.10f,   0.5f, 0.5f, 0.5f, 0.10f,0.10f,0.10f,   0.5f, 0.5f, 0.5f, 0.10f,0.10f,0.10f,  -0.5f, 0.5f, 0.5f, 0.10f,0.10f,0.10f,  -0.5f,-0.5f, 0.5f, 0.10f,0.10f,0.10f,
		-0.5f,-0.5f,-0.5f, 0.10f,0.10f,0.10f,   0.5f,-0.5f,-0.5f, 0.10f,0.10f,0.10f,   0.5f, 0.5f,-0.5f, 0.10f,0.10f,0.10f,   0.5f, 0.5f,-0.5f, 0.10f,0.10f,0.10f,  -0.5f, 0.5f,-0.5f, 0.10f,0.10f,0.10f,  -0.5f,-0.5f,-0.5f, 0.10f,0.10f,0.10f,
		-0.5f, 0.5f, 0.5f, 0.10f,0.10f,0.10f,  -0.5f, 0.5f,-0.5f, 0.10f,0.10f,0.10f,  -0.5f,-0.5f,-0.5f, 0.10f,0.10f,0.10f,  -0.5f,-0.5f,-0.5f, 0.10f,0.10f,0.10f,  -0.5f,-0.5f, 0.5f, 0.10f,0.10f,0.10f,  -0.5f, 0.5f, 0.5f, 0.10f,0.10f,0.10f,
		 0.5f, 0.5f, 0.5f, 0.10f,0.10f,0.10f,   0.5f, 0.5f,-0.5f, 0.10f,0.10f,0.10f,   0.5f,-0.5f,-0.5f, 0.10f,0.10f,0.10f,   0.5f,-0.5f,-0.5f, 0.10f,0.10f,0.10f,   0.5f,-0.5f, 0.5f, 0.10f,0.10f,0.10f,   0.5f, 0.5f, 0.5f, 0.10f,0.10f,0.10f,
		-0.5f,-0.5f,-0.5f, 0.10f,0.10f,0.10f,   0.5f,-0.5f,-0.5f, 0.10f,0.10f,0.10f,   0.5f,-0.5f, 0.5f, 0.10f,0.10f,0.10f,   0.5f,-0.5f, 0.5f, 0.10f,0.10f,0.10f,  -0.5f,-0.5f, 0.5f, 0.10f,0.10f,0.10f,  -0.5f,-0.5f,-0.5f, 0.10f,0.10f,0.10f,
		-0.5f, 0.5f,-0.5f, 0.10f,0.10f,0.10f,   0.5f, 0.5f,-0.5f, 0.10f,0.10f,0.10f,   0.5f, 0.5f, 0.5f, 0.10f,0.10f,0.10f,   0.5f, 0.5f, 0.5f, 0.10f,0.10f,0.10f,  -0.5f, 0.5f, 0.5f, 0.10f,0.10f,0.10f,  -0.5f, 0.5f,-0.5f, 0.10f,0.10f,0.10f,

		// 3. CUBO NARANJA (Pico) | Vértices 72 a 107
		-0.5f,-0.5f, 0.5f, 0.80f,0.50f,0.10f,   0.5f,-0.5f, 0.5f, 0.80f,0.50f,0.10f,   0.5f, 0.5f, 0.5f, 0.80f,0.50f,0.10f,   0.5f, 0.5f, 0.5f, 0.80f,0.50f,0.10f,  -0.5f, 0.5f, 0.5f, 0.80f,0.50f,0.10f,  -0.5f,-0.5f, 0.5f, 0.80f,0.50f,0.10f,
		-0.5f,-0.5f,-0.5f, 0.80f,0.50f,0.10f,   0.5f,-0.5f,-0.5f, 0.80f,0.50f,0.10f,   0.5f, 0.5f,-0.5f, 0.80f,0.50f,0.10f,   0.5f, 0.5f,-0.5f, 0.80f,0.50f,0.10f,  -0.5f, 0.5f,-0.5f, 0.80f,0.50f,0.10f,  -0.5f,-0.5f,-0.5f, 0.80f,0.50f,0.10f,
		-0.5f, 0.5f, 0.5f, 0.80f,0.50f,0.10f,  -0.5f, 0.5f,-0.5f, 0.80f,0.50f,0.10f,  -0.5f,-0.5f,-0.5f, 0.80f,0.50f,0.10f,  -0.5f,-0.5f,-0.5f, 0.80f,0.50f,0.10f,  -0.5f,-0.5f, 0.5f, 0.80f,0.50f,0.10f,  -0.5f, 0.5f, 0.5f, 0.80f,0.50f,0.10f,
		 0.5f, 0.5f, 0.5f, 0.80f,0.50f,0.10f,   0.5f, 0.5f,-0.5f, 0.80f,0.50f,0.10f,   0.5f,-0.5f,-0.5f, 0.80f,0.50f,0.10f,   0.5f,-0.5f,-0.5f, 0.80f,0.50f,0.10f,   0.5f,-0.5f, 0.5f, 0.80f,0.50f,0.10f,   0.5f, 0.5f, 0.5f, 0.80f,0.50f,0.10f,
		-0.5f,-0.5f,-0.5f, 0.80f,0.50f,0.10f,   0.5f,-0.5f,-0.5f, 0.80f,0.50f,0.10f,   0.5f,-0.5f, 0.5f, 0.80f,0.50f,0.10f,   0.5f,-0.5f, 0.5f, 0.80f,0.50f,0.10f,  -0.5f,-0.5f, 0.5f, 0.80f,0.50f,0.10f,  -0.5f,-0.5f,-0.5f, 0.80f,0.50f,0.10f,
		-0.5f, 0.5f,-0.5f, 0.80f,0.50f,0.10f,   0.5f, 0.5f,-0.5f, 0.80f,0.50f,0.10f,   0.5f, 0.5f, 0.5f, 0.80f,0.50f,0.10f,   0.5f, 0.5f, 0.5f, 0.80f,0.50f,0.10f,  -0.5f, 0.5f, 0.5f, 0.80f,0.50f,0.10f,  -0.5f, 0.5f,-0.5f, 0.80f,0.50f,0.10f,

		// 4. CUBO ROJO (Papada) | Vértices 108 a 143
		-0.5f,-0.5f, 0.5f, 0.85f,0.00f,0.00f,   0.5f,-0.5f, 0.5f, 0.85f,0.00f,0.00f,   0.5f, 0.5f, 0.5f, 0.85f,0.00f,0.00f,   0.5f, 0.5f, 0.5f, 0.85f,0.00f,0.00f,  -0.5f, 0.5f, 0.5f, 0.85f,0.00f,0.00f,  -0.5f,-0.5f, 0.5f, 0.85f,0.00f,0.00f,
		-0.5f,-0.5f,-0.5f, 0.85f,0.00f,0.00f,   0.5f,-0.5f,-0.5f, 0.85f,0.00f,0.00f,   0.5f, 0.5f,-0.5f, 0.85f,0.00f,0.00f,   0.5f, 0.5f,-0.5f, 0.85f,0.00f,0.00f,  -0.5f, 0.5f,-0.5f, 0.85f,0.00f,0.00f,  -0.5f,-0.5f,-0.5f, 0.85f,0.00f,0.00f,
		-0.5f, 0.5f, 0.5f, 0.85f,0.00f,0.00f,  -0.5f, 0.5f,-0.5f, 0.85f,0.00f,0.00f,  -0.5f,-0.5f,-0.5f, 0.85f,0.00f,0.00f,  -0.5f,-0.5f,-0.5f, 0.85f,0.00f,0.00f,  -0.5f,-0.5f, 0.5f, 0.85f,0.00f,0.00f,  -0.5f, 0.5f, 0.5f, 0.85f,0.00f,0.00f,
		 0.5f, 0.5f, 0.5f, 0.85f,0.00f,0.00f,   0.5f, 0.5f,-0.5f, 0.85f,0.00f,0.00f,   0.5f,-0.5f,-0.5f, 0.85f,0.00f,0.00f,   0.5f,-0.5f,-0.5f, 0.85f,0.00f,0.00f,   0.5f,-0.5f, 0.5f, 0.85f,0.00f,0.00f,   0.5f, 0.5f, 0.5f, 0.85f,0.00f,0.00f,
		-0.5f,-0.5f,-0.5f, 0.85f,0.00f,0.00f,   0.5f,-0.5f,-0.5f, 0.85f,0.00f,0.00f,   0.5f,-0.5f, 0.5f, 0.85f,0.00f,0.00f,   0.5f,-0.5f, 0.5f, 0.85f,0.00f,0.00f,  -0.5f,-0.5f, 0.5f, 0.85f,0.00f,0.00f,  -0.5f,-0.5f,-0.5f, 0.85f,0.00f,0.00f,
		-0.5f, 0.5f,-0.5f, 0.85f,0.00f,0.00f,   0.5f, 0.5f,-0.5f, 0.85f,0.00f,0.00f,   0.5f, 0.5f, 0.5f, 0.85f,0.00f,0.00f,   0.5f, 0.5f, 0.5f, 0.85f,0.00f,0.00f,  -0.5f, 0.5f, 0.5f, 0.85f,0.00f,0.00f,  -0.5f, 0.5f,-0.5f, 0.85f,0.00f,0.00f,

		// 5. CUBO AMARILLO (Patas) | Vértices 144 a 179
		-0.5f,-0.5f, 0.5f, 0.85f,0.75f,0.30f,   0.5f,-0.5f, 0.5f, 0.85f,0.75f,0.30f,   0.5f, 0.5f, 0.5f, 0.85f,0.75f,0.30f,   0.5f, 0.5f, 0.5f, 0.85f,0.75f,0.30f,  -0.5f, 0.5f, 0.5f, 0.85f,0.75f,0.30f,  -0.5f,-0.5f, 0.5f, 0.85f,0.75f,0.30f,
		-0.5f,-0.5f,-0.5f, 0.85f,0.75f,0.30f,   0.5f,-0.5f,-0.5f, 0.85f,0.75f,0.30f,   0.5f, 0.5f,-0.5f, 0.85f,0.75f,0.30f,   0.5f, 0.5f,-0.5f, 0.85f,0.75f,0.30f,  -0.5f, 0.5f,-0.5f, 0.85f,0.75f,0.30f,  -0.5f,-0.5f,-0.5f, 0.85f,0.75f,0.30f,
		-0.5f, 0.5f, 0.5f, 0.85f,0.75f,0.30f,  -0.5f, 0.5f,-0.5f, 0.85f,0.75f,0.30f,  -0.5f,-0.5f,-0.5f, 0.85f,0.75f,0.30f,  -0.5f,-0.5f,-0.5f, 0.85f,0.75f,0.30f,  -0.5f,-0.5f, 0.5f, 0.85f,0.75f,0.30f,  -0.5f, 0.5f, 0.5f, 0.85f,0.75f,0.30f,
		 0.5f, 0.5f, 0.5f, 0.85f,0.75f,0.30f,   0.5f, 0.5f,-0.5f, 0.85f,0.75f,0.30f,   0.5f,-0.5f,-0.5f, 0.85f,0.75f,0.30f,   0.5f,-0.5f,-0.5f, 0.85f,0.75f,0.30f,   0.5f,-0.5f, 0.5f, 0.85f,0.75f,0.30f,   0.5f, 0.5f, 0.5f, 0.85f,0.75f,0.30f,
		-0.5f,-0.5f,-0.5f, 0.85f,0.75f,0.30f,   0.5f,-0.5f,-0.5f, 0.85f,0.75f,0.30f,   0.5f,-0.5f, 0.5f, 0.85f,0.75f,0.30f,   0.5f,-0.5f, 0.5f, 0.85f,0.75f,0.30f,  -0.5f,-0.5f, 0.5f, 0.85f,0.75f,0.30f,  -0.5f,-0.5f,-0.5f, 0.85f,0.75f,0.30f,
		-0.5f, 0.5f,-0.5f, 0.85f,0.75f,0.30f,   0.5f, 0.5f,-0.5f, 0.85f,0.75f,0.30f,   0.5f, 0.5f, 0.5f, 0.85f,0.75f,0.30f,   0.5f, 0.5f, 0.5f, 0.85f,0.75f,0.30f,  -0.5f, 0.5f, 0.5f, 0.85f,0.75f,0.30f,  -0.5f, 0.5f,-0.5f, 0.85f,0.75f,0.30f,

		// 6. CUBO MORADO (Pantalones) | Vértices 180 a 215
		-0.5f,-0.5f, 0.5f, 0.28f,0.22f,0.44f,   0.5f,-0.5f, 0.5f, 0.28f,0.22f,0.44f,   0.5f, 0.5f, 0.5f, 0.28f,0.22f,0.44f,   0.5f, 0.5f, 0.5f, 0.28f,0.22f,0.44f,  -0.5f, 0.5f, 0.5f, 0.28f,0.22f,0.44f,  -0.5f,-0.5f, 0.5f, 0.28f,0.22f,0.44f,
		-0.5f,-0.5f,-0.5f, 0.28f,0.22f,0.44f,   0.5f,-0.5f,-0.5f, 0.28f,0.22f,0.44f,   0.5f, 0.5f,-0.5f, 0.28f,0.22f,0.44f,   0.5f, 0.5f,-0.5f, 0.28f,0.22f,0.44f,  -0.5f, 0.5f,-0.5f, 0.28f,0.22f,0.44f,  -0.5f,-0.5f,-0.5f, 0.28f,0.22f,0.44f,
		-0.5f, 0.5f, 0.5f, 0.28f,0.22f,0.44f,  -0.5f, 0.5f,-0.5f, 0.28f,0.22f,0.44f,  -0.5f,-0.5f,-0.5f, 0.28f,0.22f,0.44f,  -0.5f,-0.5f,-0.5f, 0.28f,0.22f,0.44f,  -0.5f,-0.5f, 0.5f, 0.28f,0.22f,0.44f,  -0.5f, 0.5f, 0.5f, 0.28f,0.22f,0.44f,
		 0.5f, 0.5f, 0.5f, 0.28f,0.22f,0.44f,   0.5f, 0.5f,-0.5f, 0.28f,0.22f,0.44f,   0.5f,-0.5f,-0.5f, 0.28f,0.22f,0.44f,   0.5f,-0.5f,-0.5f, 0.28f,0.22f,0.44f,   0.5f,-0.5f, 0.5f, 0.28f,0.22f,0.44f,   0.5f, 0.5f, 0.5f, 0.28f,0.22f,0.44f,
		-0.5f,-0.5f,-0.5f, 0.28f,0.22f,0.44f,   0.5f,-0.5f,-0.5f, 0.28f,0.22f,0.44f,   0.5f,-0.5f, 0.5f, 0.28f,0.22f,0.44f,   0.5f,-0.5f, 0.5f, 0.28f,0.22f,0.44f,  -0.5f,-0.5f, 0.5f, 0.28f,0.22f,0.44f,  -0.5f,-0.5f,-0.5f, 0.28f,0.22f,0.44f,
		-0.5f, 0.5f,-0.5f, 0.28f,0.22f,0.44f,   0.5f, 0.5f,-0.5f, 0.28f,0.22f,0.44f,   0.5f, 0.5f, 0.5f, 0.28f,0.22f,0.44f,   0.5f, 0.5f, 0.5f, 0.28f,0.22f,0.44f,  -0.5f, 0.5f, 0.5f, 0.28f,0.22f,0.44f,  -0.5f, 0.5f,-0.5f, 0.28f,0.22f,0.44f,

		// 7. CUBO GRIS OSCURO (Zapatos) | Vértices 216 a 251
		-0.5f,-0.5f, 0.5f, 0.30f,0.30f,0.30f,   0.5f,-0.5f, 0.5f, 0.30f,0.30f,0.30f,   0.5f, 0.5f, 0.5f, 0.30f,0.30f,0.30f,   0.5f, 0.5f, 0.5f, 0.30f,0.30f,0.30f,  -0.5f, 0.5f, 0.5f, 0.30f,0.30f,0.30f,  -0.5f,-0.5f, 0.5f, 0.30f,0.30f,0.30f,
		-0.5f,-0.5f,-0.5f, 0.30f,0.30f,0.30f,   0.5f,-0.5f,-0.5f, 0.30f,0.30f,0.30f,   0.5f, 0.5f,-0.5f, 0.30f,0.30f,0.30f,   0.5f, 0.5f,-0.5f, 0.30f,0.30f,0.30f,  -0.5f, 0.5f,-0.5f, 0.30f,0.30f,0.30f,  -0.5f,-0.5f,-0.5f, 0.30f,0.30f,0.30f,
		-0.5f, 0.5f, 0.5f, 0.30f,0.30f,0.30f,  -0.5f, 0.5f,-0.5f, 0.30f,0.30f,0.30f,  -0.5f,-0.5f,-0.5f, 0.30f,0.30f,0.30f,  -0.5f,-0.5f,-0.5f, 0.30f,0.30f,0.30f,  -0.5f,-0.5f, 0.5f, 0.30f,0.30f,0.30f,  -0.5f, 0.5f, 0.5f, 0.30f,0.30f,0.30f,
		 0.5f, 0.5f, 0.5f, 0.30f,0.30f,0.30f,   0.5f, 0.5f,-0.5f, 0.30f,0.30f,0.30f,   0.5f,-0.5f,-0.5f, 0.30f,0.30f,0.30f,   0.5f,-0.5f,-0.5f, 0.30f,0.30f,0.30f,   0.5f,-0.5f, 0.5f, 0.30f,0.30f,0.30f,   0.5f, 0.5f, 0.5f, 0.30f,0.30f,0.30f,
		-0.5f,-0.5f,-0.5f, 0.30f,0.30f,0.30f,   0.5f,-0.5f,-0.5f, 0.30f,0.30f,0.30f,   0.5f,-0.5f, 0.5f, 0.30f,0.30f,0.30f,   0.5f,-0.5f, 0.5f, 0.30f,0.30f,0.30f,  -0.5f,-0.5f, 0.5f, 0.30f,0.30f,0.30f,  -0.5f,-0.5f,-0.5f, 0.30f,0.30f,0.30f,
		-0.5f, 0.5f,-0.5f, 0.30f,0.30f,0.30f,   0.5f, 0.5f,-0.5f, 0.30f,0.30f,0.30f,   0.5f, 0.5f, 0.5f, 0.30f,0.30f,0.30f,   0.5f, 0.5f, 0.5f, 0.30f,0.30f,0.30f,  -0.5f, 0.5f, 0.5f, 0.30f,0.30f,0.30f,  -0.5f, 0.5f,-0.5f, 0.30f,0.30f,0.30f,

		// 8. CUBO CYAN (Camisa) | Vértices 252 a 287
		-0.5f,-0.5f, 0.5f, 0.00f,0.69f,0.69f,   0.5f,-0.5f, 0.5f, 0.00f,0.69f,0.69f,   0.5f, 0.5f, 0.5f, 0.00f,0.69f,0.69f,   0.5f, 0.5f, 0.5f, 0.00f,0.69f,0.69f,  -0.5f, 0.5f, 0.5f, 0.00f,0.69f,0.69f,  -0.5f,-0.5f, 0.5f, 0.00f,0.69f,0.69f,
		-0.5f,-0.5f,-0.5f, 0.00f,0.69f,0.69f,   0.5f,-0.5f,-0.5f, 0.00f,0.69f,0.69f,   0.5f, 0.5f,-0.5f, 0.00f,0.69f,0.69f,   0.5f, 0.5f,-0.5f, 0.00f,0.69f,0.69f,  -0.5f, 0.5f,-0.5f, 0.00f,0.69f,0.69f,  -0.5f,-0.5f,-0.5f, 0.00f,0.69f,0.69f,
		-0.5f, 0.5f, 0.5f, 0.00f,0.69f,0.69f,  -0.5f, 0.5f,-0.5f, 0.00f,0.69f,0.69f,  -0.5f,-0.5f,-0.5f, 0.00f,0.69f,0.69f,  -0.5f,-0.5f,-0.5f, 0.00f,0.69f,0.69f,  -0.5f,-0.5f, 0.5f, 0.00f,0.69f,0.69f,  -0.5f, 0.5f, 0.5f, 0.00f,0.69f,0.69f,
		 0.5f, 0.5f, 0.5f, 0.00f,0.69f,0.69f,   0.5f, 0.5f,-0.5f, 0.00f,0.69f,0.69f,   0.5f,-0.5f,-0.5f, 0.00f,0.69f,0.69f,   0.5f,-0.5f,-0.5f, 0.00f,0.69f,0.69f,   0.5f,-0.5f, 0.5f, 0.00f,0.69f,0.69f,   0.5f, 0.5f, 0.5f, 0.00f,0.69f,0.69f,
		-0.5f,-0.5f,-0.5f, 0.00f,0.69f,0.69f,   0.5f,-0.5f,-0.5f, 0.00f,0.69f,0.69f,   0.5f,-0.5f, 0.5f, 0.00f,0.69f,0.69f,   0.5f,-0.5f, 0.5f, 0.00f,0.69f,0.69f,  -0.5f,-0.5f, 0.5f, 0.00f,0.69f,0.69f,  -0.5f,-0.5f,-0.5f, 0.00f,0.69f,0.69f,
		-0.5f, 0.5f,-0.5f, 0.00f,0.69f,0.69f,   0.5f, 0.5f,-0.5f, 0.00f,0.69f,0.69f,   0.5f, 0.5f, 0.5f, 0.00f,0.69f,0.69f,   0.5f, 0.5f, 0.5f, 0.00f,0.69f,0.69f,  -0.5f, 0.5f, 0.5f, 0.00f,0.69f,0.69f,  -0.5f, 0.5f,-0.5f, 0.00f,0.69f,0.69f,

		// 9. CUBO VERDE (Zombie) | Vértices 288 a 323
		-0.5f,-0.5f, 0.5f, 0.26f,0.44f,0.19f,   0.5f,-0.5f, 0.5f, 0.26f,0.44f,0.19f,   0.5f, 0.5f, 0.5f, 0.26f,0.44f,0.19f,   0.5f, 0.5f, 0.5f, 0.26f,0.44f,0.19f,  -0.5f, 0.5f, 0.5f, 0.26f,0.44f,0.19f,  -0.5f,-0.5f, 0.5f, 0.26f,0.44f,0.19f,
		-0.5f,-0.5f,-0.5f, 0.26f,0.44f,0.19f,   0.5f,-0.5f,-0.5f, 0.26f,0.44f,0.19f,   0.5f, 0.5f,-0.5f, 0.26f,0.44f,0.19f,   0.5f, 0.5f,-0.5f, 0.26f,0.44f,0.19f,  -0.5f, 0.5f,-0.5f, 0.26f,0.44f,0.19f,  -0.5f,-0.5f,-0.5f, 0.26f,0.44f,0.19f,
		-0.5f, 0.5f, 0.5f, 0.26f,0.44f,0.19f,  -0.5f, 0.5f,-0.5f, 0.26f,0.44f,0.19f,  -0.5f,-0.5f,-0.5f, 0.26f,0.44f,0.19f,  -0.5f,-0.5f,-0.5f, 0.26f,0.44f,0.19f,  -0.5f,-0.5f, 0.5f, 0.26f,0.44f,0.19f,  -0.5f, 0.5f, 0.5f, 0.26f,0.44f,0.19f,
		 0.5f, 0.5f, 0.5f, 0.26f,0.44f,0.19f,   0.5f, 0.5f,-0.5f, 0.26f,0.44f,0.19f,   0.5f,-0.5f,-0.5f, 0.26f,0.44f,0.19f,   0.5f,-0.5f,-0.5f, 0.26f,0.44f,0.19f,   0.5f,-0.5f, 0.5f, 0.26f,0.44f,0.19f,   0.5f, 0.5f, 0.5f, 0.26f,0.44f,0.19f,
		-0.5f,-0.5f,-0.5f, 0.26f,0.44f,0.19f,   0.5f,-0.5f,-0.5f, 0.26f,0.44f,0.19f,   0.5f,-0.5f, 0.5f, 0.26f,0.44f,0.19f,   0.5f,-0.5f, 0.5f, 0.26f,0.44f,0.19f,  -0.5f,-0.5f, 0.5f, 0.26f,0.44f,0.19f,  -0.5f,-0.5f,-0.5f, 0.26f,0.44f,0.19f,
		-0.5f, 0.5f,-0.5f, 0.26f,0.44f,0.19f,   0.5f, 0.5f,-0.5f, 0.26f,0.44f,0.19f,   0.5f, 0.5f, 0.5f, 0.26f,0.44f,0.19f,   0.5f, 0.5f, 0.5f, 0.26f,0.44f,0.19f,  -0.5f, 0.5f, 0.5f, 0.26f,0.44f,0.19f,  -0.5f, 0.5f,-0.5f, 0.26f,0.44f,0.19f
	};


	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Ahora OpenGL subirá a la memoria todos nuestros 9 cubitos juntos (tamaño completo de vertices)
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Puntero de Posición - Igual que lo tenías
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Puntero de Color - Igual que lo tenías
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);

	while (!glfwWindowShouldClose(window)) {
		Inputs(window);
		glfwPollEvents();

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ourShader.Use();
		glm::mat4 view = glm::mat4(1.0f);
		view = glm::translate(view, glm::vec3(movX, movY, movZ));
		view = glm::rotate(view, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));

		GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
		GLint projecLoc = glGetUniformLocation(ourShader.Program, "projection");

		glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		glBindVertexArray(VAO);
		glm::mat4 model;

		// ==========================================
		// GALLINA
		// ==========================================

		// Cuerpo (Blanco, Vértice Inicial 0)
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.8f, 0.8f, 1.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Ala Izquierda (Blanco)
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.45f, 0.1f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.5f, 0.8f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Ala Derecha (Blanco)
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.45f, 0.1f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.5f, 0.8f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Cabeza (Blanco)
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.7f, 0.6f));
		model = glm::scale(model, glm::vec3(0.4f, 0.5f, 0.4f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Ojos Gallina (Negro, Vértice inicial 36)
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.21f, 0.75f, 0.65f)); // Der
		model = glm::scale(model, glm::vec3(0.05f, 0.1f, 0.1f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 36, 36);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.21f, 0.75f, 0.65f)); // Izq
		model = glm::scale(model, glm::vec3(0.05f, 0.1f, 0.1f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 36, 36);

		// Pico (Naranja, Vértice inicial 72)
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.6f, 0.9f));
		model = glm::scale(model, glm::vec3(0.4f, 0.2f, 0.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 72, 36);

		// Papada (Rojo, Vértice inicial 108)
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.4f, 0.85f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.1f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 108, 36);

		// Patas y pies (Amarillo, Vértice inicial 144)
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.2f, -0.6f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.5f, 0.1f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 144, 36);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.2f, -0.85f, 0.15f));
		model = glm::scale(model, glm::vec3(0.3f, 0.05f, 0.4f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 144, 36);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.2f, -0.6f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.5f, 0.1f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 144, 36);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.2f, -0.85f, 0.15f));
		model = glm::scale(model, glm::vec3(0.3f, 0.05f, 0.4f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 144, 36);


		// ==========================================
		// ZOMBIE BEBÉ
		// ==========================================

		// Piernas (Morado, Vértice inicial 180)
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.25f, 0.55f, -0.2f)); // Pierna Izq
		model = glm::scale(model, glm::vec3(0.18f, 0.18f, 0.4f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 180, 36);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.25f, 0.55f, -0.2f)); // Pierna Der
		model = glm::scale(model, glm::vec3(0.18f, 0.18f, 0.4f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 180, 36);

		// Zapatos (Gris, Vértice inicial 216)
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.25f, 0.45f, 0.05f));
		model = glm::scale(model, glm::vec3(0.19f, 0.19f, 0.1f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 216, 36);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.25f, 0.45f, 0.05f));
		model = glm::scale(model, glm::vec3(0.19f, 0.19f, 0.1f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 216, 36);

		// Torso (Cyan, Vértice inicial 252)
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.85f, -0.2f));
		model = glm::scale(model, glm::vec3(0.4f, 0.5f, 0.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 252, 36);

		// Brazos y Cabeza (Verde, Vértice inicial 288)
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.25f, 0.95f, 0.05f)); // Brazo Izq
		model = glm::scale(model, glm::vec3(0.15f, 0.15f, 0.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 288, 36);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.25f, 0.95f, 0.05f)); // Brazo Der
		model = glm::scale(model, glm::vec3(0.15f, 0.15f, 0.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 288, 36);
		model = glm::mat4(1.0f); // Cabeza
		model = glm::translate(model, glm::vec3(0.0f, 1.4f, -0.2f));
		model = glm::scale(model, glm::vec3(0.6f, 0.6f, 0.6f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 288, 36);

		// Ojos Zombie (Negro, reciclando el cubo en Vértice 36)
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.15f, 1.4f, 0.11f)); // Der
		model = glm::scale(model, glm::vec3(0.15f, 0.08f, 0.05f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 36, 36);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.15f, 1.4f, 0.11f)); // Izq
		model = glm::scale(model, glm::vec3(0.15f, 0.08f, 0.05f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 36, 36);

		glBindVertexArray(0);
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();

	return EXIT_SUCCESS;
}

void Inputs(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		movX += 0.08f;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		movX -= 0.08f;
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		movY += 0.01f;
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		movY -= 0.01f;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		movZ -= 0.08f;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		movZ += 0.08f;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		rot += 0.4f;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		rot -= 0.4f;
}