//GLEW
#define GLEW_STATIC
#include <GL\glew.h>
//GLFW

#include <GLFW\glfw3.h>
#include <iostream>

//Shader

#include <string>
#include <fstream>
#include <sstream>
#include  <iostream>
#include "shader.h"

using namespace std;

const GLint WIDTH = 800, HEIGHT = 600;
bool WIREFRAME = false;
int screenWithd, screenHeight;

void error_callback(int error, const char* description);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);



int main() {

	shader shader("./src/SimpleVertexShader.vertexshader", "./src/SimpleFragmentShader.fragmentshader");

	//initGLFW
	//set GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	GLFWwindow* window;
	glfwSetErrorCallback(error_callback);

	//comprobar que GLFW esta activo
	if (!glfwInit())
		std::exit(EXIT_FAILURE);

	//crear la ventana
	window = glfwCreateWindow(WIDTH, HEIGHT, "Primera ventana", nullptr, nullptr);
	if (!window) {
		cout << "Error al crear la ventana" << endl;
		glfwTerminate();
		std::exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	if (GLEW_OK != glewInit()) {
		std::cout << "Error al inicializar glew" << std::endl;
		glfwTerminate();
		return NULL;
	}

	glfwGetFramebufferSize(window, &screenWithd, &screenHeight); //??????//


																 //que funcion se llama cuando se detecta una pulsaci�n de tecla en la ventana x
	glfwSetKeyCallback(window, key_callback);


	//cargamos los shader

	// Definir el buffer de vertices (shader modificado)

	GLfloat VertexBufferObject[] = {

		0.5f,  0.5f, 0.0f,  // Top Right
		0.5f, -0.5f, 0.0f,  // Bottom Right
		-0.5f, -0.5f, 0.0f,  // Bottom Left
		-0.5f,  0.5f, 0.0f   // Top Left 

	};

	// Definir el EBO
	GLuint IndexBufferObject[]{

		3,0,2,
		0,1,2 };

	// 
	glfwGetTime();

	// Crear los VBO, VAO y EBO

	GLuint VBO;
	GLuint EBO;

	GLuint VAO;
	//reservar memoria para el VAO, VBO y EBO

	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenBuffers(1, &VAO);

	//Declarar el VBO y el EBO

	//Enlazar el buffer con openGL
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	//Alocamos memoria suficiente para almacenar 4 grupos de 3 floats (segundo parámetro)
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * 4, VertexBufferObject, GL_STATIC_DRAW);
	//Alocamos ahora el EBO()
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * 6, IndexBufferObject, GL_STATIC_DRAW);
	//Establecer las propiedades de los vertices
	glEnableVertexAttribArray(0); //??????//
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (GLvoid*)0);

	//liberar el buffer	
	//liberar el buffer de vertices
	glBindVertexArray(0);

	//Bucle de dibujado (VENTANA)

	while (!glfwWindowShouldClose(window)) {

		glViewport(0, 0, screenWithd, screenHeight);
		glClear(GL_COLOR_BUFFER_BIT);

		glClearColor(0.6f, 0.6f, 1.0f, 1.f);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-10, 10, -10.f, 10.f, -1.0f, 10.f);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		//Establecer el shader

		shader.Use();

		//Shader::USE(programID);

		//glUseProgram(programID);
		if (WIREFRAME == true) {

			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		//pintar el VAO
		glBindVertexArray(VAO);
		// bind index buffer if you want to render indexed data
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		// indexed draw call
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);


		// Swap the screen buffers
		glfwSwapBuffers(window); //?????//
								 //Event poll
		glfwPollEvents();
	}

	// liberar la memoria de los VAO, EBO y VBO
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// Terminate GLFW, clearing any resources allocated by GLFW.

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwDestroyWindow(window);
	glfwTerminate();
	std::exit(EXIT_SUCCESS);
}


void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	//Cuando pulsamos la tecla ESC se cierra la aplicacion
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	//Cuando apretamos la tecla W se cambia a modo Wireframe
	if (key == GLFW_KEY_W && action == GLFW_PRESS)
		WIREFRAME = !WIREFRAME;
}